package it.unibo.server;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Future;
import io.vertx.core.eventbus.EventBus;
import io.vertx.core.eventbus.MessageConsumer;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.bridge.BridgeOptions;
import io.vertx.ext.bridge.PermittedOptions;
import io.vertx.ext.eventbus.bridge.tcp.TcpEventBusBridge;
import it.unibo.exception.TimeoutExceededException;
import it.unibo.message.Msg;
import it.unibo.message.MsgDispatcher;
import it.unibo.utils.EnvironmentC;

import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

/**
 * EventBus Server (with Vertx) used to communicate with: - the EventBus server
 * used to receive REST calls - the Python server used to communicate with
 * Arduino devices, through a TCP Bridge
 *
 * @author Pucci Federico
 */
@SuppressWarnings("unused")
public class EventBusServer extends AbstractVerticle {

    private Executor executor;

    public void start(Future<Void> fut) {
        executor = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
        TcpEventBusBridge bridge = TcpEventBusBridge.create(vertx,
                new BridgeOptions().addInboundPermitted(new PermittedOptions().setAddress(EnvironmentC.PY_TO_JA))
                        .addOutboundPermitted(new PermittedOptions().setAddress(EnvironmentC.JA_TO_PY)));
        bridge.listen(7000, res -> {
            if (res.succeeded()) {
                System.out.println("Started");
            } else {
                System.out.println("failed");
            }
        });
        EventBus eb = vertx.eventBus();

        MessageConsumer<JsonObject> restConsumer = eb.consumer(EnvironmentC.API_CHANNEL, message -> {
            long id = MsgDispatcher.getInstance().addPendingMessage(new Msg(message.body()));
            System.out.println("restConsumer - content" + message.body());
            executor.execute(() -> {
                long startTime = System.currentTimeMillis();
                boolean timedOut = false;
                while (!MsgDispatcher.getInstance().containsMsg(id)) {
                    if (MsgDispatcher.getInstance().checkTimeout(startTime)) {
                        if (timedOut) throw new TimeoutExceededException("Timeout Exceed Exception: " + message.body());
                        //eb.publish(EnvironmentC.JA_TO_PY, MsgDispatcher.getInstance().getTimedOutMsg(id));
                        startTime = System.currentTimeMillis();
                        timedOut = true;
                    }
                }
                message.reply(MsgDispatcher.getInstance().removeWaitingMessage(id).getJsonObject("message"));
            });
        });

        MessageConsumer<JsonObject> pythonConsumer = eb.consumer(EnvironmentC.PY_TO_JA, message -> {
            JsonObject response = message.body();
            System.out.println(response);
            MsgDispatcher.getInstance().addAckMessage(new Msg(response));
        });

        executor.execute(() -> {
            while (true) {
                while (MsgDispatcher.getInstance().hasMsg()) {
                    eb.publish(EnvironmentC.JA_TO_PY, MsgDispatcher.getInstance().poll().getJsonObject());
                }
            }
        });
    }

    @Override
    public void stop() throws Exception {
        super.stop();
    }
}
