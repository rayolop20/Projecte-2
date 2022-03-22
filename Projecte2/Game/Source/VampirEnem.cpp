#include "Entity.h"
#include "App.h"
#include "Textures.h"
#include "VampirEnem.h"
#include "EntityManager.h"
#include "Collisions.h"

VampirEnem::VampirEnem():Entity (EntityType::VAMPYRENEM)
{
	name.Create("VampirEnem");

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

	TextureVampire = app->tex->Load("Assets/Textures/test.png");
	//coinFx = app->audio->LoadFx("Assets/audio/fx/coin.wav");


	for (int i = 0; i < NUM_VAMPIRE; i++)
	{
		//currentAnimation[i] = &idle;
	}

	Vpir[0] = CreateVampire(200, 200, TextureVampire);

	return false;
}

bool VampirEnem::Update(float dt)
{
	
	for (int i = 0; i < NUM_VAMPIRE; i++)
	{
		//currentAnimation[i]->Update();

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

