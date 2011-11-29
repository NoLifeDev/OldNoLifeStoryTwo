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

NLS::Text::Text() {
	width = 0;
	height = 0;
	tex = new sf::RenderTexture();
}

void NLS::Text::Set(u32string str, int size) {
	if (str.empty()) {
		width = 0;
		height = 0;
		return;
	}
	text = str;
	fsize = size;
	width = 0;
	height = 0;
	char32_t prev = 0;
	int x = 0;
	int y = 0;
	const auto& ftex = font->GetTexture(fsize);
	int linespace = font->GetLineSpacing(fsize);
	for (int i = 0; i < text.size(); ++i) {
		char32_t cur = text[i];
		if (cur == 0xFFFFFF) {
			++i;
			continue;
		}
		x += font->GetKerning(prev, cur, fsize);
		prev = cur;
		switch (cur) {
		case '\n':
		case '\r':
			y += linespace;
			width = max(width, x);
			x = 0;
			break;
		}
		const auto& glyph = font->GetGlyph(cur, fsize, false);
		x += glyph.Advance;
	}
	width = max(width, x);
	height = y+linespace;
	if (width == 0) {
		width = 0;
		height = 0;
		return;
	}
	x = 0;
	y = fsize;
	tex->Create(width, height);
	tex->SetActive();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_ONE, GL_ONE);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor4f(0, 0, 0, 1);
	ftex.Bind();
	glBegin(GL_QUADS);
	for (int i = 0; i < text.size(); ++i) {
		char32_t cur = text[i];
		if (cur == 0xFFFFFF) {
			uint8_t* c = (uint8_t*)&text[++i];
			glColor4ub(c[0], c[1], c[2], c[3]);
			continue;
		}
		x += font->GetKerning(prev, cur, fsize);
		prev = cur;
		switch (cur) {
		case '\n':
		case '\r':
			y += linespace;
			width = max(width, x);
			x = 0;
			continue;
		}
		const auto& glyph = font->GetGlyph(cur, fsize, false);
		const auto& advance = glyph.Advance;
		const auto& b = glyph.Bounds;
		const auto& c = ftex.GetTexCoords(glyph.SubRect);
		glTexCoord2f(c.Left, c.Top);
		glVertex2i(x+b.Left, y+b.Top);
		glTexCoord2f(c.Left+c.Width, c.Top);
		glVertex2i(x+b.Left+b.Width, y+b.Top);
		glTexCoord2f(c.Left+c.Width, c.Top+c.Height);
		glVertex2i(x+b.Left+b.Width, y+b.Top+b.Height);
		glTexCoord2f(c.Left, c.Top+c.Height);
		glVertex2i(x+b.Left, y+b.Top+b.Height);
		x += advance;
	}
	glEnd();
	tex->Display();
	window->SetActive();
}

int NLS::Text::Width() {
	return width;
}

int NLS::Text::Height() {
	return fsize;
}

void NLS::Text::Draw(int x, int y) {
	if (text.empty()) return;
	glPushMatrix();
	glTranslatef(x, y, 0);
	glColor4f(1, 1, 1, 1);
	tex->GetTexture().Bind();
	const auto& b = tex->GetTexture().GetTexCoords(sf::IntRect(0, 0, width, height));
	glBegin(GL_QUADS);
	glTexCoord2f(b.Left, b.Top);
	glVertex2i(0, 0);
	glTexCoord2f(b.Left+b.Width, b.Top);
	glVertex2i(width, 0);
	glTexCoord2f(b.Left+b.Width, b.Top+b.Height);
	glVertex2i(width, height);
	glTexCoord2f(b.Left, b.Top+b.Height);
	glVertex2i(0, height);
	glEnd();
	glPopMatrix();
}