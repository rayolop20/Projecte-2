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

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	if (app->map->Load("dungeon.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);


		RELEASE_ARRAY(data);
	};
	app->map->DColisions();
	pathTex = app->tex->Load("Assets/maps/path2.png");
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	//L13: TODO 2: Declare an Item and create it using the EntityManager
	//VampirEnem* Vampir = (VampirEnem*)app->entityManager->CreateEntity(EntityType::VAMPYRENEM, 0, {10, 10});


	//L13: TODO 4: Create multiple Items

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	//btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { (app->win->GetWidth() / 2) - 300, app->win->GetWidth() / 10, 160, 40 }, this);
	//btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (app->win->GetWidth() / 2) + 300, app->win->GetWidth() / 10, 160, 40 }, this);

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	
	if (musicActive == true)
	{
		app->audio->PlayMusic("Assets/audio/music/music_8_bit_adventure.ogg");
		musicActive = false;
	}
	
	{
		// L02: DONE 3: Request Load / Save when pressing L/S
		if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN && app->BTSystem->battle == false)
			app->LoadGameRequest();

		if (app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN && app->BTSystem->battle == false)
			app->SaveGameRequest();

		if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
			debug = !debug;

		}
		app->render->camera.x = (app->player->P1.position.x - 608) * -1;
		app->render->camera.y = (app->player->P1.position.y - 328) * -1;


		// Draw map
		app->map->Draw();


		//Draw Entities
		//L13
		app->entityManager->Draw();

		if (debug == true) {
			//Debug Collisions
			app->collisions->DebugDraw();
			app->scene->DebugPath();
		}


		//InGameMenu
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && paused == false)
		{
			paused = true;

			Pause();
			//InGameMenu
			if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && !cMenu && paused == false)
			{
				paused = true;

				Pause();
			}
			

		}
		//if (paused)
		//{
		//	btnResume->Update(dt);
		//	btnExit->Update(dt);
		//}

		if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && !cMenu && xCont == 0)
		{
			cMenu = true;
			paused = true;
			if (app->characterMenu->active == false)
			{
				app->characterMenu->Enable();

			}
		}
		if (app->characterMenu->exitInventory && cMenu && xCont == 1)
		{
			cMenu = false;
			paused = false;
			if (app->characterMenu->active == true)
			{
				app->characterMenu->Disable();
			}
			app->characterMenu->exitInventory = false;
			xCont = 0;
		}
		if (app->menu->config == true) {
			SDL_Rect* OptionsTxt = new SDL_Rect();
			OptionsTxt->x = 0;
			OptionsTxt->y = 0;
			OptionsTxt->w = 918;
			OptionsTxt->h = 559;
			app->render->DrawTexture(app->menu->options, app->player->P1.position.x - 400, app->player->P1.position.y - 250, OptionsTxt);
			app->menu->btnConfigBack->bounds.x = app->player->P1.position.x - 120;
			app->menu->btnConfigBack->bounds.y = app->player->P1.position.y + 325;
		}
		return true;
	}
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->menu->exit)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void Scene::Pause()
{
	app->gameMenu->Enable();
	app->gameMenu->active = true;
	app->gameMenu->Start();
}

void Scene::DebugPath()
{
	const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		app->render->DrawTexture(pathTex, pos.x, pos.y);
	}
	int a = 0;
}
