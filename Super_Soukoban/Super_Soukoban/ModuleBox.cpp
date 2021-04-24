// Modulo para las cajas del juego

#include "ModuleBox.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"


ModuleBox::ModuleBox(bool startEnabled) :Module(startEnabled)
{
	for (uint i = 0; i < MAX_BOXES; i++)
		boxes[i] = nullptr;
}
ModuleBox::~ModuleBox()
{
}

bool ModuleBox::Start() {
	
	//texture = App->textures->Load("");		Poner archivo png de la caja
	
	return true;
}

update_status ModuleBox::Update() {

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleBox::PostUpdate() {
	for (uint i = 0; i < MAX_BOXES; ++i)
	{
		/*if (boxes[i] != nullptr) {
			boxes[i]->Draw();
		}*/
	}
	return update_status::UPDATE_CONTINUE;
}

bool ModuleBox::CleanUp() {
	LOG("Deleting boxes");
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

	// añadir cajas (to do)

	return ret;
}

void ModuleBox::OnCollision(Collider* c1, Collider* c2)
{
	//for (uint i = 0; i < MAX_BOXES; ++i)
	//{
	//	if (boxes[i] != nullptr && boxes[i]->GetCollider() == c1)
	//	{
	//		boxes[i]->OnCollision(c2); //Notify the enemy of a collision

	//		delete boxes[i];
	//		boxes[i] = nullptr;
	//		break;
	//	}
	//}
}