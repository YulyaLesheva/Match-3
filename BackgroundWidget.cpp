#include "stdafx.h"
#include "BackgroundWidget.h"
#include "Background.h"

BackgroundnWidget::BackgroundnWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name),
	isGameOver(false)

{
	Init();
}

void BackgroundnWidget::Init()
{
	_background = Background::Create(Core::resourceManager.Get<Render::Texture>("bg"), IPoint(Render::device.Width()*.5, Render::device.Height()*.5));
	_redForScore = Background::Create(Core::resourceManager.Get<Render::Texture>("redForScore"), IPoint(Render::device.Width()*.5, 100.f));
	_gameOver = Background::Create(Core::resourceManager.Get<Render::Texture>("gameOver"), IPoint(Render::device.Width()*.5, 840));
	_fone = Background::Create(Core::resourceManager.Get<Render::Texture>("fone"), IPoint(Render::device.Width()*.5, Render::device.Height()*.5));
	_notebook = Background::Create(Core::resourceManager.Get<Render::Texture>("notebook"), IPoint(350, 350));
}

void BackgroundnWidget::Draw()
{
	_background->Draw();
	if (isGameOver) {
		_gameOver->Draw();
	}
	_fone->Draw();
	_redForScore->Draw();
	
	if (isGameOver) {
		_notebook->Draw();
	}
	
}

void BackgroundnWidget::Update(float dt)
{
	
}

bool BackgroundnWidget::MouseDown(const IPoint &mouse_pos)
{
	
	return false;
}

void BackgroundnWidget::MouseMove(const IPoint &mouse_pos)
{
	
}

void BackgroundnWidget::MouseUp(const IPoint &mouse_pos)
{
	
}

void BackgroundnWidget::AcceptMessage(const Message& message)
{
	//
	// Виджету могут посылаться сообщения с параметрами.
	//

	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();

	if (data == "EndGame") {
		isGameOver = true;
	}

	if (data == "RestartGame") {
		isGameOver = false;
	}
}

void BackgroundnWidget::KeyPressed(int keyCode)
{
	//
	// keyCode - виртуальный код клавиши.
	// В качестве значений для проверки нужно использовать константы VK_.
	//

	if (keyCode == VK_A) {
		// Реакция на нажатие кнопки A
	}
}

void BackgroundnWidget::CharPressed(int unicodeChar)
{
	//
	// unicodeChar - Unicode код введённого символа
	//

	if (unicodeChar == L'а') {
		// Реакция на ввод символа 'а'
	}
}
