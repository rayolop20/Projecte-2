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
	matrix[Collider::Type::PLAYER][Collider::Type::ZOMBIE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SKELETON] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::NPC] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::SENSOR] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SENSOR_PLAYER2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SENSOR_PLAYER3] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SENSOR_PLAYER4] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PRESSURE_PLATE1] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PRESSURE_PLATE2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PRESSURE_PLATE3] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SIMON1] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SIMON2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SIMON3] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SIMON4] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SIMON5] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SIMON6] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::TORCH1] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::TORCH2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::TORCH3] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::TORCH4] = true;
	
	matrix[Collider::Type::PLAYER][Collider::Type::WIN] = true;
	matrix[Collider::Type::WIN][Collider::Type::PLAYER] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::KEY_SENSOR] = true;
	matrix[Collider::Type::KEY_SENSOR][Collider::Type::PLAYER] = true;
	
	matrix[Collider::Type::WALLV][Collider::Type::WALLV] = false;
	matrix[Collider::Type::WALLV][Collider::Type::WALLH] = false;
	matrix[Collider::Type::WALLV][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALLV][Collider::Type::VAMPIRE] = true;
	
	matrix[Collider::Type::VAMPIRE][Collider::Type::WALLV] = true;
	matrix[Collider::Type::VAMPIRE][Collider::Type::WALLH] = true;
	matrix[Collider::Type::VAMPIRE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::VAMPIRE][Collider::Type::ZOMBIE] = false;
	matrix[Collider::Type::VAMPIRE][Collider::Type::VAMPIRE] = false;

	matrix[Collider::Type::ZOMBIE][Collider::Type::WALLV] = true;
	matrix[Collider::Type::ZOMBIE][Collider::Type::WALLH] = true;
	matrix[Collider::Type::ZOMBIE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ZOMBIE][Collider::Type::VAMPIRE] = false;
	matrix[Collider::Type::ZOMBIE][Collider::Type::ZOMBIE] = false;

	matrix[Collider::Type::SKELETON][Collider::Type::WALLV] = true;
	matrix[Collider::Type::SKELETON][Collider::Type::WALLH] = true;
	matrix[Collider::Type::SKELETON][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SKELETON][Collider::Type::VAMPIRE] = false;
	matrix[Collider::Type::SKELETON][Collider::Type::ZOMBIE] = false;
	matrix[Collider::Type::SKELETON][Collider::Type::SKELETON] = false;

	matrix[Collider::Type::NPC][Collider::Type::WALLV] = true;
	matrix[Collider::Type::NPC][Collider::Type::WALLH] = true;
	matrix[Collider::Type::NPC][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::NPC][Collider::Type::VAMPIRE] = true;
	matrix[Collider::Type::NPC][Collider::Type::NPC] = false;

	matrix[Collider::Type::SENSOR][Collider::Type::WALLV] = false;
	matrix[Collider::Type::SENSOR][Collider::Type::WALLH] = false;
	matrix[Collider::Type::SENSOR][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SENSOR][Collider::Type::VAMPIRE] = false;
	matrix[Collider::Type::SENSOR][Collider::Type::SENSOR] = false;
	
	matrix[Collider::Type::SENSOR_PLAYER2][Collider::Type::WALLV] = false;
	matrix[Collider::Type::SENSOR_PLAYER2][Collider::Type::WALLH] = false;
	matrix[Collider::Type::SENSOR_PLAYER2][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SENSOR_PLAYER2][Collider::Type::VAMPIRE] = false;
	matrix[Collider::Type::SENSOR_PLAYER2][Collider::Type::SENSOR] = false;
	matrix[Collider::Type::SENSOR_PLAYER2][Collider::Type::SENSOR_PLAYER2] = false;
	
	matrix[Collider::Type::SENSOR_PLAYER3][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SENSOR_PLAYER3][Collider::Type::VAMPIRE] = false;
	matrix[Collider::Type::SENSOR_PLAYER3][Collider::Type::SENSOR] = false;
	matrix[Collider::Type::SENSOR_PLAYER3][Collider::Type::SENSOR_PLAYER3] = false;
	
	matrix[Collider::Type::SENSOR_PLAYER4][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SENSOR_PLAYER4][Collider::Type::VAMPIRE] = false;
	matrix[Collider::Type::SENSOR_PLAYER4][Collider::Type::SENSOR] = false;
	matrix[Collider::Type::SENSOR_PLAYER4][Collider::Type::SENSOR_PLAYER4] = false;
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
		case Collider::Type::ZOMBIE: // RED
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case Collider::Type::SKELETON: // GREEN
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::NPC: // Green
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::SENSOR: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::KEY_SENSOR: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::PRESSURE_PLATE1: // YELLOW
			if (app->scene->pressurePlate1 == true) {
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			}
			else {
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			}
		case Collider::Type::PRESSURE_PLATE2: // YELLOW
			if (app->scene->pressurePlate2 == true) {
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			}
			else {
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			}
		case Collider::Type::PRESSURE_PLATE3: // YELLOW
			if (app->scene->pressurePlate3 == true) {
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			}
			else {
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			}
		case Collider::Type::SIMON1: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::SIMON2: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::SIMON3: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::SIMON4: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::SIMON5: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::SIMON6: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;

		case Collider::Type::SENSOR_PLAYER2: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::SENSOR_PLAYER3: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::SENSOR_PLAYER4: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::WIN: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
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