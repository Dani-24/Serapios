#include "Application.h"

#include "Module.h"
#include "ModuleAudio.h"
#include "ModuleBox.h"
#include "ModuleCollisions.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleWindow.h"

Application::Application() {
    modules[0] = window = new ModuleWindow();
    modules[1] = input = new ModuleInput();
	modules[2] = textures = new ModuleTextures();
	modules[3] = audio = new ModuleAudio();
	modules[4] = scene = new ModuleScene();
    modules[5] = player = new ModulePlayer();
	modules[6] = box = new ModuleBox();
	modules[7] = collisions = new ModuleCollisions();
	modules[8] = render = new ModuleRender();
	
}

Application::~Application() {
	for (int i = 0; i < NUM_MODULES; i++) {
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	for (int i = 0; i < NUM_MODULES && ret; ++i) {
		ret = modules[i]->Init();
	}

	for (int i = 0; i < NUM_MODULES && ret; ++i) {
		ret = modules[i]->Start();
	}

	return ret;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PreUpdate();

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->Update();

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->CleanUp();

	return ret;
}