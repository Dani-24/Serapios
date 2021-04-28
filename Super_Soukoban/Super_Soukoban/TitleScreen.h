#ifndef __TITLE_SCREEN_H__  // ADRIAN: .H DE TITLESCREEN
#define __TITLE_SCREEN_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class TitleScreen : public Module
{
public:
	//Constructor
	TitleScreen(bool startEnabled);

	//Destructor
	~TitleScreen();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;





public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* Pointer = nullptr;


	int p_x = 75;
	int p_y = 145;

	SDL_Rect p_pos;


	//The intro animation
	Animation intro;

	// Font index
	int menuFont = -1;

	//Menu Buttons
	const int B_Play = 2;
	const int B_Coop = 1;
	const int B_Edit = 0;

	int M_Index = 2;


};

#endif