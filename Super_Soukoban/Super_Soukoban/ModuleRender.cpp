#include "ModuleRender.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "External_Libraries/SDL/include/SDL_render.h"
#include "External_Libraries/SDL/include/SDL_scancode.h"

ModuleRender::ModuleRender() :Module() {

}
ModuleRender::~ModuleRender(){
}

bool ModuleRender::Init() {
	LOG("Creating Render Context :D");

	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC==true) {
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window,-1,flags);

	if (renderer == nullptr) {
		LOG(":( Renderer could not be created! SDL_Error: %s\n",SDL_GetError());
		ret = false;
	}
	return ret;
}

update_status ModuleRender::PreUpdate() {
	SDL_SetRenderDrawColor(renderer,0,0,0,255); // color
	SDL_RenderClear(renderer);
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update() {
	
	// Aquí van movimientos manuales de la camara (Soukoban no tiene)

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate() {
	
	SDL_RenderPresent(renderer);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp() {
	LOG("Destroing renderer -u.u-");

	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}
	return true;
}

bool ModuleRender::Blit(SDL_Texture* texture,int x,int y, const SDL_Rect* section,float speed) {
	bool ret = true;
}
