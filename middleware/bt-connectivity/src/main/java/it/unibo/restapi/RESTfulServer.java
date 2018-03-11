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
import static it.unibo.restapi.Utils.paramsAsJson;
import static it.unibo.restapi.Utils.queryParams;

public class RESTfulServer extends AbstractVerticle {

    private static final Logger LOGGER = LoggerFactory.getLogger(RESTfulServer.class);

    private EventBus eventBus;

    @Override
    public void start() throws Exception {
        eventBus = vertx.eventBus();
        final Router restApiRouter = Router.router(vertx);

        final Handler<RoutingContext> requestHandler = requestHandler(this::requestMapper);

        restApiRouter.route()
		.handler(BodyHandler.create());

        restApiRouter.route(C.paths.inquiry)
                .method(GET)
                .produces("application/json")
                .handler(requestHandler);

        restApiRouter.route(C.paths.devices)
                .method(GET)
                .method(POST)
                .produces("application/json")
                .handler(requestHandler);

        restApiRouter.route(C.paths.device)
                .method(DELETE)
                .produces("application/json")
                .handler(requestHandler);

        restApiRouter.route(C.paths.device_resources)
                .method(GET)
                .produces("application/json").handler(requestHandler);

        restApiRouter.route(C.paths.resources)
                .method(GET)
                .produces("application/json")
                .handler(requestHandler);

        restApiRouter.route(C.paths.resources)
                .method(PUT)
                .method(PATCH)
                .produces("application/json")
                .handler(requestHandler);

        restApiRouter.route(C.paths.resource)
                .method(GET)
                .produces("application/json")
                .handler(requestHandler);

        restApiRouter.route(C.paths.resource)
                .method(PUT)
                .method(PATCH)
                .produces("application/json")
                .handler(requestHandler);

        restApiRouter.route()
                .produces("application/json")
                .failureHandler(this::failureHandler);

        final Router mainRouter = Router.router(vertx);
        mainRouter.mountSubRouter(C.paths.api, restApiRouter);

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
        final HttpMethod method = request.method();
        LOGGER.info("Received request: {0} {1}", method, request.path());
        final JsonObject requestObject = new JsonObject();

        final String path = request.path();

        String action = null;
        if (path.startsWith(C.paths.api + C.paths.inquiry)) {
            action = C.actions.inquiry;
        } else {
            final Map<String, String> pathParams = ctx.pathParams();

            if (pathParams.containsKey(C.path_params.device_name)) {
                requestObject.put(C.labels.device, pathParams.get("deviceName"));
            }

            final JsonObject resourceObject = new JsonObject();
            if (pathParams.containsKey(C.path_params.resource_category)) {
                resourceObject.put(C.labels.category, pathParams.get(C.path_params.resource_category));
            }
            if (pathParams.containsKey(C.path_params.resource_id)) {
                final String resourceId = pathParams.get(C.path_params.resource_id);
                resourceObject.put(C.labels.id, resourceId);
            }
            if (!resourceObject.isEmpty()) {
                requestObject.put(C.labels.resource, resourceObject);
            }

            if (method == GET) {
                action = C.actions.read;
                final JsonObject queryObject = paramsAsJson(queryParams(request.params(), pathParams));
                if (!queryObject.isEmpty()) {
                    requestObject.put(C.labels.query, queryObject);
                }
            } else if (method == PUT || method == PATCH) {
                action = C.actions.write;
                final JsonObject payloadObject = ctx.getBodyAsJson();
                if (!payloadObject.isEmpty()) {
                    requestObject.put(C.labels.payload, payloadObject);
                }
            } else if (method == POST) {
                requestObject.put(C.labels.action, C.actions.connect);
                final JsonObject payloadObject = ctx.getBodyAsJson();
                if (!payloadObject.isEmpty()) {
                    requestObject.put(C.labels.payload, payloadObject);
                }
            } else if (method == DELETE) {
                requestObject.put(C.labels.action, C.actions.disconnect);
                if (pathParams.containsKey(C.path_params.device_name)) {
                    requestObject.put(C.labels.device, pathParams.get("deviceName"));
                }
            }
        }

        if (action != null && !action.isEmpty()) {
            requestObject.put(C.labels.action, action);
        }

        LOGGER.info("Request object:\n{0}", requestObject.encodePrettily());
        LOGGER.info("");
        return requestObject;
    }

    private Handler<RoutingContext> requestHandler(
            final Function<? super RoutingContext, ? extends JsonObject> requestMapper) {
        return requestHandler(requestMapper, (ar, ctx) -> {
            final HttpServerResponse response = ctx.response();
            if (ar.succeeded()) {
                response.end(((JsonObject) ar.result().body()).encodePrettily());
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
            eventBus.send(EnvironmentC.API_CHANNEL, requestMapper.apply(ctx), ar -> {
                replyHandler.accept(ar, ctx);
            });
        };
    }

    private void failureHandler(RoutingContext ctx) {
        final JsonObject errorObject = new JsonObject()
                .put(C.labels.timestamp, System.nanoTime())
                .put(C.labels.path, ctx.request().path());

        final Throwable throwable = ctx.failure();
        HttpResponseStatus responseStatus = null;
        if (throwable != null) {
            final String message = throwable.getMessage();
            if (message != null && !message.isEmpty()) {
                errorObject.put(C.labels.message, message);
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
        errorObject.put(C.labels.status, new JsonObject()
                .put(C.labels.code, statusCode)
                .put(C.labels.reason_phrase, responseStatus.reasonPhrase()));

        ctx.response()
                .setStatusCode(statusCode)
                .end(errorObject.encodePrettily());
    }

    static {
        LoggerFactory.initialise();
    }

}

