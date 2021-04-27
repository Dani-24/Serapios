#include "ModuleBox.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "ModuleScene3.h"
// BOX	-- Maneja una caja

Box::Box(int x, int y) :position(x, y) {
	spawnPos = position;

	normalBoxAnim.PushBack({ 0,0,24,24 });
	currentAnim = &normalBoxAnim;
	darkBoxAnim.PushBack({ 40,0,24,24 });

	collider = App->collisions->AddCollider({ 0,0,24,24 }, Collider::Type::BOX, (Module*)App->boxes);
}

Box::~Box() {
	if (collider != nullptr) {
		collider->pendingToDelete = true;
	}
}
const Collider* Box::GetCollider() const {
	return collider;
}

void Box::Update() {

	// aqui va el mov de la caja
	bool d = true;
	if (position.x - 17 == App->player->position.x && position.y == App->player->position.y) {	//17?
		position.x += 1;
		d = true;
	}
	if (position.x + 27 == App->player->position.x && position.y == App->player->position.y) {	//17?
		position.x -= 1;
		d = false;
	}
	if (position.y - 22 == App->player->position.y && position.x == App->player->position.x - 5) {	//17?
		position.y += 1;
		d = false;
	}
	if (position.y + 22 == App->player->position.y && position.x == App->player->position.x - 5) {	//17?
		position.y -= 1;
		d = true;
	}

	if (position.x % 24 != 0 && d == true) {
		position.x += 1;
		d = false;
	}
	if (position.x % 24 != 0 && d == false) {
		position.x -= 1;
		d = true;
	}
	if (position.y % 24 != 0 && d == true) {
		position.y -= 1;
		d = false;
	}
	if (position.y % 24 != 0 && d == false) {
		position.y += 1;
		d = true;
	}

	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (App->scene->map[i][j] == 4) {
				if (position.x == i * 24 && position.y == j * 24) {
					currentAnim = &darkBoxAnim;
					
				}
			}
			
		}
	}

	if (currentAnim != nullptr) {
		currentAnim->Update();
	}
	if (collider != nullptr) {
		collider->SetPos(position.x, position.y);
	}
}

void Box::Draw() {
	if (currentAnim != nullptr) {
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
	}
}

void Box::OnCollision(Collider* collider) {

}

// MODULE BOX	-- maneja las cajas 

ModuleBox::ModuleBox(bool startEnabled) : Module(startEnabled){
	for (uint i = 0; i < MAX_BOXES; ++i) {
		boxes[i] = nullptr;
	}
}

ModuleBox::~ModuleBox() {

}

bool ModuleBox::Start() {
	texture = App->textures->Load("Assets/boxes.png");
	return true;
}

update_status ModuleBox::Update() {

	HandleBoxSpawn();

	for (uint i = 0; i < MAX_BOXES; ++i) {
		if (boxes[i] != nullptr) {
			boxes[i]->Update();
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleBox::PostUpdate() {
	for (uint i = 0; i < MAX_BOXES; ++i) {
		if (boxes[i] != nullptr) {
			boxes[i]->Draw();
		}
	}
	return update_status::UPDATE_CONTINUE;
}

bool ModuleBox::CleanUp() {
	LOG("Deleting all boxes");
	for (uint i = 0; i < MAX_BOXES; ++i)
	{
		if (boxes[i] != nullptr)
		{
			delete boxes[i];
			boxes[i] = nullptr;
		}
	}

	return true;
}

bool ModuleBox::AddBox(int x, int y) {
	bool ret = false;

	for (uint i = 0; i < MAX_BOXES; i++) {
		if (spawnQueue[i].boxSpawned != true) {
			LOG("Adding box %d", i);
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			spawnQueue[i].boxSpawned = true;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleBox::HandleBoxSpawn() {

	for (uint i = 0; i < MAX_BOXES; i++) {
		if (spawnQueue[i].boxSpawned != false) {
			SpawnBox(spawnQueue[i]);
			spawnQueue[i].boxSpawned = false;
		}
	}
}

void ModuleBox::SpawnBox(const BoxSpawnpoint& info) {
	for (uint i = 0; i < MAX_BOXES; i++) {
		if (boxes[i] == nullptr) {

			boxes[i] = new Box(info.x, info.y);
			boxes[i]->texture = texture;
			break;
		}
	}
}

void ModuleBox::OnCollision(Collider* c1, Collider* c2) {
	
}