#include"ModuleAudio.h"
#include "Application.h"

#include "External_Libraries/SDL/include/SDL.h" // abreviar si se puede
#include "External_Libraries/SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "External_Libraries/SDL_mixer/libx86/SDL2_mixer.lib")

ModuleAudio::ModuleAudio(bool startEnabled) : Module(startEnabled)
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
		LOG("SLD_INIT_AUDIO could not initialize:( SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	// carga el formato OGG
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("could not initialize Mixer lib.Mix_Init :( SDL_Error: %s\n", Mix_GetError());
		ret = false;
	}
	//inicializa sdl mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_Mixer :( SDL_Mixer Error: %s\n", Mix_GetError());
		ret = false;
	}
	return ret;
}

bool ModuleAudio::CleanUp()
{
	LOG("freeingSound FX, closing Mixer y Audio subsystem");

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

bool ModuleAudio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;
	
	if (music != NULL)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n",path, Mix_GetError());
		ret = false;
	}
	else {
		if(fade_time>0.0f)
		{
			if(Mix_FadeInMusic(music,-1,(int)(fade_time * 1000.0f))<0)
			{
				LOG("Cannot dae in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
        else
	    {
		    if (Mix_PlayMusic(music, -1) < 0)
		    {
			     LOG("Cannot play music %s. Mix_GetError(): %s\n", path, Mix_GetError());
				 ret = false;
			}
	    }
	}

    LOG("Successfully playing %s", path);
    return ret;
}

bool ModuleAudio::PauseMusic() {
	bool ret = true;
	if (Mix_PlayMusic(music, -1) != 0) {
		Mix_PauseMusic();
	}
	return ret;
}

uint ModuleAudio::LoadFx(const char* path)
{
	uint ret = 0;
	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == nullptr)
	{
		LOG("Cannot load WAV %s. Mix_GetError(): %s\n", path, Mix_GetError());
	}
	else
	{
		for (ret = 0; ret < MAX_FX; ++ret)
		{
			if (soundFx[ret] == nullptr)
			{
				soundFx[ret] = chunk;
				break;
			}
		}
	}
	return ret;
}

bool ModuleAudio::PlayFx(uint index, int repeat)
{
	bool ret = false;
	if (soundFx[index] != nullptr)
	{
		Mix_PlayChannel(-1, soundFx[index], repeat);
		ret = true;
	}
	return ret;
}
