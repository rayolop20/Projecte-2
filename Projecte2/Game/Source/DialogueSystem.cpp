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
	return true;
}

bool DialogueSystem::Update(float dt)
{
	return true;
}

bool DialogueSystem::CleanUp()
{
	return true;
}

