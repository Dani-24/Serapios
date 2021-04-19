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

	// Loads the necessary textures for the map background
	bool Start() override;

	// Updates the scene's background animations
	update_status Update() override;

	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;
};

#endif // __MODULE_SCENE_H__