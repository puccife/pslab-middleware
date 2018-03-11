package it.unibo.message;

import io.vertx.core.json.JsonObject;
import it.unibo.device.BluetoothDevice;

public class JSonMsgParser {

    public static JsonObject connectDeviceTo(BluetoothDevice bluetoothDevice) {
        JsonObject jsonObject = new JsonObject();
        jsonObject.put("connection", "create");
        jsonObject.put("device", bluetoothDevice.getName());
        return jsonObject;
    }

    public static JsonObject disconnectDeviceTo(BluetoothDevice bluetoothDevice) {
        JsonObject jsonObject = new JsonObject();
        jsonObject.put("connection", "remove");
        jsonObject.put("device", bluetoothDevice.getName());
        return jsonObject;
    }

    public static JsonObject inquiry() {
        JsonObject jsonObject = new JsonObject();
        jsonObject.put("request", "inquiry");
        return jsonObject;
    }
}
