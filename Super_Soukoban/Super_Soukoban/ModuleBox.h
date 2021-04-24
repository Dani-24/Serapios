// Modulo para las cajas del juego

#ifndef __MODULE_BOX_H__
#define __MODULE_BOX_H__

#include "Module.h"

#define MAX_BOXES 100

class Box;
struct SDL_Texture;
struct Collider;

class ModuleBox : public Module
{
public:
	ModuleBox(bool startEnabled) ;
	~ModuleBox();

	bool Start() override;
	update_status Update() override;
	update_status PostUpdate() override;
	void OnCollision(Collider* c1, Collider* c2) override;

	bool CleanUp() override;
	bool AddBox(int x, int y);


private:

	Box* boxes[MAX_BOXES] = { nullptr };
	SDL_Texture* texture = nullptr;
	Collider* collider = nullptr;

	//animation movimientos de box?? tiene acaso?
};

#endif //!__MODULE_PLAYER_H__