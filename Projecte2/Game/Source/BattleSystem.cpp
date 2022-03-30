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
	Attack = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Attack", { (app->win->GetWidth() / 2) - 600, app->win->GetHeight() / 10 + 190, 140, 40 }, this);
	Attack->state = GuiControlState::DISABLED;
	Attack1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Attack1", { (app->win->GetWidth() / 2) - 590, app->win->GetHeight() / 14 + 180, 120, 40 }, this);
	Attack1->state = GuiControlState::DISABLED;
	Attack2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Attack2", { (app->win->GetWidth() / 2) - 590, app->win->GetHeight() / 14 + 140, 120, 40 }, this);
	Attack2->state = GuiControlState::DISABLED;
	SpecialAttack = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "SpecialAttack", { (app->win->GetWidth() / 2) - 450, app->win->GetHeight() / 10 + 190, 140, 40 }, this);
	SpecialAttack->state = GuiControlState::DISABLED;
	Inventory = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Inventory", { (app->win->GetWidth() / 2) - 600, app->win->GetHeight() / 10 + 240, 140, 40 }, this);
	Inventory->state = GuiControlState::DISABLED;
	Run = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Run", { (app->win->GetWidth() / 2) - 450, app->win->GetHeight() / 10 + 240, 140, 40 }, this);
	Run->state = GuiControlState::DISABLED;
	CloseInventory = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, "CloseInventory", { (app->win->GetWidth() / 2) - 130, app->win->GetHeight() / 10 - 30, 15, 15 }, this);
	CloseInventory->state = GuiControlState::DISABLED;
	QTE2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "QTE2", { (app->win->GetWidth() / 2) + 0, app->win->GetHeight() / 10 + 0, 50, 50 }, this);
	QTE2->state = GuiControlState::DISABLED;
	MiniPlayerButton1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 9, "MiniPlayerButton1", { (app->win->GetWidth() / 2) - 576, app->win->GetHeight() / 10 - 8, 50, 50 }, this);
	MiniPlayerButton1->state = GuiControlState::DISABLED;
	MiniPlayerButton2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, "MiniPlayerButton2", { (app->win->GetWidth() / 2) - 520, app->win->GetHeight() / 10 + 38, 50, 50 }, this);
	MiniPlayerButton2->state = GuiControlState::DISABLED;
	MiniPlayerButton3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, "MiniPlayerButton3", { (app->win->GetWidth() / 2) - 576, app->win->GetHeight() / 10 + 88, 50, 50 }, this);
	MiniPlayerButton3->state = GuiControlState::DISABLED;
	MiniPlayerButton4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 12, "MiniPlayerButton4", { (app->win->GetWidth() / 2) - 520, app->win->GetHeight() / 10 + 138, 50, 50 }, this);
	MiniPlayerButton4->state = GuiControlState::DISABLED;

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
	//app->map->DColisions();
	// L02: DONE 3: Request Load / Save when pressing L/S

	//PassTurn();

	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		debug = !debug;

	}
	app->render->camera.x = (app->player->P1.position.x - 550) * -1;
	app->render->camera.y = (app->player->P1.position.y - 300) * -1;

	//Draw map
	//app->map->Draw();

	//Draw GUI
	if (battle == true) {
		SDL_Rect battle_screen = { 20,20,530,340 };
		app->render->DrawRectangle(battle_screen, 0, 250, 250);
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
	else {
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
	SDL_Rect Inventory_ = { 20,20,530,340 };
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
			randomx = (rand() % 500);
			randomy = (rand() % 300);
			QTE2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "QTE2", { (app->win->GetWidth() / 2) + randomx - 600, app->win->GetHeight() / 10 + randomy-10, 50, 50 }, this);
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
				finalpos = timer1_ + 125;
				if (finalpos > randomtargetRect_ && finalpos + 20 < randomtargetRect_ + 30) {
					AttackAux = 100;
				}
				else if (finalpos > randomtargetRect_ - 30 && finalpos + 20 < randomtargetRect_ + 60) {
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
			
			SDL_Rect largeRect = { 125,300,300,40 };
			app->render->DrawRectangle(largeRect, 0, 250, 0);
			SDL_Rect targetRect2 = { randomtargetRect_ - 30,300,90,40 };
			app->render->DrawRectangle(targetRect2, 255, 128, 0);
			SDL_Rect targetRect = { randomtargetRect_,300,30,40 };
			app->render->DrawRectangle(targetRect, 250, 250, 0);
			SDL_Rect PointRect = { 125 + timer1_,310,20,20 };
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
			app->render->DrawTexture(TypoSpecialAttack, 250, 140,TypoLetter);
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
	SDL_Rect MiniPlayer2hp_ = { 125 + 60,110,app->player->P2.hp,10 };
	SDL_Rect MiniPlayer3hp_ = { 64 + 60,160,app->player->P3.hp,10 };
	SDL_Rect MiniPlayer1hp_ = { 64 + 60,64,app->player->P1.hp,10 };
	if (app->player->P1.IsAlive) {
		if (AttackPlayer == 1) {
			SDL_Rect MiniPlayer1_ = { 59,59,60,60 };
			app->render->DrawRectangle(MiniPlayer1_, 255, 255, 0);
			
		}
		app->render->DrawRectangle(MiniPlayer1hp_, 255, 0, 0);
		MiniPlayerButton1->state = GuiControlState::NORMAL;
		randomAux = true;
	}
	else {
		//DeathSprite
		MiniPlayerButton1->state = GuiControlState::DISABLED;
	}
	if (app->player->P2.IsAlive) {
		if (AttackPlayer == 2) {
			SDL_Rect MiniPlayer1_ = { 115,105,60,60 };
			app->render->DrawRectangle(MiniPlayer1_, 255, 255, 0);
		}
		app->render->DrawRectangle(MiniPlayer2hp_, 255, 0, 0);
		MiniPlayerButton2->state = GuiControlState::NORMAL;
	}
	else {
		//DeathSprite
		MiniPlayerButton2->state = GuiControlState::DISABLED;
	}
	if (app->player->P3.IsAlive) {
		if (AttackPlayer == 3) {
			SDL_Rect MiniPlayer1_ = { 59,155,60,60 };
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
			SDL_Rect MiniPlayer1_ = { 115,205,60,60 };
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
		if (control->id == 9 && ChoosePlayerPhase == true && waitPlayer[0] == 0) {
			AttackPlayer = 1;
			SpecialAttackEnable = false;
			
		}
		if (control->id == 9 && ChoosePlayerPhase == true && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {//GodMode
			AttackPlayer = 1;
			SpecialAttackEnable = false;
			app->player->P1.IsAlive = false;
			app->player->P1.hp = 0;
		}
		if (control->id == 10 && ChoosePlayerPhase == true &&waitPlayer[1] == 0) {
			AttackPlayer = 2;
			SpecialAttackEnable = false;
		}
		if (control->id == 10 && ChoosePlayerPhase == true && app->input->GetKey(SDL_SCANCODE_LCTRL)==KEY_REPEAT) {//GodMode
			AttackPlayer = 2;
			SpecialAttackEnable = false;
			app->player->P2.IsAlive = false;
			app->player->P2.hp = 0;

		}
		if (control->id == 11 && ChoosePlayerPhase == true && waitPlayer[2] == 0) {
			SpecialAttackEnable = false;
			AttackPlayer = 3;
		}
		if (control->id == 11 && ChoosePlayerPhase == true && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {//GodMode
			AttackPlayer = 3;
			SpecialAttackEnable = false;
			app->player->P3.IsAlive = false;
			app->player->P3.hp = 0;

		}
		if (control->id == 12 && ChoosePlayerPhase == true && waitPlayer[3] == 0) {
			SpecialAttackEnable = false;
			AttackPlayer = 4;
		}
		if (control->id == 12 && ChoosePlayerPhase == true && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {//GodMode
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
		}
		alliesDead = 0;
	
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
