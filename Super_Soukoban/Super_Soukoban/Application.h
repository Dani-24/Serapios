#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class Module;
class ModuleAudio;
class ModuleCollisions;
class ModuleFadeToBlack;
class ModuleTextures;
class ModuleInput;
class ModulePlayer;
class ModuleBox;
class ModuleRender;
class ModuleScene;
class ModuleScene2;
class ModuleScene3;
class ModuleScene4;
class ModuleWindow;
class ModuleFonts;
class SceneIntro;
class TitleScreen;
class SceneCredits;

class Application
{
public:
	Application();

	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	Module* modules[NUM_MODULES];
	ModuleAudio* audio = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
	ModulePlayer* player = nullptr;
	ModuleBox* boxes = nullptr;
	ModuleRender* render = nullptr;
	SceneCredits* sceneCredits = nullptr;
	TitleScreen* titleScreen = nullptr;
	SceneIntro* sceneintro = nullptr;
	ModuleScene* scene = nullptr;
	ModuleScene2* scene2 = nullptr;
	ModuleScene3* scene3 = nullptr;
	ModuleScene4* scene4 = nullptr;

	ModuleWindow* window = nullptr;
	ModuleFonts* fonts = nullptr;

};

extern Application* App;

#endif // __APPLICATION_H__