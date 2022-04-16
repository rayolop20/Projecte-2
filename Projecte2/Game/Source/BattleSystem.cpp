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
#include "ZombieEnem.h"
#include "EntityNPC.h"
#include "Collisions.h"
#include "BattleSystem.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"
#include <time.h>

battleSystem::battleSystem() : Module()
{
	name.Create("scene");
}

// Destructor
battleSystem::~battleSystem()
{}

// Called before render is available
bool battleSystem::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool battleSystem::Start()
{
	Attack = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 31, "Attack", {0, 0, 0, 0 }, this);
	Attack->state = GuiControlState::DISABLED;
	Attack1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 32, "Attack1", { 0, 0, 0, 0 }, this);
	Attack1->state = GuiControlState::DISABLED;
	Attack2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 33, "Attack2", { 0, 0, 0, 0 }, this);
	Attack2->state = GuiControlState::DISABLED;
	SpecialAttack = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 34, "SpecialAttack", { 0, 0, 0, 0 }, this);
	SpecialAttack->state = GuiControlState::DISABLED;
	Inventory = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 35, "Inventory", { 0,0, 0, 0 }, this);
	Inventory->state = GuiControlState::DISABLED;
	Run = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 36, "Run", { 0, 0, 0, 0 }, this);
	Run->state = GuiControlState::DISABLED;
	CloseInventory = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 37, "CloseInventory", { 0, 0, 0, 0 }, this);
	CloseInventory->state = GuiControlState::DISABLED;
	QTE2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 38, "QTE2", { 0, 0, 0, 0 }, this);
	QTE2->state = GuiControlState::DISABLED;
	MiniPlayerButton1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 39, "MiniPlayerButton1", { 0,0, 0, 0 }, this);
	MiniPlayerButton1->state = GuiControlState::DISABLED;
	MiniPlayerButton2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 40, "MiniPlayerButton2", { 0, 0, 0, 0 }, this);
	MiniPlayerButton2->state = GuiControlState::DISABLED;
	MiniPlayerButton3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 41, "MiniPlayerButton3", {0, 0, 0, 0 }, this);
	MiniPlayerButton3->state = GuiControlState::DISABLED;
	MiniPlayerButton4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 42, "MiniPlayerButton4", { 0, 0, 0, 0 }, this);
	MiniPlayerButton4->state = GuiControlState::DISABLED;

	selectPlayer = app->tex->Load("Assets/textures/UI/ChosePlayers.png");
	//Initialize playerTurns
	for (int i = 0; i <= 4 - alliesDead;i++) {
		waitPlayer[i] = 0;
	}
	for (int i = 0; i <= 5; i++) {
		poisonCount[i] = 0;
	}
	// L03: DONE: Load map
	AttackTexture = app->tex->Load("Assets/UI/CombatUI.png");
	Tutorial = app->tex->Load("Assets/textures/UI/QTETutorial.png");
	QTE4 = app->tex->Load("Assets/textures/UI/QTE4.png");
	PopQTE2 = app->tex->Load("Assets/textures/UI/QTE1_1.png");

	
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	//L13: TODO 2: Declare an Item and create it using the EntityManager
	VampirEnem* Vampir = (VampirEnem*)app->entityManager->CreateEntity(EntityType::VAMPYR, 0, { 0,0 });
	ZombieEnem* Zombies = (ZombieEnem*)app->entityManager->CreateEntity(EntityType::ZOMBIE, 0, { 0,0 });
	EntityNPC* Npc = (EntityNPC*)app->entityManager->CreateEntity(EntityType::NPC, 0, { 0,0 });

	//L13: TODO 4: Create multiple Items

	AttackPhaseActive = false;
	AttackAux = 0;

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	//btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { (app->win->GetWidth() / 2) - 300, app->win->GetWidth() / 10, 160, 40 }, this);
	//btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (app->win->GetWidth() / 2) + 300, app->win->GetWidth() / 10, 160, 40 }, this);

	return true;
}

// Called each loop iteration
bool battleSystem::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool battleSystem::Update(float dt)
{
	app->guiManager->Draw();

	//Draw GUI
	if (battle == true && app->player->P1.IsAlive == true) {
		MiniPlayerButton1->bounds.x = app->player->P1.position.x - 420 + 120;
		MiniPlayerButton1->bounds.y = app->player->P1.position.y - 220;
		MiniPlayerButton1->bounds.w = 100;
		MiniPlayerButton1->bounds.h = 100;
		MiniPlayerButton2->bounds.x = app->player->P1.position.x - 420;
		MiniPlayerButton2->bounds.y = app->player->P1.position.y - 220 + 130;
		MiniPlayerButton2->bounds.w = 100;
		MiniPlayerButton2->bounds.h = 100;
		MiniPlayerButton3->bounds.x = app->player->P1.position.x - 420 + 120;
		MiniPlayerButton3->bounds.y = app->player->P1.position.y - 220 + 260;
		MiniPlayerButton3->bounds.w = 100;
		MiniPlayerButton3->bounds.h = 100;
		MiniPlayerButton4->bounds.x = app->player->P1.position.x - 420;
		MiniPlayerButton4->bounds.y = app->player->P1.position.y - 220 + 390;
		MiniPlayerButton4->bounds.w = 100;
		MiniPlayerButton4->bounds.h = 100;
		Attack->bounds.x = app->player->P1.position.x - 165;
		Attack->bounds.y = app->player->P1.position.y + 210;
		Attack->bounds.w = 150;
		Attack->bounds.h = 61;
		Attack1->bounds.x = app->player->P1.position.x - 150;
		Attack1->bounds.y = app->player->P1.position.y + 175;
		Attack1->bounds.w = 120;
		Attack1->bounds.h = 45;
		Attack2->bounds.x = app->player->P1.position.x - 150;
		Attack2->bounds.y = app->player->P1.position.y + 120;
		Attack2->bounds.w = 120;
		Attack2->bounds.h = 45;
		SpecialAttack->bounds.x = app->player->P1.position.x + 15;
		SpecialAttack->bounds.y = app->player->P1.position.y + 210;
		SpecialAttack->bounds.w = 150;
		SpecialAttack->bounds.h = 61;
		Inventory->bounds.x = app->player->P1.position.x - 165;
		Inventory->bounds.y = app->player->P1.position.y + 285;
		Inventory->bounds.w = 150;
		Inventory->bounds.h = 61;
		CloseInventory->bounds.x = app->player->P1.position.x + 550;
		CloseInventory->bounds.y = app->player->P1.position.y - 290;
		CloseInventory->bounds.w = 50;
		CloseInventory->bounds.h = 50;
		Run->bounds.x = app->player->P1.position.x + 15;
		Run->bounds.y = app->player->P1.position.y + 285;
		Run->bounds.w = 150;
		Run->bounds.h = 61;
		SDL_Rect battle_screen = { app->player->P1.position.x - 640 + 32,app->player->P1.position.y - 360 + 32,1280,720 };		
		MiniPlayerButton1->state = GuiControlState::NORMAL;
		MiniPlayerButton2->state = GuiControlState::NORMAL;
		MiniPlayerButton4->state = GuiControlState::NORMAL;
		MiniPlayerButton3->state = GuiControlState::NORMAL; 
		app->render->DrawRectangle(battle_screen, 0, 250, 250);
		DrawHpBars();
		if (PlayerTurn == true) {
			Attack->state = GuiControlState::NORMAL;
			SpecialAttack->state = GuiControlState::NORMAL;
			Inventory->state = GuiControlState::NORMAL;
			Run->state = GuiControlState::NORMAL;
			if (ChoosePlayerPhase == true) {
				ChoosePlayer();
			}
		}
		
	}
	else if(battleAux == true){
		AttackPlayer = 0;
		for (int i = 0; i < 4; i++) {
			waitPlayer[i] = 0;
		}
		Attack->state = GuiControlState::DISABLED;
		Attack1->state = GuiControlState::DISABLED;
		Attack2->state = GuiControlState::DISABLED;
		SpecialAttack->state = GuiControlState::DISABLED;
		Inventory->state = GuiControlState::DISABLED;
		Run->state = GuiControlState::DISABLED;
		MiniPlayerButton1->state = GuiControlState::DISABLED;
		MiniPlayerButton2->state = GuiControlState::DISABLED;
		MiniPlayerButton3->state = GuiControlState::DISABLED;
		MiniPlayerButton4->state = GuiControlState::DISABLED;
	}
	else {
		MiniPlayerButton1->bounds.w = 0;
		MiniPlayerButton1->bounds.h = 0;
		MiniPlayerButton2->bounds.w = 0;
		MiniPlayerButton2->bounds.h = 0;
		MiniPlayerButton3->bounds.w = 0;
		MiniPlayerButton3->bounds.h = 0;
		MiniPlayerButton4->bounds.w = 0;
		MiniPlayerButton4->bounds.h = 0;
		SpecialAttack->bounds.w = 0;
		SpecialAttack->bounds.h = 0;
		Inventory->bounds.w = 0;
		Inventory->bounds.h = 0;
		Attack->bounds.w = 0;
		Attack->bounds.h = 0;
		Attack1->bounds.w = 0;
		Attack1->bounds.h = 0;
		Attack2->bounds.w = 0;
		Attack2->bounds.h = 0;
		CloseInventory->bounds.w = 0;
		CloseInventory->bounds.h = 0;
		Run->bounds.w = 0;
		Run->bounds.h = 0;
		for (int i = 0; i < 4; i++) {
			waitPlayer[i] = 0;
		}
	}
	if (Delay == false) {//Delay after Run Button
		timer1 = SDL_GetTicks() / 1000;
		if (AttackAux == 0) {
			timer1_ = timer1;
			AttackAux = 1;
		}
		if (timer1 > timer1_ + 3 && AttackAux != 0) {
			AttackAux = 0;
			Delay = true;
		}
	}
	if (SpecialAttackEnable && AttackPlayer != 0) {
		SpecialAttackPhase();
		Attack->state = GuiControlState::DISABLED;
		Attack1->state = GuiControlState::DISABLED;
		Attack2->state = GuiControlState::DISABLED;
		SpecialAttack->state = GuiControlState::DISABLED;
		Inventory->state = GuiControlState::DISABLED;
		Run->state = GuiControlState::DISABLED;
	}
	if (SpecialAttackEnable == false && battle == true) {
		Attack->state = GuiControlState::NORMAL;
		SpecialAttack->state = GuiControlState::NORMAL;
		Inventory->state = GuiControlState::NORMAL;
		Run->state = GuiControlState::NORMAL;
	}
	
	//Draw Entities
	//L13 
	app->entityManager->Draw();

	if (InventoryEnable) {
		if (invenCont == 0)
		{
			InventoryButtons();
			invenCont = 1;
		}
		InventoryPhase();
	}
	if (!InventoryEnable && invenCont == 1)
	{
		Ch1->state = GuiControlState::DISABLED;
		Ch2->state = GuiControlState::DISABLED;
		Ch3->state = GuiControlState::DISABLED;
		Ch4->state = GuiControlState::DISABLED;
		Item1->state = GuiControlState::DISABLED;
		Item2->state = GuiControlState::DISABLED;
		Item3->state = GuiControlState::DISABLED;
		Item4->state = GuiControlState::DISABLED;
		CloseInventory->state = GuiControlState::DISABLED;

		invenCont = 0;
	}
	if (debug == true) {
		//Debug Collisions
		app->collisions->DebugDraw();
	}

	n = app->player->P1.damage;
	//InGameMenu
	/*if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		paused = true;

		Pause();

		btnResume->state = GuiControlState::NORMAL;
		btnMenu->state = GuiControlState::NORMAL;
		btnExit->state = GuiControlState::NORMAL;
		//rendered on last layer(collision.cpp)
	}
	if (paused)
	{
		btnResume->Update(dt);
		btnExit->Update(dt);
	}*/
	CheckAllies();
	MaxHp();
	MaxMana();

	return true;
}

bool battleSystem::PostUpdate()
{
	bool ret = true;

	//if (app->menu->exit)
		//ret = false;

	return ret;
}

bool battleSystem::CleanUp()
{
	LOG("Freeing scene");

	return false;
}

void battleSystem::AttackPhase() {

	Attack->state = GuiControlState::NORMAL;
	Attack1->state = GuiControlState::NORMAL;
	Attack2->state = GuiControlState::NORMAL;
	AttackPhaseActive = true;
	AttackPhaseEnable = true;
	
}
void battleSystem::AttackPhaseDisabled() {
	Attack1->state = GuiControlState::DISABLED;
	Attack2->state = GuiControlState::DISABLED;
}
void battleSystem::AttackPhaseDisabled2() {
	Attack1->state = GuiControlState::DISABLED;
	Attack2->state = GuiControlState::DISABLED;
	VampireTarget = 0;
	ZombieTarget = 0;
	AttackPlayer = 0;
	AttackPhaseActive = false;
	AttackPhaseEnable = false;
	ChoosePlayerPhase = true;
	randomAux = true;
}

void battleSystem::InventoryButtons()
{
	Ch1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 57, "Ch1", { -app->render->camera.x + app->win->GetWidth() / 2 - 190, -app->render->camera.y + app->win->GetHeight() / 2 - 90, 80, 180 }, this);
	Ch1->state = GuiControlState::DISABLED;
	Ch2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 58, "Ch2", { -app->render->camera.x + app->win->GetWidth() / 2 - 90, -app->render->camera.y + app->win->GetHeight() / 2 - 90, 80, 180 }, this);
	Ch2->state = GuiControlState::DISABLED;
	Ch3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 59, "Ch3", { -app->render->camera.x + app->win->GetWidth() / 2 +10, -app->render->camera.y + app->win->GetHeight() / 2 - 90, 80, 180 }, this);
	Ch3->state = GuiControlState::DISABLED;
	Ch4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 60, "Ch4", { -app->render->camera.x + app->win->GetWidth() / 2 + 110, -app->render->camera.y + app->win->GetHeight() / 2 - 90, 80, 180 }, this);
	Ch4->state = GuiControlState::DISABLED;

	Item1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 61, "Item1", { -app->render->camera.x + app->win->GetWidth() / 2 - 200, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);
	Item1->state = GuiControlState::DISABLED;
	Item2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 62, "Item2", { -app->render->camera.x + app->win->GetWidth() / 2 - 100, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);
	Item2->state = GuiControlState::DISABLED;
	Item3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 63, "Item3", { -app->render->camera.x + app->win->GetWidth() / 2 - 0, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);
	Item3->state = GuiControlState::DISABLED;
	Item4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 64, "Item4", { -app->render->camera.x + app->win->GetWidth() / 2 + 100, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);
	Item4->state = GuiControlState::DISABLED;
}

void battleSystem::InventoryPhase() {
	SDL_Rect Inventory_ = { app->player->P1.position.x - 640 + 32 + 50,app->player->P1.position.y - 360 + 32 + 25,1280 - 100,720 - 50};
	app->render->DrawRectangle(Inventory_, 0,250,0);

	SDL_Rect ItemsRect = { -app->render->camera.x + (app->win->GetWidth() / 2 - 300), -app->render->camera.y + (app->win->GetHeight() / 2 - 200), 600, 400 };
	app->render->DrawRectangle(ItemsRect, 250, 0, 0);

	Item1->state = GuiControlState::NORMAL;
	Item2->state = GuiControlState::NORMAL;
	Item3->state = GuiControlState::NORMAL;
	Item4->state = GuiControlState::NORMAL;

	if (choosingPlayer)
	{
		SDL_Rect characterRect = { -app->render->camera.x + (app->win->GetWidth() / 2 - 200), -app->render->camera.y + (app->win->GetHeight() / 2 - 100), 400, 200 };
		app->render->DrawRectangle(characterRect, 0, 0, 250);

		Ch1->state = GuiControlState::NORMAL;
		Ch2->state = GuiControlState::NORMAL;
		Ch3->state = GuiControlState::NORMAL;
		Ch4->state = GuiControlState::NORMAL;

		Item1->state = GuiControlState::DISABLED;
		Item2->state = GuiControlState::DISABLED;
		Item3->state = GuiControlState::DISABLED;
		Item4->state = GuiControlState::DISABLED;
	}
	if (!choosingPlayer)
	{
		Ch1->state = GuiControlState::DISABLED;
		Ch2->state = GuiControlState::DISABLED;
		Ch3->state = GuiControlState::DISABLED;
		Ch4->state = GuiControlState::DISABLED;

		Item1->state = GuiControlState::NORMAL;
		Item2->state = GuiControlState::NORMAL;
		Item3->state = GuiControlState::NORMAL;
		Item4->state = GuiControlState::NORMAL;
	}

	MiniPlayerButton1->state = GuiControlState::DISABLED;
	MiniPlayerButton2->state = GuiControlState::DISABLED;
	MiniPlayerButton3->state = GuiControlState::DISABLED;
	MiniPlayerButton4->state = GuiControlState::DISABLED;
	Attack->state = GuiControlState::DISABLED;
	Attack1->state = GuiControlState::DISABLED;
	Attack2->state = GuiControlState::DISABLED;
	SpecialAttack->state = GuiControlState::DISABLED;
	Inventory->state = GuiControlState::DISABLED;
	Run->state = GuiControlState::DISABLED;
}

// QuickTimeEvent1 Position and Speed,
/*idle.PushBack({ 65, 47, 60, 60 });
idle.PushBack({ 206, 43, 60, 60 });
idle.PushBack({ 348, 44, 60, 60 });
idle.PushBack({ 488, 44, 60, 60 });
idle.PushBack({ 620, 40, 70, 70 });
idle.PushBack({ 47, 158, 70, 70 });
idle.PushBack({ 195, 155, 70, 70 });
idle.PushBack({ 335, 155, 70, 70 });
idle.PushBack({ 482, 155, 70, 70 });
idle.PushBack({ 625, 155, 70, 70 });
idle.PushBack({ 0, 0, 0, 0 });
idle.loop = false;
idle.speed = 0.005f;*/

void battleSystem::SpecialAttackPhase() {
	srand(time(NULL));
	if (randomAttack == 0) {//QTE Random activator
		randomAttack = (rand() % 1) + 3;
		//randomAttack = rand() % 4 + 1;
	}
	if (randomAttack == 1) {//QTE 1
		timer1 = SDL_GetTicks() / 1000;
		if (AttackAux == 0){
			SDL_Rect* Tutorial1 = new SDL_Rect();
			Tutorial1->x = 0;
			Tutorial1->y = 0;
			Tutorial1->w = 528;
			Tutorial1->h = 434;
			app->render->DrawTexture(Tutorial, app->player->P1.position.x - 238, app->player->P1.position.y- 200,Tutorial1);
		}
		if (AttackAux == 0 && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			timer1_ = timer1;
			AttackAux = 1;
		}
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			AttackAux+=2;
		}
		if (AttackAux > 100) {
    		AttackAux = 100;
		}
		if (timer1 > timer1_ + 5 && AttackAux != 0) {
			randomAttack = 0;
			//enemy.hp = enemy.hp - player.attack + AttackAux;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] == 5) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
			SpecialAttackEnable = false;
			SpeacialAttackEnd = true;
		}
	}
	if (randomAttack == 2) {//QTE 2
		timer1 = SDL_GetTicks() / 1000;
		if (AttackAux == 0) {
			SDL_Rect* Tutorial2 = new SDL_Rect();
			Tutorial2->x = 578;
			Tutorial2->y = 0;
			Tutorial2->w = 528;
			Tutorial2->h = 434;
			app->render->DrawTexture(Tutorial, app->player->P1.position.x - 238, app->player->P1.position.y - 200, Tutorial2);
		}
		if (AttackAux == 0 && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			timer1_ = timer1;
			AttackAux = 1;
		}
		if (AttackAux != 0) {
			app->render->DrawTexture(PopQTE2, POSQTE2X - 6, POSQTE2Y - 6);
		}
		randomx = (rand() % 500);
		randomy = (rand() % 300);

		if (QTE2->state == GuiControlState::DISABLED && AttackAux != 0) {
			randomx = (rand() % 700);
			randomy = (rand() % 400);
			POSQTE2X = randomx + app->player->P1.position.x - 300;
			POSQTE2Y = randomy + app->player->P1.position.y - 200;
			QTE2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 38, "QTE2", { POSQTE2X, POSQTE2Y, 50, 50 }, this);
			QTE2->state = GuiControlState::NORMAL;
		}

		if (AttackAux > 100) {
			AttackAux = 100 ;
		}
		if (timer1 > timer1_ + 5 && AttackAux != 0) {
			randomAttack = 0;
			QTE2->state = GuiControlState::DISABLED;
			//enemy.hp = enemy.hp - player.attack + AttackAux;
			AttackAux = 0;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] == 5) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
			SpecialAttackEnable = false;
			SpeacialAttackEnd = true;

		}
		//pp->render->DrawRectangle(block1, 250, 0, 0);
	}
	if (randomAttack == 3) {//QTE 3
		timer1 = SDL_GetTicks() / 1000;
		if (AttackAux == 0) {
			SDL_Rect* Tutorial3 = new SDL_Rect();
			Tutorial3->x = 1148;
			Tutorial3->y = 0;
			Tutorial3->w = 528;
			Tutorial3->h = 434;
			app->render->DrawTexture(Tutorial, app->player->P1.position.x - 238, app->player->P1.position.y - 200, Tutorial3);
		}
		randomtargetRect = (rand() % 185) + 165;
 		if (AttackAux == 0 && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			_timer1_ = timer1;
			AttackAux = 1;
			randomtargetRect = (rand() % 185) + 165;
			randomtargetRect_ = randomtargetRect;
		}
		if (AttackAux != 0) {
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timer1 > _timer1_ + 0.25) {
				finalpos = timer1_ + app->player->P1.position.x - 125;
				if (finalpos > randomtargetRect_ + app->player->P1.position.x - 125  - 115 && finalpos < randomtargetRect_ + app->player->P1.position.x - 125 - 115 + 30) {
					AttackAux = 100;
				}
				else if (finalpos > randomtargetRect_ + app->player->P1.position.x - 155 - 115 - 30 && finalpos + 20 < randomtargetRect_ + app->player->P1.position.x - 155 - 115 + 60) {
					AttackAux = 50;
				}
				else {
					AttackAux = 25;
				}
				randomAttack = 0;
			}
			if (timer1_ < 280 && rectDirection == false) {//PointRect right movement
				timer1_+=3.5;
			}
			else {
				rectDirection = true;
			}
			if (timer1_ > 0 && rectDirection == true) {//PointRect left movement
				timer1_-=3.5;
			}
			else {
				rectDirection = false;
			}
			
			SDL_Rect largeRect = { app->player->P1.position.x - 125,app->player->P1.position.y + 200,300,40 };
			app->render->DrawRectangle(largeRect, 0, 250, 0);
			SDL_Rect targetRect2 = { randomtargetRect_  + app->player->P1.position.x - 155 - 115,app->player->P1.position.y + 200,90,40 };
			app->render->DrawRectangle(targetRect2, 255, 128, 0);
			SDL_Rect targetRect = { randomtargetRect_ + app->player->P1.position.x - 125 - 115,app->player->P1.position.y + 200,30,40 };
			app->render->DrawRectangle(targetRect, 250, 250, 0);
			SDL_Rect PointRect = {timer1_ + app->player->P1.position.x - 125,app->player->P1.position.y + 210,20,20 };
			app->render->DrawRectangle(PointRect, 250, 0, 0);
			if (AttackAux == 25 || AttackAux == 50 || AttackAux == 100) {
				for (int i = 0; i <= 4; i++) {
					if (app->BTSystem->waitPlayer[i] != 0) {
						app->BTSystem->waitPlayer[i] += 1;
					}
					if (app->BTSystem->waitPlayer[i] == 5) {
						app->BTSystem->waitPlayer[i] = 0;
					}
				}
				SpecialAttackEnable = false;
				SpeacialAttackEnd = true;
			}
		}
	}
	if (randomAttack == 4) {//QTE 4
		timer1 = SDL_GetTicks() / 1000;
		if (AttackAux == 0) {
			SDL_Rect* Tutorial4 = new SDL_Rect();
			Tutorial4->x = 0;
			Tutorial4->y = 469;
			Tutorial4->w = 528;
			Tutorial4->h = 434;
			app->render->DrawTexture(Tutorial, app->player->P1.position.x - 238, app->player->P1.position.y - 200, Tutorial4);
		}
		if (AttackAux == 0 && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			timer1_ = timer1;
			AttackAux = 1;
			LetterGenerator = true;
		}
		if (AttackAux != 0) {
			if (LetterGenerator == true) {
				randomLetterGenerator = (rand() % 26) + 1;
				LetterGenerator = false;
			}
			SDL_Rect *QTE4_ = new SDL_Rect();
			QTE4_->x = (randomLetterGenerator-1)*64;
			QTE4_->y = 0;
			QTE4_->w = 64;
			QTE4_->h = 64;
			app->render->DrawTexture(QTE4, app->player->P1.position.x, app->player->P1.position.y - 64, QTE4_);
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN && randomLetterGenerator == 1) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN && randomLetterGenerator == 2) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN && randomLetterGenerator == 3) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && randomLetterGenerator == 4) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && randomLetterGenerator == 5) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN && randomLetterGenerator == 6) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN && randomLetterGenerator == 7) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN && randomLetterGenerator == 8) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && randomLetterGenerator == 9) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN && randomLetterGenerator == 10) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN && randomLetterGenerator == 11) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN && randomLetterGenerator == 12) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN && randomLetterGenerator == 13) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN && randomLetterGenerator == 14) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN && randomLetterGenerator == 15) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && randomLetterGenerator == 16) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && randomLetterGenerator == 17) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN && randomLetterGenerator == 18) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && randomLetterGenerator == 19) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN && randomLetterGenerator == 20) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN && randomLetterGenerator == 21) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN && randomLetterGenerator == 22) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && randomLetterGenerator == 23) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN && randomLetterGenerator == 24) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN && randomLetterGenerator == 25) {
				AttackAux += 10;
				LetterGenerator = true;
			}
			if (app->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN && randomLetterGenerator == 26) {
				AttackAux += 10;
				LetterGenerator = true;
			}

			if (AttackAux >= 100) {
				AttackAux = 100;
			}
			if (timer1 > timer1_ + 10 && AttackAux != 0) {
				randomLetterGenerator = 0;
				randomAttack = 0;
				for (int i = 0; i <= 4; i++) {
					if (app->BTSystem->waitPlayer[i] != 0) {
						app->BTSystem->waitPlayer[i] += 1;
					}
					if (app->BTSystem->waitPlayer[i] == 5) {
						app->BTSystem->waitPlayer[i] = 0;
					}
				}
				SpecialAttackEnable = false;
				SpeacialAttackEnd = true;

			}
		}
	}
}

void battleSystem::ChoosePlayer()
{
	if (app->player->P1.IsAlive) {
		if (AttackPlayer == 1) {
			Choose->x = 5;
			Choose->y = 6;
			Choose->w = 120;
			Choose->h = 120;
			app->render->DrawTexture(selectPlayer, app->player->P1.position.x - 430 + 120, app->player->P1.position.y - 230, Choose);
		}
		MiniPlayerButton1->state = GuiControlState::NORMAL;
		randomAux = true;
	}
	else {
		//DeathSprite
		MiniPlayerButton1->state = GuiControlState::DISABLED;
	}
	if (app->player->P2.IsAlive) {
		if (AttackPlayer == 2) {
			Choose->x = 5;
			Choose->y = 6;
			Choose->w = 120;
			Choose->h = 120;
			app->render->DrawTexture(selectPlayer, app->player->P1.position.x - 430, app->player->P1.position.y - 230 + 130, Choose);
		}
		MiniPlayerButton2->state = GuiControlState::NORMAL;
	}
	else {
		//DeathSprite
		MiniPlayerButton2->state = GuiControlState::DISABLED;
	}
	if (app->player->P3.IsAlive) {
		if (AttackPlayer == 3) {
			Choose->x = 5;
			Choose->y = 6;
			Choose->w = 120;
			Choose->h = 120;
			app->render->DrawTexture(selectPlayer, app->player->P1.position.x - 430 + 120, app->player->P1.position.y - 230 + 260, Choose);
		}
		MiniPlayerButton3->state = GuiControlState::NORMAL;
	}
	else {
		//DeathSprite
		MiniPlayerButton3->state = GuiControlState::DISABLED;
	}
	if (app->player->P4.IsAlive) {
		if (AttackPlayer == 4) {
			Choose->x = 5;
			Choose->y = 6;
			Choose->w = 120;
			Choose->h = 120;
			app->render->DrawTexture(selectPlayer, app->player->P1.position.x - 430, app->player->P1.position.y - 230 + 390, Choose);
		}
		MiniPlayerButton4->state = GuiControlState::NORMAL;
	}
	else {
		//DeathSprite
		MiniPlayerButton4->state = GuiControlState::DISABLED;
	}
}

void battleSystem::DrawHpBars() {
	if (app->player->P1.IsAlive == true) {
		app->render->DrawTexture(app->player->player1Hp, app->player->P1.position.x - 190, app->player->P1.position.y - 225);
		SDL_Rect bar1 = { app->player->P1.position.x - 180, app->player->P1.position.y - 220, (200 * app->player->P1.hp) / 100,15 };
		app->render->DrawRectangle(bar1, 255, 0, 0);
		SDL_Rect bar1_ = { app->player->P1.position.x - 180, app->player->P1.position.y - 190, (200 * app->player->P1.mana) / 100,15 };
		app->render->DrawRectangle(bar1_, 0, 0, 255);
	}
	if (app->player->P2.IsAlive == true) {
		app->render->DrawTexture(app->player->player2Hp, app->player->P1.position.x - 310, app->player->P1.position.y - 225 + 130);
		SDL_Rect bar2 = { app->player->P1.position.x - 300, app->player->P1.position.y - 220 + 130, (200 * app->player->P2.hp) / 100,15 };
		app->render->DrawRectangle(bar2, 255, 0, 0);
		SDL_Rect bar2_ = { app->player->P1.position.x - 300, app->player->P1.position.y - 190 + 130, (200 * app->player->P2.mana) / 100,15 };
		app->render->DrawRectangle(bar2_, 0, 0, 255);
	}
	if (app->player->P3.IsAlive == true) {
		app->render->DrawTexture(app->player->player3Hp, app->player->P1.position.x - 190, app->player->P1.position.y - 225 + 260);
		SDL_Rect bar3 = { app->player->P1.position.x - 180, app->player->P1.position.y - 220 + 260, (200 * app->player->P3.hp) / 100,15 };
		app->render->DrawRectangle(bar3, 255, 0, 0);
		SDL_Rect bar3_ = { app->player->P1.position.x - 180, app->player->P1.position.y - 190 + 260, (200 * app->player->P3.mana) / 100,15 };
		app->render->DrawRectangle(bar3_, 0, 0, 255);
	}
	if (app->player->P4.IsAlive == true) {
		app->render->DrawTexture(app->player->player4Hp, app->player->P1.position.x - 310, app->player->P1.position.y - 225 + 390);
		SDL_Rect bar4 = { app->player->P1.position.x - 300, app->player->P1.position.y - 220 + 390, (200 * app->player->P4.hp) / 100,15 };
		app->render->DrawRectangle(bar4, 255, 0, 0);
		SDL_Rect bar4_ = { app->player->P1.position.x - 300, app->player->P1.position.y - 190 + 390, (200 * app->player->P4.mana) / 100,15 };
		app->render->DrawRectangle(bar4_, 0, 0, 255);
	}
}

bool battleSystem::OnGuiMouseClickEvent(GuiControl* control)
{
	
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		
		//Checks the GUI element ID
		if (control->id == 31 && AttackPhaseActive == true && AttackPhaseEnable == true && VampireTarget != 0 && ZombieTarget != 0) {
			AttackPhaseDisabled2();
		}
		if (control->id == 31 && AttackPhaseActive == false && AttackPhaseEnable == false && AttackPlayer != 0 && (VampireTarget != 0 || ZombieTarget != 0))
		{
			AttackPhase();
			AttackPhaseEnable = true;
		}
		if (AttackPhaseActive == false && AttackPhaseEnable == true) {
			AttackPhaseEnable = false;
		}
		if (control->id == 32 && (VampireTarget != 0 || ZombieTarget != 0))
		{
			AttackType = 1;
			AttackPhaseDisabled();
			AttackPhaseEnable = false;
		}
		if (control->id == 33 && (VampireTarget != 0 || ZombieTarget != 0))
		{
			AttackType = 2;
			AttackPhaseDisabled();
			AttackPhaseEnable = false;
		}
		if (control->id == 34 && AttackPlayer == 1 && (VampireTarget != 0 || ZombieTarget != 0) && SpecialAttackEnable == false && app->player->P1.mana >= 60)
		{
			app->player->P1.mana -= 60;
			SpecialAttackEnable = true;
		}
		if (control->id == 34 && AttackPlayer == 2 && (VampireTarget != 0 || ZombieTarget != 0) && SpecialAttackEnable == false && app->player->P2.mana >= 80)
		{
			app->player->P2.mana -= 80;
			SpecialAttackEnable = true;
		}
		if (control->id == 34 && AttackPlayer == 3 && SpecialAttackEnable == false && app->player->P3.mana >= 25)
		{
			app->player->P3.mana -= 25;
			SpecialAttackEnable = true;
		}
		if (control->id == 34 && AttackPlayer == 4 && (VampireTarget != 0 || ZombieTarget != 0) && SpecialAttackEnable == false && app->player->P3.mana >= 40 && app->player->P4.revolverActive == true)
		{
			app->player->P4.mana -= 40;
			SpecialAttackEnable = true;
		}
		if (control->id == 35)
		{
			InventoryEnable = true;
			
			CloseInventory->state = GuiControlState::NORMAL;
		}
		if (control->id == 36 && battle == true) {
			battle = false;
			Delay = false;
			Zombiebattle = false;
			Vampirebattle = false;
			timer1 = SDL_GetTicks() / 1000;
			timer1_ = timer1;
		}
		if (control->id == 37) {
			InventoryEnable = false;
			CloseInventory->state = GuiControlState::DISABLED;
		}
		if (control->id == 38) {
			QTE2->state = GuiControlState::DISABLED;
			AttackAux += 8;
		}
		if (control->id == 39 && ChoosePlayerPhase == true && SpecialAttackEnable == false && waitPlayer[0] == 0) {
			AttackPlayer = 1;
			SpecialAttackEnable = false;
			
		}
		if (control->id == 39 && ChoosePlayerPhase == true && SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {//GodMode
			AttackPlayer = 1;
			SpecialAttackEnable = false;
			app->player->P1.IsAlive = false;
			app->player->P1.hp = 0;
		}
		if (control->id == 40 && ChoosePlayerPhase == true && SpecialAttackEnable == false && waitPlayer[1] == 0) {
			AttackPlayer = 2;
			SpecialAttackEnable = false;
		}
		if (control->id == 41 && ChoosePlayerPhase == true && SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL)==KEY_REPEAT) {//GodMode
			AttackPlayer = 2;
			SpecialAttackEnable = false;
			app->player->P2.IsAlive = false;
			app->player->P2.hp = 0;

		}
		if (control->id == 41 && ChoosePlayerPhase == true && SpecialAttackEnable == false && waitPlayer[2] == 0) {
			SpecialAttackEnable = false;
			AttackPlayer = 3;
		}
		if (control->id == 42 && ChoosePlayerPhase == true && SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {//GodMode
			AttackPlayer = 3;
			SpecialAttackEnable = false;
			app->player->P3.IsAlive = false;
			app->player->P3.hp = 0;

		}
		if (control->id == 42 && ChoosePlayerPhase == true && waitPlayer[3] == 0 && SpecialAttackEnable == false) {
			SpecialAttackEnable = false;
			AttackPlayer = 4;
		}
		if (control->id == 42 && ChoosePlayerPhase == true && SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {//GodMode
			AttackPlayer = 4;
			SpecialAttackEnable = false;
			app->player->P4.IsAlive = false;
			app->player->P4.hp = 0;

		}
		//Ch1
		if (control->id == 57) {
			
			choosingPlayer = false;
			InventoryEnable = false;

			if (increaseDmg)
			{
				app->player->P1.damage += 10;
				increaseDmg = false;
			}
			if (increaseLuck)
			{
				app->player->P1.luck += 10;
				increaseLuck = false;
			}
			if (increaseSpeed)
			{
				app->player->P1.speed += 10;
				increaseSpeed = false;
			}
			if (healing)
			{
				for (int i = 0; i < 10; i++)
				{
					app->player->P1.hp++;
				}
				if (app->player->P1.hp >= 75.0) app->player->P1.hp = 75.0;
				healing = false;
			}
		}
		//Ch2
		if (control->id == 58) {
			
			choosingPlayer = false;
			InventoryEnable = false;

			if (increaseDmg)
			{
				app->player->P2.damage += 10;
				increaseDmg = false;
			}
			if (increaseLuck)
			{
				app->player->P2.luck += 10;
				increaseLuck = false;
			}
			if (increaseSpeed)
			{
				app->player->P2.speed += 10;
				increaseSpeed = false;
			}
			if (healing)
			{
				for (int i = 0; i < 10; i++)
				{
					app->player->P2.hp++;
				}
				if (app->player->P2.hp >= 45.0) app->player->P2.hp = 45.0;
				healing = false;
			}
		}
		//Ch3
		if (control->id == 59) {
			
			choosingPlayer = false;
			InventoryEnable = false;

			if (increaseDmg)
			{
				app->player->P3.damage += 10;
				increaseDmg = false;
			}
			if (increaseLuck)
			{
				app->player->P3.luck += 10;
				increaseLuck = false;
			}
			if (increaseSpeed)
			{
				app->player->P3.speed += 10;
				increaseSpeed = false;
			}
			if (healing)
			{
				for (int i = 0; i < 10; i++)
				{
					app->player->P3.hp++;
				}
				if (app->player->P3.hp >= 40.0) app->player->P3.hp = 40.0;
				healing = false;
			}
		}
		//Ch4
		if (control->id == 60) {
			
			choosingPlayer = false;
			InventoryEnable = false;

			if (increaseDmg)
			{
				app->player->P4.damage += 10;
				increaseDmg = false;
			}
			if (increaseLuck)
			{
				app->player->P4.luck += 10;
				increaseLuck = false;
			}
			if (increaseSpeed)
			{
				app->player->P4.speed += 10;
				increaseSpeed = false;
			}
			if (healing)
			{
				for (int i = 0; i < 10; i++)
				{
					app->player->P4.hp++;
				}
				if (app->player->P4.hp >= 50.0) app->player->P4.hp = 50.0;
				healing = false;
			}
		}
		if (control->id == 61) {
			
			choosingPlayer = true;
			increaseDmg = true;
		}
		if (control->id == 62) {
			
			choosingPlayer = true;
			increaseLuck = true;
		}
		if (control->id == 63) {
			
			choosingPlayer = true;
			increaseSpeed = true;
		}
		if (control->id == 64) {
			
			choosingPlayer = true;
			healing = true;
		}
	}

	default: break;
	}
	
	return false;
}

void battleSystem::CheckAllies() {
		if (app->player->P1.hp <= 0 && app->player->P1.IsAlive) {
			app->player->P1.IsAlive = false;
			waitPlayer[0] = 0;
			waitPlayer[1] = 0;
			waitPlayer[2] = 0;
			waitPlayer[3] = 0;
		}
		if (app->player->P2.hp <= 0 && app->player->P2.IsAlive) {
			app->player->P2.IsAlive = false;
			waitPlayer[0] = 0;
			waitPlayer[1] = 0;
			waitPlayer[2] = 0;
			waitPlayer[3] = 0;
		}
		if (app->player->P3.hp <= 0 && app->player->P3.IsAlive) {
			app->player->P3.IsAlive = false;
			waitPlayer[0] = 0;
			waitPlayer[1] = 0;
			waitPlayer[2] = 0;
			waitPlayer[3] = 0;
		}
		if (app->player->P4.hp <= 0 && app->player->P4.IsAlive) {
			app->player->P4.IsAlive = false;
			waitPlayer[0] = 0;
			waitPlayer[1] = 0;
			waitPlayer[2] = 0;
			waitPlayer[3] = 0;
		}
		if (app->player->P1.IsAlive == false) {
			alliesDead++;
		}
		if (app->player->P2.IsAlive == false) {
			alliesDead++;
		}
		if (app->player->P3.IsAlive == false) {
			alliesDead++;
		}
		if (app->player->P4.IsAlive == false) {
			alliesDead++;
		}
		if (alliesDead == 4) {
			battle = false;
			battleWin = false;
		}
		alliesDead = 0;
}

void battleSystem::MaxHp() {
	if (app->player->P1.hp > 75) {
		app->player->P1.hp = 75;
	}
	if (app->player->P2.hp > 40) {
		app->player->P2.hp = 40;
	}
	if (app->player->P3.hp > 45) {
		app->player->P3.hp = 45;
	}
	if (app->player->P4.hp > 50) {
		app->player->P4.hp = 50;
	}
}

void battleSystem::MaxMana() {
	if (app->player->P1.mana > 100) {
		app->player->P1.mana = 100;
	}
	if (app->player->P2.mana > 100) {
		app->player->P2.mana = 100;
	}
	if (app->player->P3.mana > 100) {
		app->player->P3.mana = 100;
	}
	if (app->player->P4.mana > 100) {
		app->player->P4.mana = 100;
	}
}

void battleSystem::Pause()
{
	//btnResume = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Resume", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 250, 160, 40 }, this);
	//btnMenu = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Menu", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 320, 160, 40 }, this);
	//btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Exit", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 390, 160, 40 }, this);

	//btnResume->state = GuiControlState::DISABLED;
	//btnMenu->state = GuiControlState::DISABLED;
	//btnExit->state = GuiControlState::DISABLED;
}
