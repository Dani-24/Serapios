#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "External_libraries/SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
{
	// Aqui van las animaciones del player

	// Ejemplo animaciones
	/*upAnim.PushBack({ 100, 1, 32, 14 });
	upAnim.PushBack({ 132, 0, 32, 14 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;*/
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/captura54.png");
	currentAnimation = &idleAnim;
	//walkingFx = App->audio->LoadFx("Assets/sonido.wav");
	//movingBoxFx = App->audio->LoadFx("Assets/sonido.wav");

	position.x = 500;
	position.y = 500;

	// X, Y, anchura, alturra, 
	collider = App->collisions->AddCollider({ position.x, position.y, 15, 15 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	
	// Aqui van los movimientos mediante ifs y SDL_SCANCODE_*TECLA == KEY_STATE::KEY_REPEAT

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	/*if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}*/

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	// que pasa al colisionar? pues aquí va
}