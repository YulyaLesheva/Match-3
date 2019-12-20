#pragma once

class Buttons {
public:
	Buttons(Render::Texture *tex, const IPoint &position);
	~Buttons();
	void Draw();
	static std::unique_ptr<Buttons> Create(Render::Texture *tex, const IPoint &position);
	bool MouseDown(const IPoint &mouse_pos);
	IRect GetRect();
	void Light();
	void MakeLigth();
private:
	Render::Texture* _tex;
	IPoint _position;
	IRect _rect;
	bool _isLight;
};