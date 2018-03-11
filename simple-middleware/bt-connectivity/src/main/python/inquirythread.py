from threading import Thread
from bluetooth import discover_devices

DEFAULT_DURATION = 8

class InquiryThread(Thread):

    def __init__(self, eventbus, outbound_channel, resources, request, associated_resources):
        Thread.__init__(self)
        self.eventbus = eventbus
        self.outbound_channel = outbound_channel
        self.resources = resources
        self.request = request
        self.associated_resources = associated_resources
        self.message_id = self.request['id']

    def run(self):
        print 'Starting inquiry thread'
        self.perform_innquiry()
        print 'Exiting inquiry thread'

    def perform_innquiry(self):
        print 'performing inquiry...'

        inquiry_duration = request['query']['duration'] if 'query' in request and 'duration' in request['query'] else DEFAULT_DURATION

        nearby_devices = discover_devices(duration=inquiry_duration, lookup_names=True, flush_cache=True)

        print 'found %d devices' % len(nearby_devices)

        for address, name in nearby_devices:
            try:
                print '  %s - %s' % (name, address)
                for resource in self.associated_resources:
                    if resource['address'] == address:
                        self.resources.append(resource['id'])
            except UnicodeEncodeError:
                print '  %s - %s' % (address, name.encode('utf-8', 'replace'))
        self.eventbus.send(self.outbound_channel, {
            'message': {
                'resources': self.resources
            },
            'id': self.message_id
        })
