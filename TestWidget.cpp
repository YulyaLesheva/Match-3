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
	y(0)
{
	Init();
}

void TestWidget::Init() {
	
	_background = Background::Create(Core::resourceManager.Get<Render::Texture>("bg"), IPoint(Render::device.Width()*.5, Render::device.Height()*.5));

	while (true) {
		testRow = 0;
		x = 0;
		y = 960 - 256 * .625;
		for (int r = 0; r < row; r++) {
			x = 0;
			y -= _iconsSide;
			for (int c = 0; c < col; c++) {
				GameField[r][c] = SetRandomIcon(IPoint(x, y));
				GameField[r][c]->SetCol(c);
				GameField[r][c]->SetRow(r);
				x += _iconsSide;
			}
		}
		if (!LookForMatches().empty()) continue;
		if (LookForPossibles() == false) continue;

		break;
	}
	
	/*
	x = 0;
	y = 0;

	GameField[0][0] = Icons::Create(Core::resourceManager.Get<Render::Texture>("milk"), IPoint(0, 960 - _iconsSide * 2));
	GameField[0][1] = Icons::Create(Core::resourceManager.Get<Render::Texture>("apple"), IPoint(x + _iconsSide * 1, 960 - _iconsSide * 2));
	GameField[0][2] = Icons::Create(Core::resourceManager.Get<Render::Texture>("orange"), IPoint(x + _iconsSide * 2, 960 - _iconsSide * 2));
	GameField[0][3] = Icons::Create(Core::resourceManager.Get<Render::Texture>("bread"), IPoint(x + _iconsSide * 3, 960 - _iconsSide * 2));


	GameField[1][0] = Icons::Create(Core::resourceManager.Get<Render::Texture>("apple"), IPoint(0, 960 - _iconsSide * 3));
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
	*/
	bool check =false;
	auto v = LookForMatches();
	check = LookForPossibles();
	
}

std::vector<std::shared_ptr<Icons>> TestWidget::VerticMatches(int rows, int cols) {
	
	std::vector<std::shared_ptr<Icons>> vector;

	vector.push_back(GameField[rows][cols]);
	for (int i = 1; rows + i < 4; i++) {
		if (vector.back()->GetTexture() == GameField[rows+i][cols]->GetTexture()) {
			vector.push_back(GameField[rows+i][cols]);
		}
		else return vector;
	}
	return vector;
}


std::vector<std::shared_ptr<Icons>> TestWidget::HorizMatches(int rows, int cols) {
	
	std::vector<std::shared_ptr<Icons>> vector;

	vector.push_back(GameField[rows][cols]);
	for (int i = 1; cols + i < 4; i++) {
		if (vector.back()->GetTexture() == GameField[rows][cols+i]->GetTexture()) {
			vector.push_back(GameField[rows][cols + i]);
		}
		else return vector;
	}
	return vector;
}

std::vector<std::vector<std::shared_ptr<Icons>>> TestWidget::LookForMatches() {
	
	std::vector<std::vector<std::shared_ptr<Icons>>> VectorOfVectors;

	for (int rows = 0; rows < 4; rows++) {
		for (int cols = 0; cols < 2; cols++) {
			auto vector = HorizMatches(rows,cols);
			if (vector.size()>2) {
				VectorOfVectors.push_back(vector);
				cols += vector.size() - 1;
			}
		}
	}

	for (int cols = 0; cols < 4; cols++) {
		for (int rows = 0; rows < 2; rows++) {
			auto vector = VerticMatches(rows, cols);
			if (vector.size() > 2) {
				VectorOfVectors.push_back(vector);
				rows += vector.size() - 1;
			}
		}
	}

	return VectorOfVectors;
}

void TestWidget::AffectAbove() {

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (GameField[r][c]->GetTexture()==NULL) {
				for (int i = r; i >= 0; i--) {
					if (i>0) {
						GameField[i][c]->SetNewTexture(GameField[i-1][c]->GetTexture());
					}
					else {
						GameField[i][c]->SetNewTexture(Core::resourceManager.Get<Render::Texture>(Random::GetRandomTile()));
					}
				}
			}
		}
	}
	
}

bool TestWidget::LookForPossibles() {
	int mustHave1[2] = {0,2};
	std::vector<std::vector<int>> myVectorNeedOne1 ={{-1,1},{1,1}};

	int mustHave2[2] = {0,1};
	std::vector<std::vector<int>> myVectorNeedOne2 = {{0,-2},{-1,-1},{1,-1},{-1,2},{1,2},{0,3}};

	int mustHave3[2] = {1,0};
	std::vector<std::vector<int>> myVectorNeedOne3 = {{-2, 0},{-1,-1},{-1,1},{2,-1},{2,1},{3,0}};

	int mustHave4[2] = {2,0};
	std::vector<std::vector<int>> myVectorNeedOne4 = {{1,-1},{1,1}};

	for (int rows = 0; rows < 4; rows++) {
		for (int cols = 0; cols < 4;cols++) {
			if (MatchPattern(rows, cols, mustHave1, myVectorNeedOne1)) return true;// гориз, две по разным сторонам

			if (MatchPattern(rows, cols, mustHave2, myVectorNeedOne2)) return true;// гориз, две подряд

			if (MatchPattern(rows, cols, mustHave3, myVectorNeedOne3)) return true;// вертик, две подряд

			if (MatchPattern(rows, cols, mustHave4, myVectorNeedOne4)) return true;// вертик, две по разным сторонам
		}
	}

	return false;
}

bool TestWidget::MatchPattern(int rows, int cols, int mustHave[], std::vector<std::vector<int>> myVectorNeedOne) {
	
	auto texture = GameField[rows][cols]->GetTexture();
	if (!MatchType(rows + mustHave[0], cols + mustHave[1], texture)) return false;

	int sizeofv = myVectorNeedOne.size();

	for (int i = 0; i <sizeofv; i++) {
		if (MatchType(rows + myVectorNeedOne[i][0], cols + myVectorNeedOne[i][1], texture)) {
			return true;
		}
	}

	return false;
}

bool TestWidget::MatchType(int rows, int cols, Render::Texture *tex) {
	
	if ((rows < 0) || (rows >= 4) || (cols < 0) || (cols >= 4)) return false;
	
	if (GameField[rows][cols] != NULL) {
		auto newTex = GameField[rows][cols]->GetTexture();
			if (tex == newTex) return true;
	}
	
	return false;
}


std::shared_ptr<Icons> TestWidget::SetRandomIcon(IPoint& position) {
	auto icon = Icons::Create(Core::resourceManager.Get<Render::Texture>(Random::GetRandomTile()), IPoint(position), 0, 0);
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

void TestWidget::Update(float dt) {
	
	if (savedTiles.size()==2) {
		CheckNeighbors();
	}

	if (!LookForMatches().empty()) {
		auto mmmmmm = LookForMatches();
		
		for (auto i : mmmmmm.front()) {
			i->MakeUnvisiable();
		}
	}
	AffectAbove();
}

bool TestWidget::CheckNeighbors() {

	if (savedTiles.front()->ReturnRow()==savedTiles.back()->ReturnRow() && savedTiles.front()->ReturnCol()==savedTiles.back()->ReturnCol()) {
		for (auto &t : savedTiles) {
			t->DisableLigth();
			t->MarkOff();
		}
		savedTiles.clear();
		return true;
	}
	
	 else if (savedTiles.front()->ReturnRow()==savedTiles.back()->ReturnRow() && abs(savedTiles.front()->ReturnCol() - savedTiles.back()->ReturnCol()) ==1) {
		MakeSwap(savedTiles);
		for (auto &t : savedTiles) {
			t->DisableLigth();
			t->MarkOff();
		}
		savedTiles.clear();
		return true;
	}

	 else if (savedTiles.front()->ReturnCol() == savedTiles.back()->ReturnCol() && abs(savedTiles.front()->ReturnRow() - savedTiles.back()->ReturnRow()) == 1) {
		MakeSwap(savedTiles);
		for (auto &t : savedTiles) {
			t->DisableLigth();
			t->MarkOff();
		}
		savedTiles.clear();
		return true;
	}

	 else {
		for (auto &t : savedTiles) {
			t->DisableLigth();
			t->MarkOff();
		}
		savedTiles.clear();
		return true;
	}
	
	return false;
}

bool TestWidget::MouseDown(const IPoint &mouse_pos){	

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			GameField[r][c]->MouseDown(mouse_pos);
			if (GameField[r][c]->IsMarked()) {
			savedTiles.push_back(GameField[r][c]);	
			GameField[r][c]->MarkOff();
			}
		}
	}

	return false;
}

void TestWidget::MakeSwap(std::vector<std::shared_ptr<Icons>> iconsToSwipe) {
	auto firstTex = iconsToSwipe.front()->GetTexture();
	auto secondTex = iconsToSwipe.back()->GetTexture();
	
	iconsToSwipe.front()->SetNewTexture(secondTex);
	iconsToSwipe.back()->SetNewTexture(firstTex);

	if(LookForMatches().empty()){
		iconsToSwipe.front()->SetNewTexture(firstTex);
		iconsToSwipe.back()->SetNewTexture(secondTex);

	}
}

void TestWidget::EndGame() {
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
