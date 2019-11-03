#pragma once


class Icons
{
public:
	Icons(Render::Texture *tex, const IPoint &position);
	~Icons();
	static std::shared_ptr<Icons> Create(Render::Texture *tex, const IPoint &position);
	void Draw();
	void Update(float dt);
	double GetSize();
	bool MouseDown(const IPoint &mouse_pos);
	void MakeLight();
	std::vector<std::string> check;
	std::string thatName;
	std::vector<int> locations;
	IRect GetRectangle();
	IPoint GetPosition();
	std::string GetName();
	Render::Texture *GetTexture();
	void SetNewPosition(IPoint newPosition);
	void Push();
	std::shared_ptr<Icons> firstIcons;
	std::shared_ptr<Icons> secondIcons;
	void setNewTexture(Render::Texture *newTex);
	void DisableLight();
	bool _visiable;
	void HideIcon();
	void Mark();
	bool _marked;
	bool _markedToDelete;
	void markToDelete();
	void Marking();
	bool _isMarkedToDelete();
private:
	Render::Texture *_tex;
	IPoint _position;
	IRect _rect;
	std::vector<IPoint> points;

	bool _pushed;
};

