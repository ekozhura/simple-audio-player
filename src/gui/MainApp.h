#pragma once
#include <nanogui/nanogui.h>
#include "../core/PaDevice.h"
#include "../core/ConfigManager.h"

using namespace nanogui;

class MainApp : public Screen {
public:
    MainApp();
private:
    ConfigManager* m_config_manager;
    PaDevice* m_audiodevice;
};

