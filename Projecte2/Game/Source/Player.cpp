#include "Player.h"

#include "App.h"
#include "Textures.h"
#include "Animation.h"
#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Collisions.h"
#include "Scene.h"

#include "Map.h"
#include "Defs.h"
#include "Log.h"

Player::Player() : Module()
{
	name.Create("player");

}

Player::~Player()
{

}

bool Player::Awake(pugi::xml_node& config) {

	LOG("Loading Player");
	bool ret = true;

	return ret;
}

bool Player::Start()
{
	bool ret = true;
	P.Pcol = app->collisions->AddCollider({ P.position.x,P.position.y, 100, 100 }, Collider::Type::PLAYER, this);
	Wall = app->collisions->AddCollider({ 500,500, 100, 100 }, Collider::Type::WALL, this);

	return ret;
}

bool Player::Update(float dt)
{
	player = { P.position.x,P.position.y, 100, 100 };
	app->render->DrawRectangle(player, 200, 200, 200);

	//movement
	{
		//left
		{
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && P.MoveXD == false)
			{
				P.position.x++;
				P.MoveXA = true;
			}

			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
			{
				P.MoveXA = false;
			}
		}
		//right
		{
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && P.MoveXA == false)
			{
				P.position.x--;
				P.MoveXD = true;
			}

			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
			{
				P.MoveXD = false;
			}
		}
		//up
		{
			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && P.MoveYW == false)
			{
				P.position.y--;
				P.MoveYS = true;
			}

			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
			{
				P.MoveYS = false;
			}
		}
		//down
		{
			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && P.MoveYS == false)
			{
				P.position.y++;
				P.MoveYW = true;
			}

			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
			{
				P.MoveYW = false;
			}
		}
	}

	//debug
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_IDLE)
	{
		app->collisions->DebugDraw();
	}

	P.Pcol->SetPos(P.position.x, P.position.y);

	return true;
}

bool Player::PostUpdate()
{
	//draw player

	return true;
}


void Player::OnCollision(Collider* c1, Collider* c2)
{
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.
	if (c1 == P.Pcol && c2 == Wall)
	{
		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL)
		{
			if (c1->rect.x <= c2->rect.x)
			{
				P.MoveXD = true;
			}
		}
	}
}

