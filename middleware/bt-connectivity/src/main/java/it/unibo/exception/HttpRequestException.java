package it.unibo.exception;

import static io.netty.handler.codec.http.HttpResponseStatus.INTERNAL_SERVER_ERROR;
import static java.util.Objects.requireNonNull;

import io.netty.handler.codec.http.HttpResponseStatus;
import io.vertx.core.VertxException;

public class HttpRequestException extends VertxException {

    private static final long serialVersionUID = -237630245063898856L;

    private final HttpResponseStatus responseStatus;

    public HttpRequestException(HttpResponseStatus responseStatus, String message) {
        super(message);
        this.responseStatus = requireNonNull(responseStatus, "responseStatus is null");
    }

    public HttpRequestException(HttpResponseStatus responseStatus, String message, Throwable cause) {
        super(message, cause);
        this.responseStatus = requireNonNull(responseStatus, "responseStatus is null");
    }

    public HttpRequestException(HttpResponseStatus responseStatus, Throwable cause) {
        super(cause);
        this.responseStatus = requireNonNull(responseStatus, "responseStatus is null");
    }

    public HttpRequestException(String message) {
        this(INTERNAL_SERVER_ERROR, message);
    }

    public HttpRequestException(String message, Throwable cause) {
        this(INTERNAL_SERVER_ERROR, message, cause);
    }

    public HttpRequestException(Throwable cause) {
        this(INTERNAL_SERVER_ERROR, cause);
    }

    public HttpResponseStatus getResponseStatus() {
        return responseStatus;
    }

}
