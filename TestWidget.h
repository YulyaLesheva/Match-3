#pragma once

///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///

class Background;
class Icons;

#define ptr(t) \
std::unique_ptr<t>


class TestWidget : public GUI::Widget
{
public:
	TestWidget(const std::string& name, rapidxml::xml_node<>* elem);

	void Draw() override;
	void Update(float dt) override;
	
	void AcceptMessage(const Message& message) override;
	
	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;

	void KeyPressed(int keyCode) override;
	void CharPressed(int unicodeChar) override;

private:
	void Init();
	void AffectAbove();
	void MakeSwap(std::vector<std::shared_ptr<Icons>> iconsToSwipe);
	void EndGame();
	void CreateGameField();

	bool LookForPossibles();
	bool MatchPattern(int rows, int cols, int mustHave[], std::vector<std::vector<int>> myVectorNeedOne);
	bool MatchType(int rows, int cols, Render::Texture *tex);
	bool CheckNeighbors();

	std::vector<std::vector<std::shared_ptr<Icons>>> LookForMatches();
	std::vector<std::shared_ptr<Icons>> VerticMatches(int rows, int cols);
	std::vector<std::shared_ptr<Icons>> HorizMatches(int rows, int cols);

	std::shared_ptr<Icons> SetRandomIcon(IPoint& position);
	

private:
	ptr(Background) _background;

	float _iconsSide;
	float _x, _y;
	int _col, _row;
	
	std::vector<std::vector<std::shared_ptr<Icons>>*> _VectorForDelete;
	std::vector<std::shared_ptr<Icons>> _vector;
	std::vector<std::shared_ptr<Icons>> _savedTiles;
	std::shared_ptr<Icons> GameField[4][4];
};
