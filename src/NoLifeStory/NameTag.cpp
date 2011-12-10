////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"
void NLS::NameTag::Set(const string& str, Style style) {
	if (str.empty()) return;
	switch (style) {
	case Normal:
	default:
		t.Set(Text::Color(255, 255, 255)+u32(str), 12);
		break;
	case Life:
		t.Set(Text::Color(255, 255, 0)+u32(str), 12);
		break;
	}
}
void NLS::NameTag::Draw(int x, int y) {
	if (!t.Width()) return;
	int xm = t.Width()/2;
	{
		int l = x-xm-3;
		int r = x+xm+3;
		int t = y+5;
		int b = y+18;
		glColor4f(0, 0, 0, 0.7f);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_QUADS);
		glVertex2i(l, t);
		glVertex2i(r, t);
		glVertex2i(r, b);
		glVertex2i(l, b);
		glEnd();
	}
	t.Draw(x-xm, y+4);
}