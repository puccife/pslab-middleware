from threading import Thread
from bluetooth import *

class ConnectionThread(Thread):

    def __init__(self, eventbus, outbound_channel, connection_manager, request):
        Thread.__init__(self)
        self.eventbus = eventbus
        self.outbound_channel = outbound_channel
        self.connection_manager = connection_manager
        self.request = request
        self.message_id = self.request['id']

    def run(self):
        print 'Starting connection thread'
        self.connect()
        print 'Exiting connection thread'

    def connect(self):
        invalid_request = True
        message = {}
        if 'payload' in self.request:
            payload = self.request['payload']
            if 'resourceId' in payload:
                resource_id = payload['resourceId']
                try:
                    if self.connection_manager.connect_resource(resource_id):
                        message = {'message': 'Connected to ' + resource_id}
                    else:
                        message = {'error': 'Could not connect ' + resource_id}
                except BluetoothError as e:
                    message = {'error': resource_id + ': ' + e.strerror}
                invalid_request = False
        if invalid_request:
            message = {'error': 'Invalid connection request'}
        self.eventbus.send(self.outbound_channel, {
            'message': message,
            'id': self.message_id
        })
