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
#include "ModuleBox.h"

ModulePlayer::ModulePlayer(bool startEnabled) :Module(startEnabled)
{
	flyMode = false;

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
	leftAnim.speed = 0.3f;

	upAnim.PushBack({ 9, 43,14,24 });
	upAnim.PushBack({ 33,43,14,24 });
	upAnim.PushBack({ 57,43,14,24 });
	upAnim.PushBack({ 81,43,14,24 });
	upAnim.PushBack({ 106,43,14,24 });
	upAnim.PushBack({ 130,43,14,24 });
	upAnim.PushBack({ 154,43,14,24 });
	upAnim.PushBack({ 178,43,14,24 });
	upAnim.loop = true;
	upAnim.speed = 0.3f;

	rightAnim.PushBack({ 211,9,14,24 });
	rightAnim.PushBack({ 235,9,14,24 });
	rightAnim.PushBack({ 259,9,14,24 });
	rightAnim.PushBack({ 280,9,14,24 });
	rightAnim.PushBack({ 307,9,14,24 });
	rightAnim.PushBack({ 331,9,14,24 });
	rightAnim.PushBack({ 355,9,14,24 });
	rightAnim.PushBack({ 379,9,14,24 });
	rightAnim.loop = true;
	rightAnim.speed = 0.3f;

	downAnim.PushBack({ 210,43,14,24 });
	downAnim.PushBack({ 234,43,14,24 });
	downAnim.PushBack({ 258,43,14,24 });
	downAnim.PushBack({ 282,43,14,24 });
	downAnim.PushBack({ 306,43,14,24 });
	downAnim.PushBack({ 330,43,14,24 });
	downAnim.PushBack({ 354,43,14,24 });
	downAnim.PushBack({ 378,43,14,24 });
	downAnim.loop = true;
	downAnim.speed = 0.3f;

	boxleftAnim.PushBack({ 9,75,16,21 });
	boxleftAnim.PushBack({ 33,76,17,20 });
	boxleftAnim.PushBack({ 57,76,18,20 });
	boxleftAnim.PushBack({ 81,75,17,21 });
	boxleftAnim.PushBack({ 105,76,16,20 });
	boxleftAnim.PushBack({ 129,76,17,20 });
	//boxleftAnim.PushBack({ 156,76,18,20 });	// sprites mal hechos por lo que no encaja :D 
	//boxleftAnim.PushBack({ 171,75,18,21 });
	boxleftAnim.loop = true;
	boxleftAnim.speed = 0.2f;

	boxupAnim.PushBack({ 11,104,12,21 });
	boxupAnim.PushBack({ 35,104,12,21 });
	boxupAnim.PushBack({ 59,104,12,22 });
	boxupAnim.PushBack({ 83,104,12,24 });
	boxupAnim.PushBack({ 107,104,12,21 });
	boxupAnim.PushBack({ 131,104,12,21 });
	boxupAnim.PushBack({ 155,104,12,22 });
	boxupAnim.PushBack({ 179,104,12,24 });
	boxupAnim.loop = true;
	boxupAnim.speed = 0.2f;

	boxdownAnim.PushBack({ 211,104,13,24 });
	boxdownAnim.PushBack({ 235,104,13,24 });
	boxdownAnim.PushBack({ 259,104,13,24 });
	boxdownAnim.PushBack({ 283,104,13,24 });
	boxdownAnim.PushBack({ 307,104,13,24 });
	boxdownAnim.PushBack({ 331,104,13,24 });
	boxdownAnim.PushBack({ 355,104,13,24 });
	boxdownAnim.PushBack({ 379,104,13,24 });
	boxdownAnim.loop = true;
	boxdownAnim.speed = 0.2f;

	boxrightAnim.PushBack({ 204,75,19,21 });
	boxrightAnim.PushBack({ 228,75,19,21 }); 
	boxrightAnim.PushBack({ 252,75,19,21 });
	boxrightAnim.PushBack({ 276,75,19,21 });
	boxrightAnim.PushBack({ 300,75,19,21 }); 
	boxrightAnim.PushBack({ 324,75,19,21 });
	boxrightAnim.PushBack({ 348,75,19,21 });
	boxrightAnim.PushBack({ 372,75,19,21 });

	boxrightAnim.loop = true;
	boxrightAnim.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/player.png");
	table= App->textures->Load("Assets/table2.png");
	currentAnimation = &idleLeftAnim;
	
	// Posición inicial (depende del lvl)
	position.x;
	position.y;

	// X, Y, anchura, altura, 
	collider = App->collisions->AddCollider({ position.x-5, position.y, 24, 24 }, Collider::Type::PLAYER, this);

	char lookupTable[] = { "0123456789 0123456789" };
	scoreFont = App->fonts->Load("Assets/font1.png", lookupTable, 2);

	return ret;
}

update_status ModulePlayer::Update()
{

	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) {
		flyMode = !flyMode;
	}
	
	if (flyMode == true) {	// Player Godmode movement (cause bugs because the player movement set is quit from the tiles )
		if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT) {
			position.x += 1;
		}
		if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT) {	
			position.y -= 1;
		}
		if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) {	
			position.x -= 1;
		}
		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {		
			position.y += 1;
		}
	}			// Player real movement , collisions and animations 
	else {
		if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT && nPosX == 0 && nPosY == 0) {		// mov Derecha
			nPosX = position.x + 24;
		}
		if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && nPosX == 0 && nPosY == 0) {		// mov arriba
			nPosY = position.y - 24;
		}
		if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT && nPosX == 0 && nPosY == 0) {		// mov izquierda
			nPosX = position.x - 24;
		}
		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT && nPosX == 0 && nPosY == 0) {		// mov abajo
			nPosY = position.y + 24;
		}
		if (nPosX != 0) {							// LEFT
			if (nPosX < position.x) {
				for (int i = 0; i < 16; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						if (map[i][j] == 1 || map[i][j] == 2) {		// colision pared
							if (position.x - 29 == i * 24 && position.y == j * 24) {
								canMove = false;
								nPosX = 0;
							}
							for (int k = 0; k < numBox; k++) {						// colision pared + caja
								if (position.x - 53 == i * 24 && position.y == j * 24 && position.x - 29 == App->boxes->boxes[k]->position.x && position.y == App->boxes->boxes[k]->position.y) {
									canMove = false;
									nPosX = 0;
								}
								for (int f = 0; f < numBox; f++) {				// collision box + box
									if (position.x - 29 == App->boxes->boxes[k]->position.x && position.y == App->boxes->boxes[k]->position.y && position.x - 53 == App->boxes->boxes[f]->position.x && position.y == App->boxes->boxes[f]->position.y) {
										canMove = false;
										nPosX = 0;
									}
								}
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
			else if (nPosX > position.x) {			// RIGHT
				for (int i = 0; i < 16; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						if (map[i][j] == 1 || map[i][j] == 2) {
							if (position.x + 19 == i * 24 && position.y == j * 24) {
								canMove = false;
								nPosX = 0;
							}
							for (int k = 0; k < numBox; k++) {
								if (position.x + 43 == i * 24 && position.y == j * 24 && position.x + 19 == App->boxes->boxes[k]->position.x && position.y == App->boxes->boxes[k]->position.y) {
									canMove = false;
									nPosX = 0;
								}
								for (int f = 0; f < numBox; f++) {				// collision box + box
									if (position.x + 19 == App->boxes->boxes[k]->position.x && position.y == App->boxes->boxes[k]->position.y && position.x + 43 == App->boxes->boxes[f]->position.x && position.y == App->boxes->boxes[f]->position.y) {
										canMove = false;
										nPosX = 0;
									}
								}
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
				nPosX = 0; steps++;				// Contador de pasos
			}
		}
		else if (nPosY != 0) {				// UP
			if (nPosY < position.y) {
				for (int i = 0; i < 16; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						if (map[i][j] == 1 || map[i][j] == 2) {
							if (position.x - 5 == i * 24 && position.y - 24 == j * 24) {
								canMove = false;
								nPosY = 0;
							}
							for (int k = 0; k < numBox; k++) {
								if (position.x - 5 == i * 24 && position.x - 5 == App->boxes->boxes[k]->position.x && position.y - 48 == j * 24 && position.y - 24 == App->boxes->boxes[k]->position.y) {
									canMove = false;
									nPosY = 0;
								}
								for (int f = 0; f < numBox; f++) {				// collision box + box
									if (position.x - 5 == App->boxes->boxes[k]->position.x && position.y - 24 == App->boxes->boxes[k]->position.y && position.x - 5 == App->boxes->boxes[f]->position.x && position.y - 48 == App->boxes->boxes[f]->position.y) {
										canMove = false;
										nPosY = 0;
									}
								}
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
			else if (nPosY > position.y) {					// DOWN
				for (int i = 0; i < 16; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						if (map[i][j] == 1 || map[i][j] == 2) {
							if (position.x - 5 == i * 24 && position.y + 24 == j * 24) {
								canMove = false;
								nPosY = 0;
							}
							for (int k = 0; k < numBox; k++) {
								if (position.x - 5 == i * 24 && position.x - 5 == App->boxes->boxes[k]->position.x && position.y + 48 == j * 24 && position.y + 24 == App->boxes->boxes[k]->position.y) {
									canMove = false;
									nPosY = 0;
								}
								for (int f = 0; f < numBox; f++) {				// collision box + box
									if (position.x - 5 == App->boxes->boxes[k]->position.x && position.y + 24 == App->boxes->boxes[k]->position.y && position.x - 5 == App->boxes->boxes[f]->position.x && position.y + 48 == App->boxes->boxes[f]->position.y) {
										canMove = false;
										nPosY = 0;
									}
								}
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
				nPosY = 0; steps++;
			}
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
	
	if (IsEnabled())
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	else {
		steps = 0000;
		limit = 00;
		stage = 00;
		delete collider;
	}


	sprintf_s(scoreText, 10, "%4d", steps);
	App->fonts->BlitText(339, 24, scoreFont, scoreText);

	sprintf_s(limitText, 10, "%4d", limit);
	App->fonts->BlitText(339, 34, scoreFont, limitText);

	sprintf_s(stageText, 10, "%2d", stage);
	App->fonts->BlitText(356, 12, scoreFont, stageText);

	App->render->Blit(table, 310, 10, NULL);

	//App->fonts->BlitText(50, 50, scoreFont, "123456");



	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	

	// que pasa al colisionar? pues aquí va
}