#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

struct Collider;

class Module{
public:

	Module(bool startEnabled);
	virtual bool Init();
	virtual bool Start();
	virtual update_status PreUpdate();
	virtual update_status Update();
	virtual update_status PostUpdate();
	virtual bool CleanUp();
	virtual void OnCollision(Collider* c1, Collider* c2);
	void Enable();
	void Disable();
	inline bool IsEnabled()const { return  isEnabled; }
private:
	bool isEnabled = true;
};

#endif // __MODULE_H__