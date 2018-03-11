import json

from bluetooth import *
from threading import Thread
from btutils import send, recv

class CommunicationThread(Thread):

    def __init__(self, eventbus, outbound_channel, address, request):
        Thread.__init__(self)
        self.eventbus = eventbus
        self.outbound_channel = outbound_channel
        self.address = address
        self.request = request
        self.message_id = self.request['id']
        self.resource_id = self.request['resourceId']

    def run(self):
        print 'Starting communication thread'
        self.communicate()
        print 'Exiting communication thread'

    def communicate(self):
        socket = BluetoothSocket(RFCOMM)
        try:
            socket.connect((self.address, 1))
        except BluetoothError as e:
            message = {'error': resource_id + ': ' + e.strerror}
        else:
            print 'Trying to communicate with ' + self.resource_id
            request = json.dumps(self.request)
            print 'Sending ' + request + ' to ' + self.resource_id + '...'
            send(socket, request)
            # time.sleep(1)
            response = recv(socket, 256)
            print 'Message received from ' + self.resource_id + ': ' + response
            self.eventbus.send(self.outbound_channel, {
                'message': json.loads(response),
                'id': self.message_id
            })
        finally:
            try:
                socket.close()
            except BluetoothError as e:
                message = {'error': resource_id + ': ' + e.strerror}
