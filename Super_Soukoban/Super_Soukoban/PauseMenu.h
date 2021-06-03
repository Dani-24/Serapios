#ifndef __PAUSEMENU_H__
#define __PAUSEMENU_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class PauseMenu : public Module
{
public:
	PauseMenu(bool startEnabled);
	~PauseMenu();

	bool Start() override;

	update_status Update() override;
	update_status PostUpdate() override;

	bool CleanUp();

	Module* current;
private:

	SDL_Texture* menuSurface = nullptr;
	SDL_Texture* pointer = nullptr;

	uint nextFx = 0;
	uint backFx = 0;

	int pointerPosX = 130;
	int pointerPosY = 110;

	int music = 0;
	int menuFont = -1;

	
};

#endif // __PAUSEMENU_H__