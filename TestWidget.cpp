#include "stdafx.h"
#include "TestWidget.h"
#include "Background.h"

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
{
	Init();
}

void TestWidget::Init()
{
	_tex1 = Core::resourceManager.Get<Render::Texture>("btnStart_Text");
	bg = Background::Create(Core::resourceManager.Get<Render::Texture>("bg"));
	
}

void TestWidget::Draw()
{
	
		///_tex1->Draw();
		bg->Draw();
}

void TestWidget::Update(float dt)
{
	
}

bool TestWidget::MouseDown(const IPoint &mouse_pos)
{
	
	return false;
}

void TestWidget::MouseMove(const IPoint &mouse_pos)
{
}

void TestWidget::MouseUp(const IPoint &mouse_pos)
{
}

void TestWidget::AcceptMessage(const Message& message)
{
	
}

void TestWidget::KeyPressed(int keyCode)
{
	//
	// keyCode - виртуальный код клавиши.
	// В качестве значений для проверки нужно использовать константы VK_.
	//

	if (keyCode == VK_A) {
		// Реакция на нажатие кнопки A
	}
}

void TestWidget::CharPressed(int unicodeChar)
{
	//
	// unicodeChar - Unicode код введённого символа
	//

	if (unicodeChar == L'а') {
		// Реакция на ввод символа 'а'
	}
}
