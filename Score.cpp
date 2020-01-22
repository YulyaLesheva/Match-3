#include "stdafx.h"
#include "Score.h"

Score::Score(IPoint position, int r, int g, int b)
	: _score(0),
	_position(position),
	_r(r),
	_g(g),
	_b(b)
{
}

std::unique_ptr<Score> Score::CreateScore(IPoint position, int r, int g, int b){
	return std::unique_ptr<Score>(new Score(position, r, g, b));
}

void Score::Draw()
{
	Render::BeginColor(Color(_r, _g, _b, 255)); // Color(Red, Green, Blue, Alpha)
	Render::BindFont("Wingko");
	Render::PrintString(_position, std::to_string(_score), 1.f, CenterAlign);
	Render::EndColor();
}

void Score::IncreaseScore(int size){
	_score += 10 * size;
}


void Score::ResetScore() {
	_score = 0;
}

void Score::SetPosition(IPoint position) {
	_position = position;
}

int Score::ReturnScore() {
	return _score;
}

void Score::SetScore(int score) {
	_score = score;
}