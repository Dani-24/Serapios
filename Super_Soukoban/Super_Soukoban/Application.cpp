#include "Application.h"

#include "Module.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleBox.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "ModuleScene3.h"
#include "ModuleWindow.h"
#include "ModuleFonts.h"

Application::Application() {
    modules[0] = window = new ModuleWindow(true);
    modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);
	modules[4] = scene = new ModuleScene(true);
	modules[5] = scene2 = new ModuleScene2(true);
	modules[6] = scene3 = new ModuleScene3(true);
    modules[7] = player = new ModulePlayer(true);
	modules[8] = boxes = new ModuleBox(true); 
	modules[9] = collisions = new ModuleCollisions(true);
	modules[10] = fade = new ModuleFadeToBlack(true);
	modules[11] = fonts = new ModuleFonts(true);
	modules[12] = render = new ModuleRender(true);
	
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
		ret = modules[i]->IsEnabled()?modules[i]->CleanUp():true;

	return ret;
}