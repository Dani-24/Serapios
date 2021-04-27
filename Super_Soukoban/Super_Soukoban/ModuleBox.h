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
	

protected:
	Animation* currentAnim = nullptr;
	Collider* collider = nullptr;
	iPoint spawnPos;

private:
	Animation normalBoxAnim;
	Animation darkBoxAnim;
	
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

private:
	void SpawnBox(const BoxSpawnpoint& info);

	BoxSpawnpoint spawnQueue[MAX_BOXES];

	Box* boxes[MAX_BOXES] = { nullptr };

	SDL_Texture* texture = nullptr;

};
#endif // !_MODULEBOX_H_

