#ifndef __MODULE_COLLISIONS_H__
#define __MODULE_COLLISIONS_H__

#define MAX_COLLIDERS 1000 
#include "Module.h"
#include "Collider.h"

class ModuleCollisions :public Module {
public:
	ModuleCollisions(bool startEnabled) ;
	~ModuleCollisions();

	update_status PreUpdate();	// comprobar collisiones
	update_status Update();		// debug mode on/off
	update_status PostUpdate();	// draw colliders 

	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, Collider::Type type, Module* listener = nullptr);

	void DebugDraw();

	Collider* colliders[MAX_COLLIDERS] = { nullptr };

private:
	
	bool matrix[Collider::Type::MAX][Collider::Type::MAX];
	bool debug = false;
};

#endif // !__MODULE_COLLISIONS_H__
