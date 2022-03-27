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

	Vpir[0] = CreateVampire(32, 32, TextureVampire);

	return false;
}

bool VampirEnem::Update(float dt)
{
	PathFindVamp();
	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		path = true;
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
	Vpir->colliderV->SetPos(Vpir->Pos.x, Vpir->Pos.y);
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
	}
}

void VampirEnem::PathFindVamp()
{
	if (path == true)
	{
		for (uint i = 0; i < NUM_VAMPIRE; ++i)
		{
			app->pathfinding->CreatePath(app->map->WorldToMap(Vpir[i].Pos.x, Vpir[i].Pos.y), app->map->WorldToMap(app->player->P1.position.x, app->player->P1.position.y));

			const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

			for (uint j = 0; j < path->Count(); ++j)
			{
				iPoint pos = app->map->MapToWorld(path->At(j)->x, path->At(j)->y);
				if (Vpir[i].Pos.x <= pos.x)
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
				}

			}
		}
	}
	
}
Vampire VampirEnem::CreateVampire(int x, int y, SDL_Texture* t)
{
	Vampire Vampires;

	Vampires.colliderV = app->collisions->AddCollider({ x, y, 32, 32 }, Collider::Type::VAMPIRE, (Module*)app->entityManager);
	Vampires.vampireT = t;
	Vampires.Pos.x = x;
	Vampires.Pos.y = y;

	return Vampires;
}

