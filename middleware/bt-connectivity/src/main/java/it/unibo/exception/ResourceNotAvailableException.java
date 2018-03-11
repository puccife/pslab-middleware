package it.unibo.exception;

import io.vertx.core.VertxException;

public class ResourceNotAvailableException extends VertxException {

    private static final long serialVersionUID = -6308255850563661533L;

    public ResourceNotAvailableException(String message) {
        super(message);
    }

    public ResourceNotAvailableException(String message, Throwable cause) {
        super(message, cause);
    }

    public ResourceNotAvailableException(Throwable cause) {
        super(cause);
    }

}
