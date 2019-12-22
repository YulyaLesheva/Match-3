#pragma once

class Score
{
public:
	Score(IPoint position);

	static std::unique_ptr <Score> CreateScore(IPoint position);

	void Draw();
	void Update(float dt);
	void IncreaseScore(int size);
	void ResetScore();
	int GetCurrentScore();

private:
	IPoint _position;
	int _score;
	float eventTimer;
};