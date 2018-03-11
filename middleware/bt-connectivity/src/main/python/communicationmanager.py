from communicationthread import communicationThread
from disconnectthread import disconnectThread
from inquirythread import inquiryThread
import eventbus.DeliveryOption as DeliveryOption
import eventbus.Eventbus as Eventbus
import json
import bluetooth as bt

JA2PY = 'ja2py'
PY2JA = 'py2ja'

class Client:
	def __init__(self):
		self.devices = []

	#Handler for errors and msg
	def messagehandler(self,message):
		print('Request received from eventbus')
		print(message)
		thread = None
		if message != None:
			body = message['body']
			action = body['action']
			if action == "INQUIRY":
				print action
				self.devices = []
				thread = inquiryThread(eb, self.devices, body['id'], associated_devices)
			elif action == "READ" or action == "WRITE":
				deviceURI = body['device']
				print action
				for device in associated_devices:
					if device['name'] == deviceURI:
						deviceMAC = device['address']
						thread = communicationThread(eb, deviceMAC, body)
			elif action == "disconnect":
				deviceURI = body['device']
				del devices[deviceURI]	
		else:
			print("no msg found")
		thread.start()

associated_devices = {}
with open('associated_devices.json', 'r') as file:
	associated_devices = json.load(file)
print associated_devices
eb = Eventbus.Eventbus(Client(), 'localhost', 7000)
#DeliveryOption
#options = DeliveryOption.DeliveryOption()
#options.addHeader('type', 'text')
#options.addHeader('size','small')
#options.setTimeInterval(1)

#register handler
eb.registerHandler(JA2PY, Client.messagehandler)

#close after 5 seconds
#eb.closeConnection(5)
