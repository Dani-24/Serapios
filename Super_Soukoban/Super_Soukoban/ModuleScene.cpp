#include "ModuleScene.h"
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

ModuleScene::ModuleScene(bool startEnabled) :Module(startEnabled)
{

}

ModuleScene::~ModuleScene()
{

}

bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	
	background = App->textures->Load("Assets/tiles/background.png");
	wall = App->textures->Load("Assets/tiles/wall.png");
	wall2 = App->textures->Load("Assets/tiles/wall2.png");
	ground = App->textures->Load("Assets/tiles/ground.png");
	point = App->textures->Load("Assets/tiles/point.png");

	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);

	//to active the entities
	App->player->Enable();
	App->boxes->Enable();

	// Boxes lvl1 :
	App->boxes->AddBox(144, 96);
	App->boxes->AddBox(96, 144);
	App->boxes->AddBox(192, 120);

    /*App->player->currentScene = 0;*/	// Posición inicial de player en la Scene 1

	return ret;
}

update_status ModuleScene::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneintro, 60);

	}
	if (App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene3, 60);

	}
	
	return update_status::UPDATE_CONTINUE;
}


update_status ModuleScene::PostUpdate()
{
	// Aqui se dibuja el fondo

	int type = 0;
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			type=map[i][j];

			switch (type)
			{
			case 0:
				App->render->Blit(background, i*24, j*24, NULL);
				break;
			case 1:
				App->render->Blit(wall, i * 24, j * 24, NULL);
				App->collisions->AddCollider({ i*24 , j*24 , 24 , 24 }, Collider::Type::WALL);
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

	return update_status::UPDATE_CONTINUE;
}
//disable the entities
bool ModuleScene::CleanUp()
{
	//App->player->Disable();
	App->boxes->Disable();

	return true;
}