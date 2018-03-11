import json

from threading import Thread
from btutils import send, recv

class PersistentCommunicationThread(Thread):

    def __init__(self, eventbus, outbound_channel, socket, request):
        Thread.__init__(self)
        self.eventbus = eventbus
        self.outbound_channel = outbound_channel
        self.socket = socket
        self.request = request
        self.message_id = self.request['id']
        self.resource_id = self.request['resourceId']

    def run(self):
        print 'Starting persistent communication thread'
        self.communicate()
        print 'Exiting persistent communication thread'

    def communicate(self):
        print 'Trying to communicate with ' + self.resource_id
        request = json.dumps(self.request)
        print 'Sending ' + request + ' to ' + self.resource_id + '...'
        send(self.socket, request)
        # time.sleep(1)
        response = recv(self.socket, 256)
        print 'Message received from ' + self.resource_id + ': ' + response
        self.eventbus.send(self.outbound_channel, {
            'message': json.loads(response),
            'id': self.message_id
        })
