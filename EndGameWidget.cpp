#include "stdafx.h"
#include "EndGameWidget.h"
#include "Background.h"
#include "TextLabels.h"
#include "Buttons.h"
#include "Score.h"

EndGameWidget::EndGameWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name),
	isGameOver(false)

{
	Init();
}

void EndGameWidget::Init() {
	_gameOver = Background::Create(Core::resourceManager.Get<Render::Texture>("gameOver"), IPoint(Render::device.Width()*.5, 840));
	_notebook = Background::Create(Core::resourceManager.Get<Render::Texture>("notebook"), IPoint(Render::device.Width()*.5, Render::device.Height()*.5));
	_yellowForReplay = Buttons::Create(Core::resourceManager.Get<Render::Texture>("yellowForReplay"), IPoint(_notebook->GetPosition().x, _notebook->GetPosition().y / 1.2));
	_yourScore = TextLabels::CreateTextLabel(IPoint(_notebook->GetPosition().x, _notebook->GetPosition().y + 120), "your score:", 255, 0, 38);
	_bestScore = TextLabels::CreateTextLabel(IPoint(_notebook->GetPosition().x - 45, _notebook->GetPosition().y - 140), "best score:", 255, 128, 0);
	_redForScore = Background::Create(Core::resourceManager.Get<Render::Texture>("redForScore"), IPoint(Render::device.Width()*.5, 100.f));
	_whiteForBestScore = Background::Create(Core::resourceManager.Get<Render::Texture>("whiteForBestScore"), IPoint(435, _notebook->GetPosition().y - 162));
	_finalScore = Score::CreateScore(IPoint(Render::device.Width()*.5, 525));
}

void EndGameWidget::Draw() {
	
	

	if (isGameOver) {
		_gameOver->Draw();
		_notebook->Draw();
		_yellowForReplay->Draw();
		_yourScore->Draw();
		_bestScore->Draw();
		_whiteForBestScore->Draw();
		_redForScore->Draw();
	}
	
	if (isGameOver) {
		_finalScore->Draw();
	}
	

}
void EndGameWidget::Update(float dt) {

}

void EndGameWidget::AcceptMessage(const Message& message) {
	
	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();

	if (publisher == "EndGame") {
		_finalScore->SetScore(std::stoi(data));
		EndGame();
	}

	if (publisher == "RestartGame") {
		RestartGame();
	}
}
void EndGameWidget::EndGame() {
	isGameOver = true;
	_redForScore->SetPosition(IPoint(Render::device.Width()*.5, 500));
}

bool EndGameWidget::MouseDown(const IPoint& mouse_pos) {
	if (!isGameOver) return false;

	if (_yellowForReplay->GetRect().Contains(mouse_pos)) {
			Core::guiManager.getLayer("TestLayer")->getWidget("TestWidget")->AcceptMessage(Message("RestartGame", "RestartGame"));
			return true;
	}
	
	return false;
}

void EndGameWidget::MouseMove(const IPoint& mouse_pos) {

}
void EndGameWidget::MouseUp(const IPoint& mouse_pos) {

}

void EndGameWidget::KeyPressed(int keyCode) {
	
}
void EndGameWidget::CharPressed(int unicodeChar) {

}
void EndGameWidget::RestartGame() {
	isGameOver = false;
	_redForScore->SetPosition(IPoint(Render::device.Width()*.5, 100.f));
}