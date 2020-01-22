#pragma once

class Score
{
public:
	Score(IPoint position, int r, int g, int b);

	static std::unique_ptr <Score> CreateScore(IPoint position, int r = 255, int g = 255, int b = 255);

	void Draw();
	void Update(float dt);
	void IncreaseScore(int size);
	void ResetScore();
	void SetPosition(IPoint position);
	int ReturnScore();
	void SetScore(int score);
	int _score;
private:
	IPoint _position;
	int _r, _g, _b;
	float eventTimer;
};