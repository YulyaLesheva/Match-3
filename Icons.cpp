#include "stdafx.h"
#include "Icons.h"

Icons::Icons(Render::Texture *tex, const IPoint &position) :
	_tex(tex),
	_position(position),
	_pushed(false),
	counter(0)
{
}

Icons::~Icons()
{
}

std::unique_ptr<Icons> Icons::Create(Render::Texture * tex, const IPoint &position)
{
	return std::unique_ptr<Icons>(new Icons(tex, position));
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
	
	if (_pushed) {
		
	}
}

std::string Icons::returnThatName() {
	return thatName;
}

double Icons::GetSize() {
	return  _tex->_bitmap_height * .625;
}

bool Icons::MouseDown(const IPoint & mouse_pos){
	
	counter++;
	points.push_back(_position);

	_rect = IRect(_position, _tex->Width() * .625, _tex->Height() * 0.625);
	
	if (_rect.Contains(mouse_pos) && counter<=2) {
		_pushed = true;
		///_position.x = 14;
		return true;
	}

	return false;
}
