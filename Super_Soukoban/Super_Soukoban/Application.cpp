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
#include "SceneIntro.h"
//moduke
Application::Application() {
    modules[0] = window = new ModuleWindow(true);
    modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);
	modules[4] = sceneintro = new SceneIntro(true);
	modules[5] = scene = new ModuleScene(false);
	modules[6] = scene2 = new ModuleScene2(false);
	modules[7] = scene3 = new ModuleScene3(false);
    modules[8] = player = new ModulePlayer(false);
	modules[9] = boxes = new ModuleBox(false); 
	modules[10] = collisions = new ModuleCollisions(false);
	modules[11] = fade = new ModuleFadeToBlack(true);
	modules[12] = fonts = new ModuleFonts(true);
	modules[13] = render = new ModuleRender(true);
	
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
		ret = modules[i]->IsEnabled() ? modules[i]->Start():true;
	}

	return ret;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate():update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : update_status::UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled()?modules[i]->CleanUp():true;

	return ret;
}