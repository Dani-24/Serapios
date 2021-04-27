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
#include <stdio.h> // Camarada
#include "ModuleScene.h"

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

	// Posici�n inicial (depende del lvl)
	
	switch (currentScene) {
	case 0:
		position.x = 173;
		position.y = 48;
		break;
	case 1:
		position.x = 200;
		position.y = 72;
		break;
	case 2:
	    position.x = 250;
		position.y = 150;
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
	
	if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && nPosX == 0) {
		nPosX = position.x + 24;
	}
	if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && nPosY == 0) {
		nPosY = position.y - 24;
	}
	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && nPosX == 0) {
		nPosX = position.x - 24;
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && nPosY == 0) {
		nPosY = position.y + 24;
	}
	if (nPosX != 0) {
		if (nPosX < position.x) {
			for (int i = 0; i < 16; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					if (App->scene->map[i][j] == 1 || App->scene->map[i][j] == 2) {
						if (position.x - 29 == i * 24 && position.y == j * 24) {
							canMove = false;
							nPosX = 0;
						}
					}
				}
			}
			if (canMove == true) {
				position.x -= 1;
			}
			if (currentAnimation != &leftAnim) {
				currentAnimation = &leftAnim;
			}
			canMove = true;
		}
		else if (nPosX > position.x) {
			for (int i = 0; i < 16; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					if (App->scene->map[i][j] == 1 || App->scene->map[i][j] == 2) {
						if (position.x + 19 == i * 24 && position.y == j * 24) {
							canMove = false;
							nPosX = 0;
						}
					}
				}
			}
			if (canMove == true) {
				position.x += 1;
			}
			if (currentAnimation != &rightAnim) {
				currentAnimation = &rightAnim;
			}
			canMove = true;
		}
		else if (nPosX == position.x) {
			nPosX = 0;
		}
	}
	else if (nPosY != 0) {
		if (nPosY < position.y) {
			for (int i = 0; i < 16; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					if (App->scene->map[i][j] == 1 || App->scene->map[i][j] == 2) {
						if (position.x - 5 == i * 24 && position.y - 24 == j * 24) {
							canMove = false;
							nPosY = 0;
						}
					}
				}
			}
			if (canMove == true) {
				position.y -= 1;
			}
			if (currentAnimation != &upAnim) {
				currentAnimation = &upAnim;
			}
			canMove = true;
		}
		else if (nPosY > position.y) {
			for (int i = 0; i < 16; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					if (App->scene->map[i][j] == 1 || App->scene->map[i][j] == 2) {
						if (position.x - 5 == i * 24 && position.y + 24 == j * 24) {
							canMove = false;
							nPosY = 0;
						}
					}
				}
			}
			if (canMove == true) {
				position.y += 1;
			}
			if (currentAnimation != &downAnim) {
				currentAnimation = &downAnim;
			}
			canMove = true;
		}
		else if (nPosY == position.y) {
			nPosY = 0;
		}
	}

	// player stop the animation when stop walking
	if (nPosX == 0 && nPosY == 0) {
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
	
	collider->SetPos(position.x-5, position.y);	// player hitbox

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	/*if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->scene2, 60);

	}
	*/
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) {		// Apagar programa con ESC
		return update_status::UPDATE_STOP;
	}
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	sprintf_s(scoreText, 10, "%4d", steps);
	App->fonts->BlitText(350, 15, scoreFont, scoreText);
	//App->fonts->BlitText(50, 50, scoreFont, "123456");



	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	

	// que pasa al colisionar? pues aqu� va
}