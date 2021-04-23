#include "ModuleCollisions.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "External_Libraries/SDL/include/SDL_scancode.h"

ModuleCollisions::ModuleCollisions() {
	for (uint i = 0; i < MAX_COLLIDERS;i++) {
		colliders[i] = nullptr;
	}

	// Colliders paredes:
	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::BOX] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::POINT] = false;

	// Colliders cajas:
	matrix[Collider::Type::BOX][Collider::Type::WALL] = true;
	matrix[Collider::Type::BOX][Collider::Type::BOX] = true;
	matrix[Collider::Type::BOX][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BOX][Collider::Type::POINT] = true;

	// Colliders player:
	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOX] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::POINT] = false;

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
		for (uint k=i+1; k < MAX_COLLIDERS; k++) {
			if (colliders[k] == nullptr) {
				continue;
			}
			c2 = colliders[k];
			if (c1->Intersects(c2->rect)) {
				if (matrix[c1->type][c2->type] && c1->listener) {
					c1->listener->OnCollision(c1,c2);
				}
				if (matrix[c2->type][c1->type] && c2->listener) {
					c2->listener->OnCollision(c2, c1);
				}
			}
		}
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) // tecla de debug
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
		case Collider::Type::NONE: // colores de los colliders en RGB
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
