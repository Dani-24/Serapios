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
	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = nullptr, float speed = 1.0f);
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed = 1.0f);

	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	// Colocacion Camara

	int cameraSpeed = 1; // Vel.mov. de la camara con las teclas 

};

#endif // !__MODULE_RENDER_H__
