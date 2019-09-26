#include "stdafx.h"
#include "Background.h"


Background::Background(Render::Texture *tex, IPoint &position)
{
	_tex = tex;
	_position = position;
}

Background::~Background()
{
}


void Background::Draw()
{
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_position);
	_tex->Draw();
	Render::device.PopMatrix();

}

void Background::Update(float dt) {

}


std::unique_ptr<Background> Background::Create(Render::Texture *tex, IPoint &position) {

	std::unique_ptr<Background> ptr(new Background(tex, position));
	
	return ptr;
}