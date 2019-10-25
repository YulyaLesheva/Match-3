#include "stdafx.h"
#include "Icons.h"

Icons::Icons(Render::Texture *tex, const IPoint &position) :
	_tex(tex),
	_position(position),
	_pushed(false)
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
	if (_pushed) MakeLight();
	Render::device.PopMatrix();
}

void Icons::MakeLight() {
	Render::device.SetBlendMode(BlendMode::Add);
	Render::BeginAlphaMul(0.2);
	_tex->Draw();
	Render::EndAlphaMul();
	Render::device.SetBlendMode(BlendMode::Alpha);
}


void Icons::Update(float dt){

}

double Icons::GetSize() {
	return  _tex->_bitmap_height * .625;
}

bool Icons::MouseDown(const IPoint & mouse_pos){
	


	return false;
}

void Icons::Push() {
	_pushed = true;
}

void Icons::DisableLight() {
	_pushed = false;
}

IRect Icons::GetRectangle() {
	auto rect = _tex->getBitmapRect();
	_rect = IRect(_position, rect.Width() * .625, rect.Height() * 0.625);

	return _rect;
}

IPoint Icons::GetPosition() {
	return _position;
}

std::string Icons::GetName() {
	return _tex->GetName();
}

Render::Texture *Icons::GetTexture() {
	return _tex;
}

void Icons::SetNewPosition(IPoint newPosition) {
	_position = newPosition;
}

void Icons::setNewTexture(Render::Texture *newTex) {
	_tex = newTex;
}