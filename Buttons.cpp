#include "stdafx.h"
#include "Icons.h"
#include "Buttons.h"

Buttons::Buttons(Render::Texture *tex, const IPoint &position) :
	_tex(tex),
	_position(position),
	_isLight(false)
{

}

Buttons::~Buttons(){

}

void Buttons::Draw(){
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_position);
	Render::device.MatrixTranslate(-_tex->_rect_width * 0.5f, -_tex->_rect_height * 0.5f, 0);
	_tex->Draw();
	Render::device.PopMatrix();
}

std::unique_ptr<Buttons> Buttons::Create(Render::Texture * tex, const IPoint & position){
	
	return std::unique_ptr<Buttons>(new Buttons(tex, position));
}

IRect Buttons::GetRect() {
	
	if (_tex != NULL) {
		auto rect = _tex->getBitmapRect();
		_rect = IRect(IRect(_position.x - rect.width * 0.5f, _position.y - rect.height * 0.5f, rect.width, rect.height));
	}
	return _rect;
}

bool Buttons::MouseDown(const IPoint &mouse_pos) {
	if (GetRect().Contains(mouse_pos)) {
		MakeLigth();
		return true;
	}
	return false;
}

void Buttons::Light() {
	Render::device.SetBlendMode(BlendMode::Add);
	Render::BeginAlphaMul(0.5);
	_tex->Draw();
	Render::EndAlphaMul();
	Render::device.SetBlendMode(BlendMode::Alpha);
}

void Buttons::MakeLigth() {
	_isLight = true;
}