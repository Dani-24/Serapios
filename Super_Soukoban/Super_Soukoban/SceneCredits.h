#ifndef __SCENE_CREDITS_H__			//Miguel
#define __SCENE_CREDITS_H__	

#include "Module.h"
#include "Animation.h"
#include <stdio.h> //Miguel

struct SDL_Texture;

class SceneCredits : public Module
{
public:
	//Constructor
	SceneCredits(bool startEnabled);

	//Destructor
	~SceneCredits();

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

	//Animacion del fondo negro y del logo - Miguel -
	Animation black;
	Animation logo;

	// Font credits index - Miguel -
	uint credits = 000;
	int creditsFont = -1;
	char creditsText[10] = { "\0" };

	// Font names index - Miguel -
	uint names = 000;
	int namesFont = -1;
	char namesText[10] = { "\0" };

};

#endif