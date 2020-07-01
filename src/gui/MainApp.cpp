#include <nanogui/label.h>
#include "CustomWidget.h"
#include "MainApp.h"
#include "MainForm.h"
#include "Toolbar.h"

void open_file(
    SNDFILE *fin,
    SF_INFO *info,
    char *filename
) {
    fin = sf_open(filename, SFM_READ, info);
}

MainApp::MainApp() : Screen(Vector2i(800, 600), "Main GUI Application", true, false) {
    inc_ref();
    SNDFILE* fin = NULL;
    m_config_manager = new ConfigManager();

    m_audiodevice = new PaDevice(m_config_manager);

    //CustomWidget* widget = new CustomWidget(this, "sans-bold");
    MainForm* gui = new MainForm(this, m_config_manager);

    Toolbar* toolbar = new Toolbar(this, open_file, fin);
    //ref<Window> window = gui->get_window();
    
    //window->set_layout(new AdvancedGridLayout({ 10, 0, 10, 0 }, {}));
    //new Label(window, "A tool palette", "sans-bold")->set_layout(new GridLayout());
    
    //Widget* tools = new Widget(window);
    //tools->set_layout(new BoxLayout(Orientation::Horizontal,
    //    Alignment::Middle, 0, 6));

    //ToolButton* b = new ToolButton(tools, FA_CLOUD);
    //b = new ToolButton(tools, FA_FAST_FORWARD);
    //b = new ToolButton(tools, FA_COMPASS);
    //b = new ToolButton(tools, FA_UTENSILS);
    perform_layout();
}