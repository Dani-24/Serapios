#ifndef __MODULE_RENDER_H__
#define __MODULE_RENDER_H__

#include "Module.h"
#include "External_Libraries/SDL/include/SDL_rect.h"

struct SDL_Texture;
struct SDL_Renderer;

class ModuleRender :public Module {
public:
	ModuleRender();
	~ModuleRender();

	bool Init() override;
	update_status PreUpdate() override;		// clear
	update_status Update() override;		// camera
	update_status PostUpdate() override;	// render

	bool CleanUp() override;
	bool Blit();
	bool DrawQuad();

	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	// Colocacion Camara

	int cameraSpeed = 1; // Vel.mov. de la camara con las teclas 

};

#endif // !__MODULE_RENDER_H__
