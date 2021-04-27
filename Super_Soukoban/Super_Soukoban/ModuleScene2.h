#ifndef __MODULE_SCENE2_H__
#define __MODULE_SCENE2_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene2 : public Module
{
public:
	ModuleScene2(bool startEnabled);
	~ModuleScene2();

	// Loads the textures for the background
	bool Start() override;

	// Updates the scene's background animations
	update_status Update() override;

	// Renderiza
	update_status PostUpdate() override;

	bool CleanUp();


public:
int map[16][10] = {
	{0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,2,0},
	{0,0,0,0,0,3,3,3,2,0},
	{0,2,3,3,2,3,3,3,2,0},
	{0,2,3,0,3,3,3,3,2,0},
	{0,2,4,0,0,1,1,1,2,0},
	{0,2,4,2,3,3,3,2,0,0},
	{0,2,4,2,0,2,3,2,0,0},
	{0,1,1,2,3,3,3,2,0,0},
	{0,0,1,1,1,1,1,2,0,0},
	{0,0,1,1,1,1,0,0,0,0},
	{0,0,1,1,1,1,0,0,0,0},
	{0,0,0,1,1,1,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0}
	};
bool boxEnd[3] = { false };
private:
	SDL_Texture* background = nullptr;		// 0
	SDL_Texture* wall = nullptr;			// 1
	SDL_Texture* wall2 = nullptr;			// 2
	SDL_Texture* ground = nullptr;			// 3
	SDL_Texture* point = nullptr;			// 4
	SDL_Texture* lose = nullptr;
	SDL_Texture* win = nullptr;

	
};

#endif // __MODULE_SCENE_2_H_