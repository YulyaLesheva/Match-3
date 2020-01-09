#pragma once

class TextLabels
{
public:
	TextLabels(IPoint position, char* text, int r, int g, int b);

	static std::unique_ptr <TextLabels> CreateTextLabel(IPoint position, char* text, int r, int g, int b);

	void Draw();


private:
	IPoint _position;
	int _score;
	char* _text;
	int _r, _g, _b;
};