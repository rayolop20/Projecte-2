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
#include "SkeletonEnem.h"
#include "EntityNPC.h"
#include "Collisions.h"
#include "BattleSystem.h"
#include "Scene.h"
#include "CharacterMenu.h"
#include "StatsMenu.h"
#include "Menu.h"

#include "Defs.h"
#include "Log.h"
#include <time.h>

qteAnimation::qteAnimation() : Module()
{
	name.Create("qteAnimation");
	qte1.PushBack({ 65, 47, 60, 60 });
	qte1.PushBack({ 206, 43, 60, 60 });
	qte1.PushBack({ 348, 44, 60, 60 });
	qte1.PushBack({ 488, 44, 60, 60 });
	qte1.PushBack({ 620, 40, 70, 70 });
	qte1.PushBack({ 47, 158, 70, 70 });
	qte1.PushBack({ 195, 155, 70, 70 });
	qte1.PushBack({ 335, 155, 70, 70 });
	qte1.PushBack({ 482, 155, 70, 70 });
	qte1.PushBack({ 625, 155, 70, 70 });
	qte1.PushBack({ 0, 0, 0, 0 });
	qte1.loop = false;
	qte1.speed = 0.005f;


	qte2.PushBack({ 51, 36, 301, 63 });
	qte2.PushBack({ 579, 36, 301, 63 });
	qte2.PushBack({ 51, 186, 301, 63 });
	qte2.PushBack({ 579, 186, 301, 63 });
	qte2.PushBack({ 51, 336, 301, 63 });
	qte2.PushBack({ 579, 336, 301, 63 });
	qte2.PushBack({ 51, 486, 301, 63 });
	qte2.PushBack({ 579, 486, 301, 63 });
	qte2.loop = true;
	qte2.speed = 0.005f;

	/*qte2fx.PushBack({ , , , 77 });
	qte2fx.PushBack({ , , , 77 });
	qte2fx.PushBack({ , , , 77 });
	qte2fx.PushBack({ , , , 77 });
	qte2fx.PushBack({ , , , 77 });
	qte2fx.PushBack({ , , , 77 });
	qte2fx.PushBack({ , , , 77 });
	qte2fx.PushBack({ , , , 77 });
	qte2fx.loop = false;
	qte2fx.speed = 0.005f;*/
};


battleSystem::battleSystem() : Module()
{

	name.Create("battleSystem");

	idleAttack1.PushBack({ 0, 0, 160, 192 });
	idleAttack1.loop = true;
	idleAttack1.speed = 0.001f;
	AttackAnim1.PushBack({ 0, 0, 160, 192 });
	AttackAnim1.PushBack({ 160, 0, 160, 192 });
	AttackAnim1.PushBack({ 320, 0, 160, 192 });
	AttackAnim1.PushBack({ 480, 0, 160, 192 });
	AttackAnim1.PushBack({ 640, 0, 160, 192 });
	AttackAnim1.loop = false;
	AttackAnim1.speed = 0.08f;
	
	idleAttack2.PushBack({ 0, 0, 160, 192 });
	idleAttack2.loop = true;
	idleAttack2.speed = 0.001f;
	AttackAnim2.PushBack({ 0, 0, 160, 192 });
	AttackAnim2.PushBack({ 160, 0, 160, 192 });
	AttackAnim2.PushBack({ 320, 0, 160, 192 });
	AttackAnim2.PushBack({ 480, 0, 160, 192 });
	AttackAnim2.PushBack({ 640, 0, 160, 192 });
	AttackAnim2.loop = false;
	AttackAnim2.speed = 0.08f;
	
	idleAttack3.PushBack({ 0, 0, 160, 192 });
	idleAttack3.loop = true;
	idleAttack3.speed = 0.001f;
	AttackAnim3.PushBack({ 0, 0, 160, 192 });
	AttackAnim3.PushBack({ 160, 0, 160, 192 });
	AttackAnim3.PushBack({ 320, 0, 160, 192 });
	AttackAnim3.PushBack({ 480, 0, 160, 192 });
	AttackAnim3.PushBack({ 640, 0, 160, 192 });
	AttackAnim3.PushBack({ 800, 0, 160, 192 });
	AttackAnim3.loop = false;
	AttackAnim3.speed = 0.08f;
	
	
	idleAttack4.PushBack({ 0, 0, 160, 192 });
	idleAttack4.loop = true;
	idleAttack4.speed = 0.001f;
	AttackAnim4.PushBack({ 0, 0, 160, 192 });
	AttackAnim4.PushBack({ 160, 0, 160, 192 });
	AttackAnim4.PushBack({ 320, 0, 160, 192 });
	AttackAnim4.PushBack({ 480, 0, 160, 192 });
	AttackAnim4.PushBack({ 640, 0, 160, 192 });
	AttackAnim4.loop = false;
	AttackAnim4.speed = 0.08f;
	
	idleAttack5.PushBack({ 0, 0, 160, 192 });
	idleAttack5.loop = true;
	idleAttack5.speed = 0.001f;
	AttackAnim5.PushBack({ 0, 0, 160, 192 });
	AttackAnim5.PushBack({ 160, 0, 160, 192 });
	AttackAnim5.PushBack({ 320, 0, 160, 192 });
	AttackAnim5.PushBack({ 480, 0, 160, 192 });
	AttackAnim5.PushBack({ 640, 0, 160, 192 });
	AttackAnim5.loop = false;
	AttackAnim5.speed = 0.08f;

	idleHit1.PushBack({ 0, 0, 160, 192 });
	idleHit1.loop = false;
	idleHit1.speed = 0.001f;
	HitAnim1.PushBack({ 0, 0, 160, 192 });
	HitAnim1.PushBack({ 160, 0, 160, 192 });
	HitAnim1.PushBack({ 320, 0, 160, 192 });
	HitAnim1.PushBack({ 480, 0, 160, 192 });
	HitAnim1.loop = false;
	HitAnim1.speed = 0.1f;
	
	idleHit2.PushBack({ 0, 0, 160, 192 });
	idleHit2.loop = false;
	idleHit2.speed = 0.001f;
	HitAnim2.PushBack({ 0, 0, 160, 192 });
	HitAnim2.PushBack({ 160, 0, 160, 192 });
	HitAnim2.PushBack({ 320, 0, 160, 192 });
	HitAnim2.PushBack({ 480, 0, 160, 192 });
	HitAnim2.loop = false;
	HitAnim2.speed = 0.1f;
	
	idleHit3.PushBack({ 0, 0, 160, 192 });
	idleHit3.loop = false;
	idleHit3.speed = 0.001f;
	HitAnim3.PushBack({ 0, 0, 160, 192 });
	HitAnim3.PushBack({ 160, 0, 160, 192 });
	HitAnim3.PushBack({ 320, 0, 160, 192 });
	HitAnim3.PushBack({ 480, 0, 160, 192 });
	HitAnim3.loop = false;
	HitAnim3.speed = 0.1f;

	idleHit4.PushBack({ 0, 0, 160, 192 });
	idleHit4.loop = false;
	idleHit4.speed = 0.001f;
	HitAnim4.PushBack({ 0, 0, 160, 192 });
	HitAnim4.PushBack({ 160, 0, 160, 192 });
	HitAnim4.PushBack({ 320, 0, 160, 192 });
	HitAnim4.PushBack({ 480, 0, 160, 192 });
	HitAnim4.loop = false;
	HitAnim4.speed = 0.1f;

	idleHit5.PushBack({ 0, 0, 160, 192 });
	idleHit5.loop = false;
	idleHit5.speed = 0.001f;
	HitAnim5.PushBack({ 0, 0, 160, 192 });
	HitAnim5.PushBack({ 160, 0, 160, 192 });
	HitAnim5.PushBack({ 320, 0, 160, 192 });
	HitAnim5.PushBack({ 480, 0, 160, 192 });
	HitAnim5.loop = false;
	HitAnim5.speed = 0.1f;
	
	idleDeath3.PushBack({ 0, 0, 160, 192 });
	idleDeath3.loop = false;
	idleDeath3.speed = 0.001f;
	DeathAnim3.PushBack({ 0, 0, 160, 192 });
	DeathAnim3.PushBack({ 160, 0, 160, 192 });
	DeathAnim3.PushBack({ 320, 0, 160, 192 });
	DeathAnim3.PushBack({ 480, 0, 160, 192 });
	DeathAnim3.loop = false;
	DeathAnim3.speed = 0.1f;
	
	
	/*idle1.PushBack({62, 25, 85, 149});
	idle1.loop = false;
	idle1.speed = 0.001f;


	idle2.PushBack({ 37, 21, 102, 150 });
	idle2.loop = false;
	idle2.speed = 0.001f;
	
	idle3.PushBack({ 1, 58, 126, 130 });
	idle3.loop = false;
	idle3.speed = 0.001f;

	idle4.PushBack({ 14, 8, 141, 182 });
	idle4.loop = false;
	idle4.speed = 0.001f;

	Atack_1.PushBack({ 62, 25, 85, 149 });
	Atack_1.PushBack({ 192, 59, 86, 115 });
	Atack_1.PushBack({ 328, 64, 128, 110 });
	Atack_1.PushBack({ 464, 59, 86, 115 });
	Atack_1.PushBack({ 606, 25, 85, 149 });
	Atack_1.loop = false;
	Atack_1.speed = 0.05f;*/
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
	StatsMenu = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 65, "StatsMenu", { 0, 0, 0, 0 }, this);
	StatsMenu->state = GuiControlState::DISABLED;
	CloseStatsMenu = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 66, "CloseStatsMenu", { 0, 0, 0, 0 }, this);
	CloseStatsMenu->state = GuiControlState::DISABLED;

	//Initialize playerTurns
	for (int i = 0; i <= 4 - alliesDead;i++) {
		waitPlayer[i] = 0;
	}
	for (int i = 0; i <= 5; i++) {
		poisonCount[i] = 0;
	}
	// L03: DONE: Load map
	selectPlayer = app->tex->Load("Assets/Textures/UI/choseplayers.png");
	Tutorial = app->tex->Load("Assets/Textures/UI/qte_tutorial.png");
	QTE4 = app->tex->Load("Assets/Textures/UI/qte4.png");
	PopQTE2 = app->tex->Load("Assets/Textures/UI/qte1_1.png");
	quitCross = app->tex->Load("Assets/Textures/UI/quit_cross.png");
	battle_screen = app->tex->Load("Assets/Textures/UI/battle_bg.png");
	loose = app->tex->Load("Assets/Textures/Assets/pantalla_derrota.png");

	currentAttack1 = &idleAttack1;
	currentAttack2 = &idleAttack2;
	currentAttack3 = &idleAttack3;
	currentAttack4 = &idleAttack4;
	currentAttack5 = &idleAttack5;

	currentHit1 = &idleHit1;
	currentHit2 = &idleHit2;
	currentHit3 = &idleHit3;
	currentHit4 = &idleHit4;
	currentHit5 = &idleHit5;

	currentDeath3 = &idleDeath3;

	player1A = app->tex->Load("Assets/Textures/Soldiers/soldier_britain_attack_animation.png");
	player2A = app->tex->Load("Assets/Textures/Soldiers/american_dogmaster_attack_animation.png");
	player3A = app->tex->Load("Assets/Textures/Soldiers/russian_attack_animation.png");
	player4A = app->tex->Load("Assets/Textures/Soldiers/characters_italian_attack_animation.png");
	player5A = app->tex->Load("Assets/Textures/Soldiers/french_attack_animation.png");
	
	player1H = app->tex->Load("Assets/Textures/Soldiers/britain_hit_animation.png");
	player2H = app->tex->Load("Assets/Textures/Soldiers/american_dogmaster_hit_animation.png");
	player3H = app->tex->Load("Assets/Textures/Soldiers/russian_hit_animation.png");
	player4H = app->tex->Load("Assets/Textures/Soldiers/italian_hit_animation.png");
	player5H = app->tex->Load("Assets/Textures/Soldiers/french_hit_animation.png");

	player3D = app->tex->Load("Assets/Textures/Soldiers/russian_death_animation.png");
	
	//L13: TODO 2: Declare an Item and create it using the EntityManager
	VampirEnem* Vampir = (VampirEnem*)app->entityManager->CreateEntity(EntityType::VAMPYR, 0, { 0,0 });
	ZombieEnem* Zombies = (ZombieEnem*)app->entityManager->CreateEntity(EntityType::ZOMBIE, 0, { 0,0 });
	SkeletonEnem* Skeletons = (SkeletonEnem*)app->entityManager->CreateEntity(EntityType::SKELETON, 0, { 0,0 });
	EntityNPC* Npc = (EntityNPC*)app->entityManager->CreateEntity(EntityType::NPC, 0, { 0,0 });

	//L13: TODO 4: Create multiple Items

	AttackPhaseActive = false;
	AttackAux = 0;

	currentAnimation = &idle1;
	currentAnimation2 = &idle2;
	currentAnimation3 = &idle3;
	currentAnimation4 = &idle4;

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
		StatsMenu->bounds.x = app->player->P1.position.x - 500;
		StatsMenu->bounds.y = app->player->P1.position.y - 300;
		StatsMenu->bounds.w = 78;
		StatsMenu->bounds.h = 56;
		CloseStatsMenu->bounds.x = app->player->P1.position.x + 550;
		CloseStatsMenu->bounds.y = app->player->P1.position.y - 290;
		CloseStatsMenu->bounds.w = 50;
		CloseStatsMenu->bounds.h = 50;
		CloseInventory->bounds.x = app->player->P1.position.x + 550;
		CloseInventory->bounds.y = app->player->P1.position.y - 290;
		CloseInventory->bounds.w = 50;
		CloseInventory->bounds.h = 50;
		Run->bounds.x = app->player->P1.position.x + 15;
		Run->bounds.y = app->player->P1.position.y + 285;
		Run->bounds.w = 150;
		Run->bounds.h = 61;
		//SDL_Rect battle_screen = { app->player->P1.position.x - 640 + 32,app->player->P1.position.y - 360 + 32,1280,720 };		
		app->render->DrawTexture(battle_screen, app->player->P1.position.x - 640 + 32, app->player->P1.position.y - 360 + 32);
		MiniPlayerButton1->state = GuiControlState::NORMAL;
		MiniPlayerButton2->state = GuiControlState::NORMAL;
		MiniPlayerButton4->state = GuiControlState::NORMAL;
		MiniPlayerButton3->state = GuiControlState::NORMAL;
		if (app->player->P1.IsAlive == true) {
			//app->render->DrawTexture(app->characterMenu->british, app->player->P1.position.x - 420 + 120, app->player->P1.position.y - 320);
		}
		if (app->player->P2.IsAlive == true) {
			//app->render->DrawTexture(app->characterMenu->american, app->player->P1.position.x - 450, app->player->P1.position.y - 320 + 130);
		}
		if (app->player->P3.IsAlive == true) {
			//app->render->DrawTexture(app->characterMenu->russian, app->player->P1.position.x - 450 + 120, app->player->P1.position.y - 320 + 260);
		}
		if (battle1 == true && app->player->P4.IsAlive == true) {
			//app->render->DrawTexture(app->characterMenu->italian, app->player->P1.position.x - 450, app->player->P1.position.y - 320 + 390);
		}
		if (app->player->P4.IsAlive == true && battle1 == false) {
			//app->render->DrawTexture(app->characterMenu->french, app->player->P1.position.x - 450, app->player->P1.position.y - 320 + 390);
		}

		DrawHpBars();
		if (PlayerTurn == true) {
			
			Attack->state = GuiControlState::NORMAL;
			SpecialAttack->state = GuiControlState::NORMAL;
			Inventory->state = GuiControlState::NORMAL;
			StatsMenu->state = GuiControlState::NORMAL;
			if (battle1 == false) {
				Run->state = GuiControlState::NORMAL;
			}
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
		StatsMenu->state = GuiControlState::DISABLED;
		Run->state = GuiControlState::DISABLED;
		MiniPlayerButton1->state = GuiControlState::DISABLED;
		MiniPlayerButton2->state = GuiControlState::DISABLED;
		MiniPlayerButton3->state = GuiControlState::DISABLED;
		MiniPlayerButton4->state = GuiControlState::DISABLED;
	}
	else {
		SpawnedEnemies = false;
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
		StatsMenu->bounds.h = 0;
		StatsMenu->bounds.h = 0;
		Attack->bounds.w = 0;
		Attack->bounds.h = 0;
		Attack1->bounds.w = 0;
		Attack1->bounds.h = 0;
		Attack2->bounds.w = 0;
		Attack2->bounds.h = 0;
		CloseInventory->bounds.w = 0;
		CloseInventory->bounds.h = 0;
		CloseStatsMenu->bounds.w = 0;
		CloseStatsMenu->bounds.h = 0;
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
		StatsMenu->state = GuiControlState::DISABLED;
		Run->state = GuiControlState::DISABLED;
	}
	if (SpecialAttackEnable == false && battle == true) {
		Attack->state = GuiControlState::NORMAL;
		SpecialAttack->state = GuiControlState::NORMAL;
		Inventory->state = GuiControlState::NORMAL;
		StatsMenu->state = GuiControlState::NORMAL;
		if (battle1 == false) {
			Run->state = GuiControlState::NORMAL;
		}
	}
	
	//Draw Entities
	//L13 
	//L13 
	app->entityManager->Draw();

	if (InventoryEnable) {

		if (invenCont == 0)
		{
			InventoryButtons();
			invenCont = 1;
		}
		InventoryPhase();
		SDL_Rect* bagSection = new SDL_Rect();
		bagSection->x = 13;
		bagSection->y = 26;
		bagSection->w = 612;
		bagSection->h = 479;
		app->render->DrawTexture(app->characterMenu->inventoryTexBack, -app->render->camera.x, -app->render->camera.y);
		app->render->DrawTexture(app->characterMenu->inventoryTex, -app->render->camera.x + (app->win->GetWidth() / 2 - 180), -app->render->camera.y + (app->win->GetHeight() / 2 - 230), bagSection);

		app->render->DrawTexture(quitCross, app->player->P1.position.x + 550, app->player->P1.position.y - 290);

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
	if (app->BTSystem->StatsEnable == true) {
	CloseStatsMenu->state = GuiControlState::NORMAL;
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
	//Animaciones Ataque
	AttackAnimations();

	HitPlayersAnimations();
	
	DeathPlayersAnimations();

	if (app->player->P1.IsAlive == false) {
		app->player->P1.position.x = -2000;
		app->player->P1.position.y = -2000;
		app->render->DrawTexture(loose, app->player->P1.position.x - 640 + 32, app->player->P1.position.y - 360 + 32);
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			return false;
		}
	}

	if (battleTransition && battle)
	{
		transitionLock = true;
	}

	return true;
}

bool battleSystem::PostUpdate()
{
	bool ret = true;
	player1AR = currentAttack1->GetCurrentFrame();
	player2AR = currentAttack2->GetCurrentFrame();
	player3AR = currentAttack3->GetCurrentFrame();
	player4AR = currentAttack4->GetCurrentFrame();
	player5AR = currentAttack5->GetCurrentFrame();

	player1HR = currentHit1->GetCurrentFrame();
	player2HR = currentHit2->GetCurrentFrame();
	player3HR = currentHit3->GetCurrentFrame();
	player4HR = currentHit4->GetCurrentFrame();
	player5HR = currentHit5->GetCurrentFrame();

	player3DR = currentDeath3->GetCurrentFrame();

	if (battleTransition && app->player->P1.IsAlive && transitionRep == 1)
	{
		if (curtainCont <= (app->win->GetWidth() / 2) && !curtainBounce)
		{
			Curtain1 = { -app->render->camera.x - app->win->GetWidth()/2 + curtainCont, -app->render->camera.y, app->win->GetWidth() / 2, app->win->GetHeight() };
			Curtain2 = { -app->render->camera.x + app->win->GetWidth() - curtainCont, -app->render->camera.y, app->win->GetWidth() / 2, app->win->GetHeight() };

			app->render->DrawRectangle(Curtain1, 10, 10, 10);
			app->render->DrawRectangle(Curtain2, 10, 10, 10);
			curtainCont += 20;			
		}
		else if (curtainBounce)
		{			
			Curtain1 = { -app->render->camera.x - curtainCont, -app->render->camera.y, app->win->GetWidth() / 2, app->win->GetHeight() };
			Curtain2 = { -app->render->camera.x + app->win->GetWidth() / 2 + curtainCont, -app->render->camera.y, app->win->GetWidth() / 2, app->win->GetHeight() };

			app->render->DrawRectangle(Curtain1, 10, 10, 10);
			app->render->DrawRectangle(Curtain2, 10, 10, 10);
			curtainCont+=20;
		}
		
		if (Curtain1.x >= (-app->render->camera.x) && !curtainBounce)
		{
			curtainBounce = true;
			curtainCont = 0;
			battle = true;
		}
		else if (Curtain1.x <= (-app->render->camera.x - app->win->GetWidth()/2) && curtainBounce)
		{
			curtainBounce = false;
			curtainCont = 0;
			transitionEnd = true;
		}

		if (transitionEnd)
		{
			transitionEnd = false;
			battleTransition = false;
			curtainCont = 0;
			transitionRep = 0;
		}
	}

	if (battleEnd && app->player->P1.IsAlive && transitionRep == 1)
	{
		if (curtainCont <= (app->win->GetWidth() / 2) && !curtainBounce)
		{
			Curtain1 = { -app->render->camera.x - app->win->GetWidth() / 2 + curtainCont, -app->render->camera.y, app->win->GetWidth() / 2, app->win->GetHeight() };
			Curtain2 = { -app->render->camera.x + app->win->GetWidth() - curtainCont, -app->render->camera.y, app->win->GetWidth() / 2, app->win->GetHeight() };

			app->render->DrawRectangle(Curtain1, 10, 10, 10);
			app->render->DrawRectangle(Curtain2, 10, 10, 10);
			curtainCont += 20;
		}
		else if (curtainBounce)
		{
			Curtain1 = { -app->render->camera.x - curtainCont, -app->render->camera.y, app->win->GetWidth() / 2, app->win->GetHeight() };
			Curtain2 = { -app->render->camera.x + app->win->GetWidth() / 2 + curtainCont, -app->render->camera.y, app->win->GetWidth() / 2, app->win->GetHeight() };

			app->render->DrawRectangle(Curtain1, 10, 10, 10);
			app->render->DrawRectangle(Curtain2, 10, 10, 10);
			curtainCont += 20;
		}

		if (Curtain1.x >= (-app->render->camera.x) && !curtainBounce)
		{
			curtainBounce = true;
			curtainCont = 0;
			battle = false;
		}
		else if (Curtain1.x <= (-app->render->camera.x - app->win->GetWidth() / 2) && curtainBounce)
		{
			curtainBounce = false;
			curtainCont = 0;
			transitionEnd = true;
		}

		if (transitionEnd)
		{
			transitionEnd = false;
			battleEnd = false;
			curtainCont = 0;
			transitionRep = 0;
		}
	}

	/*if (battle == true && app->player->P1.IsAlive == true) {
		Player1 = currentAnimation->GetCurrentFrame();
		app->render->DrawTexture(AttackTexture, app->player->P1.position.x - 420 + 120, app->player->P1.position.y - 250, &Player1);
		currentAnimation->Update();
	}
	if (battle == true && app->player->P1.IsAlive == true) {
		Player2 = currentAnimation2->GetCurrentFrame();
		app->render->DrawTexture(AttackTextureP2, app->player->P1.position.x - 420, app->player->P1.position.y - 220 + 130, &Player2);
		currentAnimation->Update();
	}
	
	if (battle == true && app->player->P1.IsAlive == true) {
		Player3 = currentAnimation3->GetCurrentFrame();
		app->render->DrawTexture(AttackTextureP3, app->player->P1.position.x - 420 + 120, app->player->P1.position.y - 220 + 260, &Player3);
		currentAnimation->Update();
	}
	
	if (battle == true && app->player->P1.IsAlive == true) {
		Player4 = currentAnimation4->GetCurrentFrame();
		app->render->DrawTexture(AttackTextureP4, app->player->P1.position.x - 420, app->player->P1.position.y - 220 + 390, &Player4);
		currentAnimation->Update();
	}*/
	return ret;
}

bool battleSystem::CleanUp()
{
	LOG("Freeing scene");

	return false;
}

void battleSystem::AttackAnimations() {
	if (puta1 == true && AttackPlayer == 1 && battle == true) {//British
		currentAttack1 = &AttackAnim1;
		app->render->DrawTexture(player1A, app->player->P1.position.x - 420 + 100, app->player->P1.position.y - 320, &player1AR);
		currentAttack1->Update();
		if (AttackAnim1.currentFrame >= 4.0) {
			AttackAnim1.currentFrame = 0.0;
			puta1 = false;
			PlayerTurn = false;
			app->BTSystem->AttackPlayer = 0;
		}
	}
	else if (battle == true && playerTarget != 1) {
		puta1 = false;
		currentAttack1 = &idleAttack1;
		app->render->DrawTexture(player1A, app->player->P1.position.x - 420 + 100, app->player->P1.position.y - 320, &player1AR);
	}

	if (puta2 == true && AttackPlayer == 2 && battle == true) {//British
		currentAttack2 = &AttackAnim2;
		app->render->DrawTexture(player2A, app->player->P1.position.x - 450, app->player->P1.position.y - 320 + 130, &player2AR);
		currentAttack2->Update();
		if (AttackAnim2.currentFrame >= 4.0) {
			AttackAnim2.currentFrame = 0.0;
			PlayerTurn = false;
			puta2 = false;
			app->BTSystem->AttackPlayer = 0;
		}
	}
	else if (battle == true && app->player->P2.IsAlive == true && playerTarget != 2) {
		puta2 = false;
		currentAttack2 = &idleAttack2;
		app->render->DrawTexture(player2A, app->player->P1.position.x - 450, app->player->P1.position.y - 320 + 130, &player2AR);
	}
	if (puta3 == true && AttackPlayer == 3 && battle == true) {//British
		currentAttack3 = &AttackAnim3;
		app->render->DrawTexture(player3A, app->player->P1.position.x - 450 + 120, app->player->P1.position.y - 320 + 260, &player3AR);
		currentAttack3->Update();
		if (AttackAnim3.currentFrame >= 5.0) {
			AttackAnim3.currentFrame = 0.0;
			PlayerTurn = false;
			puta3 = false;
			app->BTSystem->AttackPlayer = 0;
		}
	}
	else if (battle == true && app->player->P3.IsAlive == true && playerTarget != 3) {
		puta3 = false;
		currentAttack3 = &idleAttack3;
		app->render->DrawTexture(player3A, app->player->P1.position.x - 450 + 120, app->player->P1.position.y - 320 + 260, &player3AR);
	}
	if (puta4 == true && AttackPlayer == 4 && battle1 == true && hit == false) {//Italian
		currentAttack4 = &AttackAnim4;
		app->render->DrawTexture(player4A, app->player->P1.position.x - 450, app->player->P1.position.y - 320 + 390, &player4AR);
		currentAttack4->Update();
		if (AttackAnim4.currentFrame >= 4.0) {
			PlayerTurn = false;
			AttackAnim4.currentFrame = 0;
			puta4 = false;
			app->BTSystem->AttackPlayer = 0;
		}
	}
	else if (battle == true && app->player->P4.IsAlive == true && battle1 == true && playerTarget != 4) {
		puta4 = false;
		currentAttack4 = &idleAttack4;
		app->render->DrawTexture(player4A, app->player->P1.position.x - 450, app->player->P1.position.y - 320 + 390, &player4AR);
	}
	if (puta4 == true && AttackPlayer == 4 && battle1 == false && hit == false) {//Italian
		currentAttack5 = &AttackAnim5;
		app->render->DrawTexture(player5A, app->player->P1.position.x - 450, app->player->P1.position.y - 320 + 390, &player5AR);
		currentAttack5->Update();
		if (AttackAnim5.currentFrame >= 4.0) {
			PlayerTurn = false;
			AttackAnim5.currentFrame = 0;
			puta4 = false;
			app->BTSystem->AttackPlayer = 0;
		}
	}
	else if (battle == true && app->player->P4.IsAlive == true && battle1 == false && playerTarget != 4) {
		puta4 = false;
		currentAttack5 = &idleAttack5;
		app->render->DrawTexture(player5A, app->player->P1.position.x - 450, app->player->P1.position.y - 320 + 390, &player5AR);
	}
}

void battleSystem::HitPlayersAnimations() {
	if (hit == false && playerTarget == 1 && battle == true && app->player->P1.IsAlive == true) {//British
		currentHit1 = &HitAnim1;
		app->render->DrawTexture(player1H, app->player->P1.position.x - 420 + 100, app->player->P1.position.y - 320, &player1HR);
		currentHit1->Update();
		if (HitAnim1.currentFrame >= 3.0) {
			HitAnim1.currentFrame = 0.0;
			playerTarget = 0;
			hit = false;
		}
	}

	if (hit == false && playerTarget == 2 && battle == true && app->player->P2.IsAlive == true) {//British
		currentHit2 = &HitAnim2;
		app->render->DrawTexture(player2H, app->player->P1.position.x - 450, app->player->P1.position.y - 320 + 130, &player2HR);
		currentHit2->Update();
		if (HitAnim2.currentFrame >= 3.0) {
			HitAnim2.currentFrame = 0.0;
			playerTarget = 0;
			hit = false;
		}
	}

	if (hit == false && playerTarget == 3 && battle == true && app->player->P3.IsAlive == true) {//British
		currentHit3 = &HitAnim3;
		app->render->DrawTexture(player3H, app->player->P1.position.x - 450 + 120, app->player->P1.position.y - 320 + 260, &player3HR);
		currentHit3->Update();
		if (HitAnim3.currentFrame >= 3.0) {
			HitAnim3.currentFrame = 0.0;
			playerTarget = 0;
			hit = false;
		}
	}

	if (hit == false && playerTarget == 4 && battle == true && app->player->P4.IsAlive == true && battle1 == true) {//British
		currentHit4 = &HitAnim4;
		app->render->DrawTexture(player4H, app->player->P1.position.x - 450, app->player->P1.position.y - 320 + 390, &player4HR);
		currentHit4->Update();
		if (HitAnim4.currentFrame >= 3.0) {
			HitAnim4.currentFrame = 0.0;
			playerTarget = 0;
			hit = false;
		}
	}

	if (hit == false && playerTarget == 4 && battle == true && app->player->P4.IsAlive == true && battle1 == false) {//British
		currentHit5 = &HitAnim5;
		app->render->DrawTexture(player5H, app->player->P1.position.x - 450, app->player->P1.position.y - 320 + 390, &player5HR);
		currentHit5->Update();
		if (HitAnim5.currentFrame >= 3.0) {
			HitAnim5.currentFrame = 0.0;
			playerTarget = 0;
			hit = false;
		}
	}
}

void battleSystem::DeathPlayersAnimations() {
	if (russianDead == true) {
		currentDeath3 = &DeathAnim3;
		app->render->DrawTexture(player3D, app->player->P1.position.x - 450 + 120, app->player->P1.position.y - 320 + 260, &player3DR);
		currentDeath3->Update();
	}

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

	if (AttackPlayer == 1) {
		puta1 = true;
		playerTarget = 0;
	}
	if (AttackPlayer == 2) {
		playerTarget = 0;
		puta2 = true;
	}
	if (AttackPlayer == 3) {
		playerTarget = 0;
		puta3 = true;
	}
	if (AttackPlayer == 4) {
		playerTarget = 0;
		puta4 = true;
	}
	
}
void battleSystem::AttackPhaseDisabled2() {
	Attack1->state = GuiControlState::DISABLED;
	Attack2->state = GuiControlState::DISABLED;
	VampireTarget = 0;
	ZombieTarget = 0;
	SkeletonTarget = 0;
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

	Item1->state = GuiControlState::NORMAL;
	Item2->state = GuiControlState::NORMAL;
	Item3->state = GuiControlState::NORMAL;
	Item4->state = GuiControlState::NORMAL;

	if (choosingPlayer)
	{
		SDL_Rect* bagSection = new SDL_Rect();
		bagSection->x = 13;
		bagSection->y = 26;
		bagSection->w = 612;
		bagSection->h = 479;

		app->render->DrawTexture(app->characterMenu->inventoryTex, -app->render->camera.x + (app->win->GetWidth() / 2 - 180), -app->render->camera.y + (app->win->GetHeight() / 2 - 230), bagSection);

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
	StatsMenu->state = GuiControlState::DISABLED;
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
		//randomAttack = (rand() % 1) + 3;
		randomAttack = rand() % 4 + 1;
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
	if (InventoryEnable == false) {
		if (app->player->P1.IsAlive == true && app->BTSystem->InventoryEnable == false) {
			app->render->DrawTexture(app->player->player1Hp, app->player->P1.position.x - 190, app->player->P1.position.y - 225);
			SDL_Rect bar1 = { app->player->P1.position.x - 180, app->player->P1.position.y - 220, (200 * app->player->P1.hp) / 100,15 };
			app->render->DrawRectangle(bar1, 255, 0, 0);
			SDL_Rect bar1_ = { app->player->P1.position.x - 180, app->player->P1.position.y - 190, (200 * app->player->P1.mana) / 100,15 };
			app->render->DrawRectangle(bar1_, 0, 0, 255);
		}
		if (app->player->P2.IsAlive == true && app->BTSystem->InventoryEnable == false) {
			app->render->DrawTexture(app->player->player2Hp, app->player->P1.position.x - 310, app->player->P1.position.y - 225 + 130);
			SDL_Rect bar2 = { app->player->P1.position.x - 300, app->player->P1.position.y - 220 + 130, (200 * app->player->P2.hp) / 100,15 };
			app->render->DrawRectangle(bar2, 255, 0, 0);
			SDL_Rect bar2_ = { app->player->P1.position.x - 300, app->player->P1.position.y - 190 + 130, (200 * app->player->P2.mana) / 100,15 };
			app->render->DrawRectangle(bar2_, 0, 0, 255);
		}
		if (app->player->P3.IsAlive == true && app->BTSystem->InventoryEnable == false) {
			app->render->DrawTexture(app->player->player3Hp, app->player->P1.position.x - 190, app->player->P1.position.y - 225 + 260);
			SDL_Rect bar3 = { app->player->P1.position.x - 180, app->player->P1.position.y - 220 + 260, (200 * app->player->P3.hp) / 100,15 };
			app->render->DrawRectangle(bar3, 255, 0, 0);
			SDL_Rect bar3_ = { app->player->P1.position.x - 180, app->player->P1.position.y - 190 + 260, (200 * app->player->P3.mana) / 100,15 };
			app->render->DrawRectangle(bar3_, 0, 0, 255);
		}
		if (app->player->P4.IsAlive == true && app->BTSystem->InventoryEnable == false) {
			app->render->DrawTexture(app->player->player4Hp, app->player->P1.position.x - 310, app->player->P1.position.y - 225 + 390);
			SDL_Rect bar4 = { app->player->P1.position.x - 300, app->player->P1.position.y - 220 + 390, (200 * app->player->P4.hp) / 100,15 };
			app->render->DrawRectangle(bar4, 255, 0, 0);
			SDL_Rect bar4_ = { app->player->P1.position.x - 300, app->player->P1.position.y - 190 + 390, (200 * app->player->P4.mana) / 100,15 };
			app->render->DrawRectangle(bar4_, 0, 0, 255);
		}
	}
	
}

bool battleSystem::OnGuiMouseClickEvent(GuiControl* control)
{
	
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{

		//Checks the GUI element ID
		if (control->id == 31 && AttackPhaseActive == true && AttackPhaseEnable == true && VampireTarget != 0 && ZombieTarget != 0 && SkeletonTarget != 0 && InventoryEnable == false) { //Aixo???
			AttackPhaseDisabled2();

		}
		if (control->id == 31 && AttackPhaseActive == false && AttackPhaseEnable == false && AttackPlayer != 0 && (VampireTarget != 0 || ZombieTarget != 0 || SkeletonTarget != 0) && InventoryEnable == false)
		{
			AttackPhase();
			AttackPhaseEnable = true;
			//Atack_1.Reset();

		}
		if (AttackPhaseActive == false && AttackPhaseEnable == true) {
			AttackPhaseEnable = false;
		}
		//atack 2
		if (control->id == 32 && (VampireTarget != 0 || ZombieTarget != 0 || SkeletonTarget != 0))
		{
			AttackType = 1;
			AttackPhaseDisabled();
			AttackPhaseEnable = false;
			//currentAnimation = &Atack_1;

		}
		//atack 2
		if (control->id == 33 && (VampireTarget != 0 || ZombieTarget != 0 || SkeletonTarget != 0))
		{
			AttackType = 2;
			AttackPhaseDisabled();
			AttackPhaseEnable = false;
			//currentAnimation = &Atack_1;
		}
		if (control->id == 34 && AttackPlayer == 1 && (VampireTarget != 0 || ZombieTarget != 0 || SkeletonTarget != 0) && SpecialAttackEnable == false && app->player->P1.mana >= 60)
		{
			app->player->P1.mana -= 60;
			SpecialAttackEnable = true;

		}
		if (control->id == 34 && AttackPlayer == 2 && (VampireTarget != 0 || ZombieTarget != 0 || SkeletonTarget != 0) && SpecialAttackEnable == false && app->player->P2.mana >= 80)
		{
			app->player->P2.mana -= 80;
			SpecialAttackEnable = true;
		}
		if (control->id == 34 && AttackPlayer == 3 && SpecialAttackEnable == false && app->player->P3.mana >= 25)
		{
			app->player->P3.mana -= 25;
			SpecialAttackEnable = true;
		}
		if (control->id == 34 && AttackPlayer == 4 && (VampireTarget != 0 || ZombieTarget != 0 || SkeletonTarget != 0) && SpecialAttackEnable == false && app->player->P3.mana >= 40 && app->player->P4.revolverActive == true)
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
			battleEnd = true;
			app->BTSystem->transitionRep = 1;
			Delay = false;
			Zombiebattle = false;
			Vampirebattle = false;
			Skeletonbattle = false;
			timer1 = SDL_GetTicks() / 1000;
			timer1_ = timer1;
			app->player->P1.damage = 0;
			app->player->P2.damage = 0;
			app->player->P3.damage = 0;
			app->player->P4.damage = 0;
		}
		if (control->id == 37) {
			AttackPhaseEnable = false;
			AttackPhaseActive = false;
			InventoryEnable = false;
			app->characterMenu->Character1->state = GuiControlState::DISABLED;
			app->characterMenu->Character2->state = GuiControlState::DISABLED;
			app->characterMenu->Character3->state = GuiControlState::DISABLED;
			app->characterMenu->Character4->state = GuiControlState::DISABLED;

			Item1->state = GuiControlState::DISABLED;
			Item2->state = GuiControlState::DISABLED;
			Item3->state = GuiControlState::DISABLED;
			app->BTSystem->CloseInventory->state = GuiControlState::DISABLED;

			app->characterMenu->exitInventory = true;
			app->characterMenu->inventory = false;
			CloseInventory->state = GuiControlState::DISABLED;
		}
		if (control->id == 38) {
			QTE2->state = GuiControlState::DISABLED;
			AttackAux += 16;
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
		if (control->id == 40 && ChoosePlayerPhase == true && SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {//GodMode
			AttackPlayer = 2;
			SpecialAttackEnable = false;
			app->player->P2.IsAlive = false;
			app->player->P2.hp = 0;

		}
		if (control->id == 41 && ChoosePlayerPhase == true && SpecialAttackEnable == false && waitPlayer[2] == 0) {
			SpecialAttackEnable = false;
			AttackPlayer = 3;
		}
		if (control->id == 41 && ChoosePlayerPhase == true && SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {//GodMode
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
		if (control->id == 65)
		{
			StatsEnable = true;
			app->statsMenu->Enable();
			MiniPlayerButton1->state = GuiControlState::DISABLED;
			MiniPlayerButton2->state = GuiControlState::DISABLED;
			MiniPlayerButton3->state = GuiControlState::DISABLED;
			MiniPlayerButton4->state = GuiControlState::DISABLED;
			Attack->state = GuiControlState::DISABLED;
			Attack1->state = GuiControlState::DISABLED;
			Attack2->state = GuiControlState::DISABLED;
			SpecialAttack->state = GuiControlState::DISABLED;
			Inventory->state = GuiControlState::DISABLED;
			StatsMenu->state = GuiControlState::DISABLED;
			Run->state = GuiControlState::DISABLED;
		}
		if (control->id == 66)
		{
			StatsEnable = false;
			app->statsMenu->Disable();
			MiniPlayerButton1->state = GuiControlState::NORMAL;
			MiniPlayerButton2->state = GuiControlState::NORMAL;
			MiniPlayerButton3->state = GuiControlState::NORMAL;
			MiniPlayerButton4->state = GuiControlState::NORMAL;
			Attack->state = GuiControlState::NORMAL;
			Attack1->state = GuiControlState::NORMAL;
			Attack2->state = GuiControlState::NORMAL;
			SpecialAttack->state = GuiControlState::NORMAL;
			Inventory->state = GuiControlState::NORMAL;
			StatsMenu->state = GuiControlState::NORMAL;
			Run->state = GuiControlState::NORMAL;
			CloseStatsMenu->state = GuiControlState::DISABLED;
		}
	
	}
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
			russianDead = true;
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
	if (app->player->P1.hp > p1MaxHP) {
		app->player->P1.hp = p1MaxHP;
	}
	if (app->player->P2.hp > p2MaxHP) {
		app->player->P2.hp = p2MaxHP;
	}
	if (app->player->P3.hp > p3MaxHP) {
		app->player->P3.hp = p3MaxHP;
	}
	if (app->player->P4.hp > p4MaxHP) {
		app->player->P4.hp = p4MaxHP;
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
