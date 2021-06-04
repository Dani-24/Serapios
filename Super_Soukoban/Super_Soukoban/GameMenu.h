#ifndef __GAMEMENU_H__
#define __GAMEMENU_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class GameMenu : public Module
{
public:
	GameMenu(bool startEnabled);
	~GameMenu();

	bool Start() override;

	update_status Update() override;
	update_status PostUpdate() override;

	bool CleanUp();

	Module* current = nullptr;
private:

	SDL_Texture* menu_lvl = nullptr;
	SDL_Texture* menu_title = nullptr;
	SDL_Texture* menu_options = nullptr;
	SDL_Texture* menu_pointer = nullptr;
	SDL_Texture* menu_bg = nullptr;
	uint menu_music = 0;
	uint nextFx = 0;
	uint backFx = 0;
	uint selectFx = 0;

	int pointerPosX = 130;
	int pointerPosY = 110;

	int music = 0;
	int menuFont = -1;


};

#endif // __GAMEMENU_H__