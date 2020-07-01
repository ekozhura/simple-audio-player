#pragma once
#include <iostream>
#include <sndfile.h>
#include <nanogui/nanogui.h>

using namespace nanogui;

class Toolbar
{
public:
	Toolbar(Screen *screen, void callback(SNDFILE *, SF_INFO *, char *), SNDFILE *fin);
	~Toolbar();

	void open_file(
		char openFileFlag,
		SF_INFO* info
	);


private:
	ref<Screen> m_screen;
	ref<Window> m_window;
	ref<GroupLayout> m_layout;
	std::string m_filename;

	SNDFILE* m_soundfile;
	SF_INFO m_soundfile_info;
};

