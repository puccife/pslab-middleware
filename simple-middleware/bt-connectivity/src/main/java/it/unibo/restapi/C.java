package it.unibo.restapi;

final class C {

    final static class path_params {

        static final String resource_id = "resourceId";

    }

    final static class paths {

        // Prefix
        static final String api = "/api";

        // GET
        static final String inquiry = "/inquiry";

        // GET POST
        static final String resources = "/resources";

        // GET PUT PATCH DELETE
        static final String resource = resources + "/:" + path_params.resource_id;

    }

    final static class actions {

        static final String inquiry = "INQUIRY";

        static final String read = "READ";

        static final String write = "WRITE";

        static final String connect = "CONNECT";

        static final String disconnect = "DISCONNECT";

    }

    final static class labels {

        static final String action = "action";

        static final String resource_id = "resourceId";

        static final String payload = "payload";

        static final String timestamp = "timestamp";

        static final String path = "path";

        static final String message = "message";

        static final String status = "status";

        static final String code = "code";

        static final String reason_phrase = "reasonPhrase";

        public final static String query = "query";
    }

    private C() {
    }

}
