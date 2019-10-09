#include "stdafx.h"
#include "TestWidget.h"
#include "Background.h"
#include "Icons.h"

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
{
	Init();
}

void TestWidget::Init() {

	_background = Background::Create(Core::resourceManager.Get<Render::Texture>("bg"), IPoint(Render::device.Width()*.5, Render::device.Height()*.5));
	_icon = Icons::Create(Core::resourceManager.Get<Render::Texture>("apple"), IPoint(x, y));
	
	x = 0.0f;
	y = 160.0f -_icon->GetSize();

	for (int i = 0; i <4; i++) {
		x = .0;
		y += _icon->GetSize();
		for (int i = 0; i < 4;i++) {
			_icons.push_back(Icons::Create(Core::resourceManager.Get<Render::Texture>("apple"), IPoint(x, y)));
			x+= _icon->GetSize();
		}
	}
}

void TestWidget::Draw(){

	_background->Draw();
	///_icon->Draw();
	
	for (auto& icon : _icons) {
		icon->Draw();
	}
}

void TestWidget::Update(float dt){

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
