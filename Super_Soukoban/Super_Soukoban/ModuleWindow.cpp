#include "ModuleWindow.h"
#include "Globals.h"
#include "Application.h"
#include "External_Libraries/SDL/include/SDL.h"

ModuleWindow::ModuleWindow() :Module() {

}

ModuleWindow::~ModuleWindow() {

}

bool ModuleWindow::Init() {
	LOG("SDL Window and Surface Init()");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		LOG("SDL_VIDEO could not initialize! (kboom) SDL_Error : %s\n",SDL_GetError());
		ret = false;
	}
	else {
		Uint32 flags = SDL_WINDOW_SHOWN;

		if (WIN_FULLSCREEN==true) {
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		if (WIN_BORDERLESS == true) {
			flags |= SDL_WINDOW_BORDERLESS;
		}
		if (WIN_RESIZABLE == true) {
			flags |= SDL_WINDOW_RESIZABLE;
		}
		if (WIN_FULLSCREEN_DESKTOP == true) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		window = SDL_CreateWindow("Super Soukoban", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE,flags);
	
		if (window==nullptr) {
			LOG("Window could not be created! SDL_Error: %s\n",SDL_GetError());
			ret = false;
		}
		else {
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return ret;
}

bool ModuleWindow::CleanUp() {
	LOG("Destroying SDL window and quitting all SDL systems :C")

	if (window != nullptr) {
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
	return true;
}