package it.unibo.message;

import io.vertx.core.json.JsonObject;
import it.unibo.device.BluetoothDevice;

import java.util.*;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Class used to manage messages and synchronize the communication between REST
 * Server and Python subsystem.
 *
 * @author Pucci Federico
 */
public class MsgDispatcher {

    private static final MsgDispatcher SINGLETON = new MsgDispatcher();

    /*
     * Progressive long used to assign an id to an incoming message.
     */
    private static final AtomicLong PROGRESSIVE_NUMBER = new AtomicLong(0);

    /*
     * Queue used to store pending messages received from REST calls.
     */
    private Queue<Msg> pendingMessages;

    /*
     * List used to store messages sent through bridge and waiting for ack
     * response. Storing Msg instead of just long IDs in order to have the
     * possibility to re-send lost messages after a significant timeOut.
     */
    private List<Msg> waitingMessages;

    /*
     * List used to store response messages from devices.
     */
    private List<Msg> ackMessages;

    private MsgDispatcher() {
        pendingMessages = new LinkedBlockingQueue<>();
        waitingMessages = new LinkedList<>();
        ackMessages = new LinkedList<>();
    }

    /**
     * SINGLETON to get MsgDispatcher instance.
     *
     * @return MsgDispatcher instance
     */
    public static MsgDispatcher getInstance() {
        return SINGLETON;
    }

    /**
     * Method that returns a JsonObject used for the inquiry request.
     *
     * @return JsonObject {'action':'inquiry'}
     */
    public JsonObject inquiryMsg() {
        return new JsonObject().put("action", "inquiry");
    }

    /**
     * Method used to create a JsonObject for the connection with a specific
     * Bluetooth Device
     *
     * @param bluetoothDevice
     * @return JsonObject {'action':'connect','device':'bluetoothdevice.name'}
     */
    public JsonObject connectDevice(BluetoothDevice bluetoothDevice) {
        return new JsonObject().put("action", "connect").put("device", bluetoothDevice.getName());
    }

    /**
     * Method used to create a JsonObject for the disconnection with a specific
     * Bluetooth Device
     *
     * @param bluetoothDevice
     * @return JsonObject
     * {'action':'disconnect','device':'bluetoothdevice.name'}
     */
    public JsonObject disconnectDevice(BluetoothDevice bluetoothDevice) {
        return new JsonObject().put("action", "disconnect").put("device", bluetoothDevice.getName());
    }

    /**
     * Use this method to store a message received from a REST call. It assigns
     * a specific ID to the Msg and store it in a Queue.
     *
     * @param msg
     * @return the id of the stored message.
     */
    public long addPendingMessage(Msg msg) {
        long id = this.getId();
        msg.getJsonObject().put("id", id);
        pendingMessages.add(msg);
        return id;
    }

    /*
     * Method used to add a Msg to the waiting messages list.
     */
    private boolean addWaitingMessage(Msg msg) {
        return waitingMessages.add(msg);
    }

    /**
     * Use this method to store a response message received from Python
     * subsystem.
     *
     * @param msg
     * @return true if the message is successfully added.
     */
    public boolean addAckMessage(Msg msg) {
        return ackMessages.add(msg);
    }

    /**
     * Use this message before sending a Msg to the Python subsystem. This
     * method removes the message on head of the pending messages queue and add
     * it to the list of messages waiting for ack.
     *
     * @return the Msg removed.
     */
    public Msg poll() {
        Msg pendingMsg;
        synchronized (this) {
            pendingMsg = pendingMessages.poll();
            if (pendingMsg != null)
                addWaitingMessage(pendingMsg);
        }
        return pendingMsg;
    }

    /*
     * Method used to assign an id to every message.
     */
    private long getId() {
        return PROGRESSIVE_NUMBER.incrementAndGet();
    }

    /**
     * Method used to check if there are other messages in the pending messages
     * queue.
     *
     * @return true if there are other messages.
     */
    public boolean hasMsg() {
        return this.pendingMessages.size() > 0;
    }

    /**
     * Method used to remove a message stored in waiting queue and attending ack
     * from Python subsystem. It's important to check first the availability of
     * the message in ack lists, with 'containsMsg' method.
     *
     * @param id of the message
     * @return the message received from Python subsystem.
     */
    public JsonObject removeWaitingMessage(long id) {
        Iterator<Msg> it;
        synchronized (this) {
            it = this.waitingMessages.iterator();
            while (it.hasNext()) {
                JsonObject msg = it.next().getJsonObject();
                if (msg.getLong("id").equals(id)) {
                    it.remove();
                }
            }
            it = this.ackMessages.iterator();
            while (it.hasNext()) {
                JsonObject msg = it.next().getJsonObject();
                if (msg.getLong("id").equals(id)) {
                    it.remove();
                    return msg;
                }
            }
        }
        return null;
    }

    /**
     * Method used to check if we received a response message from Python
     * subsystem given a request message id.
     *
     * @param id
     * @return true if ackMessages list contains the respective answer for
     * request with ID param.
     */
    public boolean containsMsg(long id) {
        return new ArrayList<>(this.ackMessages).stream()
                .anyMatch(msg -> msg.getJsonObject().getLong("id").equals(id));
    }

    public boolean checkTimeout(long startTime) {
        if (System.currentTimeMillis() - startTime >= 20000) {
            return true;
        } else {
            return false;
        }
    }

    public JsonObject getTimedOutMsg(long id) {
        Iterator<Msg> it = this.waitingMessages.iterator();
        while (it.hasNext()) {
            JsonObject msg = it.next().getJsonObject();
            if (msg.getLong("id").equals(id)) {
                return msg;
            }
        }
        return null;
    }
}

