import json
from eventbus.Eventbus import Eventbus
from connectionmanager import ConnectionManager
from connectionthread import ConnectionThread
from disconnectionthread import DisconnectionThread
from inquirythread import InquiryThread
from communicationthread import CommunicationThread
from persistent_communication_thread import PersistentCommunicationThread

JA2PY = 'ja2py'
PY2JA = 'py2ja'

class EventBusClient(object):

    def __init__(self, outbound_channel, associated_resources):
        self.resources = []
        self.associated_resources = associated_resources
        self.connection_manager = ConnectionManager(self.associated_resources)
        self.eventbus = None
        self.outbound_channel = outbound_channel

    def __get_resource(self, resource_id):
        for resource in self.associated_resources:
            if resource['id'] == resource_id:
                return resource
        return None

    def __get_resource_address(self, resource_id):
        resource = self.__get_resource(resource_id)
        return resource['address'] if resource != None else None

    #Handler for errors and msg
    def messagehandler(self, message):
        print 'Request received from eventbus'
        print message
        thread = None
        if message != None:
            body = message['body']
            action = body['action'].upper()
            if action == 'CONNECT':
                thread = ConnectionThread(self.eventbus, self.outbound_channel, self.connection_manager, body)
            elif action == 'DISCONNECT':
                thread = DisconnectionThread(self.eventbus, self.outbound_channel, self.connection_manager, body)
            elif action == 'INQUIRY':
                self.resources = []
                thread = InquiryThread(self.eventbus, self.outbound_channel, self.resources, body, self.associated_resources)
            elif action == 'READ' or action == 'WRITE':
                if 'resourceId' in body:
                    resource_id = body['resourceId']
                    if self.connection_manager.contains_address(self.__get_resource_address(resource_id)):
                        btsocket = self.connection_manager.get_btsocket_by_id(resource_id)
                        thread = PersistentCommunicationThread(self.eventbus, self.outbound_channel, btsocket, body)
                    else:
                        address = self.__get_resource_address(resource_id)
                        if address != None:
                            thread = CommunicationThread(self.eventbus, self.outbound_channel, address, body)
                        else:
                            response = {
                                'message': {
                                    'error': 'Could not find resource with ID equal to ' + resource_id
                                },
                                'id': body['id']
                            }
                            self.eventbus.send(self.outbound_channel, response)
                else:
                    response = {
                        'message': {
                            'resources': list(set(self.connection_manager.get_connected_resources()))
                        },
                        'id': body['id']
                    }
                    self.eventbus.send(self.outbound_channel, response)
            else:
                response = {
                    'message': {
                        'error': 'Invalid action: ' + action
                    },
                    'id': body['id']
                }
                self.eventbus.send(self.outbound_channel, response)
        else:
            print 'no msg found'
        if thread != None:
            thread.start()

def main():
    associated_resources = []
    with open('associated_resources.json', 'r') as json_file:
        associated_resources = json.load(json_file)
    print associated_resources
    clients = EventBusClient(PY2JA, associated_resources)
    eventbus = Eventbus(clients, 'localhost', 7000)
    clients.eventbus = eventbus
    eventbus.registerHandler(JA2PY, EventBusClient.messagehandler)

if __name__ == '__main__':
    main()
