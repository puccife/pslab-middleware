package it.unibo.restapi;

final class C {
    
    final static class path_params {
        
        static final String device_name = "deviceName";
        
        static final String resource_category = "resourceCategory";
        
        static final String resource_id = "resourceId";
        
    }

    final static class paths {
        
        // GET
        static final String api = "/api";

        // GET
        static final String inquiry = "/inquiry";

        // GET POST
        static final String devices = "/devices";

        // DELETE
        static final String device = "/devices/:deviceName";

        // GET
        static final String device_resources = "/devices/:deviceName/resources";

        // GET PUT PATCH
        static final String resources = "/devices/:deviceName/resources/:resourceCategory";

        // GET PUT PATCH
        static final String resource = "/devices/:deviceName/resources/:resourceCategory/:resourceId";
        
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
        
        static final String device = "device";
        
        static final String resource = "resource";
        
        static final String category = "category";
        
        static final String id = "id";
        
        static final String query = "query";
        
        static final String payload = "payload";
        
        static final String timestamp = "timestamp";
        
        static final String path = "path";
        
        static final String message = "message";
        
        static final String status = "status";
        
        static final String code = "code";
        
        static final String reason_phrase = "reasonPhrase";
        
    }

    private C() {
    }

}
