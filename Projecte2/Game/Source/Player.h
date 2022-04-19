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
	bool key = false;
	bool medkit = false;
	bool IsAlive;
	float hp;
	float speed1 = 15.0;
	float speed2 = 5.0;
	float luck = 0.0;
	float mana1 = 20.0;
	float mana2 = 30.0;
	float damage1 = 20.0;
	float damage2 = 12.0;
	float speed = 0.0;
	float mana;
	float damage = 0.0;

};

struct playr2
{
	//American
	iPoint position;
	Collider* Player2C = nullptr;
	bool P2Active = false;
	bool IsAlive = false;
	bool Move = false;
	float hp;
	float speed1 = 5.0;
	float speed2 = 15.0;
	float luck = 0.0;
	float mana1 = 35.0;
	float mana2 = 35.0;
	float damage1 = 15.0;
	float damage2 = 20.0;
	float speed = 0.0;
	float mana;
	float damage = 0.0;
};

struct playr3
{
	//Rusian
	iPoint position;
	Collider* Player3C = nullptr;
	bool P3Active = false;
	bool Move = false;
	bool IsAlive = false;
	float hp;
	float speed1 = 0.0;
	float speed2 = 10.0;
	float luck = 0.0;
	float mana1 = 25.0;
	float mana2 = 20.0;
	float damage1 = 40.0;
	float damage2 = 12.0;
	float speed = 0.0;
	float mana;
	float damage = 0.0;
};

struct playr4
{
	//Italian
	iPoint position;
	Collider* Player4C = nullptr;
	bool P4Active = false;
	bool Move = false;
	bool IsAlive = false;
	float hp = 15.0;
	float speed1 = 15.0;
	float speed2 = 10.0;
	float luck = 0.0;
	float mana1 = 30.0;
	float mana2 = 40.0;
	float damage1 = 10.0;
	float damage2 = 15.0;
	float speed = 0.0;
	float mana;
	float damage = 0.0;
	bool revolverActive = true;
};

struct playr5
{
	//French
	bool IsAlive = false;
	float hp = 50;
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

	bool LoadState(pugi::xml_node&);

	bool SaveState(pugi::xml_node&) const;

	bool Awake(pugi::xml_node& config);
	// Called when the module is activated
	// Loads the necessary textures for the player

	bool Start();

	bool door3active = false;
	bool door3active_ = false;
	// Called at the middle of the application loop
	// Processes new input and handles player movement
	bool Update(float dt);

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	bool CleanUp();

	bool PostUpdate();

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2);

	void movementPlayer();
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

	bool godMode = false;

public:
	SDL_Rect player1;
	SDL_Rect player2;
	SDL_Rect player3;
	SDL_Rect player4;
	SDL_Rect player5;
	SDL_Texture* PE;
	SDL_Texture* darkness;

	SDL_Texture* player1Hp = nullptr;
	SDL_Texture* player2Hp = nullptr;
	SDL_Texture* player3Hp = nullptr;
	SDL_Texture* player4Hp = nullptr;

	SDL_Texture* player1S = nullptr;
	SDL_Texture* player4S = nullptr;
	SDL_Texture* player2S = nullptr;
	SDL_Texture* player3S = nullptr;

	Animation* currentAnim1 = nullptr;
	Animation idleAnim1;
	Animation downAnim1;
	Animation upAnim1;
	Animation rightAnim1;
	Animation leftAnim1;

	Animation* currentAnim4 = nullptr;
	Animation idleAnim4;
	Animation downAnim4;
	Animation upAnim4;
	Animation rightAnim4;
	Animation leftAnim4;

	Animation* currentAnim2 = nullptr;
	Animation idleAnim2;
	Animation downAnim2;
	Animation upAnim2;
	Animation rightAnim2;
	Animation leftAnim2;

	Animation* currentAnim3 = nullptr;
	Animation idleAnim3;
	Animation downAnim3;
	Animation upAnim3;
	Animation rightAnim3;
	Animation leftAnim3;
	int OrdenPlayers = 0;

	iPoint resetPlayerPos;
};

#endif // __MODULEPLAYER_H__
