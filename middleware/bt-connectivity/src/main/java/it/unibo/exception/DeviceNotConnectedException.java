package it.unibo.exception;

import io.vertx.core.VertxException;

public class DeviceNotConnectedException extends VertxException {

    private static final long serialVersionUID = 377707123167664061L;

    public DeviceNotConnectedException(String message) {
        super(message);
    }

    public DeviceNotConnectedException(String message, Throwable cause) {
        super(message, cause);
    }

    public DeviceNotConnectedException(Throwable cause) {
        super(cause);
    }

}
