#include "stdafx.h"
#include "TestWidget.h"
#include "Background.h"
#include "Icons.h"
#include "RandomTile.h"

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name),
	col(4),
	row(4),
	_iconsSide(256 * .625),
	x(0),
	y(960-(256 * .625))
{
	Init();
}

void TestWidget::Init() {
	
	_background = Background::Create(Core::resourceManager.Get<Render::Texture>("bg"), IPoint(Render::device.Width()*.5, Render::device.Height()*.5));

	/*for (int r = 0; r < row; r++) {
		x = 0;
		y -= _iconsSide;
		for (int c = 0; c < col; c++) {
			GameField[r][c] = SetRandomIcon(IPoint(x,y));
			x += _iconsSide;
		}
	} */
	x = 0;
	y = 0;

	GameField[0][0] = Icons::Create(Core::resourceManager.Get<Render::Texture>("orange"), IPoint(0, 960 - _iconsSide * 2));
	GameField[0][1] = Icons::Create(Core::resourceManager.Get<Render::Texture>("orange"), IPoint(x + _iconsSide * 1, 960 - _iconsSide*2));
	GameField[0][2] = Icons::Create(Core::resourceManager.Get<Render::Texture>("orange"), IPoint(x + _iconsSide * 2, 960 - _iconsSide * 2));
	GameField[0][3] = Icons::Create(Core::resourceManager.Get<Render::Texture>("orange"), IPoint(x + _iconsSide * 3, 960 - _iconsSide*2));
	GameField[1][0] = Icons::Create(Core::resourceManager.Get<Render::Texture>("orange"), IPoint(0 , 960 - _iconsSide * 3));
	GameField[1][1] = Icons::Create(Core::resourceManager.Get<Render::Texture>("orange"), IPoint(x + _iconsSide * 1, 960 - _iconsSide * 3));
	GameField[1][2] = Icons::Create(Core::resourceManager.Get<Render::Texture>("orange"), IPoint(x + _iconsSide * 2, 960 - _iconsSide * 3));
	GameField[1][3] = Icons::Create(Core::resourceManager.Get<Render::Texture>("flower"), IPoint(x + _iconsSide * 3, 960 - _iconsSide * 3));
	GameField[2][0] = Icons::Create(Core::resourceManager.Get<Render::Texture>("brokkoli"), IPoint(0, 960 - _iconsSide * 4));
	GameField[2][1] = Icons::Create(Core::resourceManager.Get<Render::Texture>("cocos"), IPoint(x + _iconsSide * 1, 960 - _iconsSide * 4));
	GameField[2][2] = Icons::Create(Core::resourceManager.Get<Render::Texture>("bread"), IPoint(x + _iconsSide * 2, 960 - _iconsSide * 4));
	GameField[2][3] = Icons::Create(Core::resourceManager.Get<Render::Texture>("flower"), IPoint(x + _iconsSide * 3, 960 - _iconsSide * 4));
	GameField[3][0] = Icons::Create(Core::resourceManager.Get<Render::Texture>("orange"), IPoint(0, 960 - _iconsSide * 5));
	GameField[3][1] = Icons::Create(Core::resourceManager.Get<Render::Texture>("milk"), IPoint(x + _iconsSide * 1, 960 - _iconsSide * 5));
	GameField[3][2] = Icons::Create(Core::resourceManager.Get<Render::Texture>("bread"), IPoint(x + _iconsSide * 2, 960 - _iconsSide * 5));
	GameField[3][3] = Icons::Create(Core::resourceManager.Get<Render::Texture>("cocos"), IPoint(x + _iconsSide * 3, 960 - _iconsSide * 5));


	bool test = false;

	/*CurrentVector = new std::vector<std::shared_ptr<Icons>>;
		
	for (int c = 0; c < 3; c++) {
			CurrentVector->push_back(GameField[0][c]);
			if (CurrentVector->back()->GetTexture() == GameField[0][c+1]->GetTexture()) {
				CurrentVector->push_back(GameField[0][c + 1]);
				test = true;
				continue;
			}
			else {
				break;
			}
		}*/
	
	int numCol = 0;
	bool found = false;
	
	for (int c = 0; c < 2; c++) {
		CurrentVector = new std::vector<std::shared_ptr<Icons>>;
		CurrentVector->push_back(GameField[0][c]);
		numCol ++;
		
		if (found) {
			break;
		}
		
		
		for (int j = 0; j < (4-numCol); j++) {
			if (CurrentVector->back()->GetTexture() == GameField[0][j+1]->GetTexture()) {
				CurrentVector->push_back(GameField[0][j+1]);
				test = true;
				found = true;
			}
			else {
				break;
			}
			
		}
		if(CurrentVector->size()>2)
		VectorForDelete.push_back(CurrentVector);
	}

}
std::shared_ptr<Icons> TestWidget::SetRandomIcon(IPoint& position) {
	auto icon = Icons::Create(Core::resourceManager.Get<Render::Texture>(Random::GetRandomTile()), IPoint(position));
	return icon;
}


void TestWidget::Draw() {
	_background->Draw();
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			GameField[r][c]->Draw();
		}
	}
}

void TestWidget::LookForMatches(int rows, int cols) {
	 
	
}

void TestWidget::Update(float dt) {

}



bool TestWidget::MouseDown(const IPoint &mouse_pos){	

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
