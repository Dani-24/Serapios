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
#include "ModuleScene4.h"
#include "ModuleScene5.h"
#include "ModuleScene6.h"
#include "ModuleWindow.h"
#include "ModuleFonts.h"
#include "SceneIntro.h"
#include "SceneCredits.h"
#include "TitleScreen.h"
#include "PauseMenu.h"

Application::Application() {
    modules[0] = window = new ModuleWindow(true);
    modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);
	modules[4] = sceneCredits = new SceneCredits(true);
	modules[5] = sceneintro = new SceneIntro(false);
	modules[6] = titleScreen = new TitleScreen(false);
	modules[7] = scene = new ModuleScene(false);
	modules[8] = scene2 = new ModuleScene2(false);
	modules[9] = scene3 = new ModuleScene3(false);
	modules[10] = scene4 = new ModuleScene4(false);
	modules[11] = scene5 = new ModuleScene5(false);
	modules[12] = scene6 = new ModuleScene6(false);
    modules[13] = player = new ModulePlayer(false);
	modules[14] = boxes = new ModuleBox(false); 
	modules[15] = collisions = new ModuleCollisions(true);
	modules[16] = pause = new PauseMenu(false);
	modules[17] = fade = new ModuleFadeToBlack(true);
	modules[18] = fonts = new ModuleFonts(true);
	modules[19] = render = new ModuleRender(true);
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

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; i++) {
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : update_status::UPDATE_CONTINUE;
	}

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; i++) {
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : update_status::UPDATE_CONTINUE;
	}

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; i++) {
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : update_status::UPDATE_CONTINUE;
	}
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled()?modules[i]->CleanUp():true;

	return ret;
}