#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 9	// editar si se requiere

class Module;
class ModuleAudio;
class ModuleBox;
class ModuleCollisions;
class ModuleTextures;
class ModuleInput;
class ModulePlayer;
class ModuleRender;
class ModuleScene;
class ModuleWindow;
//class ModuleParticles;

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
	ModuleBox* box = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
	ModulePlayer* player = nullptr;
	ModuleRender* render = nullptr;
	ModuleScene* scene = nullptr;
	ModuleWindow* window = nullptr;
	/*ModuleParticles* particles = nullptr;*/
};

extern Application* App;

#endif // __APPLICATION_H__