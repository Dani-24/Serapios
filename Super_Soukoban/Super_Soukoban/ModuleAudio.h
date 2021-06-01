#ifndef __MODULE_AUDIO_H__
#define __MODULE_AUDIO_H__

#include"Module.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX 200

struct _Mix_Music;
struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

class ModuleAudio : public Module
{
public:

	ModuleAudio(bool startEnabled);

	~ModuleAudio();

	bool Init();

	bool CleanUp();

	//to play music
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	bool PauseMusic();

	//inicialize fx
	uint LoadFx(const char* path);

	//play fx
	bool PlayFx(uint index, int repeat = 0);
private:
	//current music
	Mix_Music* music = nullptr;

	Mix_Chunk* soundFx[MAX_FX] = { nullptr };

};

#endif