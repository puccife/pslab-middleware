import threading
import bluetooth

PY2JA = 'py2ja'

class inquiryThread (threading.Thread):
    def __init__(self, eventBus, devices, msg, associated):
        threading.Thread.__init__(self)
        self.eb = eventBus
        self.devices = devices
	self.associated = associated
	self.msg = msg
    def run(self):
        print "Starting inquiry thread"
	self.performInquiry()       
        print "Exiting inquiry thread"

    def performInquiry(self):
    	print("performing inquiry...")
    
    	nearby_devices = bluetooth.discover_devices(
            duration=8, lookup_names=True, flush_cache=True)
    
    	print("found %d devices" % len(nearby_devices))
    
    	for address, name in nearby_devices:
    		try:
			for device in self.associated:
				if device['address'] == address:
        				self.devices.append({'name': name, 'address': address})
			print(name, address)
    		except UnicodeEncodeError:
        		print("  %s - %s" % (address, name.encode('utf-8', 'replace')))
	#send device list to Java system
	response = {
		'devices': self.devices,
		'id': self.msg
	}
	self.eb.send(PY2JA, response)
