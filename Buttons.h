#pragma once

class Buttons {
public:
	Buttons(Render::Texture *tex, const IPoint &position);
	~Buttons();
	void Draw();
	static std::unique_ptr<Buttons> Create(Render::Texture *tex, const IPoint &position);

private:
	Render::Texture* _tex;
	IPoint _position;
};