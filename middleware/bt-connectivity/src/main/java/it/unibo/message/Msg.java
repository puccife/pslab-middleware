package it.unibo.message;

import io.vertx.core.json.JsonObject;

public class Msg{
	
	private final JsonObject jsonObject;
	
	public Msg(JsonObject jsonObject) {
		this.jsonObject = jsonObject;
	}
	
	public synchronized JsonObject getJsonObject() {
		return this.jsonObject;
	}
	
}
