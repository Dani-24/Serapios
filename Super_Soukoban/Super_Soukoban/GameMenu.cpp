#include "GameMenu.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "External_Libraries/SDL/include/SDL_scancode.h"

GameMenu::GameMenu(bool startEnabled) : Module(startEnabled)
{

}

GameMenu::~GameMenu()
{

}

bool GameMenu::Start() {
	bool ret = true;

	menu_music = App->audio->PlayMusic("assets/sound/music/level_menu.ogg", 1.0f);

	menu_lvl = App->textures->Load("assets/UI/game_menu_levels.png");
	menu_title = App->textures->Load("assets/UI/game_menu_title.png");
	menu_options = App->textures->Load("assets/UI/game_menu_options.png");
	menu_controls = App->textures->Load("assets/UI/game_menu_controls.png");
	menu_pointer = App->textures->Load("assets/UI/selector.png");
	menu_bg = App->textures->Load("assets/UI/game_menu_bg.png");
	menu_bg2 = App->textures->Load("assets/UI/game_menu_bg.png");

	char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	menuFont = App->fonts->Load("assets/fonts/rtype_font.png", lookupTable, 1);

	nextFx = App->audio->LoadFx("assets/sound/SFX/menu2_confirm.wav");
	backFx = App->audio->LoadFx("assets/sound/SFX/menu3_back.wav");
	selectFx = App->audio->LoadFx("assets/sound/SFX/menu1_select.wav");

	pointerPosX = 105;
	pointerPosY = 120;

	displayCtrls = false;
	return ret;
}

update_status GameMenu::Update() {

	scrollerX -= 1;
	scroller2X -= 1;

	if (scrollerX < -964) {
		scrollerX = 966;
	}
	if (scroller2X < -964) {
		scroller2X = 966;
	}

	GamePad& pad = App->input->pads[0];
	if (displayCtrls == false) {
		if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN || pad.down || pad.left_y > 0.0f)
		{
			if (pointerPosY == 30) {
				pointerPosY = 50;
				pointerPosX = 135;
				App->audio->PlayFx(selectFx);
			}
			else if (pointerPosY == 50) {
				pointerPosY = 120;
				pointerPosX = 105;
				App->audio->PlayFx(selectFx);
			}
		}
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN || pad.up || pad.left_y < 0.0f)
		{
			if (pointerPosY == 120) {
				pointerPosY = 50;
				pointerPosX = 135;
				App->audio->PlayFx(selectFx);
			}
			else if (pointerPosY == 50) {
				pointerPosY = 30;
				pointerPosX = 135;
				App->audio->PlayFx(selectFx);
			}
		}
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN || pad.left || pad.left_x < 0.0f)
		{
			if (pointerPosY == 120 && pointerPosX > 105) {
				pointerPosX = pointerPosX - 16;
				App->audio->PlayFx(selectFx);
			}
		}
		if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN || pad.right || pad.left_x > 0.0f)
		{
			if (pointerPosY == 120 && pointerPosX < 185) {
				pointerPosX = pointerPosX + 16;
				App->audio->PlayFx(selectFx);
			}
		}
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a) {

			// controls
			if (pointerPosY == 30) {
				App->audio->PlayFx(nextFx);
				displayCtrls = true;
			}
			// exit
			if (pointerPosY == 50) {
				App->audio->PlayFx(backFx);
				App->fade->FadeToBlack(this, (Module*)App->titleScreen, 60);
			}
			// 1
			if (pointerPosX == 105 && pointerPosY == 120) {
				App->audio->PlayFx(nextFx);
				App->fade->FadeToBlack(this, (Module*)App->scene, 60);
			}
			// 2
			if (pointerPosX == 121 && pointerPosY == 120) {
				App->audio->PlayFx(nextFx);
				App->fade->FadeToBlack(this, (Module*)App->scene2, 60);
			}
			// 3
			if (pointerPosX == 137 && pointerPosY == 120) {
				App->audio->PlayFx(nextFx);
				App->fade->FadeToBlack(this, (Module*)App->scene3, 60);
			}
			// 4
			if (pointerPosX == 153 && pointerPosY == 120) {
				App->audio->PlayFx(nextFx);
				App->fade->FadeToBlack(this, (Module*)App->scene4, 60);
			}
			// 5
			if (pointerPosX == 169 && pointerPosY == 120) {
				App->audio->PlayFx(nextFx);
				App->fade->FadeToBlack(this, (Module*)App->scene5, 60);
			}
			// 6
			if (pointerPosX == 185 && pointerPosY == 120) {
				App->audio->PlayFx(nextFx);
				App->fade->FadeToBlack(this, (Module*)App->scene6, 60);
			}

		}
	}
	if (displayCtrls == true) {
		if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN || pad.a) {
			displayCtrls = false;
			App->audio->PlayFx(backFx);
		}
	}
	return update_status::UPDATE_CONTINUE;
}

update_status GameMenu::PostUpdate() {

	App->render->Blit(menu_bg, scrollerX, 0, NULL);

	App->render->Blit(menu_bg2, scroller2X, 0, NULL);

	if (displayCtrls == true) {
		App->render->Blit(menu_controls, 55, 50, NULL);
		App->fonts->BlitText(145, 70, menuFont, "& controls &");
		App->fonts->BlitText(100, 90, menuFont, "esc < back");
		App->fonts->BlitText(100, 105, menuFont, "space < continue");
		App->fonts->BlitText(100, 120, menuFont, "asdw < movement");
		App->fonts->BlitText(100, 135, menuFont, "f1 f2 f3 f4 < debug keys");
		App->fonts->BlitText(97, 150, menuFont, "123456 < change level");
	}
	else if(displayCtrls == false){
		App->render->Blit(menu_lvl, 115, 120, NULL);
		App->render->Blit(menu_title, 123, 93, NULL);
		App->render->Blit(menu_options, 125, 20, NULL);

		App->render->Blit(menu_pointer, pointerPosX, pointerPosY, NULL);

		App->fonts->BlitText(135, 100, menuFont, "level selection");
		App->fonts->BlitText(150, 34, menuFont, "controls");
		App->fonts->BlitText(150, 54, menuFont, "back to title");
	}
	

	return update_status::UPDATE_CONTINUE;
}

bool GameMenu::CleanUp() {
	pointerPosX = 130;
	pointerPosY = 110;
	displayCtrls = false;
	return true;
}