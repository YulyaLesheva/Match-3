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
	void SetPosition(IPoint position);
	int ReturnScore();
	void SetScore(int score);
	int _score;
private:
	IPoint _position;
	
	float eventTimer;
};