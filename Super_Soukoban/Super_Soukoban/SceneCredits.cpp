#include "SceneCredits.h" 

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h" 
#include "ModuleInput.h"

#include "External_Libraries/SDL/include/SDL_scancode.h"


SceneCredits::SceneCredits(bool startEnabled) : Module(startEnabled)
{
	//Fondo negro - Miguel -
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.PushBack({ 250, 200, 20, 20 });
	black.loop = false;
	black.speed = 0.015f;
}

SceneCredits::~SceneCredits()
{

}

// Load assets
bool SceneCredits::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/serapios_logo.png"); //Miguel

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" }; //Miguel
	creditsFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);
	namesFont = App->fonts->Load("Assets/Fonts/rtype_font.png", lookupTable, 1);

	return ret;
}

update_status SceneCredits::Update()
{
	black.Update();//Carga el fondo negro - Miguel -

	//Particle* newParticle = App->particles->AddParticle(App->particles->serapios, 0, -25, Collider::Type::NONE, 550); //Genera el logo de serapios


	if (black.HasFinished()) //Si la animacion del logo ha acabado, ejecuta el FadeToBlack - Miguel -
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneintro, 60);
	}
	
	else if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->titleScreen, 60);

	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneCredits::PostUpdate()
{
	// Dibuja el fondo negro
	App->render->Blit(bgTexture, 0, 0, &(black.GetCurrentFrame()), 0.3f); //Dibuja la animacion del logo - Miguel -

	// Dibuja el texto - Miguel -
	App->fonts->BlitText(SCREEN_WIDTH / 2+1 , 1, creditsFont, creditsText);
	App->fonts->BlitText(SCREEN_WIDTH / 2+1, 1, namesFont, namesText);
	App->fonts->BlitText(SCREEN_WIDTH / 2+15, 15, creditsFont, "this is a project created at");
	App->fonts->BlitText(SCREEN_WIDTH / 2+10, 30, creditsFont, "citm for the project 1 subject ");
	App->fonts->BlitText(SCREEN_WIDTH / 2 + 70, 45, creditsFont, "from the degree");
	App->fonts->BlitText(SCREEN_WIDTH / 2 + 95, 60, namesFont, "videogame");
	App->fonts->BlitText(SCREEN_WIDTH / 2 + 45, 75, namesFont, "design and development");

	App->fonts->BlitText(SCREEN_WIDTH / 2 + 65, 100, creditsFont, "project teachers");
	App->fonts->BlitText(SCREEN_WIDTH / 2 + 65, 115, namesFont, "jesus alonso");
	App->fonts->BlitText(SCREEN_WIDTH / 2 + 80, 130, namesFont, "ramon santamaria");

	App->fonts->BlitText(SCREEN_WIDTH / 2 + 90, 155, creditsFont, "developers");
	App->fonts->BlitText(SCREEN_WIDTH / 2 + 20, 170, namesFont, "dani toledo, xavier lopez");
	App->fonts->BlitText(SCREEN_WIDTH / 2 + 20, 185, namesFont, "laia pachon, adrian ramirez");
	App->fonts->BlitText(SCREEN_WIDTH / 2 + 50, 200, namesFont, "and miguel rodriguez");


	return update_status::UPDATE_CONTINUE;
}