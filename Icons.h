#pragma once


class Icons
{
public:
	Icons(Render::Texture *tex, const IPoint &position);
	~Icons();
	static std::shared_ptr<Icons> Create(Render::Texture *tex, const IPoint &position);
	void Draw();
	float Icons::GetSize();
	Render::Texture* GetTexture();
private:
	Render::Texture *_tex;
	IPoint _position;
	IRect _rect;
};

