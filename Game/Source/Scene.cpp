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

	Puzle_Fail = app->audio->LoadFx("Assets/Audio/Fx/fail_puzle.wav");
	Pressure_plate = app->audio->LoadFx("Assets/Audio/Fx/pressure_plate.wav");
	Open_Door = app->audio->LoadFx("Assets/Audio/Fx/open_door.wav");
	Puzle_Complete = app->audio->LoadFx("Assets/Audio/Fx/puzzle_complete.wav");
	
	door = app->tex->Load("Assets/Textures/Assets/door.png");
	app->map->DColisions();
	pathTex = app->tex->Load("Assets/Maps/path2.png");
	torch1Texture = app->tex->Load("Assets/Textures/Assets/torch_grey.png");
	torch1Texture1 = app->tex->Load("Assets/Textures/Assets/torch_grey_1.png");
	torch1Texture2 = app->tex->Load("Assets/Textures/Assets/torch_grey_2.png");
	torch1Texture3 = app->tex->Load("Assets/Textures/Assets/torch_grey_3.png");
	torch1Texture4 = app->tex->Load("Assets/Textures/Assets/torch_grey_4.png");
	torch2Texture = app->tex->Load("Assets/Textures/Assets/torch_blue.png");
	torch3Texture = app->tex->Load("Assets/Textures/Assets/torch_green.png");
	torch4Texture = app->tex->Load("Assets/Textures/Assets/torch_purple.png");
	torch5Texture = app->tex->Load("Assets/Textures/Assets/torch_turquoise.png");
	torch6Texture = app->tex->Load("Assets/Textures/Assets/torch_yellow.png");
	torch7Texture = app->tex->Load("Assets/Textures/Assets/torch_red.png");

	pressed = app->tex->Load("Assets/Textures/Assets/floor_tile_pressed.png");
	nonPressed = app->tex->Load("Assets/Textures/Assets/floor_tile.png");

	greyButton = app->tex->Load("Assets/Textures/Assets/button_grey.png");
	greenButton = app->tex->Load("Assets/Textures/Assets/button_green.png");
	blueButton = app->tex->Load("Assets/Textures/Assets/button_blue.png");
	redButton = app->tex->Load("Assets/Textures/Assets/button_red.png");
	purpleButton = app->tex->Load("Assets/Textures/Assets/button_purple.png");
	turquoiseButton = app->tex->Load("Assets/Textures/Assets/button_turquoise.png");
	yellowButton = app->tex->Load("Assets/Textures/Assets/button_yellow.png");

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
				app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 250, OptionsOn);
				//Activar Fullscreen
				SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN);
			}
			if (app->menu->On == false) {
				app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 250, OptionsOff);
				//Desactivar Fullscreen
				SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_MAXIMIZED);
			}
			if (app->menu->fps30 == true) {
				app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 185, -app->render->camera.y + 385, Options60);
				//app->dt = 32.0f;
				app->Maxfps = false;
			}
			if (app->menu->fps30 == false) {
				app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 185, -app->render->camera.y + 385, Options30);
				//Desactivar 60fps
				//app->dt = 16.0f;
				app->Maxfps = true;
			}
			if (app->menu->VsyncEnable == true) {
				app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 515, OptionsOn);
				app->render->VsyncActive = true;
			}
			if (app->menu->VsyncEnable == false) {
				app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 515, OptionsOff);
				app->render->VsyncActive = false;
			}
			app->menu->btnFullscreen->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) + 190;
			app->menu->btnFullscreen->bounds.y = -app->render->camera.y + 240;
			app->menu->btnFullscreen->state = GuiControlState::NORMAL;
			app->menu->btnFPS->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) + 175;
			app->menu->btnFPS->bounds.y = -app->render->camera.y + 375;
			app->menu->btnFPS->state = GuiControlState::NORMAL;
			app->menu->btnVsync->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) + 175;
			app->menu->btnVsync->bounds.y = -app->render->camera.y + 500;
			app->menu->btnVsync->state = GuiControlState::NORMAL;

		}

		if (puzzle1Active == true) {
			Plate1 = app->collisions->AddCollider({ 64,2432,64,64 }, Collider::Type::PRESSURE_PLATE1);
			Plate2 = app->collisions->AddCollider({ 192,2016,64,64 }, Collider::Type::PRESSURE_PLATE2);
			Plate3 = app->collisions->AddCollider({ 800,2240,64,64 }, Collider::Type::PRESSURE_PLATE3);
			if (app->scene->pressurePlate1 == true) {
				app->render->DrawTexture(nonPressed, 64, 2432);
			}
			else {
				app->render->DrawTexture(pressed, 64, 2432);
			}
			if (app->scene->pressurePlate2 == true) {
				app->render->DrawTexture(nonPressed, 192, 2016);
			}
			else {
				app->render->DrawTexture(pressed, 192, 2026);
			}
			if (app->scene->pressurePlate3 == true) {
				app->render->DrawTexture(nonPressed, 800, 2240);
			}
			else {
				app->render->DrawTexture(pressed, 800, 2240);
			}

			app->render->DrawTexture(door, 608, 2112);
			if (pressurePlate1 == false && pressurePlateTimer1_ > pressurePlateTimer1 + 7) {
				pressurePlate1 = true;
				app->audio->PlayFx(Puzle_Fail);
			}
			if (pressurePlate2 == false && pressurePlateTimer2_ > pressurePlateTimer2 + 5) {
				pressurePlate2 = true;
				app->audio->PlayFx(Puzle_Fail);
			}
			if (pressurePlate3 == false && pressurePlateTimer3_ > pressurePlateTimer3 + 0.5) {
				pressurePlate3 = true;
				app->audio->PlayFx(Puzle_Fail);
			}
			if (pressurePlate1 == false && pressurePlate2 == false && pressurePlate3 == false) {
				app->audio->PlayFx(Open_Door);
				app->audio->PlayFx(Puzle_Complete);
				puzzle1Active = false;
			}
		}
		else {
			app->render->DrawTexture(pressed, 64, 2432);
			app->render->DrawTexture(pressed, 192, 2026);
			app->render->DrawTexture(pressed, 800, 2240);

			Wall1->pendingToDelete = true;
			Wall2->pendingToDelete = true;
			Wall3->pendingToDelete = true;
			Wall4->pendingToDelete = true;
			Wall5->pendingToDelete = true;
			Wall6->pendingToDelete = true;
		}
		if (puzzle2Active == true) {
			app->render->DrawTexture(door, 1216, 832 - 96);

			Simon[1] = CreateSimonSays(1166, 880, 1);
			Simon[1].colliderS = app->collisions->AddCollider({ 1166, 880, 32, 32 }, Collider::Type::SIMON1);
			app->render->DrawTexture(greyButton, 1166, 880);

			Simon[2] = CreateSimonSays(1345, 880, 2);
			Simon[2].colliderS = app->collisions->AddCollider({ 1345, 880, 32, 32 }, Collider::Type::SIMON2);
			app->render->DrawTexture(greyButton, 1345, 880);


			Simon[3] = CreateSimonSays(1362, 1034, 3);
			Simon[3].colliderS = app->collisions->AddCollider({ 1362, 1034, 32, 32 }, Collider::Type::SIMON3);
			app->render->DrawTexture(greyButton, 1362, 1034);


			Simon[4] = CreateSimonSays(1135, 1034, 4);
			Simon[4].colliderS = app->collisions->AddCollider({ 1135, 1034, 32, 32 }, Collider::Type::SIMON4);
			app->render->DrawTexture(greyButton, 1135, 1034);


			Simon[5] = CreateSimonSays(1362, 1205, 5);
			Simon[5].colliderS = app->collisions->AddCollider({ 1362, 1205, 32, 32 }, Collider::Type::SIMON5);
			app->render->DrawTexture(greyButton, 1362, 1205);


			Simon[6] = CreateSimonSays(1135, 1205, 6);
			Simon[6].colliderS = app->collisions->AddCollider({ 1135, 1205, 32, 32 }, Collider::Type::SIMON6);
			app->render->DrawTexture(greyButton, 1135, 1205);

			
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
			if (phase == 3 && maxPhase == 3 && End3 == true) {
				Four();
			}
			if (phase == 4 && maxPhase == 4 && End4 == true) {
				Five();
			}
			if (phase == 5 && maxPhase == 5 && End5 == true) {
				Six();
			}
			if (phase == 6) {
				puzzle2Active = false;
				app->audio->PlayFx(Puzle_Complete);
			}
			

		}
		else {
			app->render->DrawTexture(yellowButton, Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y);
			app->render->DrawTexture(yellowButton, Simon[secondSimon].Pos.x, Simon[secondSimon].Pos.y);
			app->render->DrawTexture(yellowButton, Simon[thirdSimon].Pos.x, Simon[thirdSimon].Pos.y);
			app->render->DrawTexture(yellowButton, Simon[fourthSimon].Pos.x, Simon[fourthSimon].Pos.y);
			app->render->DrawTexture(yellowButton, Simon[fifthSimon].Pos.x, Simon[fifthSimon].Pos.y);
			app->render->DrawTexture(yellowButton, Simon[sixthSimon].Pos.x, Simon[sixthSimon].Pos.y);
			Wall16->pendingToDelete = true;
			Wall17->pendingToDelete = true;
			Wall18->pendingToDelete = true;
		}
		if (puzzle3Active == true) {
			Torch1 = app->collisions->AddCollider({ 1733,2000,50,50 }, Collider::Type::TORCH1);
			Torch2 = app->collisions->AddCollider({ 1658,1100,50,50 }, Collider::Type::TORCH2);
			Torch3 = app->collisions->AddCollider({ 65,1447,50,50 }, Collider::Type::TORCH3);
			Torch4 = app->collisions->AddCollider({ 572,1855,50,50 }, Collider::Type::TORCH4);
			Drawtorch1();
			Drawtorch2();
			Drawtorch3();
			Drawtorch4();
			CheckPuzzle3();
		}
		else {
			app->render->DrawTexture(torch7Texture, 1733, 2000);
			app->render->DrawTexture(torch7Texture, 1658, 1100);
			app->render->DrawTexture(torch7Texture, 65, 1447);
			app->render->DrawTexture(torch7Texture, 572, 1855);
		}
		return true;
	}
}

void Scene::CheckPuzzle3() {
	if (torchCount1 == 3 && torchCount2 == 1 && torchCount3 == 4 && torchCount4 == 2) {
		puzzle3Active = false;
		app->audio->PlayFx(Puzle_Complete);
	}
}
void Scene::Drawtorch1() {
	app->render->DrawTexture(torch1Texture1, 1733, 2000);

	if (torchCount1 == 0) {
		app->render->DrawTexture(torch1Texture, 1733, 2000);
	}
	if (torchCount1 == 1) {
		app->render->DrawTexture(torch2Texture, 1733, 2000);
	}
	if (torchCount1 == 2) {
		app->render->DrawTexture(torch3Texture, 1733, 2000);
	}
	if (torchCount1 == 3) {
		app->render->DrawTexture(torch4Texture, 1733, 2000);
	}
	if (torchCount1 == 4) {
		app->render->DrawTexture(torch5Texture, 1733, 2000);
	}
	if (torchCount1 == 5) {
		app->render->DrawTexture(torch6Texture, 1733, 2000);
	}
}
void Scene::Drawtorch2() {
	app->render->DrawTexture(torch1Texture2, 1678, 1100);

	if (torchCount2 == 0) {
		app->render->DrawTexture(torch1Texture, 1658, 1100);
	}
	if (torchCount2 == 1) {
		app->render->DrawTexture(torch2Texture, 1658, 1100);
	}
	if (torchCount2 == 2) {
		app->render->DrawTexture(torch3Texture, 1658, 1100);
	}
	if (torchCount2 == 3) {
		app->render->DrawTexture(torch4Texture, 1658, 1100);
	}
	if (torchCount2 == 4) {
		app->render->DrawTexture(torch5Texture, 1658, 1100);
	}
	if (torchCount2 == 5) {
		app->render->DrawTexture(torch6Texture, 1658, 1100);
	}
}void Scene::Drawtorch3() {
	app->render->DrawTexture(torch1Texture3, 65, 1447);

	if (torchCount3 == 0) {
		app->render->DrawTexture(torch1Texture, 65, 1447);
	}
	if (torchCount3 == 1) {
		app->render->DrawTexture(torch2Texture, 65, 1447);
	}
	if (torchCount3 == 2) {
		app->render->DrawTexture(torch3Texture, 65, 1447);
	}
	if (torchCount3 == 3) {
		app->render->DrawTexture(torch4Texture, 65, 1447);
	}
	if (torchCount3 == 4) {
		app->render->DrawTexture(torch5Texture, 65, 1447);
	}
	if (torchCount3== 5) {
		app->render->DrawTexture(torch6Texture, 65, 1447);
	}
}void Scene::Drawtorch4() {
	app->render->DrawTexture(torch1Texture4, 572, 1855);

	if (torchCount4 == 0) {
		app->render->DrawTexture(torch1Texture, 572, 1855);
	}
	if (torchCount4 == 1) {
		app->render->DrawTexture(torch2Texture, 572, 1855);
	}
	if (torchCount4 == 2) {
		app->render->DrawTexture(torch3Texture, 572, 1855);
	}
	if (torchCount4 == 3) {
		app->render->DrawTexture(torch4Texture, 572, 1855);
	}
	if (torchCount4 == 4) {
		app->render->DrawTexture(torch5Texture, 572, 1855);
	}
	if (torchCount4 == 5) {
		app->render->DrawTexture(torch6Texture, 572, 1855);
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
	//app->render->DrawRectangle({ Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y,32,32 }, 0, 255, 0);
	app->render->DrawTexture(greenButton, Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y);
}

void Scene::Two() {
	if (timerphase2_ < timerphase2 + 1) {
		app->render->DrawTexture(greenButton, Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y);

	}
	if (timerphase2_ < timerphase2 + 2) {
		app->render->DrawTexture(blueButton, Simon[secondSimon].Pos.x, Simon[secondSimon].Pos.y);
	}
	else {
		phase = 0;
		End1 = false;
		app->scene->timerphase2 = app->scene->timerphase2_;
	}
}

void Scene::Three() {
	if (timerphase2_ < timerphase2 + 1) {
		app->render->DrawTexture(greenButton, Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y);

	}
	if (timerphase2_ < timerphase2 + 2) {
		app->render->DrawTexture(blueButton, Simon[secondSimon].Pos.x, Simon[secondSimon].Pos.y);
	}
	if (timerphase2_ < timerphase2 + 3) {
		app->render->DrawTexture(redButton, Simon[thirdSimon].Pos.x, Simon[thirdSimon].Pos.y);

	}
	else {
		phase = 1;
		End2 = false;
		End1 = false;
		app->scene->timerphase2 = app->scene->timerphase2_;

	}
}
void Scene::Four() {
	if (timerphase2_ < timerphase2 + 1) {
		app->render->DrawTexture(greenButton, Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y);

	}
	if (timerphase2_ < timerphase2 + 2) {
		app->render->DrawTexture(blueButton, Simon[secondSimon].Pos.x, Simon[secondSimon].Pos.y);
	}
	if (timerphase2_ < timerphase2 + 3) {
		app->render->DrawTexture(redButton, Simon[thirdSimon].Pos.x, Simon[thirdSimon].Pos.y);

	}
	if (timerphase2_ < timerphase2 + 4) {
		app->render->DrawTexture(purpleButton, Simon[fourthSimon].Pos.x, Simon[fourthSimon].Pos.y);

	}
	else {
		phase = 1;
		End3 = false;
		End2 = false;
		End1 = false;
		app->scene->timerphase2 = app->scene->timerphase2_;

	}
}
void Scene::Five() {
	if (timerphase2_ < timerphase2 + 1) {
		//app->render->DrawRectangle({ Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y,32,32 }, 0, 255, 0);
		app->render->DrawTexture(greenButton, Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y);

	}
	if (timerphase2_ < timerphase2 + 2) {
		app->render->DrawTexture(blueButton, Simon[secondSimon].Pos.x, Simon[secondSimon].Pos.y);
	}
	if (timerphase2_ < timerphase2 + 3) {
		app->render->DrawTexture(redButton, Simon[thirdSimon].Pos.x, Simon[thirdSimon].Pos.y);

	}
	if (timerphase2_ < timerphase2 + 4) {
		app->render->DrawTexture(purpleButton, Simon[fourthSimon].Pos.x, Simon[fourthSimon].Pos.y);

	}
	if (timerphase2_ < timerphase2 + 5) {
		app->render->DrawTexture(turquoiseButton, Simon[fifthSimon].Pos.x, Simon[fifthSimon].Pos.y);

	}
	else {
		phase = 1;
		End4 = false;
		End3 = false;
		End2 = false;
		End1 = false;
		app->scene->timerphase2 = app->scene->timerphase2_;

	}
}
void Scene::Six() {
	if (timerphase2_ < timerphase2 + 1) {
		//app->render->DrawRectangle({ Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y,32,32 }, 0, 255, 0);
		app->render->DrawTexture(greenButton, Simon[firstSimon].Pos.x, Simon[firstSimon].Pos.y);

	}
	if (timerphase2_ < timerphase2 + 2) {
		app->render->DrawTexture(blueButton, Simon[secondSimon].Pos.x, Simon[secondSimon].Pos.y);
	}
	if (timerphase2_ < timerphase2 + 3) {
		app->render->DrawTexture(redButton, Simon[thirdSimon].Pos.x, Simon[thirdSimon].Pos.y);

	}
	if (timerphase2_ < timerphase2 + 4) {
		app->render->DrawTexture(purpleButton, Simon[fourthSimon].Pos.x, Simon[fourthSimon].Pos.y);
	}
	if (timerphase2_ < timerphase2 + 5) {
		app->render->DrawTexture(turquoiseButton, Simon[fifthSimon].Pos.x, Simon[fifthSimon].Pos.y);

	}
	if (timerphase2_ < timerphase2 + 6) {
		app->render->DrawTexture(yellowButton, Simon[sixthSimon].Pos.x, Simon[sixthSimon].Pos.y);
	}
	else {
		phase = 1;
		End5 = false;
		End4 = false;
		End3 = false;
		End2 = false;
		End1 = false;
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
