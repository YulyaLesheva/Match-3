#pragma once

///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///
class Background;
class TextLabels;

#define ptr(t) \
std::unique_ptr<t>

class BackgroundnWidget : public GUI::Widget
{
public:
	BackgroundnWidget(const std::string& name, rapidxml::xml_node<>* elem);

	void Draw() override;
	void Update(float dt) override;
	
	void AcceptMessage(const Message& message) override;
	
	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;

	void KeyPressed(int keyCode) override;
	void CharPressed(int unicodeChar) override;
	void RestartGame();

private:
	void Init();

private:
	ptr(Background) _background;
	ptr(Background) _fone;
	ptr(Background) _someShit;
};
