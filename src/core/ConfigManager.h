#pragma once
#include <vector>
#include <xstring>

struct DeviceInfo {
	int idx;
	std::string name;
};

class ConfigManager
{
public:
	ConfigManager();
	void add_device(DeviceInfo *device);
	void add_host(DeviceInfo *host);

	std::vector<std::string> get_devices();
private:
	std::vector<DeviceInfo> m_hosts {};
	std::vector<DeviceInfo> m_devices {};
};

