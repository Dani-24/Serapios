#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
class SceneIntro : public Module {
	public:
		SceneIntro(bool startEnabled);

		~SceneIntro();

		bool Start() override;

		//updates the scene's background animations
		update_status Update() override;

		//forms de render call of all the parts of the scene's backgroud
		update_status PostUpdate() override;

public:

	//sprite loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
};

#endif