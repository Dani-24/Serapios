#ifndef _MODULEBOX_H_
#define _MODULEBOX_H_

#include "p2Point.h"
#include "Animation.h"
#include "Module.h"

#define MAX_BOXES 20

struct SDL_Texture;
struct Collider;

// Box

class Box {
public:
	Box(int x, int y);

	virtual ~Box();

	const Collider* GetCollider() const;

	virtual void Update();
	virtual void Draw();
	virtual void OnCollision(Collider* collider);

public:
	iPoint position;
	SDL_Texture* texture = nullptr;

	Animation* currentAnim = nullptr;
    Animation darkBoxAnim;

	int map[16][10] = {	// scene map. Obtained from Module Box 
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
protected:
	Collider* collider = nullptr;
	iPoint spawnPos;

private:
	Animation normalBoxAnim;
};

// Module Box

struct BoxSpawnpoint {
	bool boxSpawned = false;
	int x, y;
};

class ModuleBox :public Module {
public:
	ModuleBox(bool startEnabled);
	~ModuleBox();

	bool Start() override;

	update_status Update() override;
	update_status PostUpdate() override;

	bool CleanUp() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	bool AddBox(int x, int y);

	void HandleBoxSpawn();

    Box* boxes[MAX_BOXES] = { nullptr };

	int mandaMap[16][10] = {	// map obtained from the current Scene
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
private:
	void SpawnBox(const BoxSpawnpoint& info);

	BoxSpawnpoint spawnQueue[MAX_BOXES];
	SDL_Texture* texture = nullptr;
};
#endif // !_MODULEBOX_H_

