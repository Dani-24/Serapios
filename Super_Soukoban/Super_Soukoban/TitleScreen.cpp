#include "TitleScreen.h"  //ADRIAN: CLASE TITLESCREEN PARA EL MENU

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include <stdio.h>


#include "SDL/include/SDL.h"				// Required for SDL base systems functionality
#include "SDL_image/include/SDL_image.h"	// Required for image loading functionality
#include "SDL_mixer/include/SDL_mixer.h"	// Required for audio loading and playing functionality

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

	bgTexture = App->textures->Load("Assets/background_menu.png");
	Pointer = App->textures->Load("Assets/selector.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	p_pos.x = p_x;
	p_pos.y = p_y;

	char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	menuFont = App->fonts->Load("Assets/Fonts/rtype_font.png", lookupTable, 1);

	return ret;
}

update_status TitleScreen::Update()

{

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN) {
		if (M_Index < 2)
		{
			M_Index++;
			p_y -= 13;
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN) {
		if (M_Index > 0)
		{
			M_Index--;
			p_y += 13;
		}
	}

	if (M_Index == B_Play)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			App->fade->FadeToBlack(this, (Module*)App->scene, 60);
		}
	}
	/*
	if (M_Index == B_Coop) {

	}
	if (M_Index == B_Edit) {

	}
	*/


	return update_status::UPDATE_CONTINUE;
}



// Update: draw background
update_status TitleScreen::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, SCREEN_WIDTH / 2 - 115, SCREEN_HEIGHT / 2 - 120, NULL);
	App->render->Blit(Pointer, p_x, p_y, NULL);

	App->fonts->BlitText(SCREEN_WIDTH / 2 - 20, 150, menuFont, "play game");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 20, 162, menuFont, "coop mode");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 20, 174, menuFont, "level edit");


	return update_status::UPDATE_CONTINUE;
}