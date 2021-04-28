#include "SceneIntro.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "External_Libraries/SDL/include/SDL_scancode.h"

SceneIntro::SceneIntro(bool startEnabled) :Module(startEnabled)
{

	// LOGO
	intro.PushBack({ 1, 1, 256, 224 });
	intro.PushBack({ 260, 2713, 256, 224 });
	intro.PushBack({ 260, 2713, 256, 224 });
	intro.PushBack({ 1, 1, 256, 224 });

	// Intro animation
	intro.PushBack({ 1, 1, 256, 224 });
	intro.PushBack({ 1, 227, 256, 224 });
	intro.PushBack({ 1, 227, 256, 224 });
	intro.PushBack({ 1, 1, 256, 224 });
	intro.PushBack({ 2065, 227, 256, 224 });
	intro.PushBack({ 2323, 227, 256, 224 });
	intro.PushBack({ 2581, 227, 256, 224 });
	intro.PushBack({ 2839, 227, 256, 224 });
	intro.PushBack({ 3097, 227, 256, 224 });
	intro.PushBack({ 3355, 227, 256, 224 });
	intro.PushBack({ 2065, 453, 256, 224 });
	intro.PushBack({ 775, 905, 256, 224 });
	intro.PushBack({ 1033, 905, 256, 224 });
	intro.PushBack({ 1291, 905, 256, 224 });
	intro.PushBack({ 1807, 905, 256, 224 });
	intro.PushBack({ 2581,1357, 256, 224 });
	intro.PushBack({ 2839,1357, 256, 224 });
	intro.PushBack({ 3097,1357, 256, 224 });
	intro.PushBack({ 3355,1357, 256, 224 });
	intro.PushBack({ 3613,1357, 256, 224 });
	intro.PushBack({ 1,1583, 256, 224 });
	intro.PushBack({ 2323,1809, 256, 224 });
	intro.PushBack({ 2581,1809, 256, 224 });
	intro.PushBack({ 2839,1809, 256, 224 });
	intro.PushBack({ 1,2713, 256, 224 });

	intro.loop = false;
	intro.speed = 0.015f;
}

SceneIntro::~SceneIntro() {

}

bool SceneIntro::Start() {
	LOG("Loading bacgroud assets :)");

	bool ret = true;
    
	bgTexture = App->textures->Load("Assets/Intro_frames.png");
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