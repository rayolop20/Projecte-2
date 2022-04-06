#include "Entity.h"
#include "App.h"
#include "Textures.h"
#include "EntityManager.h"
#include "GuiManager.h"
#include "Scene.h"
#include "Collisions.h"
#include "Player.h"
#include "PathFinding.h"
#include "Map.h"
#include "EntityNPC.h"
#include "Window.h"

#include "Log.h"
#include "DynArray.h"
#include "BattleSystem.h"
#include <time.h>

EntityNPC::EntityNPC() :Entity(EntityType::NPC)
{
	name.Create("NPC");
	
	idle.PushBack({ 5, 6, 16, 17 });
	idle.PushBack({ 28, 6, 12, 17 });
	idle.PushBack({ 11, 29, 5, 16 });
	idle.PushBack({ 28, 28, 12, 17 });
	idle.loop = true;
	idle.speed = 0.001f;
	
}

EntityNPC::~EntityNPC()
{
	name.Create("NPC");
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
bool EntityNPC::Start()
{

	TextureNPC = app->tex->Load("Assets/textures/coins.png");
	//coinFx = app->audio->LoadFx("Assets/audio/fx/coin.wav");


	for (int i = 0; i < NUM_NPC; i++)
	{
		currentAnimation[i] = &idle;
	}

	npc[0] = CreateNPC(500, 500, TextureNPC);

	return false;
}

bool EntityNPC::Update(float dt)
{
	
	for (int i = 0; i < NUM_NPC; i++)
	{
		currentAnimation[i]->Update();

		if (npc[i].Destroyed == true)
		{
			npc[i].dead = true;
			npc[i].colliderNPC->pendingToDelete = true;
		}
	}
	for (int i = 0; i < 1; i++)
	{
		npc[i].colliderNPC->SetPos(npc[i].Pos.x, npc[i].Pos.y);
		npc[i].colliderSNPC->SetPos(npc[i].Pos.x - 32, npc[i].Pos.y - 32);
	}
	return true;
}



bool EntityNPC::PostUpdate()
{
	LOG("FUNCIONA?");
	for (int i = 0; i < NUM_NPC; i++)
	{
		if (npc[i].dead == false)
		{
			app->render->DrawTexture(npc[i].NPCT, npc[i].Pos.x, npc[i].Pos.y, &(currentAnimation[i]->GetCurrentFrame()));
		}
	}
	return true;
}



void EntityNPC::OnCollision(Collider* c1, Collider* c2)
{

	for (uint i = 0; i < NUM_NPC; ++i)
	{
		if (npc[i].colliderNPC == c1 && !npc[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
				//Vpir[0].Destroyed = true;
				LOG("Polla");
			}
		}
		else if (npc[i].colliderSNPC == c1 && !npc[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
				LOG("Polla");
			}
		}
	}
	
}



NPC EntityNPC::CreateNPC(int x, int y, SDL_Texture* t)
{
	NPC Npc;

	Npc.colliderNPC = app->collisions->AddCollider({ x, y, 32, 32 }, Collider::Type::NPC, (Module*)app->entityManager);
	Npc.colliderSNPC = app->collisions->AddCollider({ x, y, 96, 96 }, Collider::Type::SENSOR, (Module*)app->entityManager);
	Npc.NPCT = t;
	Npc.Pos.x = x;
	Npc.Pos.y = y;

	return Npc;
}

