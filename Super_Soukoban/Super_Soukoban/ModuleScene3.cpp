#include "ModuleScene3.h"
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

ModuleScene3::ModuleScene3(bool startEnabled) :Module(startEnabled)
{

}

ModuleScene3::~ModuleScene3()
{

}

bool ModuleScene3::Start()
{
	LOG("Loading background assets 2");

	bool ret = true;
	//pos = 1;

	background = App->textures->Load("Assets/tiles/background.png");
	wall = App->textures->Load("Assets/tiles/wall.png");
	wall2 = App->textures->Load("Assets/tiles/wall2.png");
	ground = App->textures->Load("Assets/tiles/ground.png");
	point = App->textures->Load("Assets/tiles/point.png");
	lose = App->textures->Load("Assets/lose.png");
	win = App->textures->Load("Assets/win.png");

	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);

	//to active the entities
	App->player->Enable();
	App->boxes->Enable();
	//App->scene2->Disabled();

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
	// Boxes lvl1 :
	App->boxes->AddBox(168, 96);
	App->boxes->AddBox(168, 72);
	App->boxes->AddBox(192, 168);
	App->boxes->AddBox(168, 144);
	App->boxes->AddBox(192, 120);

	App->player->position.x = 120;
	App->player->position.y = 48;

	/*App->player->currentScene = 2;*/	// Posici�n inicial de player en la Scene 1

	return ret;
}

update_status ModuleScene3::Update()
{
	if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene2, 60);

	}
	if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 60);

	}
	return update_status::UPDATE_CONTINUE;
}


update_status ModuleScene3::PostUpdate()
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

	//lose
	if (App->player->steps == 90) {
		App->boxes->Disable();
		App->render->Blit(lose, SCREEN_WIDTH / 2 - 68, SCREEN_HEIGHT / 2 - 36, NULL);


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

	if (boxEnd[0] == true && boxEnd[1] == true && boxEnd[2] == true && boxEnd[3] == true)
	{
		App->render->Blit(win, SCREEN_WIDTH / 2 - 62, SCREEN_HEIGHT / 2 - 36, NULL);

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			App->fade->FadeToBlack(this, (Module*)App->scene, 60);

		}
		LOG("level 3 completed");

	}

	return update_status::UPDATE_CONTINUE;
}
//disable the entities
bool ModuleScene3::CleanUp()
{
	//App->player->Disable();
	App->boxes->Disable();
	
	return true;
}