#ifndef __VAMPIRENEM_H__
#define __VAMPIRENEM_H__

#include "Entity.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

#define NUM_VAMPIRE 100

struct Vampire
{
	//bool moveXD = false, moveXA = false, moveYW = false, moveYS = false;
	Collider* colliderV = nullptr;
	SDL_Texture* vampireT = nullptr;
	int x;
	int y;
	bool Destroyed = false;
	uint vCount = 0;
	bool dead = false;
};

class VampirEnem : public Entity
{
public:
	// Constructor
	VampirEnem();

	// Destructor
	~VampirEnem();


	bool Awake(pugi::xml_node&);
	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start();

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	bool Update(float dt);

	bool PostUpdate();

	// Called at the end of the application loop
	// Performs the render call of the player sprite


public:
	iPoint position;

	SDL_Texture* TextureVampire = nullptr;

	Vampire Vpir[NUM_VAMPIRE] = { nullptr };

	Vampire CreateVampire(int x, int y, SDL_Texture* v);

	Animation* currentAnimation[NUM_VAMPIRE] = { nullptr };
	Animation idle;
	Animation dead;

};

#endif // __VAMPIRENEM_H__
