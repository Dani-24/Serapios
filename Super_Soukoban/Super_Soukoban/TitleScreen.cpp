#include "TitleScreen.h"  //ADRIAN: CLASE TITLESCREEN PARA EL MENU

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include <stdio.h>

#include "External_Libraries/SDL/include/SDL.h"				// Required for SDL base systems functionality
#include "External_Libraries/SDL_image/include/SDL_image.h"	// Required for image loading functionality
#include "External_Libraries/SDL_mixer/include/SDL_mixer.h"	// Required for audio loading and playing functionality

TitleScreen::TitleScreen(bool startEnabled) : Module(startEnabled)
{

}

TitleScreen::~TitleScreen()
{

}

// Load assets
bool TitleScreen::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//title 
	bgTexture = App->textures->Load("assets/UI/main_menu_title.png");
	Pointer = App->textures->Load("assets/UI/selector.png");
	scroller = App->textures->Load("assets/UI/scroller.png");
	scroller2 = App->textures->Load("assets/UI/scroller.png");
	menu_box = App->textures->Load("assets/UI/main_menu_options.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	p_pos.x = p_x;
	p_pos.y = p_y;

	char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	menuFont = App->fonts->Load("assets/fonts/rtype_font.png", lookupTable, 1);

	// music and fx
	titleMenuMusic = App->audio->PlayMusic("assets/sound/music/title_menu.ogg", 1.0f);
	selectFx = App->audio->LoadFx("assets/sound/SFX/menu1_select.wav");
	nextFx = App->audio->LoadFx("assets/sound/SFX/menu2_confirm.wav");
	backFx = App->audio->LoadFx("assets/sound/SFX/menu3_back.wav");

	return ret;
}

update_status TitleScreen::Update()
{
	scrollerY -= 1;
	scroller2Y -= 1;

	if (scrollerY < -1036) {
		scrollerY = 1034;
	}
	if (scroller2Y < -1036) {
		scroller2Y = 1034;
	}
	//key commands 
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN) {
		if (M_Index < 2)
		{
			M_Index++;
			p_y -= 13;
			App->audio->PlayFx(selectFx);
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN) {
		if (M_Index > 0)
		{
			M_Index--;
			p_y += 13;
			App->audio->PlayFx(selectFx);
		}
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		if (M_Index == B_Play)
		{
			App->audio->PlayFx(nextFx);
			App->fade->FadeToBlack(this, (Module*)App->scene, 60);
		}
		else {
			App->audio->PlayFx(backFx);
		}
	}

	if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene, 90);

	}
	if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene2, 90);

	}
	if (App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene3, 90);

	}
	if (App->input->keys[SDL_SCANCODE_4] == KEY_STATE::KEY_DOWN)		// Reset lvl 4
	{
		CleanUp();
		App->fade->FadeToBlack(this, (Module*)App->scene4, 90);

	}
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) {		// ESC to close the game
		return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}



// Update: draw background
update_status TitleScreen::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(scroller, 0, scrollerY, NULL);
	App->render->Blit(scroller2, 0, scroller2Y, NULL);
	App->render->Blit(menu_box, 150, 140, NULL);


	App->render->Blit(bgTexture, SCREEN_WIDTH / 2 - 115, SCREEN_HEIGHT / 2 - 120, NULL);
	App->render->Blit(Pointer, p_x, p_y, NULL);

	App->fonts->BlitText(SCREEN_WIDTH / 2 - 20, 150, menuFont, "play game");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 20, 162, menuFont, "coop mode");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 20, 174, menuFont, "level edit");


	return update_status::UPDATE_CONTINUE;
}