////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

sf::Window* NLS::window = 0;
bool NLS::Fullscreen = false;
bool NLS::Graphics::NPOT = true;
bool NLS::Graphics::Shit = false;

void NLS::Graphics::Init() {
	if (window) {
		window->Create(sf::VideoMode(800, 600), "NoLifeStory::Loading", sf::Style::Titlebar|(Fullscreen?sf::Style::Fullscreen:0));
	} else {
		window = new sf::Window(sf::VideoMode(800, 600), "NoLifeStory::Loading", sf::Style::Titlebar|(Fullscreen?sf::Style::Fullscreen:0));
	}
	glewExperimental = true;
	GLenum error = glewInit();
	switch (error) {
	case GLEW_OK:
		cout << "GLEW initialized" << endl;
		break;
	case GLEW_ERROR_NO_GL_VERSION:
		cerr << "Unable to detect OpenGL version.";
		throw(273);
		break;
	case GLEW_ERROR_GL_VERSION_10_ONLY:
		cerr << "You only have OpenGL 1.0. What a fail.";
		throw(273);
		break;
	case GLEW_ERROR_GLX_VERSION_11_ONLY:
		cerr << "You only have GLX 1.1. What a fail.";
		throw(273);
		break;
	default:
		cerr << "GLEW has given me an unknown error code so I'll just abort. (Error: " << (int)error << ")";
		throw(273);
		break;
	}
#ifdef NLS_WINDOWS
	HANDLE hIcon = LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCEW(IDI_NOLIFESTORY_ICON));
	HWND hWnd = window->GetSystemHandle();
	if (hWnd) {
		::SendMessageW(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	}
#endif
	window->ShowMouseCursor(false);
	window->EnableKeyRepeat(true);
	glClearColor(0, 0, 0, 0); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	if (Mindfuck) {
		glEnable(GL_COLOR_LOGIC_OP);
		glLogicOp(GL_OR);
	}
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	window->Display();
	if (!GLEW_VERSION_1_2) {
		cerr << "Seriously. You don't have OpenGL 1.2? Maybe you forgot to install drivers for your gpu? Wait a second, do you even HAVE a gpu? Seriously, get a job and buy a graphics card." << endl;
		Shit = true;
	}
	if (!GLEW_ARB_texture_non_power_of_two and !GLEW_VERSION_2_0) {
		cerr << "Missing support for NPOT textures. Using slower backward's compatible code. Please upgrade your graphics card and/or drivers when you get a chance." << endl;
		NPOT = false;
	}
}

void NLS::Graphics::Draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	View::Step();
	Portal::Update();
	if (Mindfuck) {
		srand(floor(Time::tdelta*3));
		rand();
		float r = rand()*(1-fmod(Time::tdelta*3, 1));
		float g = rand()*(1-fmod(Time::tdelta*3, 1));
		float b = rand()*(1-fmod(Time::tdelta*3, 1));
		srand(floor(Time::tdelta*3)+1);
		rand();
		r += rand()*fmod(Time::tdelta*3, 1);
		g += rand()*fmod(Time::tdelta*3, 1);
		b += rand()*fmod(Time::tdelta*3, 1);
		r /= RAND_MAX;
		g /= RAND_MAX;
		b /= RAND_MAX;
		glColor4f(r, g, b, 1);
		srand(Time::tdelta*10000);
		if ((double)rand()/RAND_MAX < 0.2) {
			glLogicOp(GL_XOR);
		} else {
			glLogicOp(GL_OR);
		}
	}
	Map::Draw();
	View::Reset();
	UI::Draw();
	Mouse::Draw();
	Time::Step();
	if (Map::fade > 0) {
		glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, 0);
		glColor4f(Map::fade, Map::fade, Map::fade, 0);
		glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(View::width, 0);
		glVertex2i(View::width, View::height);
		glVertex2i(0, View::height);
		glEnd();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);
		Map::fade -= 2*Time::delta;
	}
	window->SetTitle("NoLifeStory::FrameRate = "+tostring((int)Time::fps));
	window->Display();
#ifdef DEBUG
	switch (glGetError()) {
	case GL_NO_ERROR:
		break;
	default:
		cerr << "OH GOD OPENGL FAILED" << endl;
	}
#endif
}