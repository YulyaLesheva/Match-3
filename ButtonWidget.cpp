#include "stdafx.h"
#include "ButtonWidget.h"
#include "Buttons.h"

ButtonWidget::ButtonWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)

{
	Init();
}

void ButtonWidget::Init()
{
	///_closeButton = Buttons::Create(Core::resourceManager.Get<Render::Texture>("closeButton"), IPoint(Render::device.Width()-60, 900));
	_closeButton = Buttons::Create(Core::resourceManager.Get<Render::Texture>("closeButton"), IPoint(200, 800));
	_replayButton = Buttons::Create(Core::resourceManager.Get<Render::Texture>("replayButton"), IPoint(60, 900));
}

void ButtonWidget::Draw()
{
	_closeButton->Draw();
	_replayButton->Draw();
}

void ButtonWidget::Update(float dt)
{
	
}

bool ButtonWidget::MouseDown(const IPoint &mouse_pos)
{
	_closeButton->MouseDown(mouse_pos);
	
	if (_closeButton->GetRect().Contains(mouse_pos)) {
		Core::appInstance->CloseWindow();
		return true;
	}
	return false;
}

void ButtonWidget::MouseMove(const IPoint &mouse_pos)
{
	
}

void ButtonWidget::MouseUp(const IPoint &mouse_pos)
{
	
}

void ButtonWidget::AcceptMessage(const Message& message)
{
	//
	// Виджету могут посылаться сообщения с параметрами.
	//

	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();
}

void ButtonWidget::KeyPressed(int keyCode)
{
	//
	// keyCode - виртуальный код клавиши.
	// В качестве значений для проверки нужно использовать константы VK_.
	//

	if (keyCode == VK_A) {
		// Реакция на нажатие кнопки A
	}
}

void ButtonWidget::CharPressed(int unicodeChar)
{
	//
	// unicodeChar - Unicode код введённого символа
	//

	if (unicodeChar == L'а') {
		// Реакция на ввод символа 'а'
	}
}
