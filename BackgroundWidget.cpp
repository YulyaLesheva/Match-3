#include "stdafx.h"
#include "BackgroundWidget.h"
#include "Background.h"
#include "TextLabels.h"

BackgroundnWidget::BackgroundnWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)

{
	Init();
}

void BackgroundnWidget::Init()
{
	_background = Background::Create(Core::resourceManager.Get<Render::Texture>("bg"), IPoint(Render::device.Width()*.5, Render::device.Height()*.5));
	_fone = Background::Create(Core::resourceManager.Get<Render::Texture>("fone"), IPoint(Render::device.Width()*.5, Render::device.Height()*.5));
	
	//_someShit = Background::Create(Core::resourceManager.Get<Render::Texture>("milk"), IPoint(435, 200));
}

void BackgroundnWidget::Draw()
{
	_background->Draw();
	_fone->Draw();
}

	//Render::BeginAlphaMul(0.5);
	//_someShit->Draw();
	//Render::EndAlphaMul();

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

}

void BackgroundnWidget::RestartGame() {
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
