#include"ModuleAudio.h"
#include "Application.h"

#include "External_Libraries/SDL/include/SDL.h" // abreviar si se puede
#include "External_Libraries/SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "External_Libraries/SDL_mixer/libx86/SDL2_mixer.lib")

ModuleAudio::ModuleAudio()
{
	for (uint i = 0; i < MAX_FX; ++i) 
	{
		soundFx[i] = nullptr;
	}
}

ModuleAudio::~ModuleAudio()
{

}

bool ModuleAudio::Init() {
	LOG("Auddo Mixer Loading");
	bool ret = true;
	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SLD_INIT_AUDIO no se ha podido inicializar :( SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	// carga el formato OGG
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("no se ha podido inicializar Mixer lib.Mix_Init :( SDL_Error: %s\n", Mix_GetError());
		ret = false;
	}
	//inicializa sdl mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("no se ha podido inicializar SDL_Mixer :( SDL_Mixer Error: %s\n", Mix_GetError());
		ret = false;
	}
	return ret;
}

bool ModuleAudio::CleanUp()
{
	LOG("Sound FX, cerrando Mixer y Audio subsystem");

	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}

	for (uint i=0;i<MAX_FX;++i)
	{ 
		if (soundFx[i] != nullptr) 
		{
			Mix_FreeChunk(soundFx[i]);
	    }
	}

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

//holaaa