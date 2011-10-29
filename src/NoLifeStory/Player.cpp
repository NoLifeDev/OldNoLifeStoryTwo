////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

void NLS::Player::Draw() {
	Physics::Update();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor4f(1, 0, 1, 1);
	glBegin(GL_QUADS);
	glVertex2i(x-10,y-30);
	glVertex2i(x+10,y-30);
	glVertex2i(x+10,y);
	glVertex2i(x-10,y);
	glEnd();
}