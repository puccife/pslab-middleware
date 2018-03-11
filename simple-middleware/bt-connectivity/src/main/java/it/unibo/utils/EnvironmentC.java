package it.unibo.utils;

/**
 * Class used to store the Environment Const
 *
 * @author Pucci Federico
 */
public final class EnvironmentC {

    /**
     * Channel name used for the communication between Rest and EventBus servers
     */
    public final static String API_CHANNEL = "restapi";
    /**
     * Channel used for the incoming communication between Java and Python through bridge.
     */
    public final static String PY_TO_JA = "py2ja";
    /**
     * Channel used for the outgoing communication between Java and Python through bridge.
     */
    public final static String JA_TO_PY = "ja2py";
}
