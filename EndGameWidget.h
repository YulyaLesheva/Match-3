#pragma once


#define ptr(t) \
std::unique_ptr<t>

class Background;
class TextLabels;
class Buttons;
class Score;

class EndGameWidget : public GUI::Widget
{
public:
	EndGameWidget(const std::string& name, rapidxml::xml_node<>* elem);

	void Draw() override;
	void Update(float dt) override;

	void AcceptMessage(const Message& message) override;

	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;

	void KeyPressed(int keyCode) override;
	void CharPressed(int unicodeChar) override;
	void RestartGame();
	void EndGame();
	void PrintBestScore();

private:
	void Init();

private:
	ptr(Background) _redForScore;
	ptr(Background) _gameOver;
	ptr(Background) _notebook;
	ptr(Buttons) _yellowForReplay;
	ptr(TextLabels) _yourScore;
	ptr(TextLabels) _bestScore;
	ptr(Background) _whiteForBestScore;
	ptr(Score) _finalScore;
	ptr(TextLabels) _bestScoreNum;

	char* texto;
	bool isGameOver;
};