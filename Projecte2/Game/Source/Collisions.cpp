#include "Collisions.h"

#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Scene.h"
#include "SString.h"
#include "GuiManager.h"


Collisions::Collisions() : Module()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALLH][Collider::Type::WALLH] = false;
	matrix[Collider::Type::WALLH][Collider::Type::WALLV] = false;
	matrix[Collider::Type::WALLH][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALLH][Collider::Type::VAMPIRE] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::WALLH] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WALLV] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::VAMPIRE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::SENSOR] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SENSOR_PLAYER] = true;
	
	
	matrix[Collider::Type::WALLV][Collider::Type::WALLV] = false;
	matrix[Collider::Type::WALLV][Collider::Type::WALLH] = false;
	matrix[Collider::Type::WALLV][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALLV][Collider::Type::VAMPIRE] = true;
	
	matrix[Collider::Type::VAMPIRE][Collider::Type::WALLV] = true;
	matrix[Collider::Type::VAMPIRE][Collider::Type::WALLH] = true;
	matrix[Collider::Type::VAMPIRE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::VAMPIRE][Collider::Type::VAMPIRE] = false;

	matrix[Collider::Type::SENSOR][Collider::Type::WALLV] = false;
	matrix[Collider::Type::SENSOR][Collider::Type::WALLH] = false;
	matrix[Collider::Type::SENSOR][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SENSOR][Collider::Type::VAMPIRE] = false;
	matrix[Collider::Type::SENSOR][Collider::Type::SENSOR] = false;
	
	matrix[Collider::Type::SENSOR_PLAYER][Collider::Type::WALLV] = false;
	matrix[Collider::Type::SENSOR_PLAYER][Collider::Type::WALLH] = false;
	matrix[Collider::Type::SENSOR_PLAYER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SENSOR_PLAYER][Collider::Type::VAMPIRE] = false;
	matrix[Collider::Type::SENSOR_PLAYER][Collider::Type::SENSOR] = false;
	matrix[Collider::Type::SENSOR_PLAYER][Collider::Type::SENSOR_PLAYER] = false;
}

// Destructor
Collisions::~Collisions()
{

}



bool Collisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// Skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// Avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// Skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

bool Collisions::Update()
{

	return true;
}

bool Collisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	if (app->scene->paused)
		app->guiManager->Draw();

	return true;
}

void Collisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE: // white
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::WALLH: // blue
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case Collider::Type::WALLV: // blue
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case Collider::Type::PLAYER: // green
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::VAMPIRE: // RED
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::SENSOR: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::SENSOR_PLAYER: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool Collisions::CleanUp()
{


	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* Collisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void Collisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}