#include "ModuleCollisions.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "External_Libraries/SDL/include/SDL_scancode.h"

// This module should be called ModuleDRAWCollisions. The only function is to print the color of the colliders and nothing more, because in Super Soukoban collisions
// are completely different to the simple collision of box1 intersects with box2 and was better to put the collisions directly in the player and boxes movements.

ModuleCollisions::ModuleCollisions(bool startEnabled) :Module(startEnabled)
{
	for (uint i = 0; i < MAX_COLLIDERS;i++) {
		colliders[i] = nullptr;
}

	// Colliders wall:
	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::BOX] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::POINT] = false;

	// Colliders box:
	matrix[Collider::Type::BOX][Collider::Type::WALL] = true;
	matrix[Collider::Type::BOX][Collider::Type::BOX] = true;
	matrix[Collider::Type::BOX][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BOX][Collider::Type::POINT] = true;

	// Colliders player:
	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOX] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::POINT] = false;
	  
	// Colliders point:
	matrix[Collider::Type::POINT][Collider::Type::WALL] = false;
	matrix[Collider::Type::POINT][Collider::Type::BOX] = true;
	matrix[Collider::Type::POINT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::POINT][Collider::Type::POINT] = false;
}

ModuleCollisions::~ModuleCollisions() {

}

update_status ModuleCollisions::PreUpdate() {
	for (uint i = 0; i < MAX_COLLIDERS; i++) {
		if(colliders[i]!=nullptr && colliders[i]->pendingToDelete==true){
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; i++) {
		if (colliders[i] == nullptr) {
			continue;
		}
		c1 = colliders[i];
		for (uint k=i+1; k < MAX_COLLIDERS; ++k) {
			if (colliders[k] == nullptr) {
				continue;
			}
			c2 = colliders[k];

			if (matrix[c1->type][c2->type]&& c1->Intersects(c2->rect))
			{
				for(uint i=0;i<MAX_LISTENERS; ++i)
				{
					if ( c1->listeners[i]!=nullptr)
					{
					c1->listeners[i]->OnCollision(c1,c2);
					}
			    }
				for (uint i = 0; i < MAX_LISTENERS; ++i)
				{
					if (c2->listeners[i] != nullptr) {
						c2->listeners[i]->OnCollision(c2, c1);
					}
				}
			}
		}
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN) //  debug key
		debug = !debug;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return update_status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE: 
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::WALL:
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::PLAYER:
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::BOX:
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::POINT:
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		}
	}
}

bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}
