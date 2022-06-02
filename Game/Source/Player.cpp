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
#include "Menu.h"
#include "BattleSystem.h"
#include "CharacterMenu.h"
#include "EasingFunctions.h"

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


	idleAnim4.PushBack({ 39, 7, 49, 115 });
	idleAnim4.loop = true;
	idleAnim4.speed = 0.001f;

	downAnim4.PushBack({ 39, 7, 49, 115 });
	downAnim4.PushBack({ 167, 7, 49, 117 });
	downAnim4.PushBack({ 295, 7, 49, 115 });
	downAnim4.PushBack({ 423, 7, 49, 117 });
	downAnim4.loop = true;
	downAnim4.speed = 0.1f;

	leftAnim4.PushBack({ 555, 7, 44, 114 });
	leftAnim4.PushBack({ 683, 7, 44, 114 });
	leftAnim4.PushBack({ 811, 7, 44, 114 });
	leftAnim4.PushBack({ 939, 7, 44, 114 });
	leftAnim4.loop = true;
	leftAnim4.speed = 0.1f;
	
	rightAnim4.PushBack({ 1065, 7, 44, 114 });
	rightAnim4.PushBack({ 1193, 7, 44, 114 });
	rightAnim4.PushBack({ 1321, 7, 44, 114 });
	rightAnim4.PushBack({ 1449, 7, 44, 114 });
	rightAnim4.loop = true;
	rightAnim4.speed = 0.1f;

	upAnim4.PushBack({ 1575, 7, 49, 115 });
	upAnim4.PushBack({ 1703, 7, 49, 117 });
	upAnim4.PushBack({ 1831, 7, 49, 115 });
	upAnim4.PushBack({ 1959, 7, 49, 117 });
	upAnim4.loop = true;
	upAnim4.speed = 0.1f;
	
	idleAnim2.PushBack({ 39, 7, 49, 115 });
	idleAnim2.loop = true;
	idleAnim2.speed = 0.001f;

	downAnim2.PushBack({ 39, 7, 49, 115 });
	downAnim2.PushBack({ 167, 7, 49, 117 });
	downAnim2.PushBack({ 295, 7, 49, 115 });
	downAnim2.PushBack({ 423, 7, 49, 117 });
	downAnim2.loop = true;
	downAnim2.speed = 0.1f;

	leftAnim2.PushBack({ 535, 7, 64, 114 });
	leftAnim2.PushBack({ 663, 7, 64, 114 });
	leftAnim2.PushBack({ 791, 7, 64, 114 });
	leftAnim2.PushBack({ 919, 7, 64, 114 });
	leftAnim2.loop = true;
	leftAnim2.speed = 0.1f;
	
	rightAnim2.PushBack({ 1045, 7, 64, 114 });
	rightAnim2.PushBack({ 1173, 7, 64, 114 });
	rightAnim2.PushBack({ 1301, 7, 64, 114 });
	rightAnim2.PushBack({ 1429, 7, 64, 114 });
	rightAnim2.loop = true;
	rightAnim2.speed = 0.1f;

	upAnim2.PushBack({ 1575, 7, 49, 115 });
	upAnim2.PushBack({ 1703, 7, 49, 117 });
	upAnim2.PushBack({ 1831, 7, 49, 115 });
	upAnim2.PushBack({ 1959, 7, 49, 117 });
	upAnim2.loop = true;
	upAnim2.speed = 0.1f;
	
	idleAnim3.PushBack({ 40, 4, 42, 116 });
	idleAnim3.loop = true;
	idleAnim3.speed = 0.001f;

	downAnim3.PushBack({ 40, 4, 42, 116 });
	downAnim3.PushBack({ 168, 4, 42, 118 });
	downAnim3.PushBack({ 296, 4, 42, 116 });
	downAnim3.PushBack({ 424, 4, 42, 118 });
	downAnim3.loop = true;
	downAnim3.speed = 0.1f;

	leftAnim3.PushBack({ 563, 4, 29, 117 });
	leftAnim3.PushBack({ 691, 4, 29, 116 });
	leftAnim3.PushBack({ 819, 4, 29, 117 });
	leftAnim3.PushBack({ 944, 4, 32, 116 });
	leftAnim3.loop = true;
	leftAnim3.speed = 0.1f;
	
	rightAnim3.PushBack({ 1069, 4, 29, 117 });
	rightAnim3.PushBack({ 1197, 4, 29, 116 });
	rightAnim3.PushBack({ 1325, 4, 29, 117 });
	rightAnim3.PushBack({ 1453, 4, 32, 116 });
	rightAnim3.loop = true;
	rightAnim3.speed = 0.1f;

	upAnim3.PushBack({ 1576, 4, 42, 116 });
	upAnim3.PushBack({ 1704, 4, 42, 117 });
	upAnim3.PushBack({ 1831, 4, 42, 118 });
	upAnim3.PushBack({ 1960, 4, 42, 118 });
	upAnim3.loop = true;
	upAnim3.speed = 0.1f;
}

Player::~Player()
{

}

bool Player::LoadState(pugi::xml_node& data)
{
	//player 1
	P1.position.x = data.child("Player1").attribute("x").as_int();
	P1.position.y = data.child("Player1").attribute("y").as_int();
	P1.hp = data.child("Player1").attribute("Hp").as_int();
	P1.mana = data.child("Player1").attribute("mana").as_int();
	P1.IsAlive = data.child("Player1").attribute("IsAlive").as_bool();
	//player 2
	P2.position.x = data.child("Player2").attribute("x").as_int();
	P2.position.y = data.child("Player2").attribute("y").as_int();
	P2.hp = data.child("Player2").attribute("Hp").as_int();
	P2.mana = data.child("Player2").attribute("mana").as_int();
	P2.IsAlive = data.child("Player2").attribute("IsAlive").as_bool();
	//player 3
	P3.position.x = data.child("Player3").attribute("x").as_int();
	P3.position.y = data.child("Player3").attribute("y").as_int();
	P3.hp = data.child("Player3").attribute("Hp").as_int();
	P3.mana = data.child("Player3").attribute("mana").as_int();
	P3.IsAlive = data.child("Player3").attribute("IsAlive").as_bool();

	//player4
	P4.position.x = data.child("Player4").attribute("x").as_int();
	P4.position.y = data.child("Player4").attribute("y").as_int();
	P4.hp = data.child("Player4").attribute("Hp").as_int();
	P4.mana = data.child("Player4").attribute("mana").as_int();
	P4.IsAlive = data.child("Player4").attribute("IsAlive").as_bool();



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
	Pyr1.append_attribute("Hp") = app->player->P1.hp;
	Pyr1.append_attribute("mana") = app->player->P1.mana;
	Pyr1.append_attribute("IsAlive") = app->player->P1.IsAlive;
	//p2
	Pyr2.append_attribute("x") = app->player->P2.position.x;
	Pyr2.append_attribute("y") = app->player->P2.position.y;
	Pyr2.append_attribute("Hp") = app->player->P2.hp;
	Pyr2.append_attribute("mana") = app->player->P2.mana;
	Pyr2.append_attribute("IsAlive") = app->player->P2.IsAlive;

	//p3
	Pyr3.append_attribute("x") = app->player->P3.position.x;
	Pyr3.append_attribute("y") = app->player->P3.position.y;
	Pyr3.append_attribute("Hp") = app->player->P3.hp;
	Pyr3.append_attribute("mana") = app->player->P3.mana;
	Pyr3.append_attribute("IsAlive") = app->player->P3.IsAlive;
	//p4
	Pyr4.append_attribute("x") = app->player->P4.position.x;
	Pyr4.append_attribute("y") = app->player->P4.position.y;
	Pyr4.append_attribute("Hp") = app->player->P4.hp;
	Pyr4.append_attribute("mana") = app->player->P4.mana;
	Pyr4.append_attribute("IsAlive") = app->player->P4.IsAlive;
	return false;
}

bool Player::Awake(pugi::xml_node& config) {

	LOG("Loading Player");
	bool ret = true;
	
	//p1
	P1.position.x = config.child("Player1").attribute("PositionX").as_int();
	P1.position.y = config.child("Player1").attribute("PositionY").as_int();
	P1.mana = config.child("Player1").attribute("mana").as_int();
	P1.hp = config.child("Player1").attribute("Hp").as_int();
	P1.IsAlive = config.child("Player1").attribute("IsAlive").as_bool();
	//p2
	P2.position.x = config.child("Player2").attribute("PositionX").as_int();
	P2.position.y = config.child("Player2").attribute("PositionY").as_int();
	P2.mana = config.child("Player2").attribute("mana").as_int();
	P2.hp = config.child("Player2").attribute("Hp").as_int();
	P2.IsAlive = config.child("Player2").attribute("IsAlive").as_bool();
	//p3
	P3.position.x = config.child("Player3").attribute("PositionX").as_int();
	P3.position.y = config.child("Player3").attribute("PositionY").as_int();
	P3.mana = config.child("Player3").attribute("mana").as_int();
	P3.hp = config.child("Player3").attribute("Hp").as_int();
	P3.IsAlive = config.child("Player3").attribute("IsAlive").as_bool();
	//P4
	P4.position.x = config.child("Player4").attribute("PositionX").as_int();
	P4.position.y = config.child("Player4").attribute("PositionY").as_int();
	P4.mana = config.child("Player4").attribute("mana").as_int();
	P4.hp = config.child("Player4").attribute("Hp").as_int();
	P4.IsAlive = config.child("Player4").attribute("IsAlive").as_bool();

	return ret;
}

bool Player::Start()
{
	bool ret = true;

	currentAnim1 = &idleAnim1;
	currentAnim2 = &idleAnim2;
	currentAnim4 = &idleAnim4;
	currentAnim3 = &idleAnim3;

	//Pres E
	player1S = app->tex->Load("Assets/Textures/Soldiers/soldier.png");
	player4S = app->tex->Load("Assets/Textures/Soldiers/soldier_ita.png");
	player5S = app->tex->Load("Assets/Textures/Soldiers/french.png");
	player2S = app->tex->Load("Assets/Textures/Soldiers/us.png");
	player3S = app->tex->Load("Assets/Textures/Soldiers/rus.png");
	darkness = app->tex->Load("Assets/Textures/Fog/darkness.png");

	P1.Pcol = app->collisions->AddCollider({ P1.position.x,P1.position.y, 64, 90 }, Collider::Type::PLAYER, this);

	app->collisions->AddCollider({ P2.position.x, P2.position.y, 90, 90 }, Collider::Type::SENSOR_PLAYER2, this);

	app->collisions->AddCollider({ P3.position.x, P3.position.y, 90, 90 }, Collider::Type::SENSOR_PLAYER3, this);

	app->collisions->AddCollider({ P4.position.x, P4.position.y, 90, 90 }, Collider::Type::SENSOR_PLAYER4, this);
	return ret;
}

bool Player::Update(float dt)
{	
	if (app->BTSystem->battle == false && app->menu->config == false && P1.IsAlive == true && app->scene->puzzle3Active == true) {
		app->render->DrawTexture(darkness, P1.position.x - 608, P1.position.y - 360 + 32);
	}
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
		if (P2.IsAlive == true) {
			player2 = { P2.position.x, P2.position.y, 42, 42 };
			//app->render->DrawRectangle(player2, 100, 230, 200);
		}
		if (P3.IsAlive == true) {
			player3 = { P3.position.x, P3.position.y, 42, 42 };
			//app->render->DrawRectangle(player3, 100, 230, 200);
		}
		if (P4.IsAlive == true) {
			player4 = { P4.position.x, P4.position.y, 42, 42 };
			//app->render->DrawRectangle(player4, 100, 230, 200);
		}
	}


	// all textures
	{
		//player2
		if (P2.P2Active == true && app->menu->config == false)
		{
			app->render->DrawTexture(PE, P2.position.x - 20, P2.position.y - 100);
		}
		
		//player3
		if (P3.P3Active == true && app->menu->config == false)
		{
			app->render->DrawTexture(PE, P3.position.x - 20, P3.position.y - 100);
		}
		//player4
		if (P4.P4Active == true && app->menu->config == false)
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
			//godmode
			{
				if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN )
				{
					if (godMode == false)
					{
						godMode = true;
					} 
					else
					{
						godMode = false;
					}
				}
			}
			//left
			{
				if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && P1.moveXD == false && app->BTSystem->battle == false && P1.IsAlive == true)
				{
					P1.position.x += 3;
					P1.moveXA = true;
					block1 = false;
					block2 = true;
					block1_ = false;
					block2_ = true;
					currentAnim1 = &rightAnim1;
					if (P4.IsAlive == true) {
						currentAnim4 = &rightAnim4;
					}
					if (P2.IsAlive == true) {
						currentAnim2 = &rightAnim2;
					}
					
					if (P3.IsAlive == true) {
						currentAnim3 = &rightAnim3;
					}
				}

				if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP && P1.IsAlive == true)
				{
					P1.moveXA = false;
					currentAnim1 = &idleAnim1;
					if (P4.IsAlive == true) {
						currentAnim4 = &idleAnim4;
					}
					if (P2.IsAlive == true) {
						currentAnim2 = &idleAnim2;
					}
					
					if (P3.IsAlive == true) {
						currentAnim3 = &idleAnim3;
					}
				}
			}
			//right
			{
				if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && P1.moveXA == false && app->BTSystem->battle == false && P1.IsAlive == true)
				{
					P1.position.x -= 3;
					P1.moveXD = true;
					block1 = true;
					block2 = false;
					block1_ = true;
					block2_ = false;
					currentAnim1 = &leftAnim1;
					if (P4.IsAlive == true) {
						currentAnim4 = &leftAnim4;
					}
					if (P2.IsAlive == true) {
						currentAnim2 = &leftAnim2;
					}
					
					if (P3.IsAlive == true) {
						currentAnim3 = &leftAnim3;
					}
				}

				if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP && P1.IsAlive == true)
				{
					P1.moveXD = false;
					currentAnim1 = &idleAnim1;
					if (P4.IsAlive == true) {
						currentAnim4 = &idleAnim4;
					}
					if (P3.IsAlive == true) {
						currentAnim3 = &idleAnim3;
					}
					if (P2.IsAlive == true) {
						currentAnim2 = &idleAnim3;
					}
				}
			}
			//up
			{
				if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && P1.moveYW == false && app->BTSystem->battle == false && P1.IsAlive == true)
				{
					P1.position.y -= 3;
					P1.moveYS = true;
					currentAnim1 = &upAnim1;
					if (P2.IsAlive == true) {
						currentAnim2 = &upAnim2;
					}
					if (P3.IsAlive == true) {
						currentAnim3 = &upAnim3;
					}
					if (P4.IsAlive == true) {
						currentAnim4 = &upAnim4;
					}
					
					

				}

				if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP && P1.IsAlive == true)
				{
					P1.moveYS = false;
					currentAnim1 = &upAnim1;
					if (P2.IsAlive == true) {
						currentAnim2 = &upAnim2;
					}
					if (P3.IsAlive == true) {
						currentAnim3 = &upAnim3;
					}
					if (P4.IsAlive == true) {
						currentAnim4 = &upAnim4;
					}
				}
			}
			//down
			{
				if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && P1.moveYS == false && app->BTSystem->battle == false && P1.IsAlive == true)
				{
					P1.position.y += 3;
					P1.moveYW = true;
					if (P4.IsAlive == true) {
						currentAnim4 = &downAnim4;
					}
					if (P3.IsAlive == true) {
						currentAnim3 = &downAnim3;
					}
					if (P2.IsAlive == true) {
						currentAnim2 = &downAnim2;
					}
					currentAnim1 = &downAnim1;

					
					
				}

				if (app->input->GetKey(SDL_SCANCODE_S) == KEY_UP && P1.IsAlive == true)
				{
					P1.moveYW = false;
					currentAnim1 = &idleAnim1;
					if (P4.IsAlive == true) {
						currentAnim4 = &downAnim4;
					}
					if (P3.IsAlive == true) {
						currentAnim3 = &downAnim3;
					}
					if (P2.IsAlive == true) {
						currentAnim2 = &downAnim2;
					}
					currentAnim1 = &downAnim1;

				}
			}
		}
	}


	P1.Pcol->SetPos(P1.position.x, P1.position.y);


	return true;
}

bool Player::CleanUp()
{
	return false;
}

bool Player::PostUpdate()
{
	//draw player
	
	if (app->BTSystem->battle == false && app->menu->config == false && app->characterMenu->inventory == false) {
		player1 = currentAnim1->GetCurrentFrame();
		player2 = currentAnim2->GetCurrentFrame();
		player4 = currentAnim4->GetCurrentFrame();
		player3 = currentAnim3->GetCurrentFrame();
		if (P1.moveYS == false) {
			if (P4.IsAlive == true && app->BTSystem->battle1 == true) {
				app->render->DrawTexture(player4S, P4.position.x + 7, P4.position.y - 20, &player4);
				currentAnim4->Update();
			}
			if (P4.IsAlive == true && app->BTSystem->battle1 == false) {
				app->render->DrawTexture(player5S, P4.position.x + 7, P4.position.y - 20, &player4);
				currentAnim4->Update();
			}
			if (P3.IsAlive == true) {
				app->render->DrawTexture(player3S, P3.position.x + 7, P3.position.y - 20, &player3);
				currentAnim3->Update();
			}
			if (P2.IsAlive == true) {
				app->render->DrawTexture(player2S, P2.position.x + 7, P2.position.y - 20, &player2);
				currentAnim2->Update();
			}
			if (P1.IsAlive == true) {
				app->render->DrawTexture(player1S, P1.position.x + 7, P1.position.y - 20, &player1);
				currentAnim1->Update();
			}
		}
		else {
			if (P1.IsAlive == true) {
				app->render->DrawTexture(player1S, P1.position.x + 7, P1.position.y - 20, &player1);
				currentAnim1->Update();
			}
			if (P2.IsAlive == true) {
				app->render->DrawTexture(player2S, P2.position.x + 7, P2.position.y - 20, &player2);
				currentAnim2->Update();
			}
			if (P3.IsAlive == true) {
				app->render->DrawTexture(player3S, P3.position.x + 7, P3.position.y - 20, &player3);
				currentAnim3->Update();
			}
			if (P4.IsAlive == true && app->BTSystem->battle1 == true) {
				app->render->DrawTexture(player4S, P4.position.x + 7, P4.position.y - 20, &player4);
				currentAnim4->Update();
			}
			if (P4.IsAlive == true && app->BTSystem->battle1 == false) {
				app->render->DrawTexture(player5S, P4.position.x + 7, P4.position.y - 20, &player4);
				currentAnim4->Update();
			}
		}

		
	}

	return true;
}



void Player::OnCollision(Collider* c1, Collider* c2)
{
	if (godMode == false)
	{
		if ((c1 == P1.Pcol))
		{
			//walls
			{
				if (c1->type == Collider::Type::PLAYER && (c2->type == Collider::Type::WALLV || c2->type == Collider::Type::KEY_SENSOR))
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
				if (c1->type == Collider::Type::PLAYER && (c2->type == Collider::Type::WALLH || c2->type == Collider::Type::KEY_SENSOR))
				{

					if (c2->type == Collider::Type::KEY_SENSOR && door3active == true) {
						door3active_ = true;
					}
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
					if (!app->BTSystem->transitionLock)
					{
						//app->BTSystem->battle = true;
						app->BTSystem->battleTransition = true;
					}
				}
			}
			{
				if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ZOMBIE && app->BTSystem->Delay == true)
				{
					if (!app->BTSystem->transitionLock)
					{
						//app->BTSystem->battle = true;
						app->BTSystem->battleTransition = true;
					}
				}
			}
			{
				if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SKELETON && app->BTSystem->Delay == true)
				{
					if (!app->BTSystem->transitionLock)
					{
						//app->BTSystem->battle = true;
						app->BTSystem->battleTransition = true;
					}
				}
			}
			{
				if (c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::VAMPIRE && app->BTSystem->Delay && c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::ZOMBIE && c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::SKELETON && !app->BTSystem->battle)
				{
					app->BTSystem->transitionRep = 1;
					app->BTSystem->transitionLock = false;
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
				if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::PRESSURE_PLATE1 && app->scene->pressurePlate1 == true)
				{
					app->scene->pressurePlate1 = false;
					app->scene->pressurePlateTimer1 = app->scene->pressurePlateTimer1_;
				}
				if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::PRESSURE_PLATE2 && app->scene->pressurePlate2 == true)
				{
					app->scene->pressurePlate2 = false;
					app->scene->pressurePlateTimer2 = app->scene->pressurePlateTimer2_;
				}
				if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::PRESSURE_PLATE3 && app->scene->pressurePlate3 == true)
				{
					app->scene->pressurePlate3 = false;
					app->scene->pressurePlateTimer3 = app->scene->pressurePlateTimer3_;
				}
				if (app->scene->phase == 5 && app->scene->maxPhase >= 5 && app->scene->End5 == false && app->scene->timerphase2_ > app->scene->timerphase2 + 1) {
					app->scene->timerphase2 = app->scene->timerphase2_;
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON1 && app->scene->sixthSimon == 1)
					{
						app->scene->phase = 6;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON2 && app->scene->sixthSimon == 2)
					{
						app->scene->phase = 6;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON3 && app->scene->sixthSimon == 3)
					{
						app->scene->phase = 6;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON4 && app->scene->sixthSimon == 4)
					{
						app->scene->phase = 6;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON5 && app->scene->sixthSimon == 5)
					{
						app->scene->phase = 6;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON6 && app->scene->sixthSimon == 6)
					{
						app->scene->phase = 6;
					}
					if (app->scene->phase == 5) {
						app->scene->End2 = true;
						app->scene->End1 = true;
						app->scene->End3 = true;
						app->scene->End4 = true;
						app->scene->End5 = true;
						app->scene->End6 = true;
						app->scene->phase = 0;
						app->scene->prepared = false;
						app->scene->maxPhase = 0;
					}
				}
				if (app->scene->phase == 4 && app->scene->maxPhase >= 4 && app->scene->End4 == false && app->scene->timerphase2_ > app->scene->timerphase2 + 1) {
					app->scene->timerphase2 = app->scene->timerphase2_;
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON1 && app->scene->fifthSimon == 1)
					{
						app->scene->End4 = true;
						app->scene->phase = 5;
						app->scene->maxPhase = 5;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON2 && app->scene->fifthSimon == 2)
					{
						app->scene->End4 = true;
						app->scene->phase = 5;
						app->scene->maxPhase = 5;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON3 && app->scene->fifthSimon == 3)
					{
						app->scene->End4 = true;
						app->scene->phase = 5;
						app->scene->maxPhase = 5;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON4 && app->scene->fifthSimon == 4)
					{
						app->scene->End4 = true;
						app->scene->phase = 5;
						app->scene->maxPhase = 5;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON5 && app->scene->fifthSimon == 5)
					{
						app->scene->End4 = true;
						app->scene->phase = 5;
						app->scene->maxPhase = 5;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON6 && app->scene->fifthSimon == 6)
					{
						app->scene->End4 = true;
						app->scene->phase = 5;
						app->scene->maxPhase = 5;
					}
					if (app->scene->phase == 4) {
						app->scene->End2 = true;
						app->scene->End1 = true;
						app->scene->End3 = true;
						app->scene->End4 = true;
						app->scene->End5 = true;
						app->scene->End6 = true;
						app->scene->phase = 0;
						app->scene->prepared = false;
						app->scene->maxPhase = 0;
					}
				}
				if (app->scene->phase == 3 && app->scene->maxPhase >= 3 && app->scene->End3 == false && app->scene->timerphase2_ > app->scene->timerphase2 + 1) {
					app->scene->timerphase2 = app->scene->timerphase2_;
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON1 && app->scene->fourthSimon == 1)
					{
						app->scene->End3 = true;
						app->scene->phase = 4;
						app->scene->maxPhase = 4;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON2 && app->scene->fourthSimon == 2)
					{
						app->scene->End3 = true;
						app->scene->maxPhase = 4;
						app->scene->phase = 4;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON3 && app->scene->fourthSimon == 3)
					{
						app->scene->End3 = true;
						app->scene->maxPhase = 4;
						app->scene->phase = 4;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON4 && app->scene->fourthSimon == 4)
					{
						app->scene->End3 = true;
						app->scene->maxPhase = 4;
						app->scene->phase = 4;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON5 && app->scene->fourthSimon == 5)
					{
						app->scene->End3 = true;
						app->scene->maxPhase = 4;
						app->scene->phase = 4;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON6 && app->scene->fourthSimon == 6)
					{
						app->scene->End3 = true;
						app->scene->maxPhase = 4;
						app->scene->phase = 4;
					}
					if (app->scene->phase == 3) {
						app->scene->End2 = true;
						app->scene->End1 = true;
						app->scene->End3 = true;
						app->scene->End4 = true;
						app->scene->End5 = true;
						app->scene->End6 = true;
						app->scene->phase = 0;
						app->scene->prepared = false;
						app->scene->maxPhase = 0;
					}
				}
				if (app->scene->phase == 2 && app->scene->maxPhase >= 2 && app->scene->End2 == false && app->scene->timerphase2_ > app->scene->timerphase2 + 1) {
					app->scene->timerphase2 = app->scene->timerphase2_;
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON1 && app->scene->thirdSimon == 1)
					{
						app->scene->End2 = true;
						app->scene->phase = 3;
						app->scene->maxPhase = 3;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON2 && app->scene->thirdSimon == 2)
					{
						app->scene->End2 = true;
						app->scene->maxPhase = 3;
						app->scene->phase = 3;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON3 && app->scene->thirdSimon == 3)
					{
						app->scene->End2 = true;
						app->scene->maxPhase = 3;
						app->scene->phase = 3;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON4 && app->scene->thirdSimon == 4)
					{
						app->scene->End2 = true;
						app->scene->maxPhase = 3;
						app->scene->phase = 3;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON5 && app->scene->thirdSimon == 5)
					{
						app->scene->End2 = true;
						app->scene->maxPhase = 3;
						app->scene->phase = 3;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON6 && app->scene->thirdSimon == 6)
					{
						app->scene->End2 = true;
						app->scene->maxPhase = 3;
						app->scene->phase = 3;
					}
					if (app->scene->phase == 2) {
						app->scene->End2 = true;
						app->scene->End1 = true;
						app->scene->End3 = true;
						app->scene->End4 = true;
						app->scene->End5 = true;
						app->scene->End6 = true;
						app->scene->phase = 0;
						app->scene->prepared = false;
						app->scene->maxPhase = 0;
					}
				}

				if (app->scene->phase == 1 && app->scene->maxPhase >= 1 && app->scene->End1 == false && app->scene->timerphase2_ > app->scene->timerphase2 + 1) {
					app->scene->timerphase2 = app->scene->timerphase2_;
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON1 && app->scene->secondSimon == 1)
					{
						app->scene->End1 = true;
						app->scene->phase = 2;
						app->scene->maxPhase = 2;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON2 && app->scene->secondSimon == 2)
					{
						app->scene->End1 = true;
						app->scene->maxPhase = 2;
						app->scene->phase = 2;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON3 && app->scene->secondSimon == 3)
					{
						app->scene->End1 = true;
						app->scene->maxPhase = 2;
						app->scene->phase = 2;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON4 && app->scene->secondSimon == 4)
					{
						app->scene->End1 = true;
						app->scene->maxPhase = 2;
						app->scene->phase = 2;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON5 && app->scene->secondSimon == 5)
					{
						app->scene->End1 = true;
						app->scene->maxPhase = 2;
						app->scene->phase = 2;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON6 && app->scene->secondSimon == 6)
					{
						app->scene->End1 = true;
						app->scene->maxPhase = 2;
						app->scene->phase = 2;
					}
					if (app->scene->phase == 1) {
						app->scene->End2 = true;
						app->scene->End1 = true;
						app->scene->End3 = true;
						app->scene->End4 = true;
						app->scene->End5 = true;
						app->scene->End6 = true;
						app->scene->phase = 0;
						app->scene->prepared = false;
						app->scene->maxPhase = 0;
					}
				}
				if (app->scene->phase == 0) {
					app->scene->timerphase2 = app->scene->timerphase2_;
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON1 && app->scene->firstSimon == 1)
					{
						app->scene->maxPhase = 1;
						app->scene->phase = 1;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON2 && app->scene->firstSimon == 2)
					{
						app->scene->maxPhase = 1;
						app->scene->phase = 1;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON3 && app->scene->firstSimon == 3)
					{
						app->scene->maxPhase = 1;
						app->scene->phase = 1;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON4 && app->scene->firstSimon == 4)
					{
						app->scene->maxPhase = 1;
						app->scene->phase = 1;

					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON5 && app->scene->firstSimon == 5)
					{
						app->scene->phase = 1;
						app->scene->maxPhase = 1;
					}
					if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SIMON6 && app->scene->firstSimon == 6)
					{
						app->scene->phase = 1;
						app->scene->maxPhase = 1;
					}
					if (app->scene->phase == 0) {
						app->scene->End2 = true;
						app->scene->End1 = true;
						app->scene->End3 = true;
						app->scene->End4 = true;
						app->scene->End5 = true;
						app->scene->End6 = true;
						app->scene->phase = 0;
						app->scene->prepared = false;
						app->scene->maxPhase = 0;
					}
				}
				if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::TORCH1 && app->scene->puzzle3Active == true && app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && app->scene->Quest3active == true)
				{
					if (app->scene->tester1 == true) {
						if (app->scene->torchCount1 == 5) {
							app->scene->torchCount1 = 0;
						}
						app->scene->torchCount1++;
					}
					app->scene->tester1 = false;
				}
				else {
					app->scene->tester1 = true;
				}
				if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::TORCH2 && app->scene->puzzle3Active == true && app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && app->scene->Quest3active == true)
				{
					if (app->scene->tester2 == true) {
						if (app->scene->torchCount2 == 5) {
							app->scene->torchCount2 = 0;
						}
						app->scene->torchCount2++;
					}
					app->scene->tester2 = false;
				}
				else {
					app->scene->tester2 = true;
				}
				if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::TORCH3 && app->scene->puzzle3Active == true && app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && app->scene->Quest3active == true)
				{
					if (app->scene->tester3 == true) {

						if (app->scene->torchCount3 == 5) {
							app->scene->torchCount3 = 0;
						}
						app->scene->torchCount3++;
					}
					app->scene->tester3 = false;
				}
				else {
					app->scene->tester3 = true;
				}
				if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::TORCH4 && app->scene->puzzle3Active == true && app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && app->scene->Quest3active == true)
				{
					if (app->scene->tester4 == true) {
						if (app->scene->torchCount4 == 5) {
							app->scene->torchCount4 = 0;
						}
						app->scene->torchCount4++;
					}
					app->scene->tester4 = false;
				}
				else {
					app->scene->tester4 = true;
				}
				
			}
		}
	}
}



void Player::movementPlayer()
{
	//Player 2
	if (P2.Move == true && P2.IsAlive == true)
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
	else if(app->menu->config == false && P2.IsAlive == false){
		app->render->DrawTexture(app->characterMenu->americanNpc, 1780, 2410);
	}
	//Player 3
	if (P3.Move == true && P3.IsAlive == true)
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

	else if (app->menu->config == false && P3.IsAlive == false) {
		app->render->DrawTexture(app->characterMenu->russianNpc, 1777, 2252);
	}
	//Player 4
	if (P4.Move == true && P4.IsAlive == true)
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
	else if (app->menu->config == false && P4.IsAlive == false && app->BTSystem->battle1 == true && P4.hp >0) {
		app->render->DrawTexture(app->characterMenu->italianNpc, 1613, 2410);
	}
}

float Player::EaseCameraBetweenPoints(iPoint posA, iPoint posB)
{
	float value = function.backEaseOut(iterations, posA.x, posB.x - posA.x, total_iterations);


	//speedY = function.linearEaseNull(iterations, 472, 572, 300);

	//App->render->camera.y += speedY;

	if (iterations < total_iterations) {
		iterations++;
	}

	else {
		iterations = 0;
		easing_active = false;
	}

	return value;
}