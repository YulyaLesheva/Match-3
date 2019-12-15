#pragma once


class Icons
{
public:
	Icons(Render::Texture *tex, const IPoint &position, int row, int col);
	~Icons();
	static std::shared_ptr<Icons> Create(Render::Texture *tex, const IPoint &position, int row, int col);
	void Draw();
	void SetPosition(IPoint &newPosition);
	float Icons::GetSize();
	Render::Texture* GetTexture();
	void SetNewTexture(Render::Texture *newTex);
	IRect GetRect();
	bool MouseDown(const IPoint &mouse_pos);
	void Light();
	void MakeLigth();
	bool IsLigth();
	bool _isLight;
	bool _marked;
	bool IsMarked();
	void Mark();
	void MarkOff();
	int ReturnRow();
	int ReturnCol();
	void DisableLigth();
	void SetRow(int r);
	void SetCol(int c);
	
private:
	Render::Texture *_tex;
	IPoint _position;
	IRect _rect;
	int _rows, _cols;

};

