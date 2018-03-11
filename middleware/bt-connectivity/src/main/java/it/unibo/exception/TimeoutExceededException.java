package it.unibo.exception;

import io.vertx.core.VertxException;

public class TimeoutExceededException extends VertxException {

    /**
	 * 
	 */
	private static final long serialVersionUID = -3692574467137444322L;

	public TimeoutExceededException(String message) {
        super(message);
    }

    public TimeoutExceededException(String message, Throwable cause) {
        super(message, cause);
    }

    public TimeoutExceededException(Throwable cause) {
        super(cause);
    }

}
