#pragma once
#include <nanogui/nanogui.h>
#include <nanogui/opengl.h>

using namespace nanogui;

class CustomWidget : public Widget {
public:
	CustomWidget(Widget* parent, const std::string& font);
	virtual void draw(NVGcontext* ctx) override;
	virtual Vector2i preferred_size(NVGcontext* ctx) const override;
	
	void set_font(const std::string& font) { m_font = font; }

private:
	std::string m_font;
};

