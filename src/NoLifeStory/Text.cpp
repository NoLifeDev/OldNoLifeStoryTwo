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
NLS::Text::Text(const string &str, int size, TextColor clr) {
	static uint32_t s[1024];
	uint32_t* end = sf::Utf8::ToUtf32(str.begin(), str.end(), s);
	text.assign(s, end);
	fsize = size;
	color = clr;
	for (int i = 0; i < text.size(); ++i) {
		font->GetGlyph(text[i], fsize, false);
	}
}

int32_t NLS::Text::getTextWidth() {
	int32_t xx = 0;
	int32_t yy = fsize;
	uint32_t prev = 0;
	int space = font->GetGlyph(L' ', fsize, false).Advance;
	for (int i = 0; i < text.size(); ++i) {
		uint32_t cur = text[i];
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

int32_t NLS::Text::getTextHeight() {
	return fsize;
}

void NLS::Text::Draw(int x, int y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	const auto& tex = font->GetTexture(fsize);
	int xx = 0;
	int yy = fsize;
	uint32_t prev = 0;
	int space = font->GetGlyph(L' ', fsize, false).Advance;
	glColor4f(color.Red, color.Green, color.Blue, color.Alpha);
	tex.Bind();
	glBegin(GL_QUADS);
	for (int i = 0; i < text.size(); ++i) {
		uint32_t cur = text[i];
		xx += font->GetKerning(prev, cur, fsize);
		prev = cur;
		const auto& glyph = font->GetGlyph(cur, fsize, false);
		const auto& advance = glyph.Advance;
		const auto& b = glyph.Bounds;
		const auto& c = tex.GetTexCoords(glyph.SubRect);
		switch (cur) {
			case L' ' :  xx += space;              continue;
			case L'\t' : xx += space * 4;          continue;
			case L'\n' : yy += b.Height; xx = 0; continue;
			//case L'\v' : y += lineSpacing * 4;    continue;
		}
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