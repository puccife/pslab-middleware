from bluetooth import *

class ConnectionManager:

    def __init__(self, associated_devices):
        self.associated_devices = associated_devices if associated_devices != None else []
        self.connected_devices = {}

    def connect_device(self, name):
        address = self.__get_device_address(name)
	print(address)
        if address != None and not self.contains_address(address):
	    btsocket = BluetoothSocket(RFCOMM)
	    self.connected_devices[address] = btsocket
            btsocket.connect((address, 1))
            return True
        return False

    def disconnect_device(self, name):
        btsocket = self.get_btsocket_for_name(name)
        if btsocket != None:
            btsocket.close()

            del self.connected_devices[self.__get_device_address(name)]
            return True
        return False

    def contains_address(self, address):
        return address in self.connected_devices

    def contains_name(self, name):
	return self.contains_address(self.__get_device_address(name))
	
    def get_btsocket_for_name(self, name):
        associated_device = self.__get_associated_device_by_name(name);
        return self.__get_btsocket_for_address(associated_device['address']) if associated_device !=None else None

    def __get_btsocket_for_address(self, address):
	return self.connected_devices[address] if self.contains_address(address) else None

    def __get_device_address(self, name):
        device = self.__get_associated_device_by_name(name)
	device = device['address']
	return device if device != None and len(device) > 1 else None

    def __is_associated_device(self, name):
        return self.__get_associated_device_by_name(name) != None

    def __get_associated_device_by_address(self, address):
        return self.__get_associated_device(lambda device: device['address'] == address)

    def __get_associated_device_by_name(self, name):
        return self.__get_associated_device(lambda device: device['name'] == name)

    def __get_associated_device(self, filter):
        for device in self.associated_devices:
            if filter(device):
                return device
        return None
