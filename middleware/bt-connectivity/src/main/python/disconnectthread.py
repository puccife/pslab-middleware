import threading
import json

PY2JA = 'py2ja'

class disconnectThread (threading.Thread):
    def __init__(self, eventBus, deviceMAC, openConn):
        threading.Thread.__init__(self)
        self.eventBus = eventBus
        self.deviceMAC = deviceMAC
        self.openConn = openConn
    def run(self):
        print "Starting " + self.name
        self.disconnect()
        print "Exiting " + self.name

    def disconnect(self):
    	socket = openConn[self.deviceMAC]
    	socket.close()
    	del openConn[self.deviceMAC]
    	#notify Java System
    	reply = {'response', "device " + self.deviceMAC + "successfully disconnected"}
    	self.eventBus.send(PY2JA, reply)
