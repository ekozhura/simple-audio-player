#include "Toolbar.h"
#include "CustomWidget.h"

class OpenFileDialogButton : public ToolButton {
public:
    OpenFileDialogButton(Widget* parent) : ToolButton(parent, FA_FOLDER) {
        
    }

};

Toolbar::Toolbar(Screen* screen, void callback(SNDFILE*, SF_INFO*, char *), SNDFILE* fin) : m_screen(screen)
{
	m_window = new Window(m_screen, "Toolbar");
    m_layout = new GroupLayout();
    m_layout->set_margin(10);
    m_window->set_layout(m_layout);
    m_window->set_visible(true);

    Widget* tools = new Widget(m_window);
    tools->set_layout(new BoxLayout(Orientation::Horizontal,
        Alignment::Middle, 0, 6));

    OpenFileDialogButton* file_button = new OpenFileDialogButton(tools);

    file_button->set_callback([&]() {
        m_filename = file_dialog(
            { { "wav", "audio files" } }, false);
        char* c_string = (char*)"";
        if (m_filename.size() == 0) {
            std::cout << "Error" << std::endl;
        }
        m_filename.copy(c_string, m_filename.size() + 1);
        c_string[m_filename.size() + 1] = '\0';
        callback(fin, &m_soundfile_info, c_string);
        // open_file('r', &m_soundfile_info);
    });

    ToolButton* play_sound = new ToolButton(tools, FA_PLAY);

    play_sound->set_callback([&]() {
        std::cout << m_filename << std::endl;
    });

}

void Toolbar::open_file(
    char openFileFlag,
    SF_INFO* info
) {

    char* c_string = (char*) "";
    if (m_filename.size() == 0) {
        std::cout << "Error" << std::endl;
    }
    m_filename.copy(c_string, m_filename.size() + 1);
    c_string[m_filename.size() + 1] = '\0';

    int flag = openFileFlag == 'w' ? SFM_WRITE : SFM_READ;
    m_soundfile = sf_open(c_string, flag, info);
}

Toolbar::~Toolbar() {
    sf_close(m_soundfile);
}