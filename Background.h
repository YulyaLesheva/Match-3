#pragma once


class Background
{
public:
	Background();
	Background(Render::Texture *tex);
	~Background();
	void Draw();
	void Update(float dt);
	std::unique_ptr <Background> pidor;
	static Background* Create(Render::Texture *tex);
	Render::Texture* _tex;
private:

};

