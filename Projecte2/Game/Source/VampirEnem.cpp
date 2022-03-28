#include "Entity.h"
#include "App.h"
#include "Textures.h"
#include "VampirEnem.h"
#include "EntityManager.h"
#include "Scene.h"
#include "Collisions.h"
#include "Player.h"
#include "PathFinding.h"
#include "Map.h"

#include "Log.h"
#include "DynArray.h"
#include "BattleSystem.h"
#include <time.h>

VampirEnem::VampirEnem():Entity (EntityType::VAMPYRENEM)
{
	name.Create("VampirEnem");
	idle.PushBack({ 5, 6, 16, 17 });
	idle.PushBack({ 28, 6, 12, 17 });
	idle.PushBack({ 11, 29, 5, 16 });
	idle.PushBack({ 28, 28, 12, 17 });
	idle.loop = true;
	idle.speed = 0.001f;
}

VampirEnem::~VampirEnem()
{
}

bool VampirEnem::Awake(pugi::xml_node&)
{
	return false;
}

bool VampirEnem::Start()
{

	TextureVampire = app->tex->Load("Assets/textures/coins.png");
	//coinFx = app->audio->LoadFx("Assets/audio/fx/coin.wav");


	for (int i = 0; i < NUM_VAMPIRE; i++)
	{
		currentAnimation[i] = &idle;
	}

	Vpir[0] = CreateVampire(320, 320, TextureVampire);

	return false;
}

bool VampirEnem::Update(float dt)
{
	Combat();
	
	timer3 = SDL_GetTicks() / 10;

	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		if (pathfindingaux == true) {
			pathfindingtimer = timer3;
			pathfindingaux = false;
		}
		path = true;
	}
	if (Vpir[0].hp < 0) {
		app->BTSystem->battle = false;
	}
	for (int i = 0; i < NUM_VAMPIRE; i++)
	{
		currentAnimation[i]->Update();

		if (Vpir[i].Destroyed == true)
		{
			Vpir[i].dead = true;
			Vpir[i].colliderV->pendingToDelete = true;
		}
	}
	for (int i = 0; i < 1; i++)
	{
		Vpir[i].colliderV->SetPos(Vpir[i].Pos.x, Vpir[i].Pos.y);
		Vpir[i].colliderS->SetPos(Vpir[i].Pos.x - 84, Vpir[i].Pos.y - 84);
	}
	return true;
}



bool VampirEnem::PostUpdate()
{
	LOG("FUNCIONA?");
	for (int i = 0; i < NUM_VAMPIRE; i++)
	{
		if (Vpir[i].dead == false) 
		{
		app->render->DrawTexture(Vpir[i].vampireT, Vpir[i].Pos.x, Vpir[i].Pos.y, &(currentAnimation[i]->GetCurrentFrame()));
		}
	}
	return true;
}

void VampirEnem::Combat() {
	if (app->BTSystem->AttackType == 1 && app->BTSystem->AttackPlayer == 1 && app->BTSystem->randomAux == true) {
		Vpir[0].hp -= app->player->P1.damage1;
		app->player->P1.mana += app->player->P1.mana1;
		srand((unsigned)time(NULL));
		int randomNumber;
		randomNumber = (rand() % 100) + 1;
		if (randomNumber > app->player->P1.speed + app->player->P1.speed1) {
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
		}
		else {
		}
	}
	if (app->BTSystem->AttackType == 2 && app->BTSystem->AttackPlayer == 1 && app->BTSystem->randomAux == true) {
		Vpir[0].hp -= app->player->P1.damage2;
		app->player->P1.mana += app->player->P1.mana2;
		srand((unsigned)time(NULL));
		int randomNumber;
		randomNumber = (rand() % 100) + 1;
		if (randomNumber > app->player->P1.speed + app->player->P1.speed2) {
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
		}
	}
	if (app->BTSystem->AttackType == 1 && app->BTSystem->AttackPlayer == 2 && app->BTSystem->randomAux == true) {
		Vpir[0].hp -= app->player->P2.damage1;
		app->player->P2.mana += app->player->P2.mana1;
		srand((unsigned)time(NULL));
		int randomNumber;
		randomNumber = (rand() % 100) + 1;
		if (randomNumber > app->player->P2.speed + app->player->P2.speed1) {
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
		}
		else {
		}
	}
	if (app->BTSystem->AttackType == 2 && app->BTSystem->AttackPlayer == 2 && app->BTSystem->randomAux == true) {
		Vpir[0].hp -= app->player->P2.damage2;
		app->player->P2.mana += app->player->P2.mana2;
		srand((unsigned)time(NULL));
		int randomNumber;
		randomNumber = (rand() % 100) + 1;
		if (randomNumber > app->player->P2.speed + app->player->P2.speed2) {
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
		}
	}
	if (app->BTSystem->AttackType == 1 && app->BTSystem->AttackPlayer == 3 && app->BTSystem->randomAux == true) {
		Vpir[0].hp -= app->player->P3.damage1;
		app->player->P3.mana += app->player->P3.mana1;
		srand((unsigned)time(NULL));
		int randomNumber;
		randomNumber = (rand() % 100) + 1;
		if (randomNumber > app->player->P3.speed + app->player->P3.speed1) {
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
		}
		else {
		}
	}
	if (app->BTSystem->AttackType == 2 && app->BTSystem->AttackPlayer == 3 && app->BTSystem->randomAux == true) {
		Vpir[0].hp -= app->player->P3.damage2;
		app->player->P3.mana += app->player->P3.mana2;
		srand((unsigned)time(NULL));
		int randomNumber;
		randomNumber = (rand() % 100) + 1;
		if (randomNumber > app->player->P3.speed + app->player->P3.speed2) {
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
		}
	}
	
	if (app->BTSystem->AttackType == 1 && app->BTSystem->AttackPlayer == 4 && app->BTSystem->randomAux == true) {
		Vpir[0].hp -= app->player->P4.damage1;
		app->player->P4.mana += app->player->P4.mana1;
		srand((unsigned)time(NULL));
		int randomNumber;
		randomNumber = (rand() % 100) + 1;
		if (randomNumber > app->player->P4.speed + app->player->P4.speed1) {
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
		}
		else {
		}
	}
	if (app->BTSystem->AttackType == 2 && app->BTSystem->AttackPlayer == 4 && app->BTSystem->randomAux == true) {
		Vpir[0].hp -= app->player->P4.damage2;
		app->player->P4.mana += app->player->P4.mana2;
		srand((unsigned)time(NULL));
		int randomNumber;
		randomNumber = (rand() % 100) + 1;
		if (randomNumber > app->player->P4.speed + app->player->P4.speed2) {
			app->BTSystem->randomAux = false;
			app->BTSystem->AttackPlayer = 0;
			app->BTSystem->AttackType = 0;
			app->BTSystem->AttackPhaseActive = false;
			app->BTSystem->AttackPhaseEnable = false;
			app->BTSystem->ChoosePlayerPhase = true;
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
				Vpir[i].Destroyed = true;
			}
		}
		else if (Vpir[i].colliderS == c1 && !Vpir[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
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
	if (path == true && app->BTSystem->battle == false)
	{
		

		if (timer3 > pathfindingtimer + 1 && pathfindingaux == false) {
			int klk = 0;
		}
			app->pathfinding->CreatePath(app->map->WorldToMap(Vpir[i].Pos.x, Vpir[i].Pos.y), app->map->WorldToMap(app->player->P1.position.x, app->player->P1.position.y));

			const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

			for (uint j = 0; j < path->Count(); ++j)
			{
				iPoint pos = app->map->MapToWorld(path->At(j)->x, path->At(j)->y);
				if (Vpir[i].Pos.x <= pos.x - 32 && timer3 > pathfindingtimer + enemySpeed)
				{
					pathfindingtimer = timer3;
					Vpir[i].Pos.x+=32;
				}
				if (Vpir[i].Pos.x >= pos.x + 32 && timer3 > pathfindingtimer + enemySpeed)
				{
					pathfindingtimer = timer3;
					Vpir[i].Pos.x-=32;
				}
				if (Vpir[i].Pos.y <= pos.y - 32 &&  timer3 > pathfindingtimer + enemySpeed)
				{
					pathfindingtimer = timer3;
					Vpir[i].Pos.y+=32;
				}
				if (Vpir[i].Pos.y >= pos.y + 32 && timer3 > pathfindingtimer + enemySpeed)
				{
					pathfindingtimer = timer3;
					Vpir[i].Pos.y-=32;
				}
				/*if (Vpir[i].Pos.x <= pos.x)
                {
                    Vpir[i].Pos.x++;
                }
                if (Vpir[i].Pos.x >= pos.x)
                {
                    Vpir[i].Pos.x--;
                }
                if (Vpir[i].Pos.y <= pos.y)
                {
                    Vpir[i].Pos.y++;
                }
                if (Vpir[i].Pos.y >= pos.y)
                {
                    Vpir[i].Pos.y--;
                }*/
			}
		
	}
	
}
Vampire VampirEnem::CreateVampire(int x, int y, SDL_Texture* t)
{
	Vampire Vampires;

	Vampires.colliderV = app->collisions->AddCollider({ x, y, 32, 32 }, Collider::Type::VAMPIRE, (Module*)app->entityManager);
	Vampires.colliderS = app->collisions->AddCollider({ x, y, 200, 200 }, Collider::Type::SENSOR, (Module*)app->entityManager);
	Vampires.vampireT = t;
	Vampires.Pos.x = x;
	Vampires.Pos.y = y;

	return Vampires;
}

