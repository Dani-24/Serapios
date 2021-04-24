#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	ModuleScene(bool startEnabled);
	~ModuleScene();

	// Loads the textures for the background
	bool Start() override;

	// Updates the scene's background animations
	update_status Update() override;

	// Renderiza
	update_status PostUpdate() override;

	bool CleanUp();

public:

private:
	SDL_Texture* background = nullptr;		// 0
	SDL_Texture* wall = nullptr;			// 1
	SDL_Texture* wall2 = nullptr;			// 2
	SDL_Texture* ground = nullptr;			// 3
	SDL_Texture* point = nullptr;			// 4

	int map[16][10] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,2,0},
	{0,1,1,1,1,3,3,3,2,0},
	{0,2,3,3,3,3,3,3,2,0},
	{0,2,3,3,3,3,3,3,2,0},
	{0,2,4,3,3,1,1,1,2,0},
	{0,2,4,2,3,3,3,2,0,0},
	{0,2,4,2,3,3,3,2,0,0},
	{0,1,1,2,3,3,3,2,0,0},
	{0,0,0,1,1,1,1,2,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
	};
};

#endif // __MODULE_SCENE_H__