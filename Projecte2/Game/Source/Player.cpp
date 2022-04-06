#include "Player.h"

#include "App.h"
#include "Textures.h"
#include "Animation.h"
#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Collisions.h"
#include "PathFinding.h"
#include "Map.h"
#include "EntityManager.h"
#include "Scene.h"
#include "BattleSystem.h"

#include "Defs.h"
#include "Log.h"

Player::Player() : Module()
{
	name.Create("players");
	idleAnim1.PushBack({ 39, 7, 49, 115 });
	idleAnim1.loop = true;
	idleAnim1.speed = 0.001f;

	downAnim1.PushBack({ 39, 7, 49, 115 });
	downAnim1.PushBack({ 167, 7, 49, 117 });
	downAnim1.PushBack({ 295, 7, 49, 115 });
	downAnim1.PushBack({ 423, 7, 49, 117 });
	downAnim1.loop = true;
	downAnim1.speed = 0.1f;

	leftAnim1.PushBack({ 555, 7, 44, 114 });
	leftAnim1.PushBack({ 683, 7, 44, 114 });
	leftAnim1.PushBack({ 811, 7, 44, 114 });
	leftAnim1.PushBack({ 939, 7, 44, 114 });
	leftAnim1.loop = true;
	leftAnim1.speed = 0.1f;
	
	rightAnim1.PushBack({ 1065, 7, 44, 114 });
	rightAnim1.PushBack({ 1193, 7, 44, 114 });
	rightAnim1.PushBack({ 1321, 7, 44, 114 });
	rightAnim1.PushBack({ 1449, 7, 44, 114 });
	rightAnim1.loop = true;
	rightAnim1.speed = 0.1f;

	upAnim1.PushBack({ 1575, 7, 49, 115 });
	upAnim1.PushBack({ 1703, 7, 49, 117 });
	upAnim1.PushBack({ 1831, 7, 49, 115 });
	upAnim1.PushBack({ 1959, 7, 49, 117 });
	upAnim1.loop = true;
	upAnim1.speed = 0.1f;

	/*	idleAnim1.PushBack({ 0, 0, 28, 64});
	idleAnim1.loop = true;
	idleAnim1.speed = 0.001f;

	downAnim1.PushBack({ 0, 0, 28, 64 });
	downAnim1.PushBack({ 71, 0, 29, 64});
	downAnim1.PushBack({ 143, 7, 29, 64 });
	downAnim1.PushBack({ 215, 7, 29, 64 });*/
}

Player::~Player()
{

}

bool Player::LoadState(pugi::xml_node& data)
{
	//player 1
	P1.position.x = data.child("Player1").attribute("x").as_int();
	P1.position.y = data.child("Player1").attribute("y").as_int();
	//player 2
	P2.position.x = data.child("Player2").attribute("x").as_int();
	P2.position.y = data.child("Player2").attribute("y").as_int();
	//player 3
	P3.position.x = data.child("Player3").attribute("x").as_int();
	P3.position.y = data.child("Player3").attribute("y").as_int();
	//player4
	P4.position.x = data.child("Player4").attribute("x").as_int();
	P4.position.y = data.child("Player4").attribute("y").as_int();
	return false;
}

bool Player::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node Pyr1 = data.append_child("Player1");
	pugi::xml_node Pyr2 = data.append_child("Player2");
	pugi::xml_node Pyr3 = data.append_child("Player3");
	pugi::xml_node Pyr4 = data.append_child("Player4");
	//p1
	Pyr1.append_attribute("x") = app->player->P1.position.x;
	Pyr1.append_attribute("y") = app->player->P1.position.y;
	//p2
	Pyr2.append_attribute("x") = app->player->P2.position.x;
	Pyr2.append_attribute("y") = app->player->P2.position.y;
	//p3
	Pyr3.append_attribute("x") = app->player->P3.position.x;
	Pyr3.append_attribute("y") = app->player->P3.position.y;
	//p4
	Pyr4.append_attribute("x") = app->player->P4.position.x;
	Pyr4.append_attribute("y") = app->player->P4.position.y;
	return false;
}

bool Player::Awake(pugi::xml_node& config) {

	LOG("Loading Player");
	bool ret = true;
	
	//p1
	P1.position.x = config.child("Player1").attribute("PositionX").as_int();
	P1.position.y = config.child("Player1").attribute("PositionY").as_int();
	//p2
	P2.position.x = config.child("Player2").attribute("PositionX").as_int();
	P2.position.y = config.child("Player2").attribute("PositionY").as_int();
	//p3
	P3.position.x = config.child("Player3").attribute("PositionX").as_int();
	P3.position.y = config.child("Player3").attribute("PositionY").as_int();
	//P4
	P4.position.x = config.child("Player4").attribute("PositionX").as_int();
	P4.position.y = config.child("Player4").attribute("PositionY").as_int();

	resetPlayerPos.x = config.child("Player1").attribute("PositionX").as_int();
	resetPlayerPos.y = config.child("Player1").attribute("PositionY").as_int();

	return ret;
}

bool Player::Start()
{
	bool ret = true;

	currentAnim1 = &idleAnim1;

	//Pres E
	player1Hp = app->tex->Load("Assets/UI/hpbarplayertest.png");
	player2Hp = app->tex->Load("Assets/UI/hpbarplayertest2.png");
	player3Hp = app->tex->Load("Assets/UI/hpbarplayertest3.png");
	player4Hp = app->tex->Load("Assets/UI/hpbarplayertest4.png");
	PE = app->tex->Load("Assets/UI/UiIcons.png");
	player1S = app->tex->Load("Assets/textures/soldier.png");
	darkness = app->tex->Load("Assets/textures/darkness.png");

	P1.Pcol = app->collisions->AddCollider({ P1.position.x,P1.position.y, 64, 90 }, Collider::Type::PLAYER, this);

	P2.Player2C = app->collisions->AddCollider({ P2.position.x, P2.position.y, 90, 90 }, Collider::Type::SENSOR_PLAYER2, this);

	P3.Player3C = app->collisions->AddCollider({ P3.position.x, P3.position.y, 90, 90 }, Collider::Type::SENSOR_PLAYER3, this);

	P4.Player4C = app->collisions->AddCollider({ P3.position.x, P3.position.y, 90, 90 }, Collider::Type::SENSOR_PLAYER4, this);
	return ret;
}

bool Player::Update(float dt)
{
	app->render->DrawTexture(darkness, P1.position.x - 608, P1.position.y - 360 + 32);
	//imputs
	{
		if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		{
			app->collisions->DebugDraw();
		}
	}
	//Players
	{
		//player1 = { P1.position.x,P1.position.y, 64, 64 };
		//app->render->DrawRectangle(player1, 200, 200, 200);
	
		player2 = { P2.position.x, P2.position.y, 42, 42 };
		app->render->DrawRectangle(player2, 100, 230, 200);
		
		player3 = { P3.position.x, P3.position.y, 42, 42 };
		app->render->DrawRectangle(player3, 100, 230, 200);

		player4 = { P4.position.x, P4.position.y, 42, 42 };
		app->render->DrawRectangle(player4, 100, 230, 200);
	}


	// all textures
	{
		//player2
		if (P2.P2Active == true)
		{
			app->render->DrawTexture(PE, P2.position.x - 20, P2.position.y - 100);
		}
		
		//player3
		if (P3.P3Active == true)
		{
			app->render->DrawTexture(PE, P3.position.x - 20, P3.position.y - 100);
		}
		//player4
		if (P4.P4Active == true)
		{
			app->render->DrawTexture(PE, P4.position.x - 20, P4.position.y - 100);
		}
	}

	//Path Players
	movementPlayer();

	//movement
	{
		if (!app->scene->paused)
		{
			//left
			{
				if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && P1.moveXD == false && app->BTSystem->battle == false)
				{
					P1.position.x += 3;
					P1.moveXA = true;
					block1 = false;
					block2 = true;
					block1_ = false;
					block2_ = true;
					currentAnim1 = &rightAnim1;
				}

				if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
				{
					P1.moveXA = false;
					currentAnim1 = &idleAnim1;
				}
			}
			//right
			{
				if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && P1.moveXA == false && app->BTSystem->battle == false)
				{
					P1.position.x -= 3;
					P1.moveXD = true;
					block1 = true;
					block2 = false;
					block1_ = true;
					block2_ = false;
					currentAnim1 = &leftAnim1;
				}

				if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
				{
					P1.moveXD = false;
					currentAnim1 = &idleAnim1;
				}
			}
			//up
			{
				if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && P1.moveYW == false && app->BTSystem->battle == false)
				{
					P1.position.y -= 3;
					P1.moveYS = true;
					currentAnim1 = &upAnim1;
				}

				if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
				{
					P1.moveYS = false;
					currentAnim1 = &idleAnim1;
				}
			}
			//down
			{
				if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && P1.moveYS == false && app->BTSystem->battle == false)
				{
					P1.position.y += 3;
					P1.moveYW = true;
					currentAnim1 = &downAnim1;
				}

				if (app->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
				{
					P1.moveYW = false;
					currentAnim1 = &idleAnim1;
				}
			}
		}
	}


	P1.Pcol->SetPos(P1.position.x, P1.position.y);

	P2.Player2C->SetPos(P2.position.x - 21, P2.position.y - 21);

	P3.Player3C->SetPos(P3.position.x - 21, P3.position.y - 21);

	P4.Player4C->SetPos(P4.position.x - 21, P4.position.y - 21);

	return true;
}

bool Player::PostUpdate()
{
	//draw player
	player1 = currentAnim1->GetCurrentFrame();

	app->render->DrawTexture(player1S, P1.position.x + 7, P1.position.y - 20, &player1);

	currentAnim1->Update();

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
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::VAMPIRE && app->BTSystem->Delay == true)
			{
				app->BTSystem->battle = true;
			}
		}
		{
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ZOMBIE && app->BTSystem->Delay == true)
			{
				app->BTSystem->battle = true;
			}
		}

		//Sensors
		{
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SENSOR_PLAYER2 && P2.Move == false)
			{
				if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
				{
					P2.Move = true;
					P2.P2Active = false;
					P2.IsAlive = true;
				}
				if (P2.Move == false)
				{
					P2.P2Active = true;
				}
			}
			
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SENSOR_PLAYER3 && P3.Move == false)
			{
				if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
				{
					P3.Move = true;
					P3.P3Active = false;
					P3.IsAlive = true;
				}
				if (P3.Move == false)
				{
					P3.P3Active = true;
				}
			}
			
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SENSOR_PLAYER4 && P4.Move == false)
			{
				if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
				{
					P4.Move = true;
					P4.P4Active = false;
					P4.IsAlive = true;
				}
				if (P4.Move == false)
				{
					P4.P4Active = true;
				}

			}

		}
	}

	

}



void Player::movementPlayer()
{
	//Player 2
	if (P2.Move == true)
	{
		if (P2.IsAlive == true)
		{
			app->pathfinding->CreatePath(app->map->WorldToMap(P2.position.x, P2.position.y), app->map->WorldToMap(app->player->P1.position.x + 32, app->player->P1.position.y + 32));

			const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

			for (uint j = 0; j < path->Count(); ++j)
			{
				iPoint pos = app->map->MapToWorld(path->At(j)->x, path->At(j)->y);

				if (P2.position.x <= pos.x)
				{
					P2.position.x++;
				}
				if (P2.position.x >= pos.x)
				{
					P2.position.x--;
				}
				if (P2.position.y <= pos.y)
				{
					P2.position.y++;
				}
				if (P2.position.y >= pos.y)
				{
					P2.position.y--;
				}
			}
		
		}

	}
	//Player 3
	if (P3.Move == true)
	{
		if (P2.IsAlive == true)
		{
			app->pathfinding->CreatePath(app->map->WorldToMap(P3.position.x, P3.position.y), app->map->WorldToMap(app->player->P2.position.x + 32, app->player->P2.position.y + 32));
		}
		else if (P2.IsAlive == false)
		{
			app->pathfinding->CreatePath(app->map->WorldToMap(P3.position.x, P3.position.y), app->map->WorldToMap(app->player->P1.position.x + 32, app->player->P1.position.y + 32));
		}
			const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

			for (uint j = 0; j < path->Count(); ++j)
			{
				iPoint pos = app->map->MapToWorld(path->At(j)->x, path->At(j)->y);

				if (P3.position.x <= pos.x)
				{
					P3.position.x++;
				}
				if (P3.position.x >= pos.x)
				{
					P3.position.x--;
				}
				if (P3.position.y <= pos.y)
				{
					P3.position.y++;
				}
				if (P3.position.y >= pos.y)
				{
					P3.position.y--;
				}
			}
	}
	//Player 4
	if (P4.Move == true)
	{
		if (P2.IsAlive == true && P3.IsAlive == false)
		{
			app->pathfinding->CreatePath(app->map->WorldToMap(P4.position.x, P4.position.y), app->map->WorldToMap(app->player->P2.position.x + 32, app->player->P2.position.y + 32));
		}
		else if (P2.IsAlive == false && P3.IsAlive == true)
		{
			app->pathfinding->CreatePath(app->map->WorldToMap(P4.position.x, P4.position.y), app->map->WorldToMap(app->player->P3.position.x + 32, app->player->P3.position.y + 32));
		}
		else if (P2.IsAlive == true && P3.IsAlive == true)
		{
			app->pathfinding->CreatePath(app->map->WorldToMap(P4.position.x, P4.position.y), app->map->WorldToMap(app->player->P3.position.x + 32, app->player->P3.position.y + 32));
		}
		else if (P2.IsAlive == false && P3.IsAlive == false)
		{
			app->pathfinding->CreatePath(app->map->WorldToMap(P4.position.x, P4.position.y), app->map->WorldToMap(app->player->P1.position.x + 32, app->player->P1.position.y + 32));
		}
			const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

			for (uint j = 0; j < path->Count(); ++j)
			{
				iPoint pos = app->map->MapToWorld(path->At(j)->x, path->At(j)->y);

				if (P4.position.x <= pos.x)
				{
					P4.position.x++;
				}
				if (P4.position.x >= pos.x)
				{
					P4.position.x--;
				}
				if (P4.position.y <= pos.y)
				{
					P4.position.y++;
				}
				if (P4.position.y >= pos.y)
				{
					P4.position.y--;
				}
			}
	}
}

