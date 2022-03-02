#include "Entity.h"
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
	return false;
}

bool VampirEnem::PostUpdate()
{
	return false;
}

void VampirEnem::OnCollision(Collider* c1, Collider* c2)
{
}
