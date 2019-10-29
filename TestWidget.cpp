#include "stdafx.h"
#include "TestWidget.h"
#include "Background.h"
#include "Icons.h"
#include "RandomTile.h"

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name),
	cell(),
	IconsNamesCell(),
	col(4),
	row(4),
	_swapped(false),
	_needToCheckCoincidence(false),
	_readyToRemove(false),
	_ableToSwap(false)
{
	Init();
}

void TestWidget::Init() {

	_background = Background::Create(Core::resourceManager.Get<Render::Texture>("bg"), IPoint(Render::device.Width()*.5, Render::device.Height()*.5));
	_icon = Icons::Create(Core::resourceManager.Get<Render::Texture>("apple"), IPoint(x, y));

	CreateGameField();
}

void TestWidget::CreateGameField() {
	x = 0.0f;
	y = 160 - _icon->GetSize();

	std::string currentTile;
	std::string checkCell[4][4];

	for (int r = 0; r < row; ++r) {
		x = .0;
		y += _icon->GetSize();

		for (int c = 0; c < col; ++c) {
			currentTile = Random::GetRandomTile();

			while (currentTile == checkCell[r][c - 1] && currentTile == checkCell[r][c - 2]) {
				currentTile = Random::GetRandomTile();
			}

			while (currentTile == checkCell[r - 1][c] && currentTile == checkCell[r - 2][c]) {
				currentTile = Random::GetRandomTile();
			}

			cell[r][c] = Icons::Create(Core::resourceManager.Get<Render::Texture>(currentTile), IPoint(x, y));
			checkCell[r][c] = currentTile;
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

void TestWidget::Update(float dt) {
	Swapping();

	if (_swapped) {
		for (auto &i : savedIcons) {
			i->DisableLight();
		}
		savedIcons.clear();
		savedTextures.clear();
		neighbors.clear();
		_swapped = false;
		_ableToSwap = false;

	}
}

void TestWidget::Swapping() {

	if (savedIcons.size() == 2 && !_swapped) {
		for (auto &n : neighbors) {
			if (!savedIcons.empty()) {
				if (n == savedIcons.back()) {
					_ableToSwap = true;
				}
				else {
				_swapped = true;
				}
			}	
		}
	}
	
	if (_ableToSwap) {
		savedIcons.front()->setNewTexture(savedTextures[1]);
		savedIcons.back()->setNewTexture(savedTextures[0]);
		_swapped = true;
	}
	
}


bool TestWidget::MouseDown(const IPoint &mouse_pos){	

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			auto currentIcon = cell[i][j];
			auto rect = currentIcon->GetRectangle();
			if (rect.Contains(mouse_pos)) {
				currentIcon->Push();
				savedIcons.push_back(currentIcon);
				savedTextures.push_back(currentIcon->GetTexture());
				if (savedIcons.front()) {
					neighbors.push_back(cell[i][j-1]);
					neighbors.push_back(cell[i][j+1]);
					neighbors.push_back(cell[i+1][j]);
					neighbors.push_back(cell[i-1][j]);
					}
				}
			}
		}
	return false;
}

void TestWidget::CheckCoincidence() {


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
