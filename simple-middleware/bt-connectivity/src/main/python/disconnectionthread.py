from threading import Thread
from bluetooth import BluetoothError

class DisconnectionThread(Thread):

    def __init__(self, eventbus, outbound_channel, connection_manager, request):
        Thread.__init__(self)
        self.eventbus = eventbus
        self.outbound_channel = outbound_channel
        self.connection_manager = connection_manager
        self.request = request
        self.message_id = self.request['id']

    def run(self):
        print 'Starting disconnection thread'
        self.disconnect()
        print 'Exiting disconnection thread'

    def disconnect(self):
        invalid_request = True
        message = {}
        if 'resourceId' in self.request:
            resource_id = self.request['resourceId']
            try:
                if self.connection_manager.disconnect_resource(resource_id):
                    message = {'message': 'Disconnected ' + resource_id}
                else:
                    message = {'error': 'Could not disconnect ' + resource_id}
            except BluetoothError as ex:
                message = {'error': resource_id + ': ' + ex.strerror}
            invalid_request = False
        if invalid_request:
            message = {'error': 'Invalid disconnection request'}
        self.eventbus.send(self.outbound_channel, {
            'message': message,
            'id': self.message_id
        })
