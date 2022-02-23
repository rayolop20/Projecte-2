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
	P1.Pcol = app->collisions->AddCollider({ P1.position.x,P1.position.y, 100, 100 }, Collider::Type::PLAYER, this);
	return ret;
}

bool Player::Update(float dt)
{
	player = { P1.position.x,P1.position.y, 100, 100 };
	app->render->DrawRectangle(player, 200, 200, 200);

	//movement
	{
		//left
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			P1.position.x++;
		}

		//right
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			P1.position.x--;
		}

		//up
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			P1.position.y--;
		}

		//down
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			P1.position.y++;
		}
	}

	//debug
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_IDLE)
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
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.
	
}

