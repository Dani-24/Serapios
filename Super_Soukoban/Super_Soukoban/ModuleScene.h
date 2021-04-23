#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

	// Loads the textures for the background
	bool Start() override;

	// Updates the scene's background animations
	update_status Update(int arr[10][16]) ;
	//update_status Update() override;
	// Renderiza
	update_status PostUpdate() override;

public:

private:
	SDL_Texture* background = nullptr;
	SDL_Texture* wall = nullptr;
	SDL_Texture* wall2 = nullptr;
	SDL_Texture* ground = nullptr;
	SDL_Texture* point = nullptr;

	int map[16][10];
};

#endif // __MODULE_SCENE_H__