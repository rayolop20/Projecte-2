#include "Entity.h"
#include "App.h"
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
	Vpir.position.x = 200;
	Vpir.position.y = 200;

	app->entityManager->Vcol = app->collisions->AddCollider({ 200,200, 50, 50 }, Collider::Type::VAMPIRE, (Module*)app->entityManager);

	return false;
}

bool VampirEnem::Update(float dt)
{
	SDL_Rect Vampyr = {200,200, 50, 50};
	app->render->DrawRectangle(Vampyr, 0, 0, 255);

	return false;
}

