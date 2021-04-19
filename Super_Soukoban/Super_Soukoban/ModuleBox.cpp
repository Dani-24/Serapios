// Modulo para las cajas del juego

#include "ModuleBox.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"


ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < BOX_MAX; ++i)
		boxes[i] = nullptr;
}