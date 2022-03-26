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

	Vpir[0] = CreateVampire(200, 200, TextureVampire);

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
	Vpir->colliderV->SetPos(Vpir->Pos.x, Vpir->Pos.x);
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
		app->pathfinding->CreatePath(app->map->WorldToMap(Vpir->Pos.x, Vpir->Pos.x), app->map->WorldToMap(app->player->P1.position.x, app->player->P1.position.y));

		const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			if (Vpir->Pos.x <= pos.x)
			{
				Vpir->Pos.x++;
			}
			if (Vpir->Pos.x >= pos.x)
			{
				Vpir->Pos.x--;
			}
			
		}
	}
	
}
Vampire VampirEnem::CreateVampire(int x, int y, SDL_Texture* t)
{
	Vampire Vampires;

	Vampires.colliderV = app->collisions->AddCollider({ x, y, 80, 80 }, Collider::Type::VAMPIRE, (Module*)app->entityManager);
	Vampires.vampireT = t;
	Vampires.Pos.x = x;
	Vampires.Pos.y = y;

	return Vampires;
}

