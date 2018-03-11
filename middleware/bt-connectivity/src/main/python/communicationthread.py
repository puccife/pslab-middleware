import threading
import bluetooth as bt
import time
import json
import types

PY2JA = 'py2ja'

class communicationThread (threading.Thread):
    def __init__(self, eventBus, deviceMAC, requestData):
        threading.Thread.__init__(self)
        self.eventBus = eventBus
        self.deviceMAC = deviceMAC
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
        socket = bt.BluetoothSocket(bt.RFCOMM)
        socket.connect((self.deviceMAC, 1))
        requestJson = json.dumps(self.request)
        dataSize = chr(len(requestJson))
        print type(requestJson)
        print "Request size is " + str(ord(dataSize))
        print "Sending " + requestJson + " to " + self.device + "..."
        socket.send(dataSize + requestJson)
        time.sleep(1)
        dataReceived = self.__getmsg(unicode(socket.recv(256)))
        print "Message received from " + self.device + ": " + dataReceived
        dataReceived = json.loads(dataReceived)
	dataReceived['id'] = self.messageId
        self.eventBus.send(PY2JA, dataReceived)
        socket.close()

    def __getmsg(self, msg):
        len = ord(msg[:1])
        return msg[1:len]

