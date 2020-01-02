#include "stdafx.h"
#include "Background.h"


Background::Background(Render::Texture *tex, const IPoint &position) :
	_tex(tex),
	_position(position),
	_needToScale(false)
{
}

Background::~Background()
{
}


void Background::Draw() {

	Render::device.PushMatrix();
	
	Render::device.MatrixTranslate(_position);
	Render::device.MatrixTranslate(-_tex->_rect_width * 0.5f, -_tex->_rect_height * 0.5f, 0);
	_tex->Draw();
	Render::device.PopMatrix();
}

void Background::Scale() {
	_needToScale = true;
}

IPoint Background::GetPosition() {
	return _position;
}

void Background::Update(float dt) {

}


std::unique_ptr<Background> Background::Create(Render::Texture *tex, const IPoint &position) {
	
	return std::unique_ptr<Background>(new Background(tex, position));;
}