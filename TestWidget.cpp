#include "stdafx.h"
#include "TestWidget.h"
#include "Background.h"
#include "Icons.h"
#include "RandomTile.h"

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name),
	cell(),
	col(4),
	row(4),
	_swapped(false),
	_needToCheckCoincidence(false),
	_readyToRemove(false),
	_ableToSwap(false),
	_readyToCheckRow(false)
{
	Init();
}

void TestWidget::Init() {

	_background = Background::Create(Core::resourceManager.Get<Render::Texture>("bg"), IPoint(Render::device.Width()*.5, Render::device.Height()*.5));
	_icon = Icons::Create(Core::resourceManager.Get<Render::Texture>("apple"), IPoint(x, y));

	InitGameField();
}

void TestWidget::InitGameField() {
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
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			cell[r][c]->Draw();
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
		CheckCoincidence();
	}

	if (_readyToCheckRow) {
		for (int i = 0; i < row; i++) {
			if (row_0_Textures_array[i] == row_0_Textures_array[i + 1] && row_0_Textures_array[i]
				== row_0_Textures_array[i + 2]) {
				row_0_array[i]->Marking();
				row_0_array[i+1]->Marking();
				row_0_array[i+2]->Marking();
			}
			if (row_1_Textures_array[i] == row_1_Textures_array[i + 1] && row_1_Textures_array[i]
				== row_1_Textures_array[i + 2]) {
				row_1_array[i]->Marking();
				row_1_array[i + 1]->Marking();
				row_1_array[i + 2]->Marking();
			}
			if (row_2_Textures_array[i] == row_2_Textures_array[i + 1] && row_2_Textures_array[i]
				== row_2_Textures_array[i + 2]) {
				row_2_array[i]->Marking();
				row_2_array[i + 1]->Marking();
				row_2_array[i + 2]->Marking();
			}
			if (row_3_Textures_array[i] == row_3_Textures_array[i + 1] && row_3_Textures_array[i]
				== row_3_Textures_array[i + 2]) {
				row_3_array[i]->Marking();
				row_3_array[i + 1]->Marking();
				row_3_array[i + 2]->Marking();
			}
		}
	}

	collideVector.clear();
	namesCollideVector.clear();
	_readyToRemove = false;
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

	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			auto currentIcon = cell[r][c];
			auto rect = currentIcon->GetRectangle();
			if (rect.Contains(mouse_pos)) {
				currentIcon->Push();
				savedIcons.push_back(currentIcon);
				savedTextures.push_back(currentIcon->GetTexture());
				if (savedIcons.front()) {
					neighbors.push_back(cell[r][c-1]);
					neighbors.push_back(cell[r][c+1]);
					neighbors.push_back(cell[r+1][c]);
					neighbors.push_back(cell[r-1][c]);
					}
				}
			}
		}
	return false;
}

void TestWidget::CheckCoincidence() {
	
	for (int i = 0; i < col; i++) {
		row_0_array[i] = cell[0][i];
		row_0_Textures_array[i] = cell[0][i]->GetTexture();
	}

	for (int i = 0; i < col; i++) {
		row_1_array[i] = cell[1][i];
		row_1_Textures_array[i] = cell[1][i]->GetTexture();
	}

	for (int i = 0; i < col; i++) {
		row_2_array[i] = cell[2][i];
		row_2_Textures_array[i] = cell[2][i]->GetTexture();
	}

	for (int i = 0; i < col; i++) {
		row_3_array[i] = cell[3][i];
		row_3_Textures_array[i] = cell[3][i]->GetTexture();
	}

	_readyToCheckRow = true;
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
