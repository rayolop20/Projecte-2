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
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && paused == false && app->BTSystem->battle == false)
		{
			paused = true;

			Pause();
			//InGameMenu
			if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && !cMenu && paused == false && app->BTSystem->battle == false)
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

		if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && !cMenu && xCont ==  0 && app->BTSystem->battle == false)
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
			SDL_Rect* OptionsOn = new SDL_Rect();
			OptionsOn->x = 8;
			OptionsOn->y = 650;
			OptionsOn->w = 263;
			OptionsOn->h = 78;
			SDL_Rect* OptionsOff = new SDL_Rect();
			OptionsOff->x = 8;
			OptionsOff->y = 568;
			OptionsOff->w = 263;
			OptionsOff->h = 78;
			SDL_Rect* Options60 = new SDL_Rect();
			Options60->x = 272;
			Options60->y = 568;
			Options60->w = 263;
			Options60->h = 78;
			SDL_Rect* Options30 = new SDL_Rect();
			Options30->x = 274;
			Options30->y = 650;
			Options30->w = 263;
			Options30->h = 78;
			app->render->DrawTexture(app->menu->options, app->player->P1.position.x - 400, app->player->P1.position.y - 250, OptionsTxt);
			app->menu->btnConfigBack->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) - 150;
			app->menu->btnConfigBack->bounds.y = -app->render->camera.y + 650;
			if (app->menu->On == true) {
				app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 330, OptionsOn);
				//Activar Fullscreen
				SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN);
			}
			if (app->menu->On == false) {
				app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 330, OptionsOff);
				//Desactivar Fullscreen
				SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_MAXIMIZED);
			}
			if (app->menu->fps30 == true) {
				app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 495, Options30);
				//app->dt = 32.0f;
				app->Maxfps = false;
			}
			if (app->menu->fps30 == false) {
				app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 495, Options60);
				//Desactivar 60fps
				//app->dt = 16.0f;
				app->Maxfps = true;
			}
			app->menu->btnFullscreen->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) + 190;
			app->menu->btnFullscreen->bounds.y = -app->render->camera.y + 330;
			app->menu->btnFullscreen->state = GuiControlState::NORMAL;
			app->menu->btnFPS->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) + 175;
			app->menu->btnFPS->bounds.y = -app->render->camera.y + 465;
			app->menu->btnFPS->state = GuiControlState::NORMAL;

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
