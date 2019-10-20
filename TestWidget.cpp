#include "stdafx.h"
#include "TestWidget.h"
#include "Background.h"
#include "Icons.h"
#include "RandomTile.h"

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name),
	col(4),
	row(4)
{
	Init();
}

void TestWidget::Init() {

	_background = Background::Create(Core::resourceManager.Get<Render::Texture>("bg"), IPoint(Render::device.Width()*.5, Render::device.Height()*.5));
	_icon = Icons::Create(Core::resourceManager.Get<Render::Texture>("apple"), IPoint(x, y));
	
	x = 0.0f;
	y = 160-_icon->GetSize();

	for (int i = 0; i < row; i++) {
		x = .0;
		y += _icon->GetSize();
		for (int j = 0; j < col; j++) {
			cell[i][j] = Icons::Create(Core::resourceManager.Get<Render::Texture>(GetTile()), IPoint(x, y));
			x += _icon->GetSize();
		}
	}

}


void TestWidget::Draw(){

	_background->Draw();
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cell[i][j]->Draw();
		}
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
