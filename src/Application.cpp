#include <iostream>
#include <nanogui/nanogui.h>
#include <portaudio.h>
#include <sndfile.h>

#include "gui/MainApp.h"
#include "core/AudioDevice.h"
#include "core/PaDevice.h"

using namespace nanogui;

void callback(float* buffer, int channels, int frames, void *cookie) {
    for (int i = 0; i < channels * frames; i++) {
        buffer[i] = 0.0f;
    }
}

int main(void) {
    PaDevice* audiodevice = nullptr;
    try {

        //AudioDevice* audiodevice = new AudioDevice(44100, 2, 256, &callback, NULL);
        nanogui::init();
        {
            ref<MainApp> app = new MainApp();

            app->dec_ref();
            app->draw_all();
            app->set_visible(true);
            //app->perform_layout();

            nanogui::mainloop(-1);
        }


        //delete audiodevice;
        nanogui::shutdown();
        delete audiodevice;

    } catch (const std::exception& e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        std::cerr << error_msg << std::endl;
        return -1;
    } catch (...) {
        std::cerr << "Caught an unknown error!" << std::endl;
    }
    return 0;
}