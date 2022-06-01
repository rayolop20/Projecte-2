#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "GuiManager.h"
#include "EntityManager.h"
#include "Player.h"
#include "VampirEnem.h"
#include "Collisions.h"
#include "Menu.h"
#include "CharacterMenu.h"
#include "GameMenu.h"
#include "PathFinding.h"
#include "BattleSystem.h"
#include "Defs.h"
#include "Log.h"
#include "Mouse.h"


Mouse::Mouse() : Module()
{
	name.Create("mouse");
}

Mouse::~Mouse()
{}

bool Mouse::Start()
{
	cursor_img = app->tex->Load("Assets/Textures/Cursor/Cursor.png");
	cursor.w = 38;
	cursor.h = 55;
	point.w = 1;
	point.h = 1;

	SDL_ShowCursor(false);

	return true;
}

bool Mouse::Update(float dt)
{
	SDL_GetMouseState(&cursor.x, &cursor.y);
	point.x = cursor.x;
	point.y = cursor.y;

	Draw();

	return true;
}

bool Mouse::PostUpdate()
{
	Draw();

	return true;
}

bool Mouse::Draw()
{
	SDL_RenderCopy(app->render->renderer, cursor_img, NULL, &cursor);

	return true;
}