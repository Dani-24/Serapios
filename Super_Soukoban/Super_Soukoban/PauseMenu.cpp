#include "PauseMenu.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleBox.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "External_Libraries/SDL/include/SDL_scancode.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "ModuleScene3.h"
#include "ModuleScene4.h"
//#include "ModuleScene5.h"
#include "ModuleScene6.h"

PauseMenu::PauseMenu(bool startEnabled) : Module(startEnabled)
{

}

PauseMenu::~PauseMenu()
{

}

bool PauseMenu::Start() {
	bool ret = true;

	App->player->playerMovement = false;
	music = App->audio->PlayMusic("assets/sound/music/pause_menu.ogg", 1.0f);
	LOG("Loading random things and memleaks for the menu");

	menuSurface = App->textures->Load("assets/UI/level_menu.png");
	pointer = App->textures->Load("assets/UI/selector.png");

	nextFx = App->audio->LoadFx("assets/sound/SFX/menu2_confirm.wav");
	backFx = App->audio->LoadFx("assets/sound/SFX/menu3_back.wav");
	selectFx = App->audio->LoadFx("assets/sound/SFX/menu1_select.wav");

	char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	menuFont = App->fonts->Load("assets/fonts/rtype_font.png", lookupTable, 1);

	pointerPosX = 130;
	pointerPosY = 110;

	return ret;
}

update_status PauseMenu::Update() {	// teclas
	GamePad& pad = App->input->pads[0];
	// Pointer movement
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN||pad.down || pad.left_y > 0.0f)
	{
		if (pointerPosY < 140) {
			pointerPosY = pointerPosY + 15;
			App->audio->PlayFx(selectFx);
		}
	}
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN||pad.up || pad.left_y < 0.0f)
	{
		if (pointerPosY > 110) {
			pointerPosY = pointerPosY - 15;
			App->audio->PlayFx(selectFx);
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a)	// Back to Init menu
	{
		App->audio->PlayFx(nextFx);
		if (pointerPosY == 110) {
			App->player->playerMovement = true;
			App->scene->playMusic = false;
			App->scene2->playMusic = false;
			App->scene3->playMusic = false;
			App->scene4->playMusic = false;
			//App->scene5->playMusic = false;
			App->scene6->playMusic = false;
			Disable();
		}
		else if (pointerPosY == 125) {
			App->fade->FadeToBlack(current, current, 60);
			App->scene->Disable();
			App->scene2->Disable();
			App->scene3->Disable();
			App->scene4->Disable();
			//App->scene5->Disable();
			App->scene6->Disable();
			Disable();
		}
		else if (pointerPosY == 140) {
			App->fade->FadeToBlack(current, (Module*)App->titleScreen, 60);	// cambiar por menu
			App->scene->Disable();
			App->scene2->Disable();
			App->scene3->Disable();
			App->scene4->Disable();
			//App->scene5->Disable();
			App->scene6->Disable();
			Disable();
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status PauseMenu::PostUpdate() {		// imagenes

	App->render->Blit(menuSurface, 120, 80, NULL);

	App->render->Blit(pointer, pointerPosX, pointerPosY, NULL);

	App->fonts->BlitText(180, 90, menuFont, "pause");

	App->fonts->BlitText(150, 115, menuFont, "continue");
	App->fonts->BlitText(150, 130, menuFont, "restart");
	App->fonts->BlitText(150, 145, menuFont, "exit to menu");

	return update_status::UPDATE_CONTINUE;
}

bool PauseMenu::CleanUp() {

	current = nullptr;
	pointerPosX = 130;
	pointerPosY = 110;

	return true;
}