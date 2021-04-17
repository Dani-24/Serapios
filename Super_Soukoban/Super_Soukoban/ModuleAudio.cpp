#include"ModuleAudio.h"
#include "Application.h"

#include "External_Libraries/SDL/include/SDL.h" // abreviar si se puede
#include "External_Libraries/SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "External_Libraries/SDL_mixer/libx86/SDL2_mixer.lib")

ModuleAudio::ModuleAudio()
{
	for (uint i = 0; i < MAX_FX; ++i) {
		soundFx[i] = nullptr;
	}

}

ModuleAudio::~ModuleAudio()
{
	


}