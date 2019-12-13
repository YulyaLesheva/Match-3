#pragma once


class Icons
{
public:
	Icons(Render::Texture *tex, const IPoint &position);
	~Icons();
	static std::shared_ptr<Icons> Create(Render::Texture *tex, const IPoint &position);
	void Draw();
	void SetPosition(IPoint &newPosition);
	float Icons::GetSize();
	Render::Texture* GetTexture();
	void SetNewTexture(Render::Texture *newTex);
private:
	Render::Texture *_tex;
	IPoint _position;
	IRect _rect;
};

