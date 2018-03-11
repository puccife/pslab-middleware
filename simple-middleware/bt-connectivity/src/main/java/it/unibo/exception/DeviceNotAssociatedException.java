package it.unibo.exception;

import io.vertx.core.VertxException;

public class DeviceNotAssociatedException extends VertxException {

    private static final long serialVersionUID = 4451293219624636649L;

    public DeviceNotAssociatedException(String message) {
        super(message);
    }

    public DeviceNotAssociatedException(String message, Throwable cause) {
        super(message, cause);
    }

    public DeviceNotAssociatedException(Throwable cause) {
        super(cause);
    }

}
