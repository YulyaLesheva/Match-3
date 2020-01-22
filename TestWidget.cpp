#include "stdafx.h"
#include "TestWidget.h"
#include "Background.h"
#include "Icons.h"
#include "RandomTile.h"
#include "Score.h"

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name),
	_col(4),
	_row(4),
	_iconsSide(256 * .625),
	_x(0),
	_y(0),
	_endGame(false)
	
{
	Init();
}

void TestWidget::Init() {

	_scoreTable = Score::CreateScore(IPoint(Render::device.Width()*.5, 120.f));
	CreateGameField();
}
void TestWidget::CreateGameField() {
	
	while (true) {
		_x = 0;
		_y = 960 - 256 * .625;
		for (int r = 0; r < _row; r++) {
			_x = 0;
			_y -= _iconsSide;
			for (int c = 0; c < _col; c++) {
				GameField[r][c] = SetRandomIcon(IPoint(_x, _y));
				GameField[r][c]->SetCol(c);
				GameField[r][c]->SetRow(r);
				_x += _iconsSide;
			}
		}
		if (!LookForMatches().empty()) continue;
		if (LookForPossibles() == false) continue;

		break;
	}
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

	_scoreTable->Draw();

	for (int r = 0; r < _row; r++) {
		for (int c = 0; c < _col; c++) {
			GameField[r][c]->Draw();
		}
	}
	
	/*IPoint mouse_pos = Core::mainInput.GetMousePos();
	Render::BindFont("Wingko");
	Render::PrintString(IPoint(50, 50), utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y));
	*/
}

void TestWidget::Update(float dt) {
	
	IsAllowToMakeSwap();
	FindRemoveAndAddNewPieces();

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			GameField[r][c]->Update(dt);
		}
	}

	if (LookForPossibles() == false && LookForMatches().empty()) EndGame();
}

bool TestWidget::AllField() {
	for (int i = 0; i < 4;i++) {
		for (int j = 0; j < 4; j++) {
			auto tex = GameField[i][j]->GetTexture();
			if (tex == NULL) {
				return false;
			}
		}
	}
	return true;
}

void TestWidget::IsAllowToMakeSwap() {
	if (_savedTiles.size() == 2) {
		CheckNeighbors();
	}
}
void TestWidget::FindRemoveAndAddNewPieces() {
	
	if (!LookForMatches().empty()) {
		auto findedMatches = LookForMatches();
		_scoreTable->IncreaseScore(findedMatches.front().size());

		if (findedMatches.size() > 1) {
			_scoreTable->IncreaseScore(findedMatches.back().size());

		}

		for (auto i : findedMatches.front()) {
			i->MakeUnvisiable();
		}

		if (findedMatches.size()>1) {
			for (auto i : findedMatches.back()) {
				i->MakeUnvisiable(); /// для двойных совпадений. нужен тест
			}
		}

		AffectAbove();
	}
}


bool TestWidget::CheckNeighbors() {

	if (_savedTiles.front()->ReturnRow()==_savedTiles.back()->ReturnRow() && _savedTiles.front()->ReturnCol()==_savedTiles.back()->ReturnCol()) {
		MakeSwap(_savedTiles);
		Swapped();
		return true;
	}
	
	 else if (_savedTiles.front()->ReturnRow()==_savedTiles.back()->ReturnRow() && abs(_savedTiles.front()->ReturnCol() - _savedTiles.back()->ReturnCol()) ==1) {
		MakeSwap(_savedTiles);
		Swapped();
		return true;
	}

	 else if (_savedTiles.front()->ReturnCol() == _savedTiles.back()->ReturnCol() && abs(_savedTiles.front()->ReturnRow() - _savedTiles.back()->ReturnRow()) == 1) {
		MakeSwap(_savedTiles);
		Swapped();
		return true;
	}

	 else {
		Swapped();
		return true;
	}
	
	return false;
}

void TestWidget::Swapped() {

	for (auto &t : _savedTiles) {
		t->DisableLigth();
		t->MarkOff();
	}
	_savedTiles.clear();
}

void TestWidget::RestartGame() {
	_scoreTable->ResetScore();
	_savedTiles.clear();
	_vector.clear();
	CreateGameField();
	_endGame = false;
	_scoreTable->SetPosition(IPoint(Render::device.Width()*.5, 120.f));
	Core::guiManager.getLayer("TestLayer")->getWidget("EndGameWidget")->AcceptMessage(Message("RestartGame", std::to_string(_scoreTable->ReturnScore())));
}

bool TestWidget::MouseDown(const IPoint &mouse_pos){	
	
	if (_endGame) return false;

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			GameField[r][c]->MouseDown(mouse_pos);
			if (GameField[r][c]->IsMarked()) {
			_savedTiles.push_back(GameField[r][c]);	
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
	Core::guiManager.getLayer("TestLayer")->getWidget("EndGameWidget")->AcceptMessage(Message("EndGame", std::to_string(_scoreTable->ReturnScore())));
	_endGame = true;
	BlurIcons();
}

void TestWidget::BlurIcons() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			GameField[i][j]->Trans();
		}
	}
}

void TestWidget::MouseMove(const IPoint &mouse_pos)
{
}

void TestWidget::MouseUp(const IPoint &mouse_pos)
{
}

void TestWidget::AcceptMessage(const Message& message){
	
	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();

	if (data == "RestartGame") {
		RestartGame();
	}
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
