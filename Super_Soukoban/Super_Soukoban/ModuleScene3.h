#ifndef __MODULE_SCENE3_H__
#define __MODULE_SCENE3_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene3 : public Module
{
public:
	ModuleScene3(bool startEnabled);
	~ModuleScene3();

	// Loads the textures for the background
	bool Start() override;

	// Updates the scene's background animations
	update_status Update() override;

	// Renderize
	update_status PostUpdate() override;

	bool CleanUp();

	uint score = 0;

public:
int map[16][10] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,1,2,0},
	{0,1,2,3,1,2,4,4,2,0},
	{0,2,3,3,3,3,3,4,2,0},
	{0,2,3,3,3,3,3,4,2,0},
	{0,1,1,1,2,3,3,4,2,0},
	{0,0,0,0,1,1,1,1,2,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
	};
bool boxEnd[4] = { false };
bool playMusic = false;

private:
	SDL_Texture* background = nullptr;		// 0
	SDL_Texture* wall = nullptr;			// 1
	SDL_Texture* wall2 = nullptr;			// 2
	SDL_Texture* ground = nullptr;			// 3
	SDL_Texture* point = nullptr;			// 4
	SDL_Texture* lose = nullptr;
	SDL_Texture* win = nullptr;
	SDL_Texture* godModeGround = nullptr;
	bool dWin=false;
	bool dLose=false;
	bool winF = false;
	bool loseF = false;

	uint levelMusic = 0;
	uint winMusic = 0;
	uint winFx = 0;
	uint loseFx = 0;

	uint godMode = 0;
	bool godModeOn = false;
	bool EasterEgg = false; 

	uint nextFx = 0;
	uint backFx = 0;

	int numOfBoxes = 5;
};

#endif // __MODULE_SCENE_3_H_