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
#include <time.h>

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
	door = app->tex->Load("Assets/Textures/Assets/door.png");
	app->map->DColisions();
	pathTex = app->tex->Load("Assets/Maps/path2.png");
	if (puzzle1Active == true) {
		//Wall1 = app->collisions->AddCollider({ 608+32,2176+32,32,32 }, Collider::Type::WALLH);
		Wall1 = app->collisions->AddCollider({ 608,2176+32,32,32 }, Collider::Type::WALLV,this);
		Wall2 = app->collisions->AddCollider({ 640,2176+32,32,32 }, Collider::Type::WALLV,this);
		Wall3 = app->collisions->AddCollider({ 608+64,2176+32,32,32 }, Collider::Type::WALLV,this);
		Wall4 = app->collisions->AddCollider({ 608,2112-64,32,32 }, Collider::Type::WALLV,this);
		Wall5 = app->collisions->AddCollider({ 640,2112-64,32,32 }, Collider::Type::WALLV,this);
		Wall6 = app->collisions->AddCollider({ 608+64,2112-64,32,32 }, Collider::Type::WALLV,this);
	}
	if (puzzle2Active == true) {
		Wall16 = app->collisions->AddCollider({ 1216,832,32,32 }, Collider::Type::WALLV, this);
		Wall17 = app->collisions->AddCollider({ 1248,832,32,32 }, Collider::Type::WALLV, this);
		Wall18 = app->collisions->AddCollider({ 1280,832,32,32 }, Collider::Type::WALLV, this);
	}
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
	pressurePlateTimer1_ = SDL_GetTicks() / 1000;
	pressurePlateTimer2_ = SDL_GetTicks() / 1000;
	pressurePlateTimer3_ = SDL_GetTicks() / 1000;

	timerphase1_ = SDL_GetTicks() / 1000;
	timerphase2_ = SDL_GetTicks() / 1000;

	if (musicActive == true)
	{
		app->audio->PlayMusic("Assets/Audio/Music/music_8_bit_adventure.ogg");
		musicActive = false;
	}
	
	{
		// L02: DONE 3: Request Load / Save when pressing L/S
		if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN && app->BTSystem->battle == false)
			app->LoadGameRequest();

		if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN && app->BTSystem->battle == false)
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

		if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && !cMenu && xCont ==  0 && app->BTSystem->battle == false || app->BTSystem->InventoryEnable)
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
				app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 495, Options60);
				//app->dt = 32.0f;
				app->Maxfps = false;
			}
			if (app->menu->fps30 == false) {
				app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 495, Options30);
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
		

		if (puzzle1Active == true) {
			Plate1 = app->collisions->AddCollider({ 64,2432,64,64 }, Collider::Type::PRESSURE_PLATE1);
			Plate2 = app->collisions->AddCollider({ 192,2016,64,64 }, Collider::Type::PRESSURE_PLATE2);
			Plate3 = app->collisions->AddCollider({ 800,2240,64,64 }, Collider::Type::PRESSURE_PLATE3);
			app->render->DrawTexture(door, 608, 2112);
			if (pressurePlate1 == false && pressurePlateTimer1_ > pressurePlateTimer1 + 7) {
				pressurePlate1 = true;
			}
			if (pressurePlate2 == false && pressurePlateTimer2_ > pressurePlateTimer2 + 5) {
				pressurePlate2 = true;
			}
			if (pressurePlate3 == false && pressurePlateTimer3_ > pressurePlateTimer3 + 0.5) {
				pressurePlate3 = true;
			}
			if (pressurePlate1 == false && pressurePlate2 == false && pressurePlate3 == false) {
				puzzle1Active = false;
			}
		}
		else {
			Wall1->pendingToDelete = true;
			Wall2->pendingToDelete = true;
			Wall3->pendingToDelete = true;
			Wall4->pendingToDelete = true;
			Wall5->pendingToDelete = true;
			Wall6->pendingToDelete = true;
		}
		if (puzzle2Active == true) {
			Simon[1] = CreateSimonSays(1166, 850, 1);
			Simon[1].colliderS = app->collisions->AddCollider({ 1166, 850, 32, 32 }, Collider::Type::SIMON1);

			Simon[2] = CreateSimonSays(1345, 850, 2);
			Simon[2].colliderS = app->collisions->AddCollider({ 1345, 850, 32, 32 }, Collider::Type::SIMON2);

			Simon[3] = CreateSimonSays(1392, 1034, 3);
			Simon[3].colliderS = app->collisions->AddCollider({ 1392, 1034, 32, 32 }, Collider::Type::SIMON3);

			Simon[4] = CreateSimonSays(1105, 1034, 4);
			Simon[4].colliderS = app->collisions->AddCollider({ 1105, 1034, 32, 32 }, Collider::Type::SIMON4);

			Simon[5] = CreateSimonSays(1392, 1205, 5);
			Simon[5].colliderS = app->collisions->AddCollider({ 1392, 1205, 32, 32 }, Collider::Type::SIMON5);

			Simon[6] = CreateSimonSays(1105, 1205, 6);
			Simon[6].colliderS = app->collisions->AddCollider({ 1105, 1205, 32, 32 }, Collider::Type::SIMON6);

			
			if (prepared == false) {
				PrepareSimon();
			}
			if (phase == 0 && maxPhase == 0) {
				One();
			}
			if (phase == 1 && maxPhase == 1 && End1 == true) {
				Two();
			}
			if (phase == 2 && maxPhase == 2 && End2 == true) {
				Three();
			}
			

		}
		else {
			Wall16->pendingToDelete = true;
			Wall17->pendingToDelete = true;
			Wall18->pendingToDelete = true;
		}
		return true;
	}
}

S Scene::CreateSimonSays(int x, int y, int order)
{
	S Simon[7];

	Simon[order].Pos.x = x;
	Simon[order].Pos.y = y;
	Simon[order].num = order;
		return Simon[order];
}

void Scene::PrepareSimon() {
	srand(time(NULL));
	firstSimon = rand() % 6 + 1;
	do {
		secondSimon = rand() % 6 + 1;
	} while (secondSimon == firstSimon);
	do {
		thirdSimon = rand() % 6 + 1;
	} while (thirdSimon == firstSimon || thirdSimon == secondSimon);
	do {
		fourthSimon = rand() % 6 + 1;
	} while (fourthSimon == firstSimon || fourthSimon == secondSimon || fourthSimon == thirdSimon);
	do {
		fifthSimon = rand() % 6 + 1;
	} while (fifthSimon == firstSimon || fifthSimon == secondSimon || fifthSimon == thirdSimon || fifthSimon == fourthSimon);
	do {
		sixthSimon = rand() % 6 + 1;
	} while (sixthSimon == firstSimon || sixthSimon == secondSimon || sixthSimon == thirdSimon || sixthSimon == fourthSimon || sixthSimon == fifthSimon);
	prepared = true;
}

void Scene::One() {
	app->render->DrawRectangle({ Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y,32,32 }, 0, 255, 0);
}

void Scene::Two() {
	if (timerphase2_ < timerphase2 + 1) {
		app->render->DrawRectangle({ Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y,32,32 }, 0, 255, 0);
	}
	if (timerphase2_ < timerphase2 + 2) {
		app->render->DrawRectangle({ Simon[secondSimon].Pos.x, Simon[secondSimon].Pos.y,32,32 }, 0, 0, 255);
	}
	else {
		phase = 0;
		End1 = false;
		app->scene->timerphase2 = app->scene->timerphase2_;
	}
}

void Scene::Three() {
	if (timerphase2_ < timerphase2 + 1) {
		app->render->DrawRectangle({ Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y,32,32 }, 0, 255, 0);
	}
	if (timerphase2_ < timerphase2 + 2) {
		app->render->DrawRectangle({ Simon[secondSimon].Pos.x, Simon[secondSimon].Pos.y,32,32 }, 0, 0, 255);
	}
	if (timerphase2_ < timerphase2 + 3) {
		app->render->DrawRectangle({ Simon[thirdSimon].Pos.x, Simon[thirdSimon].Pos.y,32,32 }, 255, 0, 0);
	}
	else {
		phase = 0;
		End2 = false;
		app->scene->timerphase2 = app->scene->timerphase2_;

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
