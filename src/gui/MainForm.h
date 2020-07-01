#pragma once
#include <nanogui/nanogui.h>
#include "../core/ConfigManager.h"

using namespace nanogui;

class MainForm : public FormHelper {
public:
    MainForm(Screen* screen, ConfigManager* config_manager);
    ref<Window> get_window();

private:
    ConfigManager* m_config_manager;
    ref<Window> window;
};
