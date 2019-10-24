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
	const int row, col;
	using IconsVector = std::vector<std::unique_ptr<Icons>>;
	IconsVector _icons;
	std::shared_ptr<Icons> cell[4][4];
	std::vector<std::shared_ptr<Icons>> savedIcons;
	std::vector<IPoint> savedPositions;
	std::vector<std::string> savedNames;
	std::vector<Render::Texture*> savedTextures;
	float x, y;
};
