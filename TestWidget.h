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
	void Swapping();

private:
	void Init();

private:
	ptr(Background) _background;
	std::shared_ptr<Icons> _icon;
	using IconsVector = std::vector<std::unique_ptr<Icons>>;
	IconsVector _icons;
	std::vector<std::shared_ptr<Icons>> iconsToRemove;
	std::shared_ptr<Icons> cell[4][4];

	std::vector<std::shared_ptr<Icons>> savedIcons;
	std::vector<std::string> savedNames;
	std::vector<std::shared_ptr<Icons>> collideVector;
	std::vector <std::string> namesCollideVector;
	std::vector<Render::Texture*> savedTextures;
	std::vector<std::shared_ptr<Icons>> neighbors;
	
	std::vector<std::shared_ptr<Icons>> row_0;
	std::vector<std::string> row_0_Names;

	std::shared_ptr<Icons> row_0_array[4];
	Render::Texture* row_0_Textures_array[4];

	std::shared_ptr<Icons> row_1_array[4];
	Render::Texture* row_1_Textures_array[4];

	std::shared_ptr<Icons> row_2_array[4];
	Render::Texture* row_2_Textures_array[4];

	std::shared_ptr<Icons> row_3_array[4];
	Render::Texture* row_3_Textures_array[4];

	bool _matchesFinded;

	void FindMatches();
	void InitGameField();
	void CheckCoincidence();
	void Replace();

	bool _replaced;
	bool _needToCheckCoincidence;
	bool _swapped;
	bool _readyToCheckRow;
	bool _readyToRemove;
	bool _ableToSwap;
	
	
	float x, y;
	const int row, col;

	Render::Texture* _textex;

	std::shared_ptr<Icons>	TEST_ICON;

};
