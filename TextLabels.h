#pragma once

class TextLabels
{
public:
	TextLabels(IPoint position, char* text);

	static std::unique_ptr <TextLabels> CreateTextLabel(IPoint position, char* text);

	void Draw();


private:
	IPoint _position;
	int _score;
	char* _text;
};