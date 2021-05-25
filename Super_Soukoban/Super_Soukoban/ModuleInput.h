#ifndef __MODULE_INPUT_H_
#define __MODULE_INPUT_H_


#include "Module.h"
#include "Globals.h"

#include "External_Libraries/SDL/include/SDL_scancode.h"

#define MAX_KEYS 256

#define MAX_PADS 4

struct _SDL_GameController;
struct _SDL_Haptic;


enum KEY_STATE
{
	KEY_IDLE,
    KEY_DOWN,
    KEY_REPEAT,
    KEY_UP
};


struct GamePad
{
	// Input data
	bool start, back, guide;
	bool x, y, a, b, l1, r1, l3, r3;
	bool up, down, left, right;
	float l2, r2;
	float left_x, left_y, right_x, right_y, left_dz, right_dz;

	// Controller data
	bool enabled;
	int index;
	_SDL_GameController* controller;
	_SDL_Haptic* haptic;

	// Rumble controller
	int rumble_countdown;
	float rumble_strength;
};

class ModuleInput :public Module {
public:
    ModuleInput(bool startEnabled);

    ~ModuleInput();

    bool Init() override;
    update_status PreUpdate() override;
    bool CleanUp() override;
	//ACTIVE gampad when is connected
	void HandleDeviceConnection(int index);
	// DESACTIVE gampad when is disconnected
	void HandleDeviceRemoval(int index);
	//iterates through all active gamepads
	void UpdateGamepadsInput();

	bool ShakeController(int id, int duration, float strenght = 0.5f);
	const char* GetControllerName(int id)const;

public:
    KEY_STATE keys[MAX_KEYS] = { KEY_IDLE };
	//array for detected pads
	GamePad pads[MAX_PADS];
};

#endif // __MODULE_INPUT_H_