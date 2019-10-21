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
private:
	Render::Texture *_tex;
	IPoint _position;
};

