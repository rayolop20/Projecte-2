#include "Entity.h"
#include "App.h"
#include "VampirEnem.h"
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


	return false;
}

bool VampirEnem::Update(float dt)
{
	SDL_Rect Vampyr = {100, 100, 150, 150};
	app->render->DrawRectangle(Vampyr, 255, 0, 255);
	return false;
}

