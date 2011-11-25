////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

sf::Font* font;

void NLS::Text::Init() {
	font = new sf::Font();
	font->LoadFromFile("font.ttf");
}
void NLS::Text::Unload() {
	delete font;
}
u32string NLS::Text::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	static char32_t s[2] = {0xFFFFFF, 0};
	static uint8_t* c = (uint8_t*)&s[1];
	c[0] = r;
	c[1] = g;
	c[2] = b;
	c[3] = a;
	return u32string(s, 2);
}
NLS::Text::Text(u32string str, int size) {
	text = str;
	fsize = size;
	for (int i = 0; i < text.size(); ++i) {
		font->GetGlyph(text[i], fsize, false);
	}
}

int NLS::Text::Width() {
	int xx = 0;
	int yy = fsize;
	char32_t prev = 0;
	int space = font->GetGlyph(' ', fsize, false).Advance;
	for (int i = 0; i < text.size(); ++i) {
		char32_t cur = text[i];
		if (cur == 0xFFFFFF) {
			++i;
			continue;
		}
		xx += font->GetKerning(prev, cur, fsize);
		prev = cur;
		switch (cur) {
			case L' ' :  xx += space;              continue;
			case L'\t' : xx += space * 4;          continue;
			//case L'\n' : y += lineSpacing; x = 0; continue;
			//case L'\v' : y += lineSpacing * 4;    continue;
		}
		const auto& glyph = font->GetGlyph(cur, fsize, false);
		const auto& advance = glyph.Advance;
		xx += advance;
	}
	return xx;
}

int NLS::Text::Height() {
	return fsize;
}

void NLS::Text::Draw(int x, int y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	const auto& tex = font->GetTexture(fsize);
	int xx = 0;
	int yy = fsize;
	char32_t prev = 0;
	int space = font->GetGlyph(' ', fsize, false).Advance;
	int linespace = font->GetLineSpacing(fsize);
	glColor4f(0, 0, 0, 1);
	tex.Bind();
	glBegin(GL_QUADS);
	for (int i = 0; i < text.size(); ++i) {
		char32_t cur = text[i];
		xx += font->GetKerning(prev, cur, fsize);
		if (cur == 0xFFFFFF) {
			uint8_t* c = (uint8_t*)&text[++i];
			glColor4ub(c[0], c[1], c[2], c[3]);
			continue;
		}
		prev = cur;
		switch (cur) {
			case ' ' :  xx += space;              continue;
			case '\t' : xx += space * 4;          continue;
			//case '\n' : y += lineSpacing; x = 0; continue;
			//case '\v' : y += lineSpacing * 4;    continue;
		}
		const auto& glyph = font->GetGlyph(cur, fsize, false);
		const auto& advance = glyph.Advance;
		const auto& b = glyph.Bounds;
		const auto& c = tex.GetTexCoords(glyph.SubRect);
		glTexCoord2f(c.Left, c.Top);
		glVertex2i(xx+b.Left, yy+b.Top);
		glTexCoord2f(c.Left+c.Width, c.Top);
		glVertex2i(xx+b.Left+b.Width, yy+b.Top);
		glTexCoord2f(c.Left+c.Width, c.Top+c.Height);
		glVertex2i(xx+b.Left+b.Width, yy+b.Top+b.Height);
		glTexCoord2f(c.Left, c.Top+c.Height);
		glVertex2i(xx+b.Left, yy+b.Top+b.Height);
		xx += advance;
	}
	glEnd();
	glPopMatrix();
}