#include "EntityManager.h"
//#include "Item.h"
#include "App.h"
#include "VampirEnem.h"
#include "ZombieEnem.h"
#include "SkeletonEnem.h"
#include "EntityNPC.h"
#include "Entity.h"
#include "Defs.h"
#include "Log.h"

EntityManager::EntityManager() : Module()
{
	name.Create("entitymanager");
}

// Destructor
EntityManager::~EntityManager()
{}

// Called before render is available
bool EntityManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Entity Manager");
	bool ret = true;

	//L13: TODO 6: Initialize Entities from XML 

	return ret;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	bool ret = true;
	ListItem<Entity*>* item;
	item = entities.end;

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	entities.clear();

	return ret;
}

Entity* EntityManager::CreateEntity(EntityType type, int id, SDL_Rect bounds)
{
	Entity* entity = nullptr; 

	//L13:L13: TODO 1: Create an Entity and add it to the list of Entities
	switch (type)
	{
	case EntityType::VAMPYR:entity = new VampirEnem();
		break;
	case EntityType::ZOMBIE:entity = new ZombieEnem();
		break;
	case EntityType::SKELETON:entity = new SkeletonEnem();
		break;
	case EntityType::NPC:entity = new EntityNPC();
		break;
	case EntityType::GROUNDENEMY:
		break;
	case EntityType::ITEM:
		break;
	case EntityType::LIFE:
		break;
	case EntityType::UNKNOWN:
		break;
	default:
		break;
	}
	
	entity->Start();

	if (entity != nullptr) entities.add(entity);

	return entity;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	ListItem<Entity*>* item;

	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data == entity) entities.del(item);
	}
}

void EntityManager::AddEntity(Entity* entity)
{
	if ( entity != nullptr) entities.add(entity);
}

bool EntityManager::Update(float dt)
{

	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}
	entities[0]->PostUpdate();
	entities[1]->PostUpdate();
	entities[2]->PostUpdate();
	entities[3]->PostUpdate();
	return true;
}


bool EntityManager::UpdateAll(float dt, bool doLogic)
{

	bool ret = true;
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;


	if (doLogic)
	{
		for (item = entities.start; item != NULL && ret == true; item = item->next)
		{
			pEntity = item->data;
			if (pEntity->active == false) continue;
			ret = item->data->Update(dt);

		}
	}

	return ret;
}

bool EntityManager::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	ListItem<Entity*>* item;
	item = entities.start;

	while (item != NULL && ret == true)
	{
		ret = item->data->LoadState(data.child(item->data->name.GetString()));
		item = item->next;
	}

	return ret;
}

bool EntityManager::SaveState(pugi::xml_node& data)
{
	bool ret = true;

	ListItem<Entity*>* item;
	item = entities.start;

	while (item != NULL && ret == true)
	{
		data.append_child(item->data->name.GetString());
		ret = item->data->SaveState(data.child(item->data->name.GetString()));
		item = item->next;
	}

	return ret;
}

bool EntityManager::Draw() {

	bool ret = true;
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Draw(app->render);
	}

	return ret;

}

void EntityManager::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::VAMPIRE && c2->type == Collider::Type::PLAYER) {
		entities[0]->OnCollision(c1, c2);
	}
	if (c1->type == Collider::Type::ZOMBIE && c2->type == Collider::Type::PLAYER) {
		entities[1]->OnCollision(c1, c2);
	}
	if (c1->type == Collider::Type::NPC && c2->type == Collider::Type::PLAYER) {
		entities[2]->OnCollision(c1, c2);
	}
	if (c1->type == Collider::Type::SKELETON && c2->type == Collider::Type::PLAYER) {
		entities[3]->OnCollision(c1, c2);
	}
	if (c1->type == Collider::Type::SENSOR && c2->type == Collider::Type::PLAYER) {
		entities[0]->OnCollision(c1, c2);
		entities[1]->OnCollision(c1, c2);
		entities[2]->OnCollision(c1, c2);
		entities[3]->OnCollision(c1, c2);
	}
}