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
	idleLeftAnim.PushBack({ 9,9,14,24 });


	leftAnim.PushBack({ 9,9,14,24 });
	leftAnim.PushBack({ 33,9,14,24 });
	leftAnim.PushBack({ 9,9,14,24 });
	leftAnim.PushBack({ 9,9,14,24 });
	leftAnim.PushBack({ 9,9,14,24 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;


	texture = App->textures->Load("Assets/player.png");
	currentAnimation = &idleAnim;


	//walkingFx = App->audio->LoadFx("Assets/sonido.wav");
	//movingBoxFx = App->audio->LoadFx("Assets/sonido.wav");

	position.x = 0;
	position.y = 0;

	// X, Y, anchura, alturra, 
	collider = App->collisions->AddCollider({ position.x, position.y, 200, 200 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	
	// Aqui van los movimientos mediante ifs y SDL_SCANCODE_*TECLA == KEY_STATE::KEY_REPEAT
	if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT) {
		position.y -= 1;
	}
	else if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) {
		position.x -= 1;
		if (currentAnimation != &leftAnim) {
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
		position.y += 1;
	}
	else if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT) {
		position.x += 1;
	}
	else {
		if (currentAnimation != &idleLeftAnim) {		// hacer con el if que detecte cual fue la anterior animacion par a que la current sea en esa direccion
			idleLeftAnim.Reset();
			currentAnimation = &idleLeftAnim;
		}
	}


	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) {		// Apagar programa con ESC
		return update_status::UPDATE_STOP;
	}
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	// que pasa al colisionar? pues aquí va
}