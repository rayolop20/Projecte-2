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

	P1.position.x = config.child("Position").attribute("PositionX").as_int();
	P1.position.y = config.child("Position").attribute("PositionY").as_int();

	return ret;
}

bool Player::Start()
{
	bool ret = true;
	P1.Pcol = app->collisions->AddCollider({ P1.position.x,P1.position.y, 100, 100 }, Collider::Type::PLAYER, this);
	Wall = app->collisions->AddCollider({ 500,500, 100, 100 }, Collider::Type::WALL, this);

	return ret;
}

bool Player::Update(float dt)
{
	
	player = { P1.position.x,P1.position.y, 100, 100 };
	app->render->DrawRectangle(player, 200, 200, 200);

	//movement
	{
		//left
		{
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && P1.MoveXD == false)
			{
				P1.position.x++;
				P1.MoveXA = true;
			}

			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
			{
				P1.MoveXA = false;
			}
		}
		//right
		{
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && P1.MoveXA == false)
			{
				P1.position.x--;
				P1.MoveXD = true;
			}

			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
			{
				P1.MoveXD = false;
			}
		}
		//up
		{
			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && P1.MoveYW == false)
			{
				P1.position.y--;
				P1.MoveYS = true;
			}

			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
			{
				P1.MoveYS = false;
			}
		}
		//down
		{
			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && P1.MoveYS == false)
			{
				P1.position.y++;
				P1.MoveYW = true;
			}

			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
			{
				P1.MoveYW = false;
			}
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		app->collisions->DebugDraw();
	}
	P1.Pcol->SetPos(P1.position.x, P1.position.y);

	return true;
}

bool Player::PostUpdate()
{
	//draw player

	return true;
}



void Player::OnCollision(Collider* c1, Collider* c2)
{
	if ((c1 == P1.Pcol))
	{

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL)
		{
			if (c1->rect.x < c2->rect.x && c1->rect.x + 64 > c2->rect.x && P1.MoveXA == true)//Esquerra
			{
				P1.position.x = c2->rect.x - 64;
			}
			if (c1->rect.x > c2->rect.x && c1->rect.x + 64 > c2->rect.x && P1.MoveXA == false)//Adalt
			{
				P1.position.x = c2->rect.x + 32;
			}

			if (c1->rect.y < c2->rect.y && c1->rect.y + 64 > c2->rect.y && P1.MoveXA == false)//Dreta
			{
				P1.position.y = c2->rect.y - 64;
			}

			if (c1->rect.y > c2->rect.y && c1->rect.y + 64 > c2->rect.y && P1.MoveXA == false)//Abaix
			{
				P1.position.y = c2->rect.y + 32;
			}
		}


	}
}

