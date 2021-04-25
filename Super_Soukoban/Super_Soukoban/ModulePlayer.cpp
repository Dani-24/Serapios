#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "External_libraries/SDL/include/SDL_scancode.h"
#include<stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) :Module(startEnabled)
{
	// Aqui van las animaciones del player
	idleLeftAnim.PushBack({ 9,9,14,24 });
	idleUpAnim.PushBack({ 9,43,14,24 });
	idleRightAnim.PushBack({ 211,9,14,24 });
	idleDownAnim.PushBack({ 210,43,14,24 });

	leftAnim.PushBack({ 9,9,14,24 });
	leftAnim.PushBack({ 33,9,14,24 });
	leftAnim.PushBack({ 57,9,14,24 });
	leftAnim.PushBack({ 81,9,14,24 });
	leftAnim.PushBack({ 106,9,14,24 });
	leftAnim.PushBack({ 130,9,14,24 });
	leftAnim.PushBack({ 154,9,14,24 });
	leftAnim.PushBack({ 178,9,14,24 });
	leftAnim.loop = true;
	leftAnim.speed = 0.2f;

	upAnim.PushBack({ 9, 43,14,24 });
	upAnim.PushBack({ 33,43,14,24 });
	upAnim.PushBack({ 57,43,14,24 });
	upAnim.PushBack({ 81,43,14,24 });
	upAnim.PushBack({ 106,43,14,24 });
	upAnim.PushBack({ 130,43,14,24 });
	upAnim.PushBack({ 154,43,14,24 });
	upAnim.PushBack({ 178,43,14,24 });
	upAnim.loop = true;
	upAnim.speed = 0.2f;

	rightAnim.PushBack({ 211,9,14,24 });
	rightAnim.PushBack({ 235,9,14,24 });
	rightAnim.PushBack({ 259,9,14,24 });
	rightAnim.PushBack({ 280,9,14,24 });
	rightAnim.PushBack({ 307,9,14,24 });
	rightAnim.PushBack({ 331,9,14,24 });
	rightAnim.PushBack({ 355,9,14,24 });
	rightAnim.PushBack({ 379,9,14,24 });
	rightAnim.loop = true;
	rightAnim.speed = 0.2f;

	downAnim.PushBack({ 210,43,14,24 });
	downAnim.PushBack({ 234,43,14,24 });
	downAnim.PushBack({ 258,43,14,24 });
	downAnim.PushBack({ 282,43,14,24 });
	downAnim.PushBack({ 306,43,14,24 });
	downAnim.PushBack({ 330,43,14,24 });
	downAnim.PushBack({ 354,43,14,24 });
	downAnim.PushBack({ 378,43,14,24 });
	downAnim.loop = true;
	downAnim.speed = 0.2f;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/player.png");
	currentAnimation = &idleLeftAnim;

	//walkingFx = App->audio->LoadFx("Assets/sonido.wav");
	//movingBoxFx = App->audio->LoadFx("Assets/sonido.wav");

	// Posición inicial (depende del lvl)
	
	switch (currentScene) {
	case 0:
		position.x = 150;
		position.y = 48;
		break;
	case 1:
		position.x = 200;
		position.y = 72;
		break;
	}
	// X, Y, anchura, altura, 
	collider = App->collisions->AddCollider({ position.x-5, position.y, 24, 24 }, Collider::Type::PLAYER, this);

	char lookupTable[] = { "0123456789 0123456789" };
	scoreFont = App->fonts->Load("Assets/font.png", lookupTable, 2);

	return ret;
}

update_status ModulePlayer::Update()
{
	
	// Player movement and animations 
	
		if ((App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)) {
			

			position.y -= 1;
			
			if (currentAnimation != &upAnim) {
				upAnim.Reset();
				currentAnimation = &upAnim;
			}
		}
		else if ((App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)) {
			
			position.y += 1;
			
			if (currentAnimation != &downAnim) {
				downAnim.Reset();
				currentAnimation = &downAnim;
			}
		}
		if ((App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) ) {
			
			position.x -= 1;

			
			if (currentAnimation != &leftAnim) {
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
		}
		else if ((App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT) ) {
			
			position.x += 1;
			
			if (currentAnimation != &rightAnim) {
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}
		}
		/*if ((position.x % 24 == 0 || position.y % 24 == 0) && move == true) {
			score += 1;
			
		}*/
	

	// Here we make the player stop de animation when stop walking
	if(App->input->keys[SDL_SCANCODE_D] == KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == KEY_IDLE && App->input->keys[SDL_SCANCODE_A] == KEY_IDLE && App->input->keys[SDL_SCANCODE_W] == KEY_IDLE) {
		if (currentAnimation == &leftAnim) {
			if (currentAnimation != &idleLeftAnim) {
				idleLeftAnim.Reset();
				currentAnimation = &idleLeftAnim;
			}
		}
		if (currentAnimation == &upAnim) {
			if (currentAnimation != &idleUpAnim) {
				idleUpAnim.Reset();
				currentAnimation = &idleUpAnim;
			}
		}
		if (currentAnimation == &rightAnim) {
			if (currentAnimation != &idleRightAnim) {
				idleRightAnim.Reset();
				currentAnimation = &idleRightAnim;
			}
		}
		if (currentAnimation == &downAnim) {
			if (currentAnimation != &idleDownAnim) {
				idleDownAnim.Reset();
				currentAnimation = &idleDownAnim;
			}
		}
	}
	
	// Auto player movement
	if (currentAnimation == &idleLeftAnim && (position.x % 24)-5 != 0) {
		position.x -= 1;
		currentAnimation = &leftAnim;
	}
	if (currentAnimation == &idleUpAnim && (position.y % 24) != 0) {
		position.y -= 1;
		currentAnimation = &upAnim;
	}
	if (currentAnimation == &idleRightAnim && (position.x % 24)-5 != 0) {
		position.x += 1;
		currentAnimation = &rightAnim;
	}
	if (currentAnimation == &idleDownAnim && (position.y % 24) != 0) {
		position.y += 1;
		currentAnimation = &downAnim;
	}

	
	collider->SetPos(position.x-5, position.y);	// player hitbox

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) {		// Apagar programa con ESC
		return update_status::UPDATE_STOP;
	}
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	sprintf_s(scoreText, 10, "%4d", score);
	App->fonts->BlitText(50, 50, scoreFont, scoreText);
	//App->fonts->BlitText(50, 50, scoreFont, "123456");



	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	

	// que pasa al colisionar? pues aquí va
}