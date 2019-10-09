#pragma once

class Background
{
public:
	Background(Render::Texture *tex, const IPoint &position);
	~Background();
	void Draw();
	void Update(float dt);
	static std::unique_ptr<Background> Create(Render::Texture *tex, const IPoint &position);
private:
	Render::Texture* _tex;
	IPoint _position;
};

