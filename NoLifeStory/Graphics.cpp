///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

SDL_Surface* screen;

void init_graphics() {
	SDL_Init(SDL_INIT_EVERYTHING);
#define glAttr SDL_GL_SetAttribute
	glAttr(SDL_GL_ACCELERATED_VISUAL, 1);
	glAttr(SDL_GL_DOUBLEBUFFER, 1);
#ifdef NLS_WINDOWS
	glAttr(SDL_GL_STEREO, 1);
#endif
#undef glAttr
#ifdef NLS_WINDOWS
	HANDLE hIcon = LoadIconW(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_NOLIFESTORY_ICON));
	SDL_SysWMinfo SysInfo;
	SDL_VERSION(&SysInfo.version);
	HWND hWnd = 0;
	if (SDL_GetWMInfo(&SysInfo) <= 0) {
		printf("%s : %d\n", SDL_GetError(), SysInfo.window);
	} else {
		hWnd = SysInfo.window;
	}
#endif
	SDL_SetVideoMode(800, 600, 32, SDL_OPENGL|SDL_HWSURFACE);
	SDL_ShowCursor(SDL_DISABLE);
#ifdef NLS_WINDOWS
	if (hWnd) {
		::SendMessageW(hWnd, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
		::SendMessageW(GetConsoleWindow(), WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
	}
#endif
	SDL_WM_SetCaption("NoLifeStory", NULL);
	glClearColor(0, 0, 0, 0); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapBuffers();
	if (glGetError()!=GL_NO_ERROR) {
		cout << "ERROR initializing graphics: " << (int)glGetError() << endl;
	}
}