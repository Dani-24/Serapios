#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

struct Collider;

class Module{
public:
	virtual bool Init();
	virtual bool Start();
	virtual update_status PreUpdate();
	virtual update_status Update();
	virtual update_status PostUpdate();
	virtual bool CleanUp();
	virtual void OnCollision(Collider* c1, Collider* c2);

	int NumScene; // en que lvl esta
};

#endif // __MODULE_H__