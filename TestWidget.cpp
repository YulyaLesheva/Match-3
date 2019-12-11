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
	}
	*/


	x = 0;
	y = 0;

	GameField[0][0] = Icons::Create(Core::resourceManager.Get<Render::Texture>("milk"), IPoint(0, 960 - _iconsSide * 2));
	GameField[0][1] = Icons::Create(Core::resourceManager.Get<Render::Texture>("apple"), IPoint(x + _iconsSide * 1, 960 - _iconsSide*2));
	GameField[0][2] = Icons::Create(Core::resourceManager.Get<Render::Texture>("orange"), IPoint(x + _iconsSide * 2, 960 - _iconsSide * 2));
	GameField[0][3] = Icons::Create(Core::resourceManager.Get<Render::Texture>("bread"), IPoint(x + _iconsSide * 3, 960 - _iconsSide*2));


	GameField[1][0] = Icons::Create(Core::resourceManager.Get<Render::Texture>("apple"), IPoint(0 , 960 - _iconsSide * 3));
	GameField[1][1] = Icons::Create(Core::resourceManager.Get<Render::Texture>("flower"), IPoint(x + _iconsSide * 1, 960 - _iconsSide * 3));
	GameField[1][2] = Icons::Create(Core::resourceManager.Get<Render::Texture>("apple"), IPoint(x + _iconsSide * 2, 960 - _iconsSide * 3));
	GameField[1][3] = Icons::Create(Core::resourceManager.Get<Render::Texture>("cocos"), IPoint(x + _iconsSide * 3, 960 - _iconsSide * 3));


	GameField[2][0] = Icons::Create(Core::resourceManager.Get<Render::Texture>("cocos"), IPoint(0, 960 - _iconsSide * 4));
	GameField[2][1] = Icons::Create(Core::resourceManager.Get<Render::Texture>("apple"), IPoint(x + _iconsSide * 1, 960 - _iconsSide * 4));
	GameField[2][2] = Icons::Create(Core::resourceManager.Get<Render::Texture>("brokkoli"), IPoint(x + _iconsSide * 2, 960 - _iconsSide * 4));
	GameField[2][3] = Icons::Create(Core::resourceManager.Get<Render::Texture>("bread"), IPoint(x + _iconsSide * 3, 960 - _iconsSide * 4));


	GameField[3][0] = Icons::Create(Core::resourceManager.Get<Render::Texture>("flower"), IPoint(0, 960 - _iconsSide * 5));
	GameField[3][1] = Icons::Create(Core::resourceManager.Get<Render::Texture>("orange"), IPoint(x + _iconsSide * 1, 960 - _iconsSide * 5));
	GameField[3][2] = Icons::Create(Core::resourceManager.Get<Render::Texture>("bread"), IPoint(x + _iconsSide * 2, 960 - _iconsSide * 5));
	GameField[3][3] = Icons::Create(Core::resourceManager.Get<Render::Texture>("brokkoli"), IPoint(x + _iconsSide * 3, 960 - _iconsSide * 5));


	
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
	bool check =false;
	auto v = LookForMatches();
	check = LookForPossibles();

}


/*std::vector<std::vector<std::shared_ptr<Icons>>*> TestWidget::CheckMatches() {

	for (int r = 0; r < 4; r++) {
		bool found = false;
		for (int i = 0; i < 2; i++) {
			vector = new std::vector<std::shared_ptr<Icons>>;
			vector->push_back(GameField[r][i]);
			for (int c = i; c < 3; c++) {
				if (vector->back()->GetTexture() == GameField[r][c + 1]->GetTexture()) {
					vector->push_back(GameField[r][c + 1]);
					found = true;
				}

				else break;
				
			}

			if (vector->size() > 2) {
				VectorForDelete.push_back(vector);
			}

			if (found) break;
		}

		found = false;

		for (int rw = 0; rw < 2; rw++) {
			vector = new std::vector<std::shared_ptr<Icons>>;
			vector->push_back(GameField[rw][r]);
			for (int rg = rw; rg < 3; rg++) {
				if (vector->back()->GetTexture() == GameField[rg + 1][r]->GetTexture()) {
					vector->push_back(GameField[rg + 1][r]);
					found = true;
				}

				else break;
				
			}
			if (vector->size() > 2) {
				VectorForDelete.push_back(vector);
			}

			if (found) break;
		}
	}

	return VectorForDelete;
}
*/

std::vector<std::shared_ptr<Icons>>* TestWidget::VerticMatches(int rows, int cols) {
	
	auto vector = new std::vector<std::shared_ptr<Icons>>;
	vector->push_back(GameField[rows][cols]);
	for (int i = 1; rows + i < 4; i++) {
		if (vector->back()->GetTexture() == GameField[rows+i][cols]->GetTexture()) {
			vector->push_back(GameField[rows+i][cols]);
		}
		else return vector;
	}
	return vector;
}


std::vector<std::shared_ptr<Icons>>* TestWidget::HorizMatches(int rows, int cols) {
	
	auto vector = new std::vector<std::shared_ptr<Icons>>;
	vector->push_back(GameField[rows][cols]);
	for (int i = 1; cols + i < 4; i++) {
		if (vector->back()->GetTexture() == GameField[rows][cols+i]->GetTexture()) {
			vector->push_back(GameField[rows][cols + i]);
		}
		else return vector;
	}
	return vector;
}

std::vector<std::vector<std::shared_ptr<Icons>>*> *TestWidget::LookForMatches() {
	
	auto VectorOfVectors = new std::vector<std::vector<std::shared_ptr<Icons>>*>;
	for (int rows = 0; rows < 4; rows++) {
		for (int cols = 0; cols < 2; cols++) {
			auto vector = HorizMatches(rows,cols);
			if (vector->size()>2) {
				VectorOfVectors->push_back(vector);
				cols += vector->size() - 1;
			}
		}
	}

	for (int cols = 0; cols < 4; cols++) {
		for (int rows = 0; rows < 2; rows++) {
			auto vector = VerticMatches(rows, cols);
			if (vector->size() > 2) {
				VectorOfVectors->push_back(vector);
				rows += vector->size() - 1;
			}
		}
	}

	return VectorOfVectors;
}

bool TestWidget::LookForPossibles() {
	int mustHave[2] = {0,2};
	int needOne[][2] = {{-1, 1},
						{1, 1}};

	
	if (MatchPattern(1, 1, mustHave, needOne)) return true;
	
	return false;
}

bool TestWidget::MatchPattern(int rows, int cols, int mustHave[2], int needOne[][2]) {
	auto texture = GameField[rows][cols]->GetTexture();
	if (!MatchType(rows + mustHave[0], cols + mustHave[1], texture)) return false;

	return true;
}

bool TestWidget::MatchType(int rows, int cols, Render::Texture *tex) {
	
	if ((rows < 0) || (rows > 4) || (cols < 0) || (cols > 4)) return false;
	
	if (GameField[rows][cols] != NULL) {
		auto newTex = GameField[rows][cols]->GetTexture();
			if (tex == newTex) return true;
	}
	
	return false;
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
