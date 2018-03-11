from bluetooth import BluetoothSocket, RFCOMM

class ConnectionManager(object):

    def __init__(self, associated_resources):
        self.associated_resources = associated_resources if associated_resources != None else []
        self.connected_devices = {}
        self.connected_resources = []

    def connect_resource(self, resource_id):
        address = self.__get_resource_address(resource_id)
        if address != None:
            if not self.contains_address(address):
                btsocket = BluetoothSocket(RFCOMM)
                btsocket.connect((address, 1))
                self.connected_devices[address] = btsocket
            if not self.__has_connected_resource(resource_id):
                self.connected_resources.append({'id': resource_id, 'address': address})
            return True
        return False

    def disconnect_resource(self, resource_id):
        address = self.__get_resource_address(resource_id)
        if address != None:
            self.__remove_connected_resource(resource_id)
            if not self.__has_connected_resources(address):
                self.__get_btsocket_by_address(address).close()
                del self.connected_devices[self.__get_resource_address(resource_id)]
            return True
        return False

    def contains_resource(self, resource_id):
        return self.contains_address(self.__get_resource_address(resource_id))

    def contains_address(self, address):
        return address in self.connected_devices

    def get_connected_resources(self):
        resources = []
        for resource in self.connected_resources:
            resources.append(resource['id'])
        return resources

    def get_btsocket_by_id(self, resource_id):
        associated_resource = self.__get_associated_resource(resource_id)
        if associated_resource != None:
            address = self.__get_btsocket_by_address(associated_resource['address'])
            if address != None:
                return address if associated_resource != None else None
        return None

    def __get_btsocket_by_address(self, address):
        return self.connected_devices[address] if self.contains_address(address) else None

    def __get_resource_address(self, resource_id):
        resource = self.__get_associated_resource(resource_id)
        if resource != None:
            address = resource['address']
            return address if address != None else None
        return None

    def __is_associated_resource(self, resource_id):
        return self.__get_associated_resource(resource_id) != None

    def __get_associated_resource(self, resource_id):
        for resource in self.associated_resources:
            if resource['id'] == resource_id:
                return resource
        return None

    def __remove_connected_resource(self, resource_id):
        for i in range(len(self.connected_resources)):
            if self.connected_resources[i]['id'] == resource_id:
                del self.connected_resources[i]
                return True

    def __has_connected_resource(self, resource_id):
        for resource in self.connected_resources:
            if resource['id'] == resource_id:
                return True
        return False

    def __has_connected_resources(self, address):
        for resource in self.connected_resources:
            if resource['address'] == address:
                return True
        return False
