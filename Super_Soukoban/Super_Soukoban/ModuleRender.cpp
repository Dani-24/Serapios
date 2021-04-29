#include "ModuleRender.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "External_Libraries/SDL/include/SDL_render.h"
#include "External_Libraries/SDL/include/SDL_scancode.h"

ModuleRender::ModuleRender (bool startEnabled) : Module(startEnabled)
{
}
ModuleRender::~ModuleRender()
{
}

bool ModuleRender::Init() {
	LOG("Creating Render Context :D");

	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC==true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window,-1,flags);

	if (renderer == nullptr) {
		LOG(":( Renderer could not be created! SDL_Error: %s\n",SDL_GetError());
		ret = false;
	}
	//SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT); // active that and change fullscreen desktop 0 to 1 and size 1 to have a fullscreen despktop

	return ret;
}

update_status ModuleRender::PreUpdate() {
	SDL_SetRenderDrawColor(renderer,0,0,0,255); // color
	SDL_RenderClear(renderer);
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()
{
	// Aquí van movimientos manuales de la camara (Soukoban no tiene)

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
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

	SDL_Rect rect{(int)(-camera.x * speed) + x * SCREEN_SIZE,(int)(-camera.y * speed) + y * SCREEN_SIZE,0,0 };

	if (section!=nullptr) {
		rect.w = section->w;
		rect.h = section->h;
	}
	else {
		SDL_QueryTexture(texture,nullptr,nullptr,&rect.w,&rect.h);
	}
	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer,texture,section,&rect)!=0) {
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s",SDL_GetError());
		ret = false;
	}
	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a,float speed) 
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer,r,g,b,a);

	SDL_Rect dstRect{
		(int)(-camera.x * speed) + rect.x * SCREEN_SIZE,
		(int)(-camera.y * speed) + rect.y * SCREEN_SIZE,
		rect.w* SCREEN_SIZE, rect.h* SCREEN_SIZE };
	
	if (SDL_RenderFillRect(renderer,&dstRect)!=0) {
		LOG("Cannot draw quad to screen. :( SDL_RenderFillRect error %s");
		ret = false;
	}
	return ret;
}
