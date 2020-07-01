#include "CustomWidget.h"

//   CustomWidget *widget = new CustomWidget(m_screen, "sans-bold");
CustomWidget::CustomWidget(Widget* parent, const std::string& font) : Widget(parent), m_font(font) {
	if (m_theme) {
		m_font_size = m_theme->m_standard_font_size;
	}
}

void CustomWidget::draw(NVGcontext *ctx) {
	Widget::draw(ctx);
	nvgFontFace(ctx, m_font.c_str());
	nvgFontSize(ctx, font_size());

	nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
	nvgText(ctx, m_pos.x(), m_pos.y() + m_size.y() * 0.5f, "hello world", nullptr);
}

Vector2i CustomWidget::preferred_size(NVGcontext* ctx) const {
	return Vector2i(100, 40);
}