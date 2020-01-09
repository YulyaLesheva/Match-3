#include "stdafx.h"
#include "Score.h"

Score::Score(IPoint position)
	: _score(0),
	_position(position)
{
}

std::unique_ptr<Score> Score::CreateScore(IPoint position){
	return std::unique_ptr<Score>(new Score(position));
}

void Score::Draw()
{
	Render::BindFont("Wingko");
	Render::PrintString(_position, std::to_string(_score), 1.f, CenterAlign);
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