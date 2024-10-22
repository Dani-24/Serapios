#pragma once
#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "Module.h"
#include "External_Libraries/SDL/include/SDL_rect.h"
class ModuleFadeToBlack : public Module
{
public:
	ModuleFadeToBlack(bool startEnabled);

	~ModuleFadeToBlack();

	bool Start()override;

	update_status Update() override;

	update_status PostUpdate()override;
	//call another module and starts the proces to fade
	bool FadeToBlack(Module* toDisable, Module* toEnable, float frames = 60);
private:

	enum Fade_Step
	{
		NONE,
		TO_BLACK,
		FROM_BLACK
	}currentStep= Fade_Step::NONE;
	//frame count
	Uint32 frameCount = 0;
	Uint32 maxFadeFrames = 0;
	//rectangle of the screen
	SDL_Rect screenRect;

	Module* moduleToEnable = nullptr;
	Module* moduleToDisable = nullptr;
};

#endif //__MODULEFADETOBLACK_H__