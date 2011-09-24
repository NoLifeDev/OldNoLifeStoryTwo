////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

sf::Window* NLS::window = 0;

void NLS::Graphics::Init() {
	window = new sf::Window(sf::VideoMode(800, 600), "NoLifeStory::Loading", sf::Style::Titlebar, sf::ContextSettings(0, 0, 0, 2, 0));
#ifdef NLS_WINDOWS
	HANDLE hIcon = LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCEW(IDI_NOLIFESTORY_ICON));
	HWND hWnd = window->GetSystemHandle();
	if (hWnd) {
		::SendMessageW(hWnd, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
	}
#endif
	window->ShowMouseCursor(false);
	window->EnableKeyRepeat(true);
	glClearColor(0, 0, 0, 0); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	window->Display();
}

void NLS::Graphics::Draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	View.Step();
	Map::Draw();
	Foothold::Draw();
	View.Reset();
	Time.Step();
	window->SetTitle("NoLifeStory::FrameRate = "+tostring((int)Time.fps));
	window->Display();
#ifdef DEBUG
	switch (glGetError()) {
	case GL_NO_ERROR:
		break;
	default:
		C("ERROR") << "OH GOD OPENGL FAILED" << endl;
	}
#endif
}