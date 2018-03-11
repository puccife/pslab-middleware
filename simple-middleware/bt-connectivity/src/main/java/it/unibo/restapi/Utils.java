package it.unibo.restapi;

import io.vertx.core.MultiMap;
import io.vertx.core.json.JsonObject;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

final class Utils {

    static JsonObject paramsAsJson(Map<String, String> params) {
        return params
                .entrySet()
                .stream()
                .collect(JsonObject::new, (json, e) -> json.put(e.getKey(), e.getValue()), JsonObject::mergeIn);
    }

    static Map<String, String> queryParams(MultiMap params, Map<String, String> pathParams) {
        Map<String, String> queryParams = new HashMap<>();
        for (Entry<String, String> entry : params) {
            if (!pathParams.containsKey(entry.getKey()) && !queryParams.containsKey(entry.getKey())) {
                queryParams.put(entry.getKey(), entry.getValue());
            }
        }
        return queryParams;
    }

    private Utils() {
    }

}
