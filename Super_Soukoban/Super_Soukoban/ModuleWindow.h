#ifndef _MODULE_WINDOW_H__
#define _MODULE_WINDOW_H__

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow :public Module {
public:
	ModuleWindow();
	~ModuleWindow();

	bool Init() override;
	bool CleanUp() override;

	SDL_Surface* screenSurface = nullptr;
	SDL_Window* window = nullptr;
};


#endif // !_MODULE_WINDOW_H__
