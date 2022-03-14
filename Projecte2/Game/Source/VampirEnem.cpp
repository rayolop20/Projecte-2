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
	Vpir.position.x = 150;
	Vpir.position.y = 150;

	Vpir.Vcol = app->collisions->AddCollider({ Vpir.position.x,Vpir.position.y, 50, 50 }, Collider::Type::VAMPIRE);


	return false;
}

bool VampirEnem::Update(float dt)
{
	SDL_Rect Vampyr = { Vpir.position.x,Vpir.position.y, 50, 50};
	app->render->DrawRectangle(Vampyr, 0, 0, 255);

	return false;
}

