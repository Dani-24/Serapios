#include "ModuleScene.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleBox.h"
int Scene1[10][16] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
	{0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0},
	{0,0,3,3,4,3,3,0,0,0,0,0,0,0,0,0},
	{0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0},
	{0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

ModuleScene::ModuleScene()
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
	wall2 = App->textures->Load("Assets/wall2.png");
	ground = App->textures->Load("Assets/tiles/ground.png");
	point = App->textures->Load("Assets/tiles/point.png");
	

	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);

	Update(Scene1);
	
	// Ejemplo Collider:
	// App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	// Ejemplo cajas: 
	// App->boxes->AddBox(600, 80);

	return ret;
}

update_status ModuleScene::Update(int arr[10][16])
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			map[i][j] == arr[i][j];
		}
	}
	return update_status::UPDATE_CONTINUE;
}


update_status ModuleScene::PostUpdate()
{
	// Aqui se dibuja el fondo

	int type = 0;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			type=map[i][j];
			switch (type)
			{
			case 0:
				App->render->Blit(background, i*24, j*24, NULL);
				break;
			case 1:
				App->render->Blit(wall, i * 24, j * 24, NULL);
				break;
			case 2:
				App->render->Blit(wall2, i * 24, j * 24, NULL);
				break;
			case 3:
				App->render->Blit(ground, i * 24, j * 24, NULL);
				break;
			case 4:
				App->render->Blit(point, i * 24, j * 24, NULL);
				break;
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}