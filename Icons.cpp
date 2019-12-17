#include "stdafx.h"
#include "Icons.h"
Icons::Icons(Render::Texture *tex, const IPoint &position, int row, int col) :
	_tex(tex),
	_position(position),
	_isLight(false),
	_marked(false),
	_visiable(true),
	_cols(col),
	_rows(row)
{
}

Icons::~Icons()
{
}

std::shared_ptr<Icons> Icons::Create(Render::Texture * tex, const IPoint &position, int row, int col)
{
	return std::shared_ptr<Icons>(new Icons(tex, position, row, col));
}

void Icons::Draw() {
	if (_tex != NULL) {
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_position);
		Render::device.MatrixScale(.625);
		_tex->Draw();
		if (_isLight) Light();
		Render::device.PopMatrix();
	}
}

float Icons::GetSize() {
	return  _tex->_bitmap_height * .625;
}

Render::Texture* Icons::GetTexture() {
	return _tex;
}

void Icons::SetNewTexture(Render::Texture *newTex) {
	_tex = newTex;
}

void Icons::SetPosition(IPoint &newPosition) {
	_position = newPosition;
}

IRect Icons::GetRect() {
	if (_tex != NULL) {
		auto rect = _tex->getBitmapRect();
		_rect = IRect(_position, rect.Width() * .625, rect.Height() * .625);

	}
	return _rect;
}

bool Icons::MouseDown(const IPoint &mouse_pos){
	if (GetRect().Contains(mouse_pos)) {
		MakeLigth();
		Mark();
		return true;
	}
	return false;
}

void Icons::Light(){
	Render::device.SetBlendMode(BlendMode::Add);
	Render::BeginAlphaMul(0.5);
	_tex->Draw();
	Render::EndAlphaMul();
	Render::device.SetBlendMode(BlendMode::Alpha);
}

void Icons::MakeLigth() {
	_isLight = true;
}
void Icons::DisableLigth() {
	_isLight = false;
}

bool Icons::IsLigth() {
	return _isLight;
}

void Icons::Mark() {
	_marked = true;
}

bool Icons::IsMarked() {
	return _marked;
}

void Icons::MarkOff() {
	_marked = false;
}

int Icons::ReturnRow() {
	return _rows;
}

int Icons::ReturnCol() {
	return _cols;
}

void Icons::SetRow(int r) {
	_rows = r;
}

void Icons::SetCol(int c){
	_cols = c;
}

void Icons::ChangeRowAndCol(int newRow, int newCol) {
	_rows = newRow;
	_cols = newCol;
}

void Icons::MakeUnvisiable() {
	_tex = NULL;
	_visiable = false;
}

bool Icons::IsVisiable() {
	return _visiable;
}