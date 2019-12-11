#include "stdafx.h"
#include "Icons.h"
Icons::Icons(Render::Texture *tex, const IPoint &position) :
	_tex(tex),
	_position(position)
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
