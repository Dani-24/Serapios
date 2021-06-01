#ifndef __SCENE_CREDITS_H__	
#define __SCENE_CREDITS_H__	

#include "Module.h"
#include "Animation.h"
#include <stdio.h> 

struct SDL_Texture;

class SceneCredits : public Module
{
public:
	
	SceneCredits(bool startEnabled);

	
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
	//background texture
	SDL_Texture* bgTexture = nullptr;

	//Background animation
	Animation black;
	Animation logo;

	// Font credits index 
	uint credits = 000;
	int creditsFont = -1;
	char creditsText[10] = { "\0" };

	// Font names index 
	uint names = 000;
	int namesFont = -1;
	char namesText[10] = { "\0" };

};

#endif