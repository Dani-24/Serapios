#include "ModuleScene3.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleBox.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "PauseMenu.h"
#include "ModuleFonts.h"
#include "External_Libraries/SDL/include/SDL_scancode.h"

ModuleScene3::ModuleScene3(bool startEnabled) :Module(startEnabled)
{

}

ModuleScene3::~ModuleScene3()
{

}

bool ModuleScene3::Start()
{
	LOG("Loading background assets (SCENE 3)");

	bool ret = true;
	background = App->textures->Load("assets/tiles/background.png");
	wall = App->textures->Load("assets/tiles/wall.png");
	wall2 = App->textures->Load("assets/tiles/wall2.png");
	ground = App->textures->Load("assets/tiles/ground.png");
	point = App->textures->Load("assets/tiles/point.png");
	lose = App->textures->Load("assets/UI/lose.png");
	win = App->textures->Load("assets/UI/win.png");
	godModeGround = App->textures->Load("assets/UI/meowsprite.png");
	//FX

	winMusic = App->audio->LoadFx("assets/sound/music/win_sound_loop.ogg"); 
	loseFx = App->audio->LoadFx("assets/sound/SFX/lost_sound.wav");
	nextFx = App->audio->LoadFx("assets/sound/SFX/menu2_confirm.wav");
	backFx = App->audio->LoadFx("assets/sound/SFX/menu3_back.wav");

	
	// Tell module Player how is the map
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			App->player->map[i][j] = map[i][j];
			App->boxes->mandaMap[i][j] = map[i][j];
		}
	}

	App->player->numBox = 5;

	// Set up stage, steps and step limit
	App->player->stage = 03;
	App->player->limit = 50;
	App->player->steps = 0;
	App->player->playerMovement = true;

	// Boxes lvl 3 :
	App->boxes->AddBox(168, 96);
	App->boxes->AddBox(168, 72);
	App->boxes->AddBox(192, 168);
	App->boxes->AddBox(168, 144);
	App->boxes->AddBox(192, 120);

	// Player position: (multiples de 24.) Add +5 to position.x 
	App->player->position.x = 149;
	App->player->position.y = 72;

	//active the entities
	App->player->Enable();
	App->boxes->Enable();

	return ret;
}

update_status ModuleScene3::Update()
{
	// Music
	if (playMusic == false) {
		if (godModeOn == true) {
			godMode = App->audio->PlayMusic("assets/sound/music/god_mode.ogg", 1.0f);
		}
		else {
			levelMusic = App->audio->PlayMusic("assets/sound/music/stage1.ogg", 1.0f);
		}
		playMusic = true;
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN)	//menu
	{
		App->audio->PlayFx(backFx);
		App->pause->current = (Module*)App->scene3;
		App->pause->Enable();

	}
	if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)		// Go to lvl 1
	{
		App->audio->PlayFx(nextFx);
		CleanUp();
		App->fade->FadeToBlack(this, (Module*)App->scene, 60);

	}

	if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)		// Go to lvl 2 
	{
		App->audio->PlayFx(nextFx);
		CleanUp();
		App->fade->FadeToBlack(this, (Module*)App->scene2, 60);

	}
	if (App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_DOWN)		// Reset lvl 3
	{
		App->audio->PlayFx(nextFx);
		CleanUp();
		App->fade->FadeToBlack(this, (Module*)App->scene3, 60);

	}
	if (App->input->keys[SDL_SCANCODE_4] == KEY_STATE::KEY_DOWN)		// Go to lvl 4
	{
		App->audio->PlayFx(nextFx);
		CleanUp();
		App->fade->FadeToBlack(this, (Module*)App->scene4, 60);
	}
	if (App->input->keys[SDL_SCANCODE_5] == KEY_STATE::KEY_DOWN)		// go to lvl 5
	{
		App->audio->PlayFx(nextFx);
		CleanUp();
		App->fade->FadeToBlack(this, (Module*)App->scene5, 60);

	}
	if (App->input->keys[SDL_SCANCODE_6] == KEY_STATE::KEY_DOWN)		// Go to lvl 6
	{
		App->audio->PlayFx(nextFx);
		CleanUp();
		App->fade->FadeToBlack(this, (Module*)App->scene6, 60);
	}
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN)		// GOD MODE
	{
		if (godModeOn == true) {
			LOG("GOD MODE OFF");
			App->player->limit = 50;
			godModeOn = false;
		}
		else {
			LOG("GOD MODE ON");
			App->player->limit = 9999;
			godModeOn = true;
		}
		playMusic = false;
	}
	return update_status::UPDATE_CONTINUE;
}


update_status ModuleScene3::PostUpdate()
{
	// draw the background and tiles
	GamePad& pad = App->input->pads[0];
	int type = 0;
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			type = map[i][j];

			switch (type)
			{
			case 0:
				if (godModeOn == true) {
					App->render->Blit(godModeGround, i * 24, j * 24, NULL);
				}
				else {
					App->render->Blit(background, i * 24, j * 24, NULL);
				}
				break;
			case 1:
				App->render->Blit(wall, i * 24, j * 24, NULL);
				App->collisions->AddCollider({ i * 24 , j * 24 , 24 , 24 }, Collider::Type::WALL);
				break;
			case 2:
				App->render->Blit(wall2, i * 24, j * 24, NULL);
				App->collisions->AddCollider({ i * 24 , j * 24 , 24 , 24 }, Collider::Type::WALL);
				break;
			case 3:
				App->render->Blit(ground, i * 24, j * 24, NULL);
				break;
			case 4:
				App->render->Blit(point, i * 24, j * 24, NULL);
				App->collisions->AddCollider({ i * 24 , j * 24 , 24 , 24 }, Collider::Type::POINT);
				break;
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN && dWin == false) {
		dLose = true;
	}
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN && dLose == false) {
		dWin = true;
	}

	//lose
	if (App->player->steps == App->player->limit || dLose==true) {
		App->render->Blit(lose, SCREEN_WIDTH / 2 - 68, SCREEN_HEIGHT / 2 - 36, NULL);
		App->player->playerMovement = false;
		if (loseF != true) {

			App->audio->PlayFx(loseFx);
			loseF = true;
		}
		playMusic = false;
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a)
		{
			App->audio->PlayFx(nextFx);
			CleanUp();
			App->fade->FadeToBlack(this, (Module*)App->scene3, 60);
		}
	}

	//win
	for (int i = 0; i < 4; ++i)
	{
		if (App->boxes->boxes[i] != nullptr) {
			if (App->boxes->boxes[i]->currentAnim == &(App->boxes->boxes[i]->darkBoxAnim))
			{
				boxEnd[i] = true;
			}
		}
	}

	if (boxEnd[0] == true && boxEnd[1] == true && boxEnd[2] == true && boxEnd[3] == true || dWin==true)
	{
		App->player->playerMovement = false;
		if (winF != true) {
			App->audio->PlayFx(winMusic);
			winF = true;
		}
		playMusic = false;
		App->render->Blit(win, SCREEN_WIDTH / 2 - 62, SCREEN_HEIGHT / 2 - 36, NULL);
		
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a)
		{
			App->audio->PlayFx(nextFx);
			CleanUp();
			App->fade->FadeToBlack(this, (Module*)App->scene4, 60);
		}
	}

	return update_status::UPDATE_CONTINUE;
}
//disable the entities
bool ModuleScene3::CleanUp()
{
	LOG("Cleaning SCENE 3");
	App->player->Disable();
	App->boxes->Disable();
	App->collisions->CleanUp();
	dWin = false;
	dLose = false;
	winF = false;
	loseF = false;
	godModeOn = false;
	playMusic = false;
	for (int i = 0; i < numOfBoxes; i++) {
		boxEnd[i] = false;
	}
	App->fonts->UnLoad();
	return true;
}