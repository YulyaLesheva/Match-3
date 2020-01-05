#include "stdafx.h"
#include "TextLabels.h"

TextLabels::TextLabels(IPoint position, char* text)
	: _text(text),
	_position(position)
{
}

std::unique_ptr<TextLabels> TextLabels::CreateTextLabel(IPoint position, char *text) {
	return std::unique_ptr<TextLabels>(new TextLabels(position, text));
}

void TextLabels::Draw()
{
	Render::BeginColor(Color(255, 0, 38, 255)); // Color(Red, Green, Blue, Alpha)
	Render::BindFont("Wingko");
	Render::PrintString(_position, _text, 1.f, CenterAlign);
	Render::EndColor();
}
