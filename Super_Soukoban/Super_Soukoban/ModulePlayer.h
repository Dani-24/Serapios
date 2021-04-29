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
	ModulePlayer(bool startEnabled);
	~ModulePlayer();

	bool Start() override;

	// Processes new input and handles player movement
	update_status Update() override;
	// Performs the render call of the player sprite
	update_status PostUpdate() override;
	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;	
	int nPosX = 0;
	int nPosY = 0;
	// The speed in which we move the player (pixels per frame)
	int speed = 1;
	bool destroyed = false;
	// The player spritesheet
	SDL_Texture* texture = nullptr;
	SDL_Texture* table = nullptr;
	// The pointer to the current player animation
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleLeftAnim;
	Animation idleRightAnim;
	Animation idleUpAnim;
	Animation idleDownAnim;
	Animation upAnim;
	Animation downAnim;
	Animation leftAnim;
	Animation rightAnim;
	
	Animation boxupAnim;
	Animation boxdownAnim;
	Animation boxleftAnim;
	Animation boxrightAnim;

	Collider* collider = nullptr;

	uint steps = 0000;
	uint limit = 90;
	uint stage = 01;

	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	int limitFont = -1;
	char limitText[10] = { "\0" };

	int stageFont = -1;
	char stageText[10] = { "\0" };

	bool canMove = true;
	int currentScene;
	uint numBox;

	int map[16][10] = {	// mapa, se va a llamar desde cada scene para cambiarse
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
	};
};

#endif //!__MODULE_PLAYER_H__