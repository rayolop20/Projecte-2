#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

struct playr1
{
	//British
	iPoint position;
	Collider* Pcol = nullptr;
	bool moveXD = false, moveXA = false, moveYW = false, moveYS = false;
	bool IsAlive = true;
	float hp = 75.0;
	float speed1 = 15.0;
	float speed2 = 5.0;
	float luck = 0.0;
	float mana1 = 20.0;
	float mana2 = 30.0;
	float damage1 = 20.0;
	float damage2 = 12.0;
	float speed = 0.0;
	float mana = 0.0;
	float damage = 0.0;
	

};

struct playr2
{
	//French
	bool IsAlive = false;
	float hp = 40.0;
	float speed1 = 5.0;
	float speed2 = 15.0;
	float luck = 0.0;
	float mana1 = 35.0;
	float mana2 = 35.0;
	float damage1 = 15.0;
	float damage2 = 20.0;
	float speed = 0.0;
	float mana = 0.0;
	float damage = 0.0;
	
};

struct playr3
{
	//Russian
	bool IsAlive = true;
	float hp = 45.0;
	float speed1 = 0.0;
	float speed2 = 10.0;
	float luck = 0.0;
	float mana1 = 25.0;
	float mana2 = 20.0;
	float damage1 = 40.0;
	float damage2 = 12.0;
	float speed = 0.0;
	float mana = 0.0;
	float damage = 0.0;
};

struct playr4
{
	//Italian
	bool IsAlive = true;
	float hp = 50.0;
	float speed1 = 15.0;
	float speed2 = 10.0;
	float luck = 0.0;
	float mana1 = 30.0;
	float mana2 = 40.0;
	float damage1 = 10.0;
	float damage2 = 15.0;
	float speed = 0.0;
	float mana = 0.0;
	float damage = 0.0;
};

struct playr5
{
	//American
	bool IsAlive = true;
	float hp = 50.0;
	float speed1 = 20.0;
	float speed2 = 15.0;
	float luck = 0.0;
	float mana1 = 35.0;
	float mana2 = 45.0;
	float damage1 = 20.0;
	float damage2 = 35.0;
	float speed = 0.0;
	float mana = 0.0;
	float damage = 0.0;
};



class Player : public Module
{
public:
	// Constructor
	Player();

	// Destructor
	~Player();

	bool Awake(pugi::xml_node&);
	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start();

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	bool Update(float dt);

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	bool PostUpdate();

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2);



	//int Timer(int second);
	playr1 P1;
	playr2 P2;
	playr3 P3;
	playr4 P4;
	playr5 P5;

	bool block1 = true;
	bool block2 = true;
	bool block3 = true;
	bool block4 = true;
	bool block1_ = true;
	bool block2_ = true;
	bool block3_ = true;
	bool block4_ = true;

public:
	SDL_Rect player;
	Collider* wall = nullptr;

	iPoint resetPlayerPos;
};

#endif // __MODULEPLAYER_H__
