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

	return ret;
}

bool Player::Update(float dt)
{


	return true;
}

bool Player::PostUpdate()
{
	//draw player

	return true;
}


void Player::OnCollision(Collider* c1, Collider* c2)
{
	

}

