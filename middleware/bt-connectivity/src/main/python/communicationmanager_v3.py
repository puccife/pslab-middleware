from communicationthread import communicationThread
from disconnectthread import disconnectThread
from inquirythread import inquiryThread
from persistent_connection_thread import PersistentConnectionThread
from connectionmanager import ConnectionManager
import eventbus.DeliveryOption as DeliveryOption
import eventbus.Eventbus as Eventbus
import json
import bluetooth as bt

JA2PY = 'ja2py'
PY2JA = 'py2ja'

class Client:
	def __init__(self, associated_devices):
		self.devices = []
		self.associated_devices = associated_devices

	#Handler for errors and msg
	def messagehandler(self,message):
    		connection_manager = ConnectionManager(self.associated_devices) 
		print('Request received from eventbus')
		print(message)
		thread = None
		if message != None:
			body = message['body']
			action = body['action']
			payload = body['payload']
			if action == "CONNECT":
    				deviceName = payload['deviceName']
				connection_manager.connect_device(deviceName)
			elif action == "INQUIRY":
				print action
				self.devices = []
				thread = inquiryThread(eb, self.devices, body['id'], associated_devices)
			elif action == "READ" or action == "WRITE":
				deviceURI = body['device']
				if connection_manager.contains_name(deviceURI):
    					thread = PersistentConnectionThread(eb, connection_manager.get_btsocket_for_name(deviceURI), body)
				else:
					print action
					for device in self.associated_devices:
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
eb = Eventbus.Eventbus(Client(associated_devices), 'localhost', 7000)
eb.registerHandler(JA2PY, Client.messagehandler)
