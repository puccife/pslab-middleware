import threading
import bluetooth as bt
import time
import json
import types

PY2JA = 'py2ja'

class PersistentConnectionThread (threading.Thread):
    def __init__(self, eventBus, socket, requestData):
        threading.Thread.__init__(self)
        self.eventBus = eventBus
        self.socket = socket
        self.messageId = requestData['id']
        self.device = requestData['device']
        self.request = requestData
        del self.request['device']
        del self.request['id']

    def run(self):
        print "Starting communication thread: " + self.name
        self.communicate()
        print "Exiting communication thread: " + self.name

    def communicate(self):
        print "Trying to communicate with " + self.device
        requestJson = json.dumps(self.request)
        dataSize = chr(len(requestJson))
        print type(requestJson)
        print "Request size is " + str(ord(dataSize))
        print "Sending " + requestJson + " to " + self.device + "..."
        self.socket.send(dataSize + requestJson)
#        time.sleep(1)
	msg = ""
	tmp = self.socket.recv(256)
	size = self.__getsize(tmp)
	size = size - 1
	print(size)
	msg = self.__getmsg(tmp)
	while(len(msg) < size):
		print(msg)
		tmp = self.socket.recv(256)
		msg += tmp
		
	dataReceived = msg
        print "Message received from " + self.device + ": " + dataReceived
        dataReceived = json.loads(dataReceived)
	dataReceived['id'] = self.messageId
        self.eventBus.send(PY2JA, dataReceived)

    def __getmsg(self, msg):
        len = ord(msg[:1])
        return msg[1:len]

    def __getsize(self, msg):
	return ord(msg[:1])
