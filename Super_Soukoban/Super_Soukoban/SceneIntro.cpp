#include "SceneIntro.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "External_Libraries/SDL/include/SDL_scancode.h"

SceneIntro::SceneIntro(bool startEnabled) :Module(startEnabled) {

}

SceneIntro::~SceneIntro() {

}

bool SceneIntro::Start() {
	LOG("Loading bacgroud assets :)");

	bool ret = true;
    
	bgTexture = App->textures->Load("Assets/logo.png");
	App->audio->PlayMusic("Assets/Music/Intro.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneIntro::Update() {
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene2, 90);

	}

	return update_status::UPDATE_CONTINUE;
}

//DRAW BACKGROUD

update_status SceneIntro::PostUpdate() {
	App->render->Blit(bgTexture, SCREEN_WIDTH/2-115, SCREEN_HEIGHT/2-115 , NULL);

	return update_status::UPDATE_CONTINUE;
}