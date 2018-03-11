package it.unibo.restapi;

import io.netty.handler.codec.http.HttpResponseStatus;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.AsyncResult;
import io.vertx.core.Handler;
import io.vertx.core.eventbus.EventBus;
import io.vertx.core.eventbus.Message;
import io.vertx.core.http.HttpMethod;
import io.vertx.core.http.HttpServerRequest;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.core.logging.Logger;
import io.vertx.core.logging.LoggerFactory;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import it.unibo.exception.HttpRequestException;
import it.unibo.utils.EnvironmentC;

import java.util.Map;
import java.util.function.BiConsumer;
import java.util.function.Function;

import static io.netty.handler.codec.http.HttpResponseStatus.INTERNAL_SERVER_ERROR;
import static io.vertx.core.http.HttpMethod.*;
import static it.unibo.restapi.C.*;
import static it.unibo.restapi.Utils.paramsAsJson;
import static it.unibo.restapi.Utils.queryParams;

public class RESTfulServer extends AbstractVerticle {

    private static final Logger LOGGER = LoggerFactory.getLogger(RESTfulServer.class);

    private EventBus eventBus;

    @Override
    public void start() throws Exception {
        eventBus = vertx.eventBus();
        final Router restApiRouter = Router.router(vertx);

        restApiRouter.route()
                .handler(BodyHandler.create());

        final Handler<RoutingContext> requestHandler = requestHandler(this::requestMapper);

        restApiRouter.route(paths.inquiry)
                .method(GET)
                .produces("application/json")
                .handler(requestHandler);

        restApiRouter.route(paths.resources)
                .method(GET)
                .method(POST)
                .produces("application/json")
                .handler(requestHandler);

        restApiRouter.route(paths.resource)
                .method(GET)
                .method(PUT)
                .method(PATCH)
                .method(DELETE)
                .produces("application/json")
                .handler(requestHandler);

        restApiRouter.route()
                .produces("application/json")
                .failureHandler(this::failureHandler);

        final Router mainRouter = Router.router(vertx);
        mainRouter.mountSubRouter(paths.api, restApiRouter);

        vertx.createHttpServer().requestHandler(mainRouter::accept).listen(8080, ar -> {
            if (ar.succeeded()) {
                LOGGER.info("Server started, listening on port{0, number, #}", ar.result().actualPort());
            } else {
                LOGGER.error("Could not start the server: {0}", ar.cause().getMessage());
            }
        });
    }

    private JsonObject requestMapper(final RoutingContext ctx) {
        final HttpServerRequest request = ctx.request();
        LOGGER.info("Received request: {0} {1}", request.method(), request.path());
        final JsonObject requestObject = new JsonObject();

        setAction(ctx, requestObject);
        setResourceId(ctx, requestObject);
        setQuery(ctx, requestObject);
        setPayload(ctx, requestObject);

        LOGGER.info("Request object:\n{0}", requestObject.encodePrettily());
        LOGGER.info("");
        return requestObject;
    }

    private void setResourceId(RoutingContext ctx, JsonObject requestObject) {
        final Map<String, String> pathParams = ctx.pathParams();
        if (pathParams.containsKey(path_params.resource_id)) {
            requestObject.put(labels.resource_id, pathParams.get(path_params.resource_id));
        }
    }

    private void setAction(RoutingContext ctx, JsonObject requestObject) {
        String action = null;
        final String path = ctx.request().path();
        if (path.startsWith(paths.api + paths.inquiry)) {
            action = actions.inquiry;
        } else {
            final HttpMethod method = ctx.request().method();
            if (method == GET) {
                action = actions.read;
            } else if (method == PUT || method == PATCH) {
                action = actions.write;
            } else if (method == POST) {
                setPayload(ctx, requestObject);
                action = actions.connect;
            } else if (method == DELETE) {
                action = actions.disconnect;
            }
        }
        if (action != null && !action.isEmpty()) {
            requestObject.put(labels.action, action);
        }
    }

    private void setQuery(RoutingContext ctx, JsonObject requestObject) {
        final Map<String, String> pathParams = ctx.pathParams();
        final HttpServerRequest request = ctx.request();
        final JsonObject queryObject = paramsAsJson(queryParams(request.params(), pathParams));
        if (!queryObject.isEmpty()) {
            requestObject.put(C.labels.query, queryObject);
        }
    }

    private void setPayload(RoutingContext ctx, JsonObject requestObject) {

        final Map<String, String> pathParams = ctx.pathParams();
        final HttpServerRequest request = ctx.request();
        final HttpMethod method = request.method();
        if (method == PUT || method == PATCH || method == POST) {
            final JsonObject payloadObject = ctx.getBodyAsJson();
            if (!payloadObject.isEmpty()) {
                requestObject.put(labels.payload, payloadObject);
            }
        }
    }

    private Handler<RoutingContext> requestHandler(
            final Function<? super RoutingContext, ? extends JsonObject> requestMapper) {
        return requestHandler(requestMapper, (ar, ctx) -> {
            final HttpServerResponse response = ctx.response();
            if (ar.succeeded()) {
                JsonObject body = (JsonObject) ar.result().body();
                LOGGER.info("Received reply from event bus: {}", body.encodePrettily());
                response.end(body.encode());
            } else {
                final Throwable cause = ar.cause();
                ctx.fail(new HttpRequestException(cause.getMessage(), cause));
            }
        });
    }

    private Handler<RoutingContext> requestHandler(
            final Function<? super RoutingContext, ? extends JsonObject> requestMapper,
            final BiConsumer<AsyncResult<Message<Object>>, RoutingContext> replyHandler) {
        return ctx -> {
            // Send the request to the event bus and wait for the response,
            // then send the request back to the user.
            eventBus.send(EnvironmentC.API_CHANNEL, requestMapper.apply(ctx), ar -> replyHandler.accept(ar, ctx));
        };
    }

    private void failureHandler(RoutingContext ctx) {
        final JsonObject errorObject = new JsonObject()
                .put(labels.timestamp, System.nanoTime())
                .put(labels.path, ctx.request().path());

        final Throwable throwable = ctx.failure();
        HttpResponseStatus responseStatus = null;
        if (throwable != null) {
            final String message = throwable.getMessage();
            if (message != null && !message.isEmpty()) {
                errorObject.put(labels.message, message);
            }
            if (throwable instanceof HttpRequestException) {
                responseStatus = ((HttpRequestException) throwable).getResponseStatus();
            }
        }
        if (responseStatus == null) {
            final int statusCode = ctx.statusCode();
            responseStatus = (statusCode == -1)
                    ? INTERNAL_SERVER_ERROR
                    : HttpResponseStatus.valueOf(statusCode);
        }

        final int statusCode = responseStatus.code();
        errorObject.put(labels.status, new JsonObject()
                .put(labels.code, statusCode)
                .put(labels.reason_phrase, responseStatus.reasonPhrase()));

        ctx.response()
                .setStatusCode(statusCode)
                .end(errorObject.encodePrettily());
    }

    static {
        LoggerFactory.initialise();
    }

}
