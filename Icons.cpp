#include "stdafx.h"
#include "Icons.h"
Icons::Icons(Render::Texture *tex, const IPoint &position) :
	_tex(tex),
	_position(position),
	_isLight(false)
{
}

Icons::~Icons()
{
}

std::shared_ptr<Icons> Icons::Create(Render::Texture * tex, const IPoint &position)
{
	return std::shared_ptr<Icons>(new Icons(tex, position));
}

void Icons::Draw() {
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_position);
	Render::device.MatrixScale(.625);
	_tex->Draw();
	if(_isLight) Light();
	Render::device.PopMatrix();
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
	auto rect = _tex->getBitmapRect();
	_rect = IRect(_position, rect.Width() * .625, rect.Height() * .625);
	return _rect;
}

bool Icons::MouseDown(const IPoint &mouse_pos){
	if (GetRect().Contains(mouse_pos)) {
		MakeLigth();
		return true;
	}
	return false;
}

void Icons::Light(){
	Render::device.SetBlendMode(BlendMode::Add);
	Render::BeginAlphaMul(0.1);
	_tex->Draw();
	Render::EndAlphaMul();
	Render::device.SetBlendMode(BlendMode::Alpha);
}

void Icons::MakeLigth() {
	_isLight = true;
}

bool Icons::IsLigth() {
	return _isLight;
}