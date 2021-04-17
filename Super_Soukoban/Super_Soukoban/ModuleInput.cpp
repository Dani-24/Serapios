#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "External_libraries/SDL/include/SDL.h"


ModuleInput::ModuleInput() :Module() {

}

ModuleInput::~ModuleInput() {

}

bool ModuleInput::Init() {
	LOG("Init SDL input event system :)");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) {
		LOG("SDL_EVENTS could not initialize! SDL_Error:%s\n", SDL_GetError());
	}
}