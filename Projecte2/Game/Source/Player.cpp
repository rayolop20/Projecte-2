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

	resetPlayerPos.x = config.child("Position").attribute("PositionX").as_int();
	resetPlayerPos.y = config.child("Position").attribute("PositionY").as_int();

	return ret;
}

bool Player::Start()
{
	bool ret = true;
	
	P1.Pcol = app->collisions->AddCollider({ P1.position.x,P1.position.y, 64, 64 }, Collider::Type::PLAYER, this);
	return ret;
}

bool Player::Update(float dt)
{
	
	player = { P1.position.x,P1.position.y, 64, 64 };
	app->render->DrawRectangle(player, 200, 200, 200);

	//movement
	if(!app->scene->paused)
	{
		//left
		{
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && P1.moveXD == false)
			{
				P1.position.x +=3;
				P1.moveXA = true;
				block1 = false;
				block2 = true;
				block1_ = false;
				block2_ = true;
			}

			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
			{
				P1.moveXA = false;
			}
		}
		//right
		{
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && P1.moveXA == false)
			{
				P1.position.x-=3;
				P1.moveXD = true;
				block1 = true;
				block2 = false;
				block1_ = true;
				block2_ = false;
			}

			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
			{
				P1.moveXD = false;
			}
		}
		//up
		{
			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && P1.moveYW == false)
			{
				P1.position.y-=3;
				P1.moveYS = true;
			}

			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
			{
				P1.moveYS = false;
			}
		}
		//down
		{
			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && P1.moveYS == false)
			{
				P1.position.y+=3;
				P1.moveYW = true;
			}

			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
			{
				P1.moveYW = false;
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
		//walls
		{
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALLV)
			{

				if (c1->rect.x < c2->rect.x && c1->rect.x + 64 > c2->rect.x && P1.moveXA == true && block1 == false && block2 == true)//Esquerra
				{
					P1.position.x = c2->rect.x - 64;
					block1 = false;
				}
				else {
					block1 = true;
				}

				if (c1->rect.x > c2->rect.x && c1->rect.x + 64 > c2->rect.x && P1.moveXD == true && block1 == true && block2 == false && block3 == true && block4 == true)//Dreta
				{
					P1.position.x = c2->rect.x + 32;
					block2 = false;
				}
				else {
					block2 = true;
				}

				if (c1->rect.y < c2->rect.y && c1->rect.y + 64 > c2->rect.y && P1.moveYW == true && block1 == true && block2 == true)//Adalt
				{
					P1.position.y = c2->rect.y - 64;
					block3 = false;
				}
				else {
					block3 = true;
				}

				if (c1->rect.y > c2->rect.y && c1->rect.y + 64 > c2->rect.y && P1.moveYS == true && block1 == true && block2 == true)//Abaix
				{
					P1.position.y = c2->rect.y + 32;
					block4 = false;
				}
				else {
					block4 = true;
				}

			}
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALLH)
			{

				if (c1->rect.x < c2->rect.x && c1->rect.x + 64 > c2->rect.x && P1.moveXA == true && block1_ == false && block2_ == true)//Esquerra
				{
					P1.position.x = c2->rect.x - 64;
					block1_ = false;
				}
				else {
					block1_ = true;
				}

				if (c1->rect.x > c2->rect.x && c1->rect.x + 64 > c2->rect.x && P1.moveXD == true && block1_ == true && block2_ == false && block3_ == true && block4_ == true)//Dreta
				{
					P1.position.x = c2->rect.x + 32;
					block2_ = false;
				}
				else {
					block2_ = true;
				}

				if (c1->rect.y < c2->rect.y && c1->rect.y + 64 > c2->rect.y && P1.moveYW == true && block1_ == true && block2_ == true)//Adalt
				{
					P1.position.y = c2->rect.y - 64;
					block3_ = false;
				}
				else {
					block3_ = true;
				}

				if (c1->rect.y > c2->rect.y && c1->rect.y + 64 > c2->rect.y && P1.moveYS == true && block1_ == true && block2_ == true)//Abaix
				{
					P1.position.y = c2->rect.y + 32;
					block4_ = false;
				}
				else {
					block4_ = true;
				}

			}
		}

		//Enemies
		{
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::VAMPIRE)
			{
				P1.position.x + 100;
			}
		}
	}

}

