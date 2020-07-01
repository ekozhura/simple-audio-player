#include <iostream>
#include "MainForm.h"

enum class test_enum {
    Item1,
    Item2,
    Item3
};

bool bvar = true;
int ivar = 12345678;
double dvar = 3.1415926;
float fvar = (float)dvar;
std::string strval = "A string";
std::string strval2 = "";
test_enum enumval = test_enum::Item2;
Color colval(0.5f, 0.5f, 0.7f, 1.f);

MainForm::MainForm(Screen* screen, ConfigManager* config_manager): FormHelper(screen), m_config_manager(config_manager) {
    this->window = this->add_window(Vector2i(0, 0), "Form helper example");
    
    bool enabled = true;

    this->add_group("Devices");
    
    {
        std::vector<std::string> devices = m_config_manager->get_devices();
        for (std::string device_name : devices) {
            std::cout << device_name << std::endl;
            this->add_variable("string", device_name);
        }
    }
}

ref<Window> MainForm::get_window() {
    return this->window;
}