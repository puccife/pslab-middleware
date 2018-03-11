package it.unibo.exception;

import io.vertx.core.VertxException;

public class DeviceNotFoundException extends VertxException {

    private static final long serialVersionUID = 998487958949034125L;

    public DeviceNotFoundException(String message) {
        super(message);
    }

    public DeviceNotFoundException(String message, Throwable cause) {
        super(message, cause);
    }

    public DeviceNotFoundException(Throwable cause) {
        super(cause);
    }

}
