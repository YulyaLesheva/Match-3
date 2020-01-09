#include "stdafx.h"
#include "TextLabels.h"

TextLabels::TextLabels(IPoint position, char* text, int r, int g, int b)
	: _text(text),
	_position(position),
	_r(r),
	_g(g),
	_b(b)
{
}

std::unique_ptr<TextLabels> TextLabels::CreateTextLabel(IPoint position, char *text, int r, int g, int b) {
	return std::unique_ptr<TextLabels>(new TextLabels(position, text, r, g, b));
}

void TextLabels::Draw()
{
	Render::BeginColor(Color(_r, _g, _b, 255)); // Color(Red, Green, Blue, Alpha)
	Render::BindFont("Wingko");
	Render::PrintString(_position, _text, 1.f, CenterAlign);
	Render::EndColor();
}
