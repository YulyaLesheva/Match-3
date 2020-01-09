#pragma once


class Icons
{
public:
	Icons(Render::Texture *tex, const IPoint &position, int row, int col);
	~Icons();
	static std::shared_ptr<Icons> Create(Render::Texture *tex, const IPoint &position, int row, int col);
	Render::Texture* GetTexture();

	void Draw();
	void SetPosition(IPoint &newPosition);
	void SetNewTexture(Render::Texture *newTex);
	void Light();
	void Update(float dt);
	void MakeLigth();
	void Mark();
	void MarkOff();
	void DisableLigth();
	void SetRow(int r);
	void SetCol(int c);
	void ChangeRowAndCol(int newRow, int newCol);
	void MakeUnvisiable();
	void SetTrans();
	int ReturnRow();
	int ReturnCol();
	
	float Icons::GetSize();
	
	IRect GetRect();
	IPoint GetPosition();

	bool MouseDown(const IPoint &mouse_pos);
	bool IsLigth();
	bool  IsVisiable();
	bool IsMarked();

	bool _isLight;
	bool _marked;
	bool _visiable;
	bool _needToTrans;
	
	IPoint _initialPos;

	void Trans();
	
private:
	Render::Texture *_tex;
	IPoint _position;
	IRect _rect;
	int _rows, _cols;

};

