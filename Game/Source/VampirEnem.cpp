#include "Entity.h"
#include "App.h"
#include "Textures.h"
#include "VampirEnem.h"
#include "EntityManager.h"
#include "GuiManager.h"
#include "Scene.h"
#include "Collisions.h"
#include "Player.h"
#include "PathFinding.h"
#include "Map.h"
#include "Window.h"
#include "Log.h"
#include "DynArray.h"
#include "BattleSystem.h"
#include "Menu.h"
#include "Particles.h"
#include "Mouse.h"
#include <time.h>

VampirEnem::VampirEnem():Entity (EntityType::VAMPYR)
{
	name.Create("Vampire");
	idleAnim.PushBack({ 41,18, 45, 102 });
	idleAnim.loop = true;
	idleAnim.speed = 0.1f;

	VidleAttack1.PushBack({ 0, 0, 160, 192 });
	VidleAttack1.PushBack({ 160, 0, 160, 192 });
	VidleAttack1.PushBack({ 320, 0, 160, 192 });
	VidleAttack1.PushBack({ 480, 0, 160, 192 });
	VidleAttack1.PushBack({ 640, 0, 160, 192 });
	VidleAttack1.PushBack({ 800, 0, 160, 192 });
	VidleAttack1.loop = true;
	VidleAttack1.speed = 0.01f;

	VidleHit1.PushBack({ 0, 202, 160, 192 });
	VidleHit1.PushBack({ 160, 202, 160, 192 });
	VidleHit1.PushBack({ 320, 202, 160, 192 });
	VidleHit1.PushBack({ 480, 202, 160, 192 });
	VidleHit1.PushBack({ 480, 202, 160, 192 });
	VidleHit1.loop = false;
	VidleHit1.speed = 0.03f;

	VidleDead1.PushBack({ 0, 418, 160, 192 });
	VidleDead1.PushBack({ 160, 418, 160, 192 });
	VidleDead1.PushBack({ 320, 418, 160, 192 });
	VidleDead1.PushBack({ 480, 418, 160, 192 });
	VidleDead1.PushBack({ 640, 418, 160, 192 });
	VidleDead1.PushBack({ 800, 418, 160, 192 });
	VidleDead1.PushBack({ 960, 418, 160, 192 });
	VidleDead1.PushBack({ 1120, 418, 160, 192 });
	VidleDead1.PushBack({ 1280, 418, 160, 192 });
	VidleDead1.PushBack({ 1440, 418, 160, 192 });
	VidleDead1.loop = false;
	VidleDead1.speed = 0.1f;
	
	VidleA1.PushBack({ 0, 716, 160, 192 });
	VidleA1.PushBack({ 160, 716, 160, 192 });
	VidleA1.PushBack({ 160, 716, 160, 192 });
	VidleA1.PushBack({ 320, 625, 160, 284 });
	VidleA1.PushBack({ 320, 625, 160, 284 });
	VidleA1.PushBack({ 480, 624, 222, 284 });
	VidleA1.PushBack({ 480, 624, 200, 283 });
	VidleA1.PushBack({ 480, 624, 200, 283 });
	VidleA1.loop = false;
	VidleA1.speed = 0.1f;

	downAnim.PushBack({ 41,18, 45, 102 });
	downAnim.PushBack({ 169,18, 45, 104 });
	downAnim.PushBack({ 297,18, 45, 102 });
	downAnim.PushBack({ 425,18, 65, 104 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	leftAnim.PushBack({ 563,19, 31, 102 });
	leftAnim.PushBack({ 691,19, 31, 102 });
	leftAnim.PushBack({ 819,19, 31, 102 });
	leftAnim.PushBack({ 945,19, 33, 101 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	rightAnim.PushBack({ 1070,19, 31, 102 });
	rightAnim.PushBack({ 1198,19, 31, 102 });
	rightAnim.PushBack({ 1326,19, 31, 102 });
	rightAnim.PushBack({ 1454,19, 33, 101 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	upAnim.PushBack({ 1577,18, 45, 102 });
	upAnim.PushBack({ 1705,18, 45, 104 });
	upAnim.PushBack({ 1833,18, 45, 102 });
	upAnim.PushBack({ 1961,18, 45, 104 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;
}

VampirEnem::~VampirEnem()
{

}

bool VampirEnem::Start()
{

	TextureVampire = app->tex->Load("Assets/Textures/Enem/vampire.png");
	selectVampire = app->tex->Load("Assets/Textures/UI/choseplayers.png");
	vampireEnem = app->tex->Load("Assets/Textures/Enem/characters_vampire.png");

	for (int i = 0; i < NUM_VAMPIRE; i++)
	{
		currentAnimation[i] = &idleAnim;
	}

	Vpir[0] = CreateVampire(/*Vpir->Pos.x, Vpir->Pos.x,*/1248,448, TextureVampire);
	Vpir[10] = CreateVampire(/*Vpir->Pos.x, Vpir->Pos.x,*/1696,1536, TextureVampire);

	currentAttack1V = &VidleAttack1;
	currentHit1V = &VidleHit1;
	currentDead1V = &VidleDead1;
	currentA1V = &VidleA1;

	return false;
}

bool VampirEnem::Update(float dt)
{
	if (app->BTSystem->battle == true && app->player->P1.IsAlive == true && app->BTSystem->Vampirebattle == true) {
		if (app->BTSystem->SpawnedEnemies == false) {
			SpawnEnemies();
		}
		DrawEnemies();
		ChooseEnemy();
		Combat();
		DrawHpBars();
		if (app->BTSystem->PlayerTurn == false)  {
			EnemyPhase();
			CheckEnemy();
		}
	}
	else if (app->BTSystem->battleAux == true) {
		app->BTSystem->battleAux = false;
		app->BTSystem->playerTarget = 0;
		Vpir[WhichVampire].Destroyed = true;
	}
	timer3 = SDL_GetTicks() / 10;

	for (int i = 0; i < NUM_VAMPIRE; i++)
	{
		currentAnimation[i]->Update();

		if (Vpir[i].Destroyed == true)
		{
			Vpir[i].dead = true;
			Vpir[i].colliderV->pendingToDelete = true;
		}
	}
	for (int i = 0; i < 11; i+= 10)
	{
		Vpir[i].colliderV->SetPos(Vpir[i].Pos.x, Vpir[i].Pos.y);
		Vpir[i].colliderS->SetPos(Vpir[i].Pos.x - 168, Vpir[i].Pos.y - 168);
	}

	if (app->BTSystem->battle == false)
	{
		for (int i = 0; i < 5; i++) {
			Vpir[i].onFire = false;
			Vpir[i].poisoned = false;
		}
	}

	return true;
}



bool VampirEnem::PostUpdate()
{
	LOG("FUNCIONA?");

	VampireAR = currentAttack1V->GetCurrentFrame();
	vampireH1AR = currentHit1V->GetCurrentFrame();
	vampireD1AR = currentDead1V->GetCurrentFrame();
	vampireA1AR = currentA1V->GetCurrentFrame();
	app->particle->fireparticv = app->particle->currentFire->GetCurrentFrame();
	app->particle->Venomparticv = app->particle->currentVenom->GetCurrentFrame();
	for (int i = 0; i < NUM_VAMPIRE; i++)
	{
		if (Vpir[i].dead == false && app->menu->config == false && app->BTSystem->battle == false)
		{
		app->render->DrawTexture(Vpir[i].vampireT, Vpir[i].Pos.x, Vpir[i].Pos.y, &(currentAnimation[i]->GetCurrentFrame()));
		currentAnimation[i]->Update();
		}
	}
	return true;
}



void VampirEnem::Combat() {
	if (app->BTSystem->Vampirebattle == true) {

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
				Vpir[app->BTSystem->VampireTarget].hp -= app->player->P1.damage1 + app->player->P1.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P1.speed + app->player->P1.speed1);
			app->player->P1.mana += app->player->P1.mana1;
			app->BTSystem->VampireTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[0] += 1;
			app->BTSystem->PlayerTurn = false;
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
				} while (randomNumber2 == app->BTSystem->VampireTarget);
				do {
					randomNumber2_ = (rand() % 4 - app->BTSystem->CombatDeaths) + 1;
				} while (randomNumber2_ == app->BTSystem->VampireTarget || randomNumber2_ == randomNumber2);

				Vpir[randomNumber2].hp -= app->player->P1.damage2 + app->player->P1.damage;
				Vpir[randomNumber2_].hp -= app->player->P1.damage + app->player->P1.damage2;
				Vpir[app->BTSystem->VampireTarget].hp -= app->player->P1.damage2 + app->player->P1.damage;
				Vpir[app->BTSystem->VampireTarget].Vhit = true;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P1.speed + app->player->P1.speed2);
			app->player->P1.mana += app->player->P1.mana2;
			app->BTSystem->VampireTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[0] += 1;
			app->BTSystem->PlayerTurn = false;
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
				Vpir[app->BTSystem->VampireTarget].hp -= app->player->P2.damage1 + app->player->P2.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P2.speed + app->player->P2.speed1);
			app->player->P2.mana += app->player->P2.mana1;
			app->BTSystem->VampireTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[1] += 1;
			app->BTSystem->PlayerTurn = false;
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
				Vpir[app->BTSystem->VampireTarget].hp -= app->player->P2.damage2 + app->player->P2.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P2.speed + app->player->P2.speed2);
			app->player->P2.mana += app->player->P2.mana2;
			app->BTSystem->VampireTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[1] += 1;
			app->BTSystem->PlayerTurn = false;
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
				} while (randomNumber2 == app->BTSystem->VampireTarget);
				do {
					randomNumber2_ = (rand() % 4 - app->BTSystem->CombatDeaths) + 1;
				} while (randomNumber2_ == app->BTSystem->VampireTarget || randomNumber2_ == randomNumber2);
				Vpir[randomNumber2].hp -= app->player->P3.damage2 + app->player->P3.damage;
				Vpir[randomNumber2_].hp -= app->player->P3.damage2 + app->player->P3.damage;
				Vpir[app->BTSystem->VampireTarget].hp -= app->player->P3.damage1 + app->player->P3.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P3.speed + app->player->P3.speed1);
			app->player->P3.mana += app->player->P3.mana1;
			app->BTSystem->VampireTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[2] += 1;
			app->BTSystem->PlayerTurn = false;
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
				Vpir[app->BTSystem->VampireTarget].hp -= app->player->P3.damage2 + app->player->P3.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P3.speed + app->player->P3.speed2);
			app->player->P3.mana += app->player->P3.mana2;
			app->BTSystem->VampireTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[2] += 1;
			app->BTSystem->PlayerTurn = false;
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
					} while (randomNumber2 == app->BTSystem->VampireTarget);
					Vpir[randomNumber2].hp -= app->player->P4.damage2 + app->player->P4.damage;
				}
				Vpir[app->BTSystem->VampireTarget].hp -= app->player->P4.damage1 + app->player->P4.damage;
				randomNumber = (rand() % 100) + 1;
			} while (randomNumber <= app->player->P4.speed + app->player->P4.speed1);
			app->player->P4.mana += app->player->P4.mana1;
			app->BTSystem->VampireTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[3] += 1;
			app->BTSystem->PlayerTurn = false;
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
				Vpir[app->BTSystem->VampireTarget].hp -= app->player->P4.damage2 + app->player->P4.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P4.speed + app->player->P4.speed2);
			app->player->P4.mana += app->player->P4.mana2;
			app->BTSystem->VampireTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[3] += 1;
			app->BTSystem->PlayerTurn = false;
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
 			Vpir[app->BTSystem->VampireTarget].poisoned = true;
			Vpir[app->BTSystem->VampireTarget].hp -= (20 * app->BTSystem->AttackAux) / 100;
			app->BTSystem->AttackAux = 0;
			app->BTSystem->VampireTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[0] += 1;
			app->BTSystem->PlayerTurn = false;
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
			Vpir[WhichVampire].onFire = true;
			Vpir[1].onFire = true;
			Vpir[2].onFire = true;
			Vpir[3].onFire = true;
			Vpir[4].onFire = true;
			Vpir[app->BTSystem->VampireTarget].hp -= (15 * app->BTSystem->AttackAux) / 100;
			app->BTSystem->AttackAux = 0;
			app->BTSystem->VampireTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[1]++;
			app->BTSystem->PlayerTurn = false;
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
			app->BTSystem->VampireTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[2]++;
			app->BTSystem->PlayerTurn = false;
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
			Vpir[app->BTSystem->VampireTarget].hp -= (75 * app->BTSystem->AttackAux) / 100;
			app->BTSystem->AttackAux = 0;
			app->BTSystem->VampireTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[3]++;
			app->BTSystem->PlayerTurn = false;
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

void VampirEnem::SpawnEnemies() {
	if (app->BTSystem->Vampirebattle == true) {
		srand(time(NULL));

		for (int i = 1; i < Vpir[WhichVampire].numEnemies + 1; i++) {
			Vpir[i].dead = false;
			randomEnemyhp = (rand() % 10) + 1;
			randomEnemySpeed = (rand() % 6) + 1;
			randomEnemyDamage = (rand() % 6) + 1;
			if (randomstats == true) {
				Vpir[i].hp += randomEnemyhp;
				Vpir[i].speed += randomEnemySpeed;
				Vpir[i].damage += randomEnemyDamage;
			}

		}
	}
	randomstats = false;
	app->BTSystem->SpawnedEnemies = true;
}

void VampirEnem::DrawEnemies() {
	if (app->BTSystem->Vampirebattle == true && app->BTSystem->InventoryEnable == false) {
		for (int i = 1; i < Vpir[WhichVampire].numEnemies + 1; i++) {
			if (Vpir[i].dead == false) {
				if (app->BTSystem->VampireTarget == i) {
					Choose->x = 4;
					Choose->y = 135;
					Choose->w = 110;
					Choose->h = 110;
					app->render->DrawTexture(selectVampire, app->player->P1.position.x + 395, app->player->P1.position.y - 335 + 120 * i, Choose);
				}
				if (Vpir[i].Vhit == false && Vpir[i].atack == false)
				{
					SDL_Rect Enem1 = { app->player->P1.position.x + 400, app->player->P1.position.y - 330 + 120 * i, 100, 100 };
					currentAnimation[i] = &VidleAttack1;;
					app->render->DrawTexture(vampireEnem, app->player->P1.position.x + 350, app->player->P1.position.y - 330 + 100 * i, &VampireAR);
					currentAnimation[i]->Update();
				}
				if (Vpir[i].Vhit == true)
				{
					currentAnimation[i] = &VidleHit1;;
					app->render->DrawTexture(vampireEnem, app->player->P1.position.x + 350, app->player->P1.position.y - 330 + 100 * i, &vampireH1AR);
					currentAnimation[i]->Update();
					if (VidleHit1.currentFrame >= 4.0) {
						VidleHit1.currentFrame = 0;
						Vpir[i].Vhit = false;
					}
				}
				if (Vpir[i].atack == true)
				{
					if (VidleA1.currentFrame <= 3.0) {
						currentAnimation[i] = &VidleA1;
						app->render->DrawTexture(vampireEnem, app->player->P1.position.x + 350, app->player->P1.position.y - 330 + 100 * i, &vampireA1AR);
						currentAnimation[i]->Update();

					}
					if (VidleA1.currentFrame >= 3.0 && VidleA1.currentFrame <= 5.0)
					{

						//currentAnimation[i] = &VidleA1;
						app->render->DrawTexture(vampireEnem, app->player->P1.position.x + 350, app->player->P1.position.y - 391 + 100 * i, &vampireA1AR);
						//currentAnimation[i]->Update();
					}

					if (VidleA1.currentFrame >= 5.0 && VidleA1.currentFrame <= 7.0)
					{

						//currentAnimation[i] = &VidleA1;
						app->render->DrawTexture(vampireEnem, app->player->P1.position.x + 390, app->player->P1.position.y - 391 + 100 * i, &vampireA1AR);
						//currentAnimation[i]->Update();
						VidleA1.currentFrame = 0;
						Vpir[i].atack = false;
					}
				}
				if (Vpir[i].onFire == true && app->menu->config == false && app->BTSystem->battle == true)
				{
					app->particle->currentAnimationF[i] = &app->particle->fire_particles;
					app->render->DrawTexture(app->particle->firepart, app->player->P1.position.x + 395, app->player->P1.position.y - 320 + 100 * i, &app->particle->fireparticv);
					app->particle->currentAnimationF[i]->Update();
				}
				if (Vpir[i].poisoned == true && app->menu->config == false && app->BTSystem->battle == true)
				{
					app->particle->currentAnimationV[i] = &app->particle->Venom_particles;
					app->render->DrawTexture(app->particle->Venompart, app->player->P1.position.x + 350, app->player->P1.position.y - 330 + 100 * i, &app->particle->Venomparticv);
					app->particle->currentAnimationV[i]->Update();
				}
			}
			if (Vpir[i].dead == true)
			{
				currentAnimation[i] = &VidleDead1;;
				app->render->DrawTexture(vampireEnem, app->player->P1.position.x + 350, app->player->P1.position.y - 330 + 100 * i, &vampireD1AR);
				currentAnimation[i]->Update();
			}

		}
		app->guiManager->Draw();
	}
}

void VampirEnem::ChooseEnemy() {
	if (app->BTSystem->Vampirebattle == true) {
		int x, y;
		SDL_PumpEvents();  // make sure we have the latest mouse state.

		x = app->mouse->cursor.x;
		y = app->mouse->cursor.y;

		for (int i = 1; i < Vpir[WhichVampire].numEnemies + 1; i++) {
			/*if (Vpir[i].dead == false && x >= 772 && x <= 772 + 50 && y >= 18 + 60*i && y <= 18 + 60 * i + 50 && app->input->GetMouseButtonDown(1) == KEY_DOWN && app->BTSystem->AttackPlayer != 0 && app->BTSystem->PlayerTurn == true) {
				app->BTSystem->VampireTarget = i;
				//SDL_Rect Enem1 = { app->player->P1.position.x + 400, app->player->P1.position.y - 330 + 120 * i, 100, 100 };

			}*/
			if (Vpir[i].dead == false && x > 1005 && x < 1110 && y > -5 + 120 * i && y < 115 + 120 * i + 100 && (app->input->GetMouseButtonDown(1) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->Pad->GetButton(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) && app->BTSystem->AttackPlayer != 0 && app->BTSystem->PlayerTurn == true && app->BTSystem->SpecialAttackEnable == false) {
				app->BTSystem->VampireTarget = i;
				//SDL_Rect Enem1 = { app->player->P1.position.x + 500, app->player->P1.position.y - 330 + 120 * i, 100, 100 };
			}
		}
		for (int i = 1; i < Vpir[WhichVampire].numEnemies + 1; i++) {//
			if (Vpir[i].dead == false && x > 1005 && x < 1110 && y > -5 + 120 * i && y < 115 + 120 * i + 100 && (app->input->GetMouseButtonDown(1) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->Pad->GetButton(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) && app->BTSystem->PlayerTurn == true && app->BTSystem->SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && app->player->godMode == true) {
				//app->BTSystem->VampireTarget = i;
				Vpir[i].hp = 0;
			}

		}
	}
}

void VampirEnem::EnemyPhase() {
	if (app->BTSystem->Vampirebattle == true) {
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
		for (int i = 1; i < Vpir[WhichVampire].numEnemies + 1; i++) {
			if (Vpir[i].dead == false && app->BTSystem->PlayerTurn == false) {
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

				if (app->BTSystem->playerTarget == 1 && app->player->P1.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						if (app->player->godMode == false) {
							app->player->P1.hp -= Vpir[app->BTSystem->playerTarget].damage;
							Vpir[i].atack = true;
						}
					} while (randomNumber <= Vpir[app->BTSystem->playerTarget].speed);
   					app->BTSystem->PlayerTurn = true;

				}
				if (app->BTSystem->playerTarget == 2 && app->player->P2.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						if (app->player->godMode == false) {
							app->player->P2.hp -= Vpir[app->BTSystem->playerTarget].damage;
							Vpir[i].atack = true;
						}
					} while (randomNumber <= Vpir[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;

				}
				if (app->BTSystem->playerTarget == 3 && app->player->P3.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						if (app->player->godMode == false) {
							app->player->P3.hp -= Vpir[app->BTSystem->playerTarget].damage;
							Vpir[i].atack = true;
						}
					} while (randomNumber <= Vpir[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;

				}
				if (app->BTSystem->playerTarget == 4 && app->player->P4.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						if (app->player->godMode == false) {
							app->player->P4.hp -= Vpir[app->BTSystem->playerTarget].damage;
							Vpir[i].atack = true;
						}
					} while (randomNumber <= Vpir[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;
				}
			}
		}
		app->BTSystem->SpecialAttackEnable = false;
		app->BTSystem->alliesDead = 0;
	}
}

void VampirEnem::CheckEnemy() {
	if (app->BTSystem->Vampirebattle == true) {
		for (int i = 0; i < 5; i++) {
   			if (Vpir[i].poisoned == true && app->BTSystem->SpecialAttackEnable == false) {
   				Vpir[i].hp -= 2;
				app->BTSystem->poisonCount[i]++;
				app->BTSystem->SpecialAttackEnable = true;
			}
			if (app->BTSystem->poisonCount[i] >= 10) {
				app->BTSystem->poisonCount[i] = 0;
				Vpir[i].poisoned = false;
			}
			if (Vpir[i].onFire == true && app->BTSystem->SpecialAttackEnable == false) {
				Vpir[i].hp -= 10;
			}
			if (app->BTSystem->onFireCount != 0 && Vpir[WhichVampire].onFire == true) {
				app->BTSystem->onFireCount++;
			}
			if (app->BTSystem->onFireCount >= 3) {
				app->BTSystem->onFireCount = 0;
				Vpir[WhichVampire].onFire = false;
				Vpir[1].onFire = false;
				Vpir[2].onFire = false;
				Vpir[3].onFire = false;
				Vpir[4].onFire = false;
			}
		}
		for (int i = 1; i < Vpir[WhichVampire].numEnemies + 1; i++) {
			if (Vpir[i].hp <= 0) {
				Vpir[i].dead = true;
				app->BTSystem->CombatDeaths += 1;
			}
			if (app->BTSystem->CombatDeaths == Vpir[WhichVampire].numEnemies) {
				app->BTSystem->battleEnd = true;
				app->BTSystem->transitionRep = 1;
				app->BTSystem->Vampirebattle = false;
				app->BTSystem->battleWin = false;
				app->BTSystem->battle1 = false;
				app->player->P4.revolverActive = true;
				Vpir[WhichVampire].Destroyed = true;
				randomstats = true;
				app->player->P1.damage = 0;
				app->player->P2.damage = 0;
				app->player->P3.damage = 0;
				app->player->P4.damage = 0;
				for (int i = 0; i < Vpir[WhichVampire].numEnemies + 1; i++) {
					Vpir[i].hp = Vpir[i].basehp;
					Vpir[i].speed = Vpir[i].basespeed;
					Vpir[i].damage = Vpir[i].basedamage;
				}
			}
		}
		app->BTSystem->CombatDeaths = 0;
	}
}

void VampirEnem::DrawHpBars() {
	if (app->BTSystem->InventoryEnable == false) {
		if (Vpir[1].dead == false && app->BTSystem->InventoryEnable == false) {
			SDL_Rect bar1 = { app->player->P1.position.x + 380, app->player->P1.position.y - 200, -(200 * Vpir[1].hp) / 100,15 };
			app->render->DrawRectangle(bar1, 255, 0, 0);
		}
		if (Vpir[2].dead == false && app->BTSystem->InventoryEnable == false && Vpir[WhichVampire].numEnemies > 1) {
			SDL_Rect bar2 = { app->player->P1.position.x + 380, app->player->P1.position.y - 200 + 120, -(200 * Vpir[2].hp) / 100,15 };
			app->render->DrawRectangle(bar2, 255, 0, 0);
		}
		if (Vpir[3].dead == false && app->BTSystem->InventoryEnable == false && Vpir[WhichVampire].numEnemies > 2) {
			SDL_Rect bar3 = { app->player->P1.position.x + 380, app->player->P1.position.y - 200 + 240, -(200 * Vpir[3].hp) / 100,15 };
			app->render->DrawRectangle(bar3, 255, 0, 0);
		}
		if (Vpir[4].dead == false && app->BTSystem->InventoryEnable == false && Vpir[WhichVampire].numEnemies > 3) {
			SDL_Rect bar4 = { app->player->P1.position.x + 380, app->player->P1.position.y - 200 + 360, -(200 * Vpir[4].hp) / 100,15 };
			app->render->DrawRectangle(bar4, 255, 0, 0);
		}
	}
}

void VampirEnem::OnCollision(Collider* c1, Collider* c2)
{

	for (uint i = 0; i < NUM_VAMPIRE; ++i)
	{
		if (Vpir[i].colliderV == c1 && !Vpir[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
				app->BTSystem->Skeletonbattle = false;
				app->BTSystem->Vampirebattle = true;
			}
		}
		else if (Vpir[i].colliderS == c1 && !Vpir[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
				switch (i)
				{
				case 0:
					WhichVampire = i;
					Vpir[0].numEnemies = 2;
					break;
				case 10:
					WhichVampire = i;
					Vpir[10].numEnemies = 3;

					break;
				default:
					break;
				}
				if (pathfindingaux == true) {
					pathfindingtimer = timer3;
					pathfindingaux = false;
				}
				path = true;
				VampireNum = i;
				PathFindVamp(VampireNum);
			}
		}
	}
}

void VampirEnem::PathFindVamp(int i)
{
	if (app->player->godMode == false)
	{
		if (path == true && app->BTSystem->battle == false && app->BTSystem->Delay == true && app->scene->paused == false)
		{
			app->pathfinding->CreatePath(app->map->WorldToMap(Vpir[i].Pos.x, Vpir[i].Pos.y), app->map->WorldToMap(app->player->P1.position.x, app->player->P1.position.y));

			const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

			for (uint j = 0; j < path->Count(); ++j)
			{
				iPoint pos = app->map->MapToWorld(path->At(j)->x, path->At(j)->y);
				if (Vpir[i].Pos.x <= pos.x - 32 && timer3 > pathfindingtimer + enemySpeed)
				{
					currentAnimation[i] = &rightAnim;
					pathfindingtimer = timer3;
					Vpir[i].Pos.x += 32;
				}
				if (Vpir[i].Pos.x >= pos.x + 32 && timer3 > pathfindingtimer + enemySpeed)
				{
					currentAnimation[i] = &leftAnim;
					pathfindingtimer = timer3;
					Vpir[i].Pos.x -= 32;
				}
				if (Vpir[i].Pos.y <= pos.y - 32 && timer3 > pathfindingtimer + enemySpeed)
				{
					currentAnimation[i] = &downAnim;
					pathfindingtimer = timer3;
					Vpir[i].Pos.y += 32;
				}
				if (Vpir[i].Pos.y >= pos.y + 32 && timer3 > pathfindingtimer + enemySpeed)
				{
					currentAnimation[i] = &upAnim;
					pathfindingtimer = timer3;
					Vpir[i].Pos.y -= 32;
				}
			}

		}
	}

}
Vampire VampirEnem::CreateVampire(int x, int y, SDL_Texture* t)
{
	Vampire Vampires;

	Vampires.colliderV = app->collisions->AddCollider({ x, y, 32, 32 }, Collider::Type::VAMPIRE, (Module*)app->entityManager);
	Vampires.colliderS = app->collisions->AddCollider({ x, y, 400, 400 }, Collider::Type::SENSOR, (Module*)app->entityManager);
	Vampires.vampireT = t;
	Vampires.Pos.x = x;
	Vampires.Pos.y = y;

	return Vampires;
}
