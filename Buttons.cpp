#include "stdafx.h"
#include "Icons.h"
#include "Buttons.h"

Buttons::Buttons(Render::Texture *tex, const IPoint &position):
	_tex(tex),
	_position(position)
{

}

Buttons::~Buttons(){

}

void Buttons::Draw(){
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_position);
	_tex->Draw();
	Render::device.PopMatrix();
}

std::unique_ptr<Buttons> Buttons::Create(Render::Texture * tex, const IPoint & position){
	
	return std::unique_ptr<Buttons>(new Buttons(tex, position));
}
