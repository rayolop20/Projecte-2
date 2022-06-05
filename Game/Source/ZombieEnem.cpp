#include "Entity.h"
#include "App.h"
#include "Textures.h"
#include "ZombieEnem.h"
#include "EntityManager.h"
#include "GuiManager.h"
#include "Scene.h"
#include "Collisions.h"
#include "Player.h"
#include "PathFinding.h"
#include "Map.h"
#include "Window.h"
#include "Menu.h"
#include "Particles.h"

#include "Log.h"
#include "DynArray.h"
#include "BattleSystem.h"
#include <time.h>

ZombieEnem::ZombieEnem() :Entity(EntityType::ZOMBIE)
{
	name.Create("VampirEnem");

	ZidleAttack1.PushBack({0, 0, 160, 192});
	ZidleAttack1.PushBack({160, 0, 160, 192});
	ZidleAttack1.PushBack({320, 0, 160, 192});
	ZidleAttack1.PushBack({480, 0, 160, 192});
	ZidleAttack1.PushBack({640, 0, 160, 192});
	ZidleAttack1.PushBack({800, 0, 160, 192});
	ZidleAttack1.loop = true;
	ZidleAttack1.speed = 0.01f;
	
	ZidleHit1.PushBack({0, 211, 160, 192});
	ZidleHit1.PushBack({160, 211, 160, 192});
	ZidleHit1.PushBack({320, 211, 160, 192});
	ZidleHit1.PushBack({320, 211, 160, 192});
	ZidleHit1.loop = false;
	ZidleHit1.speed = 0.01f;
	
	ZidleDead1.PushBack({0, 404, 160, 192});
	ZidleDead1.PushBack({160, 404, 160, 192});
	ZidleDead1.PushBack({320, 404, 160, 192});
	ZidleDead1.PushBack({320, 404, 160, 192});
	ZidleDead1.loop = false;
	ZidleDead1.speed = 0.01f;

	ZidleA1.PushBack({0, 635, 160, 192});
	ZidleA1.PushBack({160, 635, 160, 192});
	ZidleA1.PushBack({320, 635, 160, 192});
	ZidleA1.PushBack({320, 635, 160, 192});
	ZidleA1.PushBack({480, 635, 160, 192});
	ZidleA1.PushBack({640, 635, 160, 192});
	ZidleA1.PushBack({640, 635, 160, 192});
	ZidleA1.loop = false;
	ZidleA1.speed = 0.01f;
	
	
	//movement
	idleAnim.PushBack({ 45, 18, 36, 102 });
	idleAnim.loop = true;
	idleAnim.speed = 0.001f;

	downAnim.PushBack({ 45, 18, 36, 102 });
	downAnim.PushBack({ 168,18, 41, 104 });
	downAnim.PushBack({ 301,18, 36, 102 });
	downAnim.PushBack({ 429,17, 42, 104 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	leftAnim.PushBack({ 563,18, 31, 103 });
	leftAnim.PushBack({ 674,20, 43, 101 });
	leftAnim.PushBack({ 819,18, 31, 103 });
	leftAnim.PushBack({ 929,19, 42, 101 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	rightAnim.PushBack({ 1058,18, 31, 103 });
	rightAnim.PushBack({ 1191,21, 42, 100 });
	rightAnim.PushBack({ 1314,18, 31, 103 });
	rightAnim.PushBack({ 1450,21, 42, 99 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	upAnim.PushBack({ 1581,18, 36, 102 });
	upAnim.PushBack({ 1704,18, 41, 104 });
	upAnim.PushBack({ 1837,18, 36, 102 });
	upAnim.PushBack({ 1965,17, 42, 104 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	
}

ZombieEnem::~ZombieEnem()
{
	name.Create("Vampire");
}

/*
bool VampirEnem::Awake(pugi::xml_node& config)
{
	LOG("Loading VampirEnem");
	bool ret = true;


	Vpir[WhichVampire].Pos.x = config.child("Position").attribute("PositionX").as_int();
	Vpir[WhichVampire].Pos.y = config.child("Position").attribute("PositionY").as_int();


	return false;
}


bool VampirEnem::LoadState(pugi::xml_node& data)
{
	Vpir[WhichVampire].Pos.x = data.child("Vampire").attribute("x").as_int();
	Vpir[WhichVampire].Pos.y = data.child("Vampire").attribute("y").as_int();
	return false;
}

bool VampirEnem::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node VPyr = data.append_child("Vampire");

	VPyr.append_attribute("x") = Vpir[WhichVampire].Pos.x;
	VPyr.append_attribute("y") = Vpir[WhichVampire].Pos.y;
	return false;
}
*/
bool ZombieEnem::Start()
{

	TextureZombie = app->tex->Load("Assets/Textures/Enem/zombie.png");
	zombieEnem = app->tex->Load("Assets/Textures/Enem/zombie_idle_animation.png");
	selectZombie = app->tex->Load("Assets/Textures/UI/choseplayers.png");


	for (int i = 0; i < NUM_ZOMBIE; i++)
	{
		currentAnimation[i] = &idleAnim;
	}

	Zbie[0] = CreateZombie(960, 2336, TextureZombie);
	Zbie[10] = CreateZombie(960, 1920, TextureZombie);
	Zbie[20] = CreateZombie(928, 608, TextureZombie);

	currentAttack1Z = &ZidleAttack1;
	currentHit1Z = &ZidleHit1;
	currentDead1Z = &ZidleDead1;
	currentA1Z = &ZidleA1;

	return false;
}

bool ZombieEnem::Update(float dt)
{
	static char title[256];
	//sprintf_s(title, 256, "ENEMH1: %.1f ENEMHP2: %.1f ENEMH3: %.1f ENEMHP4: %.1f Playerhp1: %.1f Playerhp2: %.1f Playerhp3: %.1f Playerhp4: %.1f",
//Zbie[1].hp, Zbie[2].hp, Zbie[3].hp, Zbie[4].hp, app->player->P1.hp, app->player->P2.hp, app->player->P3.hp, app->player->P4.hp);

	//app->win->SetTitle(title);
	
	if (app->BTSystem->battle == true && app->player->P1.IsAlive == true && app->BTSystem->Zombiebattle) {
		if (app->BTSystem->SpawnedEnemies == false) {
			SpawnEnemies();
		}
		
		DrawEnemies();
		ChooseEnemy();
		Combat();
		DrawHpBars();
		
		if (app->BTSystem->PlayerTurn == false) {
			
			CheckEnemy();
			EnemyPhase();

		}
	}
	else if (app->BTSystem->battleAux == true) {
		app->BTSystem->battleAux = false;

		Zbie[WhichZombie].Destroyed = true;
	}
	timer3 = SDL_GetTicks() / 10;

	for (int i = 0; i < NUM_ZOMBIE; i++)
	{
		currentAnimation[i]->Update();

		if (Zbie[i].Destroyed == true)
		{
			Zbie[i].dead = true;
			Zbie[i].colliderZ->pendingToDelete = true;

		}
	}
	timer3 = SDL_GetTicks() / 10;

	for (int i = 0; i < NUM_ZOMBIE; i++)
	{
		currentAnimation[i]->Update();

		if (Zbie[i].Destroyed == true)
		{
			Zbie[i].dead = true;
			Zbie[i].colliderS->pendingToDelete = true;
		}
	}
	for (int i = 0; i < 21; i+=10)
	{
		Zbie[i].colliderZ->SetPos(Zbie[i].Pos.x, Zbie[i].Pos.y);
		Zbie[i].colliderS->SetPos(Zbie[i].Pos.x - 168, Zbie[i].Pos.y - 168);
	}

	if (app->BTSystem->battle == false)
	{
		for (int i = 0; i < 5; i++) {
			Zbie[i].onFire = false;
			Zbie[i].poisoned = false;
		}
	}
	return true;
}

bool ZombieEnem::PostUpdate()
{

	LOG("FUNCIONA?");
	bool ret = true;

	zombie1AR = currentAttack1Z->GetCurrentFrame();
	zombieH1AR = currentHit1Z->GetCurrentFrame();
	zombieD1AR = currentDead1Z->GetCurrentFrame();
	zombieA1AR = currentA1Z->GetCurrentFrame();
	app->particle->fireparticv = app->particle->currentFire->GetCurrentFrame();
	app->particle->Venomparticv = app->particle->currentVenom->GetCurrentFrame();

	for (int i = 0; i < NUM_ZOMBIE; i++)
	{
		if (Zbie[i].dead == false && app->menu->config == false && app->BTSystem->battle == false)
		{
			app->render->DrawTexture(Zbie[i].zombieT, Zbie[i].Pos.x, Zbie[i].Pos.y, &(currentAnimation[i]->GetCurrentFrame()));
		}
	}

	return ret;
}

void ZombieEnem::Combat() {
	if (app->BTSystem->Zombiebattle == true) {

		//currentAtackAnimation 
		if (app->BTSystem->alliesDead == 0) {
			if (app->player->P1.IsAlive == false) {
				app->BTSystem->alliesDead++;
			}
			if (app->player->P2.IsAlive == false) {
				app->BTSystem->alliesDead++;
			}
			if (app->player->P3.IsAlive == false) {
				app->BTSystem->alliesDead++;
			}
			if (app->player->P4.IsAlive == false) {
				app->BTSystem->alliesDead++;
			}
			if (app->BTSystem->alliesDead == 4) {
				app->BTSystem->battleEnd = true;
				app->BTSystem->transitionRep = 1;
				app->BTSystem->battleWin = false;
			}
		}
		if (app->BTSystem->AttackType == 1 && app->BTSystem->AttackPlayer == 1 && app->BTSystem->randomAux == true) {
			int randomNumber = 0;
			do {
				Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P1.damage1 + app->player->P1.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P1.speed + app->player->P1.speed1);

			app->player->P1.mana += app->player->P1.mana1;
			app->BTSystem->ZombieTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[0] += 1;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] >= 5 - app->BTSystem->alliesDead) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
		}
		if (app->BTSystem->AttackType == 2 && app->BTSystem->AttackPlayer == 1 && app->BTSystem->randomAux == true) {
			int randomNumber = 0;
			int randomNumber2 = 0;
			int randomNumber2_ = 0;
			do {
				do {
					randomNumber2 = (rand() % 4 - app->BTSystem->CombatDeaths) + 1;
				} while (randomNumber2 == app->BTSystem->ZombieTarget);
				do {
					randomNumber2_ = (rand() % 4 - app->BTSystem->CombatDeaths) + 1;
				} while (randomNumber2_ == app->BTSystem->ZombieTarget || randomNumber2_ == randomNumber2);

				Zbie[randomNumber2].hp -= app->player->P1.damage2 + app->player->P1.damage;
				Zbie[randomNumber2_].hp -= app->player->P1.damage2 + app->player->P1.damage;
				Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P1.damage2 + app->player->P1.damage;
				Zbie[app->BTSystem->ZombieTarget].Zhit = true;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P1.speed + app->player->P1.speed2);
			app->player->P1.mana += app->player->P1.mana2;
			app->BTSystem->ZombieTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[0] += 1;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] >= 5 - app->BTSystem->alliesDead) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
		}
		if (app->BTSystem->AttackType == 1 && app->BTSystem->AttackPlayer == 2 && app->BTSystem->randomAux == true) {
			int randomNumber = 0;
			do {
				Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P2.damage1 + app->player->P2.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P2.speed + app->player->P2.speed1);
			app->player->P2.mana += app->player->P2.mana1;
			app->BTSystem->ZombieTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[1] += 1;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] >= 5 - app->BTSystem->alliesDead) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
		}
		if (app->BTSystem->AttackType == 2 && app->BTSystem->AttackPlayer == 2 && app->BTSystem->randomAux == true) {
			int randomNumber = 0;
			do {
				Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P2.damage2 + app->player->P2.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P2.speed + app->player->P2.speed2);
			app->player->P2.mana += app->player->P2.mana2;
			app->BTSystem->ZombieTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[1] += 1;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] >= 5 - app->BTSystem->alliesDead) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
		}
		if (app->BTSystem->AttackType == 1 && app->BTSystem->AttackPlayer == 3 && app->BTSystem->randomAux == true) {
			int randomNumber = 0;
			int randomNumber2 = 0;
			int randomNumber2_ = 0;
			do {
				do {
					randomNumber2 = (rand() % 4 - app->BTSystem->CombatDeaths) + 1;
				} while (randomNumber2 == app->BTSystem->ZombieTarget);
				do {
					randomNumber2_ = (rand() % 4 - app->BTSystem->CombatDeaths) + 1;
				} while (randomNumber2_ == app->BTSystem->ZombieTarget || randomNumber2_ == randomNumber2);
				Zbie[randomNumber2].hp -= app->player->P3.damage2 + app->player->P3.damage;
				Zbie[randomNumber2_].hp -= app->player->P3.damage2 + app->player->P3.damage;
				Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P3.damage1 + app->player->P3.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P3.speed + app->player->P3.speed1);
			app->player->P3.mana += app->player->P3.mana1;
			app->BTSystem->ZombieTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[2] += 1;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] >= 5 - app->BTSystem->alliesDead) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
		}
		if (app->BTSystem->AttackType == 2 && app->BTSystem->AttackPlayer == 3 && app->BTSystem->randomAux == true) {
			int randomNumber = 0;
			do {
				Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P3.damage2 + app->player->P3.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P3.speed + app->player->P3.speed2);
			app->player->P3.mana += app->player->P3.mana2;
			app->BTSystem->ZombieTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[2] += 1;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] >= 5 - app->BTSystem->alliesDead) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
		}
		if (app->BTSystem->AttackType == 1 && app->BTSystem->AttackPlayer == 4 && app->BTSystem->randomAux == true) {
			int randomNumber = 0;
			int randomNumber2 = 0;
			do {
				if (app->BTSystem->battle1 == true) {
					do {
						randomNumber2 = (rand() % 4 - app->BTSystem->CombatDeaths) + 1;
					} while (randomNumber2 == app->BTSystem->ZombieTarget);
					Zbie[randomNumber2].hp -= app->player->P4.damage2 + app->player->P4.damage;
				}
			Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P4.damage1 + app->player->P4.damage;
			randomNumber = (rand() % 100) + 1;
			} while (randomNumber <= app->player->P4.speed + app->player->P4.speed1);
			app->player->P4.mana += app->player->P4.mana1;
			app->BTSystem->ZombieTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[3] += 1;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] >= 5 - app->BTSystem->alliesDead) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
		}
		if (app->BTSystem->AttackType == 2 && app->BTSystem->AttackPlayer == 4 && app->BTSystem->randomAux == true) {
			int randomNumber = 0;
			do {
				Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P4.damage2;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P4.speed + app->player->P4.speed2);
			app->player->P4.mana += app->player->P4.mana2;
			app->BTSystem->ZombieTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[3] += 1;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] >= 5 - app->BTSystem->alliesDead) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}

		}
		if (app->BTSystem->AttackPlayer == 1 && app->BTSystem->SpecialAttackEnable == false && app->BTSystem->SpeacialAttackEnd == true) {
			Zbie[app->BTSystem->ZombieTarget].poisoned = true;
			Zbie[app->BTSystem->ZombieTarget].hp -= (20 * app->BTSystem->AttackAux) / 100;
			app->BTSystem->AttackAux = 0;
			app->BTSystem->ZombieTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[0]++;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] >= 5 - app->BTSystem->alliesDead) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
		}
		if (app->BTSystem->AttackPlayer == 2 && app->BTSystem->SpecialAttackEnable == false && app->BTSystem->SpeacialAttackEnd == true) {
			Zbie[WhichZombie].onFire = true;
			Zbie[1].onFire = true;
			Zbie[2].onFire = true;
			Zbie[3].onFire = true;
			Zbie[4].onFire = true;
			Zbie[app->BTSystem->ZombieTarget].hp -= (15 * app->BTSystem->AttackAux) / 100;
			app->BTSystem->AttackAux = 0;
			app->BTSystem->ZombieTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[1]++;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] >= 5 - app->BTSystem->alliesDead) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
		}
		if (app->BTSystem->AttackPlayer == 3 && app->BTSystem->SpecialAttackEnable == false && app->BTSystem->SpeacialAttackEnd == true) {
			app->player->P3.hp += (18 * app->BTSystem->AttackAux) / 100;
			app->BTSystem->AttackAux = 0;
			app->BTSystem->ZombieTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[2]++;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] >= 5 - app->BTSystem->alliesDead) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
		}
		if (app->BTSystem->AttackPlayer == 4 && app->BTSystem->SpecialAttackEnable == false && app->BTSystem->SpeacialAttackEnd == true) {
			Zbie[app->BTSystem->ZombieTarget].hp -= (75 * app->BTSystem->AttackAux) / 100;
			app->BTSystem->AttackAux = 0;
			app->BTSystem->ZombieTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[3]++;
			app->player->P4.revolverActive = false;
			for (int i = 0; i <= 4; i++) {
				if (app->BTSystem->waitPlayer[i] != 0) {
					app->BTSystem->waitPlayer[i] += 1;
				}
				if (app->BTSystem->waitPlayer[i] >= 5 - app->BTSystem->alliesDead) {
					app->BTSystem->waitPlayer[i] = 0;
				}
			}
		}
		app->BTSystem->SpeacialAttackEnd = false;
		app->BTSystem->alliesDead = 0;
	}
}

void ZombieEnem::SpawnEnemies() {
	if (app->BTSystem->Zombiebattle == true) {
		srand(time(NULL));
		for (int i = 1; i < Zbie[WhichZombie].numEnemies + 1; i++) {
			Zbie[i].dead = false;
			randomEnemyhp = (rand() % 10) + 1;
			randomEnemySpeed = (rand() % 6) + 1;
			randomEnemyDamage = (rand() % 6) + 1;
			if (randomstats == true) {
				Zbie[i].hp += randomEnemyhp;
				Zbie[i].speed += randomEnemySpeed;
				Zbie[i].damage += randomEnemyDamage;
			}
		}	}
	randomstats = false;
	app->BTSystem->SpawnedEnemies = true;
}

void ZombieEnem::DrawEnemies() {
	if (app->BTSystem->Zombiebattle == true && app->BTSystem->InventoryEnable == false) {

		for (int i = 1; i < Zbie[WhichZombie].numEnemies + 1; i++) {
			if (Zbie[i].dead == false) {
				if (app->BTSystem->ZombieTarget == i) {
					Choose->x = 4;
					Choose->y = 135;
					Choose->w = 110;
					Choose->h = 110;
					app->render->DrawTexture(selectZombie, app->player->P1.position.x + 395, app->player->P1.position.y - 335 + 120 * i, Choose);
				}
				if (Zbie[i].Zhit == false && Zbie[i].atack == false)
				{
					SDL_Rect Enem1 = { app->player->P1.position.x + 400, app->player->P1.position.y - 330 + 120 * i, 100, 100 };
					currentAnimation[i] = &ZidleAttack1;
					app->render->DrawTexture(zombieEnem, app->player->P1.position.x + 350, app->player->P1.position.y - 330 + 100 * i, &zombie1AR);
					currentAnimation[i]->Update();
				}
				if (Zbie[i].Zhit == true)
				{
					currentAnimation[i] = &ZidleHit1;;
					app->render->DrawTexture(zombieEnem, app->player->P1.position.x + 350, app->player->P1.position.y - 330 + 100 * i, &zombieH1AR);
					currentAnimation[i]->Update();
					if (ZidleHit1.currentFrame >= 3.0) {
						ZidleHit1.currentFrame = 0;
						Zbie[i].Zhit = false;
					}
				}
				if (Zbie[i].atack == true)
				{
					currentAnimation[i] = &ZidleA1;;
					app->render->DrawTexture(zombieEnem, app->player->P1.position.x + 350, app->player->P1.position.y - 330 + 100 * i, &zombieA1AR);
					currentAnimation[i]->Update();
					if (ZidleA1.currentFrame >= 6.0) {
						ZidleA1.currentFrame = 0;
						Zbie[i].atack = false;
					}
				}
				
				if (Zbie[i].onFire == true && app->menu->config == false && app->BTSystem->battle == true)
				{
					app->particle->currentAnimationF[i] = &app->particle->fire_particles;
					app->render->DrawTexture(app->particle->firepart, app->player->P1.position.x + 395, app->player->P1.position.y - 320 + 100 * i, &app->particle->fireparticv);
					app->particle->currentAnimationF[i]->Update();
				}
				
				if (Zbie[i].poisoned == true && app->menu->config == false && app->BTSystem->battle == true)
				{
					app->particle->currentAnimationV[i] = &app->particle->Venom_particles;
					app->render->DrawTexture(app->particle->Venompart, app->player->P1.position.x + 350, app->player->P1.position.y - 330 + 100 * i, &app->particle->Venomparticv);
					app->particle->currentAnimationV[i]->Update();
				}
			
			}
			if (Zbie[i].dead == true)
			{
				currentAnimation[i] = &ZidleDead1;;
				app->render->DrawTexture(zombieEnem, app->player->P1.position.x + 350, app->player->P1.position.y - 330 + 100 * i, &zombieD1AR);
				currentAnimation[i]->Update();
			}
		}
		
		app->guiManager->Draw();
	}
}

void ZombieEnem::ChooseEnemy() {
	if (app->BTSystem->Zombiebattle == true) {
	int x, y;
	Uint32 buttons;
	SDL_PumpEvents();  // make sure we have the latest mouse state.

	buttons = SDL_GetMouseState(&x, &y);

	for (int i = 1; i < Zbie[WhichZombie].numEnemies + 1; i++) {
		/*if (Vpir[i].dead == false && x >= 772 && x <= 772 + 50 && y >= 18 + 60*i && y <= 18 + 60 * i + 50 && app->input->GetMouseButtonDown(1) == KEY_DOWN && app->BTSystem->AttackPlayer != 0 && app->BTSystem->PlayerTurn == true) {
			app->BTSystem->ZombieTarget = i;
			//SDL_Rect Enem1 = { app->player->P1.position.x + 400, app->player->P1.position.y - 330 + 120 * i, 100, 100 };

		}*/
		if (Zbie[i].dead == false && x > 1005 && x < 1110 && y > -5 + 120 * i && y < 115 + 120 * i + 100 && app->input->GetMouseButtonDown(1) == KEY_DOWN && app->BTSystem->AttackPlayer != 0 && app->BTSystem->PlayerTurn == true && app->BTSystem->SpecialAttackEnable == false) {
			app->BTSystem->ZombieTarget = i;
			//SDL_Rect Enem1 = { app->player->P1.position.x + 500, app->player->P1.position.y - 330 + 120 * i, 100, 100 };
		}
	}
	for (int i = 1; i < Zbie[WhichZombie].numEnemies + 1; i++) {//
		if (Zbie[i].dead == false && x > 1005 && x < 1110 && y > -5 + 120 * i && y < 115 + 120 * i + 100 && app->input->GetMouseButtonDown(1) == KEY_DOWN && app->BTSystem->PlayerTurn == true && app->BTSystem->SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && app->player->godMode == true) {
			//app->BTSystem->ZombieTarget = i;
			Zbie[i].hp = 0;
		}

	}
	}
}

void ZombieEnem::EnemyPhase() {
	if (app->BTSystem->Zombiebattle == true) {

		if (app->BTSystem->alliesDead == 0) {
			if (app->player->P1.IsAlive == false) {
				app->BTSystem->alliesDead++;
			}
			if (app->player->P2.IsAlive == false) {
				app->BTSystem->alliesDead++;
			}
			if (app->player->P3.IsAlive == false) {
				app->BTSystem->alliesDead++;
			}
			if (app->player->P4.IsAlive == false) {
				app->BTSystem->alliesDead++;
			}
			if (app->BTSystem->alliesDead == 4) {
				app->BTSystem->battleEnd = true;
				app->BTSystem->transitionRep = 1;
				app->BTSystem->battleWin = false;

			}
		}
		for (int i = 1; i < Zbie[WhichZombie].numEnemies + 1; i++) {
			if (Zbie[i].dead == false && app->BTSystem->PlayerTurn == false) {
				do {
					srand(time(NULL));
					app->BTSystem->playerTarget_ = (rand() % (4)) + 1;
					if (app->BTSystem->playerTarget_ == 1 && app->player->P1.IsAlive == true) {
						app->BTSystem->playerTarget = 0;
						app->BTSystem->playerTarget_ = 1;
						break;
					}
					else {
						app->BTSystem->playerTarget = app->BTSystem->playerTarget_;
					}
					if (app->BTSystem->playerTarget_ == 2 && app->player->P2.IsAlive == true) {
						app->BTSystem->playerTarget_ = 2;
						app->BTSystem->playerTarget = 0;
						break;
					}
					else {
						app->BTSystem->playerTarget = app->BTSystem->playerTarget_;
					}
					if (app->BTSystem->playerTarget_ == 3 && app->player->P3.IsAlive == true) {
						app->BTSystem->playerTarget_ = 3;
						app->BTSystem->playerTarget = 0;
						break;
					}
					else {
						app->BTSystem->playerTarget = app->BTSystem->playerTarget_;
					}
					if (app->BTSystem->playerTarget_ == 4 && app->player->P4.IsAlive == true) {
						app->BTSystem->playerTarget_ = 4;
						app->BTSystem->playerTarget = 0;
						break;
					}
					else {
						app->BTSystem->playerTarget = app->BTSystem->playerTarget_;
					}

				} while (app->BTSystem->playerTarget == 0 && app->BTSystem->playerTarget_ != 0);

				app->BTSystem->playerTarget = app->BTSystem->playerTarget_;

				if (app->BTSystem->battle1 == true && app->player->P4.IsAlive == true) {
					app->BTSystem->playerTarget = 4;
				}
				if (app->BTSystem->playerTarget == 1 && app->player->P1.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						if (app->player->godMode == false) {
							app->player->P1.hp -= Zbie[app->BTSystem->playerTarget].damage;
							Zbie[i].atack = true;
						}
					} while (randomNumber <= Zbie[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;
				}
				if (app->BTSystem->playerTarget == 2 && app->player->P2.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						if (app->player->godMode == false) {
							app->player->P2.hp -= Zbie[app->BTSystem->playerTarget].damage;
							Zbie[i].atack = true;
						}
					} while (randomNumber <= Zbie[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;

				}
				if (app->BTSystem->playerTarget == 3 && app->player->P3.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						if (app->player->godMode == false) {
							app->player->P3.hp -= Zbie[app->BTSystem->playerTarget].damage;
							Zbie[i].atack = true;
						}
					} while (randomNumber <= Zbie[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;

				}
				if (app->BTSystem->playerTarget == 4 && app->player->P4.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						if (app->player->godMode == false) {
							app->player->P4.hp -= Zbie[app->BTSystem->playerTarget].damage;
							Zbie[i].atack = true;
						}
					} while (randomNumber <= Zbie[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;

				}

			}
		}
		app->BTSystem->SpecialAttackEnable = false;
		app->BTSystem->alliesDead = 0;
	}

}

void ZombieEnem::CheckEnemy() {
	if (app->BTSystem->Zombiebattle == true) {
		for (int i = 0; i < 5; i++) {
			if (Zbie[i].poisoned == true && app->BTSystem->SpecialAttackEnable == false) {
				Zbie[i].hp -= 2;
				app->BTSystem->poisonCount[i]++;
				app->BTSystem->SpecialAttackEnable = true;
			}
			if (app->BTSystem->poisonCount[i] >= 10) {
				app->BTSystem->poisonCount[i] = 0;
				Zbie[i].poisoned = false;
			}
			if (Zbie[i].onFire == true && app->BTSystem->SpecialAttackEnable == false) {
				Zbie[i].hp -= 10;
			}
			if (app->BTSystem->onFireCount != 0 && Zbie[WhichZombie].onFire == true) {
				app->BTSystem->onFireCount++;
			}
			if (app->BTSystem->onFireCount >= 3) {
				app->BTSystem->onFireCount = 0;
				Zbie[WhichZombie].onFire = false;
				Zbie[1].onFire = false;
				Zbie[2].onFire = false;
				Zbie[3].onFire = false;
				Zbie[4].onFire = false;
			}
		}
		for (int i = 1; i < Zbie[WhichZombie].numEnemies + 1; i++) {
			if (Zbie[i].hp <= 0) {
				Zbie[i].dead = true;
				app->BTSystem->CombatDeaths += 1;
			}
			if (app->BTSystem->CombatDeaths == Zbie[WhichZombie].numEnemies) {

				app->BTSystem->battleEnd = true;
				app->BTSystem->transitionRep = 1;
				app->BTSystem->Zombiebattle = false;
				app->BTSystem->battleWin = false;
				app->BTSystem->battle1 = false;
				app->player->P4.revolverActive = true;
				Zbie[WhichZombie].Destroyed = true;
				randomstats = true;
				app->player->P1.damage = 0;
				app->player->P2.damage = 0;
				app->player->P3.damage = 0;
				app->player->P4.damage = 0;
				for (int i = 0; i < Zbie[WhichZombie].numEnemies + 1; i++) {
					Zbie[i].hp = Zbie[i].basehp;
					Zbie[i].speed = Zbie[i].basespeed;
					Zbie[i].damage = Zbie[i].basedamage;
				}
				
			}
		}
		app->BTSystem->CombatDeaths = 0;
	}
}

void ZombieEnem::DrawHpBars() {
	if (app->BTSystem->InventoryEnable == false) {

		if (Zbie[1].dead == false && app->BTSystem->InventoryEnable == false) {
			SDL_Rect bar1 = { app->player->P1.position.x + 380, app->player->P1.position.y - 200, -(200 * Zbie[1].hp) / 100,15 };
			app->render->DrawRectangle(bar1, 255, 0, 0);
		}
		if (Zbie[2].dead == false && app->BTSystem->InventoryEnable == false && Zbie[WhichZombie].numEnemies > 1) {
			SDL_Rect bar2 = { app->player->P1.position.x + 380, app->player->P1.position.y - 200 + 120, -(200 * Zbie[2].hp) / 100,15 };
			app->render->DrawRectangle(bar2, 255, 0, 0);
		}
		if (Zbie[3].dead == false && app->BTSystem->InventoryEnable == false && Zbie[WhichZombie].numEnemies > 2) {
			SDL_Rect bar3 = { app->player->P1.position.x + 380, app->player->P1.position.y - 200 + 240, -(200 * Zbie[3].hp) / 100,15 };
			app->render->DrawRectangle(bar3, 255, 0, 0);
		}
		if (Zbie[4].dead == false && app->BTSystem->InventoryEnable == false && Zbie[WhichZombie].numEnemies > 3) {
			SDL_Rect bar4 = { app->player->P1.position.x + 380, app->player->P1.position.y - 200 + 360, -(200 * Zbie[4].hp) / 100,15 };
			app->render->DrawRectangle(bar4, 255, 0, 0);
		}
	}
}

void ZombieEnem::OnCollision(Collider* c1, Collider* c2)
{

	for (uint i = 0; i < NUM_ZOMBIE; ++i)
	{
		if (Zbie[i].colliderZ == c1 && !Zbie[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
				app->BTSystem->Zombiebattle = true;
				//Vpir[WhichVampire].Destroyed = true;
			}
		}
		else if (Zbie[i].colliderS == c1 && !Zbie[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
				switch (i)
				{
				case 0:
					WhichZombie = i;
					Zbie[0].numEnemies = 3;
					break;
				case 10:
					WhichZombie = i;
					Zbie[10].numEnemies = 1;
					break;
				case 20:
					WhichZombie = i;
					Zbie[20].numEnemies = 4;
					break;
				default:
					break;
				}
				if (pathfindingaux == true) {
					pathfindingtimer = timer3;
					pathfindingaux = false;
				}
				path = true;
				ZombieNum = i;
				PathFindVamp(ZombieNum);
			}
		}
	}
}

void ZombieEnem::PathFindVamp(int i)
{
	if (app->player->godMode == false)
	{
		if (path == true && app->BTSystem->battle == false && app->BTSystem->Delay == true && app->scene->paused == false)
		{
			app->pathfinding->CreatePath(app->map->WorldToMap(Zbie[i].Pos.x, Zbie[i].Pos.y), app->map->WorldToMap(app->player->P1.position.x, app->player->P1.position.y));

			const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

			for (uint j = 0; j < path->Count(); ++j)
			{
				iPoint pos = app->map->MapToWorld(path->At(j)->x, path->At(j)->y);
				if (Zbie[i].Pos.x <= pos.x - 32 && timer3 > pathfindingtimer + enemySpeed)
				{
					currentAnimation[i] = &rightAnim;
					pathfindingtimer = timer3;
					Zbie[i].Pos.x += 32;
				}
				if (Zbie[i].Pos.x >= pos.x + 32 && timer3 > pathfindingtimer + enemySpeed)
				{
					currentAnimation[i] = &leftAnim;
					pathfindingtimer = timer3;
					Zbie[i].Pos.x -= 32;
				}
				if (Zbie[i].Pos.y <= pos.y - 32 && timer3 > pathfindingtimer + enemySpeed)
				{
					currentAnimation[i] = &downAnim;
					pathfindingtimer = timer3;
					Zbie[i].Pos.y += 32;
				}
				if (Zbie[i].Pos.y >= pos.y + 32 && timer3 > pathfindingtimer + enemySpeed)
				{
					currentAnimation[i] = &upAnim;
					pathfindingtimer = timer3;
					Zbie[i].Pos.y -= 32;
				}
			}

		}
	}
}
Zombie ZombieEnem::CreateZombie(int x, int y, SDL_Texture* t)
{
	Zombie Zombies;

	Zombies.colliderZ = app->collisions->AddCollider({ x, y, 32, 32 }, Collider::Type::ZOMBIE, (Module*)app->entityManager);
	Zombies.colliderS = app->collisions->AddCollider({ x, y, 400, 400 }, Collider::Type::SENSOR, (Module*)app->entityManager);
	Zombies.zombieT = t;
	Zombies.Pos.x = x;
	Zombies.Pos.y = y;

	return Zombies;
}

