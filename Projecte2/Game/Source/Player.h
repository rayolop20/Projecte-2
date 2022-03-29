#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

struct playr1
{
	iPoint position;
	Collider* Pcol = nullptr;
	bool moveXD = false, moveXA = false, moveYW = false, moveYS = false;
	float hp = 50.0;
	float speed = 60.0;
	float luck = 0.0;
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

	bool LoadState(pugi::xml_node&);

	bool SaveState(pugi::xml_node&) const;

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
