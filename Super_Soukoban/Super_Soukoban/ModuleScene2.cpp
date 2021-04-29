#include "ModuleScene2.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleBox.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"

#include "External_Libraries/SDL/include/SDL_scancode.h"

ModuleScene2::ModuleScene2(bool startEnabled) :Module(startEnabled)
{

}

ModuleScene2::~ModuleScene2()
{

}

bool ModuleScene2::Start()
{
	LOG("Loading background assets 3");

	bool ret = true;
	dWin = false;
	dLose = false;

	background = App->textures->Load("Assets/tiles/background.png");
	wall = App->textures->Load("Assets/tiles/wall.png");
	wall2 = App->textures->Load("Assets/tiles/wall2.png");
	ground = App->textures->Load("Assets/tiles/ground.png");
	point = App->textures->Load("Assets/tiles/point.png");
	lose= App->textures->Load("Assets/lose.png");
	win = App->textures->Load("Assets/win.png");

	// Music and FX
	levelMusic = App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);;
	winMusic = App->audio->LoadFx("Assets/Music/Win_Sound_Loop.ogg"); // deberia ser un PlayMusic. (Mirar mas tarde para que no solape)

	winFx = App->audio->LoadFx("Assets/SFX/Win_Sound_Init.wav");
	loseFx = App->audio->LoadFx("Assets/SFX/Lost_Sound.wav");

	nextFx = App->audio->LoadFx("Assets/SFX/Menu2_confirm.wav");
	backFx = App->audio->LoadFx("Assets/SFX/Menu3_back.wav");

	// Tell module Player how is the map
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			App->player->map[i][j] = map[i][j];
			App->boxes->mandaMap[i][j] = map[i][j];
		}
	}
	App->player->numBox = 3;

	//to active the entities
	App->player->Enable();
	App->boxes->Enable();
	App->collisions->Enable();

	// Set up stage, steps and step limit
	App->player->stage = 02;
	App->player->limit = 120;
	App->player->steps = 0;

	// Boxes lvl1 :
	App->boxes->AddBox(144, 72);
	App->boxes->AddBox(144, 49);
	App->boxes->AddBox(168, 49);

	// Player position: (multiples de 24.) Add +5 to position.x 
	App->player->position.x = 125;
	App->player->position.y = 24;


	return ret;
}

update_status ModuleScene2::Update()
{
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN)	// Back to Init menu
	{
		App->audio->PlayFx(backFx);
		CleanUp();
		App->fade->FadeToBlack(this, (Module*)App->sceneintro, 60);

	}
	if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)		// Go to lvl 1
	{
		CleanUp();
		App->fade->FadeToBlack(this, (Module*)App->scene, 60);

	}
	
	if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)		// Reset lvl 2 
	{
		CleanUp();
		App->fade->FadeToBlack(this, (Module*)App->scene2, 60);

	}
	if (App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_DOWN)		// Go to lvl 3
	{
		CleanUp();
		App->fade->FadeToBlack(this, (Module*)App->scene3, 60);

	}
	return update_status::UPDATE_CONTINUE;
}


update_status ModuleScene2::PostUpdate()
{
	// Aqui se dibuja el fondo

	int type = 0;
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			type = map[i][j];

			switch (type)
			{
			case 0:
				App->render->Blit(background, i * 24, j * 24, NULL);
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
	if (App->player->steps == App->player->limit || dLose ==true) {
		
		App->render->Blit(lose, SCREEN_WIDTH / 2 - 68, SCREEN_HEIGHT / 2 - 36, NULL);
		CleanUp();
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			App->audio->PlayFx(nextFx);
			App->fade->FadeToBlack(this, (Module*)App->scene2, 60);
		}
	}

	//win
	for (int i = 0; i < 3; ++i)
	{
		if (App->boxes->boxes[i] != nullptr) {
			if (App->boxes->boxes[i]->currentAnim == &(App->boxes->boxes[i]->darkBoxAnim))
			{
				boxEnd[i] = true;
			}
		}
	}

	if (boxEnd[0] == true && boxEnd[1] == true && boxEnd[2] == true || dWin==true)
	{
		App->boxes->Disable();
		App->render->Blit(win, SCREEN_WIDTH / 2 - 62, SCREEN_HEIGHT / 2 - 36, NULL);
		LOG("level 2 completed");
		CleanUp();
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			App->audio->PlayFx(nextFx);
			App->fade->FadeToBlack(this, (Module*)App->scene3, 60);
		}
	}
	
	return update_status::UPDATE_CONTINUE;
}
//disable the entities
bool ModuleScene2::CleanUp()
{
	App->player->Disable();
	App->boxes->Disable();
	App->collisions->CleanUp();
	App->collisions->Disable();
	return true;
}

