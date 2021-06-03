#include "SceneCredits.h" 

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h" 
#include "ModuleInput.h"

#include "External_Libraries/SDL/include/SDL_scancode.h"


SceneCredits::SceneCredits(bool startEnabled) : Module(startEnabled)
{
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.loop = false;
	black.speed = 0.015f;
}

SceneCredits::~SceneCredits()
{

}

bool SceneCredits::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("assets/UI/logo.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	creditsFont = App->fonts->Load("assets/fonts/rtype_font3.png", lookupTable, 2);
	namesFont = App->fonts->Load("assets/fonts/rtype_font.png", lookupTable, 1);

	return ret;
}

update_status SceneCredits::Update()
{
	GamePad& pad = App->input->pads[0];
	black.Update();
	if (black.HasFinished())
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneintro, 60);
	}
	
	else if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneintro, 60);
	}

	return update_status::UPDATE_CONTINUE;
}

update_status SceneCredits::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, &(black.GetCurrentFrame()), 0.3f);

	// Credits:
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 - 100, creditsFont, "this is a project created ");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 85, creditsFont, "by students at citm for the");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 - 70, creditsFont, " project 1 subject from");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 55, namesFont, "videogames design");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 40, namesFont, "and development degree");

	App->fonts->BlitText(SCREEN_WIDTH / 2 - 55, SCREEN_HEIGHT / 2 - 15, creditsFont, "project teachers");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2, namesFont, "jesus alonso");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 55, SCREEN_HEIGHT / 2 + 15, namesFont, "ramon santamaria");

	App->fonts->BlitText(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 40, creditsFont, "developers");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 55, namesFont, "dani toledo, xavier lopez");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 70, namesFont, "laia pachon, adrian ramirez");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 + 85, namesFont, "and miguel rodriguez");

	return update_status::UPDATE_CONTINUE;
}