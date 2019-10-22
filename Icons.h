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
	bool MouseDown(const IPoint &mouse_pos);
	void MakeLight();
	std::vector<std::string> check;
	std::string thatName;
	std::string returnThatName();
	IPoint ourPos;
	IPoint GetPosition();
	IPoint GlobalPosition;

	int counter;
private:
	Render::Texture *_tex;
	IPoint _position;
	IRect _rect;
	std::vector<IPoint> points;

	bool _pushed;
};

