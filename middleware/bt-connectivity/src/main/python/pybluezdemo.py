import bluetooth
import eventbus.Eventbus as Eventbus
import eventbus.DeliveryOption as DeliveryOption
import json
import time

print("performing inquiry...")

nearby_devices = bluetooth.discover_devices(
        duration=8, lookup_names=True, flush_cache=True, lookup_class=False)

print("found %d devices" % len(nearby_devices))

devices = []
for address, name in nearby_devices:
    try:
        devices.append({'address': address, 'name': name})
    except UnicodeEncodeError:
        print("  %s - %s" % (address, name.encode('utf-8', 'replace')))

#replyHanlder (self,error,message)
#handlers (self,message)

class Client:
	#replyHandler 
	def replyhandler(self,error,message):
		print('replyhandler')
		if error != None:
			print(error)
		if message != None:
			print(message['body'])
	
	#Handler for errors and msg
	def messagehandler(self,message):
		print('messagehandler')
		if message != None:
			print(message['body'])

eb = Eventbus.Eventbus(Client(), 'localhost', 7000)

#jsonObject -body
body = {'devices': devices }

#DeliveryOption
options = DeliveryOption.DeliveryOption()
options.addHeader('type', 'text')
options.addHeader('size','small')
options.setTimeInterval(1)

#register handler
eb.registerHandler('pybluez', Client.messagehandler)

while True:
	#send
	eb.send('pybluez', body, options)
	time.sleep(2)

#close after 5 seconds
eb.closeConnection(10)

