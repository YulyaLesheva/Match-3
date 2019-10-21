#include "stdafx.h"
#include "Icons.h"

Icons::Icons(Render::Texture *tex, const IPoint &position) :
	_tex(tex),
	_position(position),
	r(0)
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
	
	return  _tex->_bitmap_height * .625;
}

std::string Icons::GetName() {

	return _tex->GetName();
}

bool Icons::MouseDown(const IPoint & mouse_pos)
{
	_rect = IRect(_position, _tex->Width() * .625, _tex->Height() * 0.625);
	
	if (_rect.Contains(mouse_pos)) {
			return true;
	}
	
	return false;
}
