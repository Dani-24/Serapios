#ifndef __MODULE_COLLISIONS_H__
#define __MODULE_COLLISIONS_H__

#define MAX_COLLIDERS 50 // Se intuye que es (cambiar si se necesita)
#include "Module.h"
#include "Collider.h"

class ModuleCollisions :public Module {
public:
	ModuleCollisions();
	~ModuleCollisions();

	update_status PreUpdate();	// comprobar collisiones
	update_status Update();		// debug mode on/off
	update_status PostUpdate();	// dibuja colliders (si debug m. on)

	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, Collider::Type type, Module* listener = nullptr);

	void DebugDraw();

private:
	Collider* colliders[MAX_COLLIDERS] = { nullptr };
	bool matrix[Collider::Type::MAX][Collider::Type::MAX];
	bool debug = false;
};

#endif // !__MODULE_COLLISIONS_H__
