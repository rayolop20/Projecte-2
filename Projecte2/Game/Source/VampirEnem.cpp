#include "Entity.h"
#include "App.h"
#include "Textures.h"
#include "VampirEnem.h"
#include "EntityManager.h"
#include "Scene.h"
#include "Collisions.h"

#include "Log.h"
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
	
	for (int i = 0; i < NUM_VAMPIRE; i++)
	{
		currentAnimation[i]->Update();

		if (Vpir[i].Destroyed == true)
		{
			Vpir[i].dead = true;
			Vpir[i].colliderV->pendingToDelete = true;
		}
	}
	//SDL_Rect Vampyr = {200,200, 50, 50};
	//app->render->DrawRectangle(Vampyr, 0, 0, 255);

	return false;
}

bool VampirEnem::PostUpdate()
{
	for (int i = 0; i < NUM_VAMPIRE; i++)
	{

		app->render->DrawTexture(Vpir[i].vampireT, Vpir[i].x, Vpir[i].y, &(currentAnimation[i]->GetCurrentFrame()));
	
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
				LOG("FUNCIONA?");
				Vpir[i].Destroyed = true;
			}
		}
	}
}
Vampire VampirEnem::CreateVampire(int x, int y, SDL_Texture* t)
{
	Vampire Vampires;

	Vampires.colliderV = app->collisions->AddCollider({ x, y, 80, 80 }, Collider::Type::VAMPIRE, (Module*)app->entityManager);
	Vampires.vampireT = t;
	Vampires.x = x;
	Vampires.y = y;

	return Vampires;
}