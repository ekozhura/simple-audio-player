#include "ConfigManager.h"

ConfigManager::ConfigManager() {

}

void ConfigManager::add_device(DeviceInfo *device) {
	m_devices.push_back(*device);
}

void ConfigManager::add_host(DeviceInfo *host) {
	m_hosts.push_back(*host);
}

std::vector<std::string> ConfigManager::get_devices() {
	std::vector<std::string> devices;
	for (DeviceInfo d: m_devices) {
		devices.push_back(d.name);
	}
	return devices;
}