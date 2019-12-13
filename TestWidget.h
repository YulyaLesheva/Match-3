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
	std::shared_ptr<Icons> SetRandomIcon(IPoint& position);
private:
	ptr(Background) _background;
	std::shared_ptr<Icons> GameRow[4];
	std::shared_ptr<Icons> GameField[4][4];
	float x, y;
	int col, row;
	int rw;
	float _iconsSide;
	void LookForMatches(int rows, int cols);
	
	std::vector<std::vector<std::shared_ptr<Icons>>*> VectorForDelete;
	std::vector<std::vector<std::shared_ptr<Icons>>*> VectorForDelete1;
	std::vector<std::shared_ptr<Icons>>* vector;
	std::vector<std::vector<std::shared_ptr<Icons>>*>* LookForMatches();
	std::vector<std::shared_ptr<Icons>>* VerticMatches(int rows, int cols);
	std::vector<std::shared_ptr<Icons>>* HorizMatches(int rows, int cols);
	bool LookForPossibles();
	bool MatchPattern(int rows, int cols, int mustHave[], std::vector<std::vector<int>> myVectorNeedOne);
	bool MatchType(int rows, int cols, Render::Texture *tex);
	void createGameField();
};
