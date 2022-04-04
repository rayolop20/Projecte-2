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
	Attack = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Attack", {0, 0, 0, 0 }, this);
	Attack->state = GuiControlState::DISABLED;
	Attack1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Attack1", { 0, 0, 0, 0 }, this);
	Attack1->state = GuiControlState::DISABLED;
	Attack2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Attack2", { 0, 0, 0, 0 }, this);
	Attack2->state = GuiControlState::DISABLED;
	SpecialAttack = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "SpecialAttack", { 0, 0, 0, 0 }, this);
	SpecialAttack->state = GuiControlState::DISABLED;
	Inventory = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Inventory", { 0,0, 0, 0 }, this);
	Inventory->state = GuiControlState::DISABLED;
	Run = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Run", { 0, 0, 0, 0 }, this);
	Run->state = GuiControlState::DISABLED;
	CloseInventory = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, "CloseInventory", { 0, 0, 0, 0 }, this);
	CloseInventory->state = GuiControlState::DISABLED;
	QTE2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "QTE2", { 0, 0, 0, 0 }, this);
	QTE2->state = GuiControlState::DISABLED;
	MiniPlayerButton1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 9, "MiniPlayerButton1", { 0,0, 0, 0 }, this);
	MiniPlayerButton1->state = GuiControlState::DISABLED;
	MiniPlayerButton2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, "MiniPlayerButton2", { 0, 0, 0, 0 }, this);
	MiniPlayerButton2->state = GuiControlState::DISABLED;
	MiniPlayerButton3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, "MiniPlayerButton3", {0, 0, 0, 0 }, this);
	MiniPlayerButton3->state = GuiControlState::DISABLED;
	MiniPlayerButton4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 12, "MiniPlayerButton4", { 0, 0, 0, 0 }, this);
	MiniPlayerButton4->state = GuiControlState::DISABLED;
	//Initialize playerTurns
	for (int i = 0; i <= 4 - alliesDead;i++) {
		waitPlayer[i] = 0;
	}
	// L03: DONE: Load map
	TypoSpecialAttack = app->tex->Load("Assets/textures/Typo_SpecialAttack_4.png");
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	//L13: TODO 2: Declare an Item and create it using the EntityManager
	VampirEnem* Vampir = (VampirEnem*)app->entityManager->CreateEntity(EntityType::VAMPYRENEM, 0, { 0,0 });

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
		MiniPlayerButton3->state = GuiControlState::NORMAL; app->render->DrawRectangle(battle_screen, 0, 250, 250);
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
	if (SpecialAttackEnable && AttackPlayer != 0 && VampireTarget != 0 ) {
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
		InventoryPhase();
	}
	if (debug == true) {
		//Debug Collisions
		app->collisions->DebugDraw();
	}
	app->guiManager->Draw();
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
	AttackPlayer = 0;
	AttackPhaseActive = false;
	AttackPhaseEnable = false;
	ChoosePlayerPhase = true;
	randomAux = true;
}

void battleSystem::InventoryPhase() {
	SDL_Rect Inventory_ = { app->player->P1.position.x - 640 + 32 + 50,app->player->P1.position.y - 360 + 32 + 25,1280 - 100,720 - 50};
	app->render->DrawRectangle(Inventory_, 0,250,0);
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

void battleSystem::SpecialAttackPhase() {
	srand(time(NULL));
	if (randomAttack == 0) {//QTE Random activator
		randomAttack = (rand() % 4) + 1;
	}
	if (randomAttack == 1) {//QTE 1
		timer1 = SDL_GetTicks() / 1000;
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
			AttackAux = 0;
			app->BTSystem->waitPlayer[AttackPlayer-1] += 1;
 			AttackPlayer = 0;
			VampireTarget = 0;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] == 5) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
			SpecialAttackEnable = false;
		}
	}
	if (randomAttack == 2) {//QTE 2
		timer1 = SDL_GetTicks() / 1000;
		if (AttackAux == 0 && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			timer1_ = timer1;
			AttackAux = 1;
		}
		randomx = (rand() % 500);
		randomy = (rand() % 300);
		if (QTE2->state == GuiControlState::DISABLED && AttackAux != 0) {
			randomx = (rand() % 800);
			randomy = (rand() % 400);
			QTE2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "QTE2", { randomx + app->player->P1.position.x - 300, randomy + app->player->P1.position.y - 200, 50, 50 }, this);
			QTE2->state = GuiControlState::NORMAL;
		}
		if (AttackAux > 100) {
			AttackAux = 100 ;
		}
		if (timer1 > timer1_ + 5 && AttackAux != 0) {
			randomAttack = 0;
			QTE2->state = GuiControlState::DISABLED;
			//enemy.hp = enemy.hp - player.attack + AttackAux;
			app->BTSystem->waitPlayer[AttackPlayer - 1] += 1;
			AttackPlayer = 0;
			VampireTarget = 0;
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
		}
		//pp->render->DrawRectangle(block1, 250, 0, 0);
	}
	if (randomAttack == 3) {//QTE 3
		randomtargetRect = (rand() % 185) + 165;
		if (AttackAux == 0 && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			timer1_ = timer1;
			AttackAux = 1;
			randomtargetRect = (rand() % 185) + 165;
			randomtargetRect_ = randomtargetRect;
		}
		if (AttackAux != 0) {

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timer1_ > timer1 + 0.5) {
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
				//enemy.hp = enemy.hp - player.attack + AttackAux;
				app->BTSystem->waitPlayer[AttackPlayer - 1] += 1;
				AttackPlayer = 0;
				VampireTarget = 0;
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
		}
	}
	if (randomAttack == 4) {//QTE 4
		timer1 = SDL_GetTicks() / 1000;
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
			SDL_Rect *TypoLetter = new SDL_Rect();
			TypoLetter->x = (randomLetterGenerator-1)*22;
			TypoLetter->y = 0;
			TypoLetter->w = 22;
			TypoLetter->h = 54;
			app->render->DrawTexture(TypoSpecialAttack, app->player->P1.position.x + 32, app->player->P1.position.y - 64,TypoLetter);
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
				//enemy.hp = enemy.hp - player.attack + AttackAux;
				app->BTSystem->waitPlayer[AttackPlayer - 1] += 1;
				AttackPlayer = 0;
				VampireTarget = 0;
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
			}
		}
	}
}

void battleSystem::ChoosePlayer()
{
	if (app->player->P1.IsAlive) {
		if (AttackPlayer == 1) {
			SDL_Rect MiniPlayer1_ = { app->player->P1.position.x - 430 + 120, app->player->P1.position.y - 230, 120, 120 };
			app->render->DrawRectangle(MiniPlayer1_, 255, 255, 0);
			
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
			SDL_Rect MiniPlayer1_ = { app->player->P1.position.x - 430, app->player->P1.position.y - 230 + 130, 120, 120 };
			app->render->DrawRectangle(MiniPlayer1_, 255, 255, 0);
		}
		MiniPlayerButton2->state = GuiControlState::NORMAL;
	}
	else {
		//DeathSprite
		MiniPlayerButton2->state = GuiControlState::DISABLED;
	}
	if (app->player->P3.IsAlive) {
		if (AttackPlayer == 3) {
			SDL_Rect MiniPlayer1_ = { app->player->P1.position.x - 430 + 120, app->player->P1.position.y - 230 + 260, 120, 120 };
			app->render->DrawRectangle(MiniPlayer1_, 255, 255, 0);
		}
		MiniPlayerButton3->state = GuiControlState::NORMAL;
	}
	else {
		//DeathSprite
		MiniPlayerButton3->state = GuiControlState::DISABLED;
	}
	if (app->player->P4.IsAlive) {
		if (AttackPlayer == 4) {
			SDL_Rect MiniPlayer1_ = { app->player->P1.position.x - 430, app->player->P1.position.y - 230 + 390, 120, 120 };
			app->render->DrawRectangle(MiniPlayer1_, 255, 255, 0);
		}
		MiniPlayerButton4->state = GuiControlState::NORMAL;
	}
	else {
		//DeathSprite
		MiniPlayerButton4->state = GuiControlState::DISABLED;
	}
}

bool battleSystem::OnGuiMouseClickEvent(GuiControl* control)
{
	
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		
		//Checks the GUI element ID
		if (control->id == 1 && AttackPhaseActive == true && AttackPhaseEnable == true && VampireTarget != 0) {
			AttackPhaseDisabled2();
		}
		if (control->id == 1 && AttackPhaseActive == false && AttackPhaseEnable == false && AttackPlayer != 0 && VampireTarget != 0)
		{
			AttackPhase();
			AttackPhaseEnable = true;
		}
		if (AttackPhaseActive == false && AttackPhaseEnable == true) {
			AttackPhaseEnable = false;
		}
		if (control->id == 2 && VampireTarget != 0)
		{
			AttackType = 1;
			AttackPhaseDisabled();
			AttackPhaseEnable = false;
		}
		if (control->id == 3 && VampireTarget != 0)
		{
			AttackType = 2;
			AttackPhaseDisabled();
			AttackPhaseEnable = false;
		}
		if (control->id == 4)
		{
			SpecialAttackEnable = true;
		}
		if (control->id == 5)
		{
			InventoryEnable = true;
			
			CloseInventory->state = GuiControlState::NORMAL;
		}
		if (control->id == 6 && battle == true) {
			battle = false;
			Delay = false;
			timer1 = SDL_GetTicks() / 1000;
			timer1_ = timer1;

		}
		if (control->id == 7) {
			InventoryEnable = false;
			CloseInventory->state = GuiControlState::DISABLED;
		}
		if (control->id == 8) {
			QTE2->state = GuiControlState::DISABLED;
			AttackAux += 8;
		}
		if (control->id == 9 && ChoosePlayerPhase == true && SpecialAttackEnable == false && waitPlayer[0] == 0) {
			AttackPlayer = 1;
			SpecialAttackEnable = false;
			
		}
		if (control->id == 9 && ChoosePlayerPhase == true && SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {//GodMode
			AttackPlayer = 1;
			SpecialAttackEnable = false;
			app->player->P1.IsAlive = false;
			app->player->P1.hp = 0;
		}
		if (control->id == 10 && ChoosePlayerPhase == true && SpecialAttackEnable == false && waitPlayer[1] == 0) {
			AttackPlayer = 2;
			SpecialAttackEnable = false;
		}
		if (control->id == 10 && ChoosePlayerPhase == true && SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL)==KEY_REPEAT) {//GodMode
			AttackPlayer = 2;
			SpecialAttackEnable = false;
			app->player->P2.IsAlive = false;
			app->player->P2.hp = 0;

		}
		if (control->id == 11 && ChoosePlayerPhase == true && SpecialAttackEnable == false && waitPlayer[2] == 0) {
			SpecialAttackEnable = false;
			AttackPlayer = 3;
		}
		if (control->id == 11 && ChoosePlayerPhase == true && SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {//GodMode
			AttackPlayer = 3;
			SpecialAttackEnable = false;
			app->player->P3.IsAlive = false;
			app->player->P3.hp = 0;

		}
		if (control->id == 12 && ChoosePlayerPhase == true && waitPlayer[3] == 0 && SpecialAttackEnable == false) {
			SpecialAttackEnable = false;
			AttackPlayer = 4;
		}
		if (control->id == 12 && ChoosePlayerPhase == true && SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {//GodMode
			AttackPlayer = 4;
			SpecialAttackEnable = false;
			app->player->P4.IsAlive = false;
			app->player->P4.hp = 0;

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

void battleSystem::Pause()
{
	//btnResume = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Resume", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 250, 160, 40 }, this);
	//btnMenu = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Menu", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 320, 160, 40 }, this);
	//btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Exit", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 390, 160, 40 }, this);

	//btnResume->state = GuiControlState::DISABLED;
	//btnMenu->state = GuiControlState::DISABLED;
	//btnExit->state = GuiControlState::DISABLED;
}
