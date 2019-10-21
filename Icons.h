#pragma once


class Icons
{
public:
	Icons(Render::Texture *tex, const IPoint &position);
	~Icons();
	static std::unique_ptr<Icons> Create(Render::Texture *tex, const IPoint &position);
	void Draw();
	void Update(float dt);
	double GetSize();
	std::string GetName();
	bool MouseDown(const IPoint &mouse_pos);
private:
	Render::Texture *_tex;
	IPoint _position;
	IRect _rect;
	int r, g, b;
};

