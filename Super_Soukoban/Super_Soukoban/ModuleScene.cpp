#include "ModuleScene.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleBox.h"

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

	//bgTexture = App->textures->Load("Assets/background.png");

	App->audio->PlayMusic("Game/Assets/mlbattle.mp3", 1.0f);

	
	// Ejemplo Collider:
	// App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	// Ejemplo cajas: 
	// App->boxes->AddBox(600, 80);

	return ret;
}

update_status ModuleScene::Update()
{
	// Mover la camara (no necesario para el soukoban :D)
	App->render->camera.x += 0;

	return update_status::UPDATE_CONTINUE;
}


update_status ModuleScene::PostUpdate()
{
	// Aqui se dibuja el fondo
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}