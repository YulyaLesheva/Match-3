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

std::unique_ptr<Icons> Icons::Create(Render::Texture * tex, const IPoint &position)
{
	return std::unique_ptr<Icons>(new Icons(tex, position));
}

void Icons::Draw() {
	
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_position);
	Render::device.MatrixScale(.625);
	_tex->Draw();
	Render::device.PopMatrix();
}

void Icons::Update(float dt){
}

double Icons::GetSize() {
	auto r = _tex->_bitmap_height * .625;
	return  r;
}

std::string Icons::GetName1() {
	auto name = _tex->GetName();
	return name;
}