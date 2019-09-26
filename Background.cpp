#include "stdafx.h"
#include "Background.h"


Background::Background() 
{
	
}
Background::Background(Render::Texture *tex)
{
	_tex = tex;
}

Background::~Background()
{
}


void Background::Draw() {
	_tex->Draw();
}

void Background::Update(float dt) {


}

Background* Background::Create(Render::Texture  *tex) {
	
	Background *bgg = new Background(tex);
	
	return bgg;

}