#ifndef __MODULE_BOX_H__
#define __MODULE_BOX_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start() override;

	// Processes new input and handles player movement
	update_status Update() override;
	// Performs the render call of the player sprite
	update_status PostUpdate() override;
	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the box in the map
	iPoint position;
	int newPos = 0;

	// The speed in which we move the box (pixels per frame)
	int speed = 1;
	bool destroyed = false;
	int acum;

	// The box spritesheet
	SDL_Texture* texture = nullptr;

	// The pointer to the current box animation
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation endAnim;


	Collider* collider = nullptr;


};

#endif //!__MODULE_BoX_H__