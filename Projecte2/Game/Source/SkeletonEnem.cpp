#include "Entity.h"
#include "App.h"
#include "Textures.h"
#include "SkeletonEnem.h"
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
#include <time.h>

SkeletonEnem::SkeletonEnem() :Entity(EntityType::SKELETON)
{
	name.Create("VampirEnem");
	idle.PushBack({ 5, 6, 16, 17 });
	idle.PushBack({ 28, 6, 12, 17 });
	idle.PushBack({ 11, 29, 5, 16 });
	idle.PushBack({ 28, 28, 12, 17 });
	idle.loop = true;
	idle.speed = 0.001f;
}

SkeletonEnem::~SkeletonEnem()
{
	name.Create("Vampire");
}

/*
bool VampirEnem::Awake(pugi::xml_node& config)
{
	LOG("Loading VampirEnem");
	bool ret = true;


	Vpir[0].Pos.x = config.child("Position").attribute("PositionX").as_int();
	Vpir[0].Pos.y = config.child("Position").attribute("PositionY").as_int();


	return false;
}


bool VampirEnem::LoadState(pugi::xml_node& data)
{
	Vpir[0].Pos.x = data.child("Vampire").attribute("x").as_int();
	Vpir[0].Pos.y = data.child("Vampire").attribute("y").as_int();
	return false;
}

bool VampirEnem::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node VPyr = data.append_child("Vampire");

	VPyr.append_attribute("x") = Vpir[0].Pos.x;
	VPyr.append_attribute("y") = Vpir[0].Pos.y;
	return false;
}
*/
bool SkeletonEnem::Start()
{

	TextureSkeleton = app->tex->Load("Assets/textures/coins.png");
	//coinFx = app->audio->LoadFx("Assets/audio/fx/coin.wav");


	for (int i = 0; i < NUM_SKELETON; i++)
	{
		currentAnimation[i] = &idle;
	}

	Ston[0] = CreateSkeleton(/*Vpir->Pos.x, Vpir->Pos.x,*/360, 360, TextureSkeleton);

	return false;
}

bool SkeletonEnem::Update(float dt)
{

	static char title[256];
	sprintf_s(title, 256, "ENEMH1: %.1f ENEMHP2: %.1f ENEMH3: %.1f ENEMHP4: %.1f Playerhp1: %.1f Playerhp2: %.1f Playerhp3: %.1f Playerhp4: %.1f",
		Ston[1].hp, Ston[2].hp, Ston[3].hp, Ston[4].hp, app->player->P1.hp, app->player->P2.hp, app->player->P3.hp, app->player->P4.hp);
	app->win->SetTitle(title);

	if (app->BTSystem->battle == true && app->player->P1.IsAlive == true && app->BTSystem->Skeletonbattle) {
		if (app->BTSystem->SpawnedEnemies == false) {
			SpawnEnemies();
		}
		DrawEnemies();
		ChooseEnemy();
		Combat();
		if (app->BTSystem->PlayerTurn == false) {
			CheckEnemy();

			EnemyPhase();
		}
	}
	else if (app->BTSystem->battleAux == true) {
		app->BTSystem->battleAux = false;
		Ston[0].Destroyed = true;
	}
	timer3 = SDL_GetTicks() / 10;

	/*if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
	{
		PathFindVamp(VampireNum);
	}

	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		if (pathfindingaux == true) {
			pathfindingtimer = timer3;
			pathfindingaux = false;
		}
		path = true;
	}*/
	for (int i = 0; i < NUM_SKELETON; i++)
	{
		currentAnimation[i]->Update();

		if (Ston[i].Destroyed == true)
		{
			Ston[i].dead = true;
			Ston[i].colliderSK->pendingToDelete = true;
		}
	}
	for (int i = 0; i < 1; i++)
	{
		Ston[i].colliderSK->SetPos(Ston[i].Pos.x, Ston[i].Pos.y);
		Ston[i].colliderS->SetPos(Ston[i].Pos.x - 84, Ston[i].Pos.y - 84);
	}
	return true;
}



bool SkeletonEnem::PostUpdate()
{
	LOG("FUNCIONA?");
	for (int i = 0; i < NUM_SKELETON; i++)
	{
		if (Ston[i].dead == false)
		{
			app->render->DrawTexture(Ston[i].skeletonT, Ston[i].Pos.x, Ston[i].Pos.y, &(currentAnimation[i]->GetCurrentFrame()));
		}
	}
	return true;
}



void SkeletonEnem::Combat() {
	if (app->BTSystem->Skeletonbattle == true) {

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
				app->BTSystem->battle = false;
				app->BTSystem->battleWin = false;
			}
		}
		if (app->BTSystem->AttackType == 1 && app->BTSystem->AttackPlayer == 1 && app->BTSystem->randomAux == true) {
			int randomNumber = 0;
			do {
				Ston[app->BTSystem->SkeletonTarget].hp -= app->player->P1.damage1 + app->player->P1.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P1.speed + app->player->P1.speed1);
			app->player->P1.mana += app->player->P1.mana1;
			app->BTSystem->SkeletonTarget = 0;
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
		if (app->BTSystem->AttackType == 2 && app->BTSystem->AttackPlayer == 1 && app->BTSystem->randomAux == true) {
			int randomNumber = 0;
			int randomNumber2 = 0;
			int randomNumber2_ = 0;
			do {
				do {
					randomNumber2 = (rand() % 4 - app->BTSystem->CombatDeaths) + 1;
				} while (randomNumber2 == app->BTSystem->SkeletonTarget);
				do {
					randomNumber2_ = (rand() % 4 - app->BTSystem->CombatDeaths) + 1;
				} while (randomNumber2_ == app->BTSystem->SkeletonTarget || randomNumber2_ == randomNumber2);

				Ston[randomNumber2].hp -= app->player->P1.damage2 + app->player->P1.damage;
				Ston[randomNumber2_].hp -= app->player->P1.damage + app->player->P1.damage2;
				Ston[app->BTSystem->SkeletonTarget].hp -= app->player->P1.damage2 + app->player->P1.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P1.speed + app->player->P1.speed2);
			app->player->P1.mana += app->player->P1.mana2;
			app->BTSystem->SkeletonTarget = 0;
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
		if (app->BTSystem->AttackType == 1 && app->BTSystem->AttackPlayer == 2 && app->BTSystem->randomAux == true) {
			int randomNumber = 0;
			do {
				Ston[app->BTSystem->SkeletonTarget].hp -= app->player->P2.damage1 + app->player->P2.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P2.speed + app->player->P2.speed1);
			app->player->P2.mana += app->player->P2.mana1;
			app->BTSystem->SkeletonTarget = 0;
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
				Ston[app->BTSystem->SkeletonTarget].hp -= app->player->P2.damage2 + app->player->P2.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P2.speed + app->player->P2.speed2);
			app->player->P2.mana += app->player->P2.mana2;
			app->BTSystem->SkeletonTarget = 0;
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
				} while (randomNumber2 == app->BTSystem->SkeletonTarget);
				do {
					randomNumber2_ = (rand() % 4 - app->BTSystem->CombatDeaths) + 1;
				} while (randomNumber2_ == app->BTSystem->SkeletonTarget || randomNumber2_ == randomNumber2);
				Ston[randomNumber2].hp -= app->player->P3.damage2 + app->player->P3.damage;
				Ston[randomNumber2_].hp -= app->player->P3.damage2 + app->player->P3.damage;
				Ston[app->BTSystem->SkeletonTarget].hp -= app->player->P3.damage1 + app->player->P3.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P3.speed + app->player->P3.speed1);
			app->player->P3.mana += app->player->P3.mana1;
			app->BTSystem->SkeletonTarget = 0;
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
				Ston[app->BTSystem->SkeletonTarget].hp -= app->player->P3.damage2 + app->player->P3.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P3.speed + app->player->P3.speed2);
			app->player->P3.mana += app->player->P3.mana2;
			app->BTSystem->SkeletonTarget = 0;
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
					} while (randomNumber2 == app->BTSystem->SkeletonTarget);
					Ston[randomNumber2].hp -= app->player->P4.damage2 + app->player->P4.damage;
				}

				Ston[app->BTSystem->SkeletonTarget].hp -= app->player->P4.damage1 + app->player->P4.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P4.speed + app->player->P4.speed1);
			app->player->P4.mana += app->player->P4.mana1;
			app->BTSystem->SkeletonTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
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
				Ston[app->BTSystem->SkeletonTarget].hp -= app->player->P4.damage2 + app->player->P4.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P4.speed + app->player->P4.speed2);
			app->player->P4.mana += app->player->P4.mana2;
			app->BTSystem->SkeletonTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
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
			Ston[app->BTSystem->SkeletonTarget].poisoned = true;
			Ston[app->BTSystem->SkeletonTarget].hp -= (20 * app->BTSystem->AttackAux) / 100;
			app->BTSystem->AttackAux = 0;
			app->BTSystem->SkeletonTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[0]++;
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
			Ston[0].onFire = true;
			Ston[1].onFire = true;
			Ston[2].onFire = true;
			Ston[3].onFire = true;
			Ston[4].onFire = true;
			Ston[app->BTSystem->SkeletonTarget].hp -= (15 * app->BTSystem->AttackAux) / 100;
			app->BTSystem->AttackAux = 0;
			app->BTSystem->SkeletonTarget = 0;
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
			app->BTSystem->SkeletonTarget = 0;
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
			Ston[app->BTSystem->SkeletonTarget].hp -= (75 * app->BTSystem->AttackAux) / 100;
			app->BTSystem->AttackAux = 0;
			app->BTSystem->SkeletonTarget = 0;
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
			app->BTSystem->waitPlayer[1]++;
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

void SkeletonEnem::SpawnEnemies() {
	if (app->BTSystem->Skeletonbattle == true) {
		srand(time(NULL));

		for (int i = 1; i < Ston[0].numEnemies + 1; i++) {
			Ston[i].dead = false;
			randomEnemyhp = (rand() % 10) + 1;
			randomEnemySpeed = (rand() % 6) + 1;
			randomEnemyDamage = (rand() % 6) + 1;
			if (klk == true) {
				Ston[i].hp += randomEnemyhp;
				Ston[i].speed += randomEnemySpeed;
				Ston[i].damage += randomEnemyDamage;
			}

		}
	}
	klk = false;
	app->BTSystem->SpawnedEnemies = true;
}

void SkeletonEnem::DrawEnemies() {
	if (app->BTSystem->Skeletonbattle == true) {
		for (int i = 1; i < Ston[0].numEnemies + 1; i++) {
			if (Ston[i].dead == false) {
				if (app->BTSystem->SkeletonTarget == i) {
					SDL_Rect Enem1 = { app->player->P1.position.x + 395, app->player->P1.position.y - 335 + 120 * i, 110, 110 };
					app->render->DrawRectangle(Enem1, 255, 255, 0);
				}
				SDL_Rect Enem1 = { app->player->P1.position.x + 400, app->player->P1.position.y - 330 + 120 * i, 100, 100 };
				app->render->DrawRectangle(Enem1, 255, 255, 255);
			}

		}
		app->guiManager->Draw();
	}
}

void SkeletonEnem::ChooseEnemy() {
	if (app->BTSystem->Skeletonbattle == true) {
		int x, y;
		Uint32 buttons;
		SDL_PumpEvents();  // make sure we have the latest mouse state.

		buttons = SDL_GetMouseState(&x, &y);

		for (int i = 1; i < Ston[0].numEnemies + 1; i++) {
			/*if (Vpir[i].dead == false && x >= 772 && x <= 772 + 50 && y >= 18 + 60*i && y <= 18 + 60 * i + 50 && app->input->GetMouseButtonDown(1) == KEY_DOWN && app->BTSystem->AttackPlayer != 0 && app->BTSystem->PlayerTurn == true) {
				app->BTSystem->VampireTarget = i;
				//SDL_Rect Enem1 = { app->player->P1.position.x + 400, app->player->P1.position.y - 330 + 120 * i, 100, 100 };

			}*/
			if (Ston[i].dead == false && x > 1005 && x < 1110 && y > -5 + 120 * i && y < 115 + 120 * i + 100 && app->input->GetMouseButtonDown(1) == KEY_DOWN && app->BTSystem->AttackPlayer != 0 && app->BTSystem->PlayerTurn == true && app->BTSystem->SpecialAttackEnable == false) {
				app->BTSystem->SkeletonTarget = i;
				//SDL_Rect Enem1 = { app->player->P1.position.x + 500, app->player->P1.position.y - 330 + 120 * i, 100, 100 };
			}
		}
		for (int i = 1; i < Ston[0].numEnemies + 1; i++) {//
			if (Ston[i].dead == false && x > 1005 && x < 1110 && y > -5 + 120 * i && y < 115 + 120 * i + 100 && app->input->GetMouseButtonDown(1) == KEY_DOWN && app->BTSystem->PlayerTurn == true && app->BTSystem->SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {
				//app->BTSystem->VampireTarget = i;
				Ston[i].hp = 0;
			}

		}
	}
}

void SkeletonEnem::EnemyPhase() {
	if (app->BTSystem->Skeletonbattle == true) {
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
				app->BTSystem->battle = false;
				app->BTSystem->battleWin = false;

			}
		}
		for (int i = 1; i < Ston[0].numEnemies + 1; i++) {
			if (Ston[i].dead == false && app->BTSystem->PlayerTurn == false) {
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
						app->player->P1.hp -= Ston[app->BTSystem->playerTarget].damage;
					} while (randomNumber <= Ston[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;
				}
				if (app->BTSystem->playerTarget == 2 && app->player->P2.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						app->player->P2.hp -= Ston[app->BTSystem->playerTarget].damage;
					} while (randomNumber <= Ston[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;

				}
				if (app->BTSystem->playerTarget == 3 && app->player->P3.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						app->player->P3.hp -= Ston[app->BTSystem->playerTarget].damage;
					} while (randomNumber <= Ston[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;

				}
				if (app->BTSystem->playerTarget == 4 && app->player->P4.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						app->player->P4.hp -= Ston[app->BTSystem->playerTarget].damage;
					} while (randomNumber <= Ston[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;

				}

			}
		}
		app->BTSystem->SpecialAttackEnable = false;
		app->BTSystem->alliesDead = 0;
	}
}

void SkeletonEnem::CheckEnemy() {
	if (app->BTSystem->Skeletonbattle == true) {
		for (int i = 0; i < 5; i++) {
			if (Ston[i].poisoned == true && app->BTSystem->SpecialAttackEnable == false) {
				Ston[i].hp -= 2;
				app->BTSystem->poisonCount[i]++;
				app->BTSystem->SpecialAttackEnable = true;
			}
			if (app->BTSystem->poisonCount[i] >= 10) {
				app->BTSystem->poisonCount[i] = 0;
				Ston[i].poisoned = false;
			}
			if (Ston[i].onFire == true && app->BTSystem->SpecialAttackEnable == false) {
				Ston[i].hp -= 10;
			}
			if (app->BTSystem->onFireCount != 0 && Ston[0].onFire == true) {
				app->BTSystem->onFireCount++;
			}
			if (app->BTSystem->onFireCount >= 3) {
				app->BTSystem->onFireCount = 0;
				Ston[0].onFire = false;
				Ston[1].onFire = false;
				Ston[2].onFire = false;
				Ston[3].onFire = false;
				Ston[4].onFire = false;
			}
		}
		for (int i = 1; i < Ston[0].numEnemies + 1; i++) {
			if (Ston[i].hp <= 0) {
				Ston[i].dead = true;
				app->BTSystem->CombatDeaths += 1;
			}
			if (app->BTSystem->CombatDeaths == Ston[0].numEnemies) {
				app->BTSystem->battle = false;
				app->BTSystem->Skeletonbattle = false;
				app->BTSystem->battleWin = false;
				app->BTSystem->battle1 = false;
				app->player->P4.revolverActive = true;
				Ston[0].Destroyed = true;
				klk = true;
			}
		}
		app->BTSystem->PlayerTurn = true;
		app->BTSystem->CombatDeaths = 0;
	}
}

void SkeletonEnem::OnCollision(Collider* c1, Collider* c2)
{

	for (uint i = 0; i < NUM_SKELETON; ++i)
	{
		if (Ston[i].colliderSK == c1 && !Ston[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
				app->BTSystem->Skeletonbattle = true;
			}
		}
		else if (Ston[i].colliderS == c1 && !Ston[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
				if (pathfindingaux == true) {
					pathfindingtimer = timer3;
					pathfindingaux = false;
				}
				path = true;
				SkeletonNum = i;
				PathFindVamp(SkeletonNum);
			}
		}
	}
}

void SkeletonEnem::PathFindVamp(int i)
{
	if (path == true && app->BTSystem->battle == false && app->BTSystem->Delay == true)
	{
		app->pathfinding->CreatePath(app->map->WorldToMap(Ston[i].Pos.x, Ston[i].Pos.y), app->map->WorldToMap(app->player->P1.position.x, app->player->P1.position.y));

		const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

		for (uint j = 0; j < path->Count(); ++j)
		{
			iPoint pos = app->map->MapToWorld(path->At(j)->x, path->At(j)->y);
			if (Ston[i].Pos.x <= pos.x - 32 && timer3 > pathfindingtimer + enemySpeed)
			{
				pathfindingtimer = timer3;
				Ston[i].Pos.x += 32;
			}
			if (Ston[i].Pos.x >= pos.x + 32 && timer3 > pathfindingtimer + enemySpeed)
			{
				pathfindingtimer = timer3;
				Ston[i].Pos.x -= 32;
			}
			if (Ston[i].Pos.y <= pos.y - 32 && timer3 > pathfindingtimer + enemySpeed)
			{
				pathfindingtimer = timer3;
				Ston[i].Pos.y += 32;
			}
			if (Ston[i].Pos.y >= pos.y + 32 && timer3 > pathfindingtimer + enemySpeed)
			{
				pathfindingtimer = timer3;
				Ston[i].Pos.y -= 32;
			}
		}

	}

}
Skeleton SkeletonEnem::CreateSkeleton(int x, int y, SDL_Texture* t)
{
	Skeleton skeleton;

	skeleton.colliderSK = app->collisions->AddCollider({ x, y, 32, 32 }, Collider::Type::SKELETON, (Module*)app->entityManager);
	skeleton.colliderS = app->collisions->AddCollider({ x, y, 200, 200 }, Collider::Type::SENSOR, (Module*)app->entityManager);
	skeleton.skeletonT = t;
	skeleton.Pos.x = x;
	skeleton.Pos.y = y;

	return skeleton;
}

