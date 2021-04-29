#ifndef __MODULE_TEXTURES_H__
#define __MODULE_TEXTURES_H__

#include "Module.h"

#define MAX_TEXTURES 50

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures(bool startEnabled) ;
	~ModuleTextures();

	// Initializes the SDL_Image library
	bool Init() override;

	// Uninitializes the SDL_Image library
	bool CleanUp() override;

	// Loads a new SDL_Texture from a file path, returns nullptr if could not be created
	SDL_Texture* const Load(const char* path);

	bool Unload(SDL_Texture* texture);

	void GetTextureSize(const SDL_Texture* texture, uint& width, uint& height) const;
public:
	// Array of all the loaded textures
	SDL_Texture* textures[MAX_TEXTURES] = { nullptr };
};


#endif // __ModuleTextures_H__
