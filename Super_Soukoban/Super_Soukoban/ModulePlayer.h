#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

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
	
	iPoint position;			

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	bool destroyed = false;

	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation leftAnim;
	Animation rightAnim;
	// + animation movimientos de box??

	Collider* collider = nullptr;

	// Sound effects
	uint walkingFx = 0;
	uint movingBoxFx = 0;

};

#endif //!__MODULE_PLAYER_H__