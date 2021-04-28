#include "SceneIntro.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
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
	intro.Update(); // EJECUTA LA ANIMACION DE LA INTRO DEL VIDEOJUEGO "SUPER SOKOUBAN" - Miguel -

	if (intro.HasFinished()) //Si el loop de la animacion incial ha acabado ejecuta el FadeToBlack - Miguel -
	{
		App->fade->FadeToBlack(this, (Module*)App->titleScreen, 60);
	}

	else if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->titleScreen, 60);

	}

	if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene, 90);
		App->player->currentScene=0;

	}
	if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene2, 90);
		App->player->currentScene = 1;

	}
	if (App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene3, 90);
		App->player->currentScene = 2;

	}

	return update_status::UPDATE_CONTINUE;
}

//DRAW BACKGROUD

update_status SceneIntro::PostUpdate() {

	App->render->Blit(bgTexture, SCREEN_WIDTH / 2 - 115, SCREEN_HEIGHT / 2 - 115, &(intro.GetCurrentFrame()), 0.1f); // intro
	App->render->Blit(bgTexture1, SCREEN_WIDTH / 2 - 115, SCREEN_HEIGHT / 2 - 115, &(logo.GetCurrentFrame()), 0.1f);
	return update_status::UPDATE_CONTINUE;
}