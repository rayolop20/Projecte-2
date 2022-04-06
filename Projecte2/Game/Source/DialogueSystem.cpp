#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "GuiManager.h"
#include "EntityManager.h"
#include "Player.h"
#include "VampirEnem.h"
#include "EntityNPC.h"
#include "Collisions.h"
#include "BattleSystem.h"
#include "DialogueSystem.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"
#include <time.h>

DialogueSystem::DialogueSystem() : Module()
{

}

DialogueSystem::~DialogueSystem()
{

}

bool DialogueSystem::Start()
{

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = app->fonts->Load("Assets/Textures/Fonts/fonts.png", lookupTable, 2);
	return true;
}

bool DialogueSystem::Update(float dt)
{
	sprintf_s(scoreText, "pts;%2d", score);
	app->fonts->DrawTxt(50, 20, scoreFont, scoreText);
	return true;
}

bool DialogueSystem::CleanUp()
{
	return true;
}

