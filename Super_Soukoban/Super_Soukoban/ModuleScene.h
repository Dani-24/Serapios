#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

//enum GameScreen
//{
//	LOGO = 0,
//	TITLE,
//	GAMEPLAY,
//	ENDING
//};

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

	// Loads the textures for the background
	bool Start() override;

	// Updates the scene's background animations
	update_status Update() override;

	// Renderiza
	update_status PostUpdate() override;

public:

	// Con lo de abajo creas sprites para el fondo

	SDL_Texture* bgTexture = nullptr;

	//GameScreen currentScreen;// 0-LOGO, 1-TITLE, 2-GAMEPLAY, 3-ENDING
};

#endif // __MODULE_SCENE_H__