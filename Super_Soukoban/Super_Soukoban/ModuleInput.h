#ifndef __MODULE_INPUT_H_
#define __MODULE_INPUT_H_


#include "Module.h"
#include "Globals.h"

#define MAX_KEYS 256

enum KEY_STATE
{
	KEY_IDLE,
    KEY_DOWN,
    KEY_REPEAT,
    KEY_UP
};

class ModuleInput :public Module {
public:
    ModuleInput();

    ~ModuleInput();

    bool Init() override;
    update_status PreUpdate() override;
    bool CleanUp() override;
public:
    KEY_STATE keys[MAX_KEYS] = { KEY_IDLE };
};

#endif