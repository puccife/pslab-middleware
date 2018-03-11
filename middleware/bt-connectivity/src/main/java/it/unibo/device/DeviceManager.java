package it.unibo.device;

import java.util.HashSet;
import java.util.Set;

import it.unibo.exception.DeviceNotAssociatedException;
import it.unibo.exception.DeviceNotConnectedException;

public class DeviceManager {

	Set<BluetoothDevice> associatedDevices;
	Set<BluetoothDevice> connectedDevices;

	public DeviceManager() {
		associatedDevices = new HashSet<>();
		connectedDevices = new HashSet<>();
	}

	public boolean addAssociatedDevice(BluetoothDevice bluetoothDevice) {
		return this.associatedDevices.add(bluetoothDevice);
	}

	public boolean removeAssociatedDevice(BluetoothDevice bluetoothDevice) {
		return this.associatedDevices.remove(bluetoothDevice);
	}

	public boolean addConnectedDevice(BluetoothDevice bluetoothDevice) throws DeviceNotAssociatedException {
		if (!associatedDevices.contains(bluetoothDevice))
			throw new DeviceNotAssociatedException(bluetoothDevice.getName() + " is not associated.");
		return this.connectedDevices.add(bluetoothDevice);
	}

	public boolean removeConnectedDevice(BluetoothDevice bluetoothDevice) throws DeviceNotConnectedException {
		if (!associatedDevices.contains(bluetoothDevice))
			throw new DeviceNotConnectedException(bluetoothDevice.getName() + " is not connected.");
		return this.connectedDevices.remove(bluetoothDevice);
	}
}
