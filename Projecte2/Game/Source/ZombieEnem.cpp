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

#include "Log.h"
#include "DynArray.h"
#include "BattleSystem.h"
#include <time.h>

ZombieEnem::ZombieEnem() :Entity(EntityType::ZOMBIE)
{
	name.Create("VampirEnem");
	idle.PushBack({ 5, 6, 16, 17 });
	idle.PushBack({ 28, 6, 12, 17 });
	idle.PushBack({ 11, 29, 5, 16 });
	idle.PushBack({ 28, 28, 12, 17 });
	idle.loop = true;
	idle.speed = 0.001f;
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
bool ZombieEnem::Start()
{

	TextureZombie = app->tex->Load("Assets/textures/coins.png");
	//coinFx = app->audio->LoadFx("Assets/audio/fx/coin.wav");


	for (int i = 0; i < NUM_ZOMBIE; i++)
	{
		currentAnimation[i] = &idle;
	}

	Zbie[0] = CreateZombie(/*Vpir->Pos.x, Vpir->Pos.x,*/360, 360, TextureZombie);

	return false;
}

bool ZombieEnem::Update(float dt)
{
	static char title[256];
	sprintf_s(title, 256, "ENEMH1: %.1f ENEMHP2: %.1f ENEMH3: %.1f ENEMHP4: %.1f Playerhp1: %.1f Playerhp2: %.1f Playerhp3: %.1f Playerhp4: %.1f",
Zbie[1].hp, Zbie[2].hp, Zbie[3].hp, Zbie[4].hp, app->player->P1.hp, app->player->P2.hp, app->player->P3.hp, app->player->P4.hp);

	app->win->SetTitle(title);
	
	if (app->BTSystem->battle == true && app->player->P1.IsAlive == true && app->BTSystem->Zombiebattle) {
		if (app->BTSystem->SpawnedEnemies == false) {
			SpawnEnemies();
		}
		DrawEnemies();
		ChooseEnemy();
		if (app->BTSystem->PlayerTurn == false) {
			CheckEnemy();
			EnemyPhase();
		}
		Combat();
	}
	else if (app->BTSystem->battleAux == true) {
		app->BTSystem->battleAux = false;
		Zbie[0].Destroyed = true;
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
	for (int i = 0; i < NUM_ZOMBIE; i++)
	{
		currentAnimation[i]->Update();

		if (Zbie[i].Destroyed == true)
		{
			Zbie[i].dead = true;
			Zbie[i].colliderZ->pendingToDelete = true;
		}
	}
	for (int i = 0; i < 1; i++)
	{
		Zbie[i].colliderZ->SetPos(Zbie[i].Pos.x, Zbie[i].Pos.y);
		Zbie[i].colliderS->SetPos(Zbie[i].Pos.x - 84, Zbie[i].Pos.y - 84);
	}
	return true;
}



bool ZombieEnem::PostUpdate()
{
	LOG("FUNCIONA?");
	for (int i = 0; i < NUM_ZOMBIE; i++)
	{
		if (Zbie[i].dead == false)
		{
			app->render->DrawTexture(Zbie[i].zombieT, Zbie[i].Pos.x, Zbie[i].Pos.y, &(currentAnimation[i]->GetCurrentFrame()));
		}
	}
	return true;
}

void ZombieEnem::Combat() {
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
				app->BTSystem->battle = false;
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
				} while (randomNumber2 == app->BTSystem->ZombieTarget);
				do {
					randomNumber2_ = (rand() % 4 - app->BTSystem->CombatDeaths) + 1;
				} while (randomNumber2_ == app->BTSystem->ZombieTarget || randomNumber2_ == randomNumber2);

				Zbie[randomNumber2].hp -= app->player->P1.damage2 + app->player->P1.damage;
				Zbie[randomNumber2_].hp -= app->player->P1.damage2 + app->player->P1.damage;
				Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P1.damage2 + app->player->P1.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P1.speed + app->player->P1.speed2);
			app->player->P1.mana += app->player->P1.mana2;
			app->BTSystem->ZombieTarget = 0;
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
				Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P2.damage1 + app->player->P2.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P2.speed + app->player->P2.speed1);
			app->player->P2.mana += app->player->P2.mana1;
			app->BTSystem->ZombieTarget = 0;
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
				Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P2.damage2 + app->player->P2.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P2.speed + app->player->P2.speed2);
			app->player->P2.mana += app->player->P2.mana2;
			app->BTSystem->ZombieTarget = 0;
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
				Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P3.damage2 + app->player->P3.damage;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P3.speed + app->player->P3.speed2);
			app->player->P3.mana += app->player->P3.mana2;
			app->BTSystem->ZombieTarget = 0;
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
					} while (randomNumber2 == app->BTSystem->ZombieTarget);
					Zbie[randomNumber2].hp -= app->player->P4.damage2 + app->player->P4.damage;
				}

			Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P4.damage1 + app->player->P4.damage;
			randomNumber = (rand() % 100) + 1;
			} while (randomNumber <= app->player->P4.speed + app->player->P4.speed1);
			app->player->P4.mana += app->player->P4.mana1;
			app->BTSystem->ZombieTarget = 0;
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
				Zbie[app->BTSystem->ZombieTarget].hp -= app->player->P4.damage2;
				randomNumber = (rand() % 100) + 1;

			} while (randomNumber <= app->player->P4.speed + app->player->P4.speed2);
			app->player->P4.mana += app->player->P4.mana2;
			app->BTSystem->ZombieTarget = 0;
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
		app->BTSystem->alliesDead = 0;
	}
}

void ZombieEnem::SpawnEnemies() {
	if (app->BTSystem->Zombiebattle == true) {
		srand(time(NULL));
		for (int i = 1; i < Zbie[0].numEnemies + 1; i++) {
			Zbie[i].dead = false;
			randomEnemyhp = (rand() % 10) + 1;
			randomEnemySpeed = (rand() % 6) + 1;
			randomEnemyDamage = (rand() % 6) + 1;
			if (klk == true) {
				Zbie[i].hp += randomEnemyhp;
				Zbie[i].speed += randomEnemySpeed;
				Zbie[i].damage += randomEnemyDamage;
			}
		}
		klk = false;
		app->BTSystem->SpawnedEnemies = true;
	}
}

void ZombieEnem::DrawEnemies() {
	if (app->BTSystem->Zombiebattle == true) {

		for (int i = 1; i < Zbie[0].numEnemies + 1; i++) {
			if (Zbie[i].dead == false) {
				if (app->BTSystem->ZombieTarget == i) {
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

void ZombieEnem::ChooseEnemy() {
	if (app->BTSystem->Zombiebattle == true) {
	int x, y;
	Uint32 buttons;
	SDL_PumpEvents();  // make sure we have the latest mouse state.

	buttons = SDL_GetMouseState(&x, &y);

	for (int i = 1; i < Zbie[0].numEnemies + 1; i++) {
		/*if (Vpir[i].dead == false && x >= 772 && x <= 772 + 50 && y >= 18 + 60*i && y <= 18 + 60 * i + 50 && app->input->GetMouseButtonDown(1) == KEY_DOWN && app->BTSystem->AttackPlayer != 0 && app->BTSystem->PlayerTurn == true) {
			app->BTSystem->ZombieTarget = i;
			//SDL_Rect Enem1 = { app->player->P1.position.x + 400, app->player->P1.position.y - 330 + 120 * i, 100, 100 };

		}*/
		if (Zbie[i].dead == false && x > 1005 && x < 1110 && y > -5 + 120 * i && y < 115 + 120 * i + 100 && app->input->GetMouseButtonDown(1) == KEY_DOWN && app->BTSystem->AttackPlayer != 0 && app->BTSystem->PlayerTurn == true && app->BTSystem->SpecialAttackEnable == false) {
			app->BTSystem->ZombieTarget = i;
			//SDL_Rect Enem1 = { app->player->P1.position.x + 500, app->player->P1.position.y - 330 + 120 * i, 100, 100 };
		}
	}
	for (int i = 1; i < Zbie[0].numEnemies + 1; i++) {//
		if (Zbie[i].dead == false && x > 1005 && x < 1110 && y > -5 + 120 * i && y < 115 + 120 * i + 100 && app->input->GetMouseButtonDown(1) == KEY_DOWN && app->BTSystem->PlayerTurn == true && app->BTSystem->SpecialAttackEnable == false && app->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT) {
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
				app->BTSystem->battle = false;
				app->BTSystem->battleWin = false;

			}
		}
		for (int i = 1; i < Zbie[0].numEnemies + 1; i++) {
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
						app->player->P1.hp -= Zbie[app->BTSystem->playerTarget].damage;
					} while (randomNumber <= Zbie[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;
				}
				if (app->BTSystem->playerTarget == 2 && app->player->P2.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						app->player->P2.hp -= Zbie[app->BTSystem->playerTarget].damage;
					} while (randomNumber <= Zbie[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;

				}
				if (app->BTSystem->playerTarget == 3 && app->player->P3.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						app->player->P3.hp -= Zbie[app->BTSystem->playerTarget].damage;
					} while (randomNumber <= Zbie[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;

				}
				if (app->BTSystem->playerTarget == 4 && app->player->P4.IsAlive == true) {
					int randomNumber = 0;
					do {
						randomNumber = (rand() % 100) + 1;
						app->player->P4.hp -= Zbie[app->BTSystem->playerTarget].damage;
					} while (randomNumber <= Zbie[app->BTSystem->playerTarget].speed);
					app->BTSystem->PlayerTurn = true;

				}

			}
		}
		app->BTSystem->alliesDead = 0;
	}
}

void ZombieEnem::CheckEnemy() {
	if (app->BTSystem->Zombiebattle == true) {

		for (int i = 1; i < Zbie[0].numEnemies + 1; i++) {
			if (Zbie[i].hp <= 0) {
				Zbie[i].dead = true;
				app->BTSystem->CombatDeaths += 1;
			}
			if (app->BTSystem->CombatDeaths == Zbie[0].numEnemies) {
				app->BTSystem->battle = false;
				app->BTSystem->Zombiebattle = false;
				app->BTSystem->battleWin = false;
				app->BTSystem->battle1 = false;

				Zbie[0].Destroyed = true;
				klk = true;
			}
		}
		app->BTSystem->CombatDeaths = 0;
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
				//Vpir[0].Destroyed = true;
			}
		}
		else if (Zbie[i].colliderS == c1 && !Zbie[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
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
	if (path == true && app->BTSystem->battle == false && app->BTSystem->Delay == true)
	{
		app->pathfinding->CreatePath(app->map->WorldToMap(Zbie[i].Pos.x, Zbie[i].Pos.y), app->map->WorldToMap(app->player->P1.position.x, app->player->P1.position.y));

		const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

		for (uint j = 0; j < path->Count(); ++j)
		{
			iPoint pos = app->map->MapToWorld(path->At(j)->x, path->At(j)->y);
			if (Zbie[i].Pos.x <= pos.x - 32 && timer3 > pathfindingtimer + enemySpeed)
			{
				pathfindingtimer = timer3;
				Zbie[i].Pos.x += 32;
			}
			if (Zbie[i].Pos.x >= pos.x + 32 && timer3 > pathfindingtimer + enemySpeed)
			{
				pathfindingtimer = timer3;
				Zbie[i].Pos.x -= 32;
			}
			if (Zbie[i].Pos.y <= pos.y - 32 && timer3 > pathfindingtimer + enemySpeed)
			{
				pathfindingtimer = timer3;
				Zbie[i].Pos.y += 32;
			}
			if (Zbie[i].Pos.y >= pos.y + 32 && timer3 > pathfindingtimer + enemySpeed)
			{
				pathfindingtimer = timer3;
				Zbie[i].Pos.y -= 32;
			}
		}

	}

}
Zombie ZombieEnem::CreateZombie(int x, int y, SDL_Texture* t)
{
	Zombie Zombies;

	Zombies.colliderZ = app->collisions->AddCollider({ x, y, 32, 32 }, Collider::Type::ZOMBIE, (Module*)app->entityManager);
	Zombies.colliderS = app->collisions->AddCollider({ x, y, 200, 200 }, Collider::Type::SENSOR, (Module*)app->entityManager);
	Zombies.zombieT = t;
	Zombies.Pos.x = x;
	Zombies.Pos.y = y;

	return Zombies;
}

