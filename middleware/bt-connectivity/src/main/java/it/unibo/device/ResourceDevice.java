package it.unibo.device;

public class ResourceDevice {

	private final ResourceCategory category;
	private final int id;
	
	/**
	 * 
	 * @param deviceCategory
	 * @param id
	 * @param name
	 */
	public ResourceDevice(String deviceCategory, int id) {
		this.category = new ResourceCategory(deviceCategory);
		this.id = id;
	}

	public ResourceCategory getCategory() {
		return category;
	}

	/**
	 * 
	 * @return the resource identifier.
	 */
	public int getId() {
		return id;
	}

}
