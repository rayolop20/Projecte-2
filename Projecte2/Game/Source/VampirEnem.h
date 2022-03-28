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
	Collider* colliderS = nullptr;
	SDL_Texture* vampireT = nullptr;
	iPoint Pos;
	bool Destroyed = false;
	uint vCount = 0;
	bool dead = false;
	float hp = 222.0;
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

	void Combat();
	// Called at the middle of the application loop
	// Processes new input and handles player movement
	bool Update(float dt);

	bool PostUpdate();

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	void OnCollision(Collider* c1, Collider* c2) override;

	Vampire CreateVampire(int x, int y, SDL_Texture* v);

	void PathFindVamp(int i);

public:
	iPoint position;

	SDL_Texture* TextureVampire = nullptr;

	Vampire Vpir[NUM_VAMPIRE] = { nullptr };

	Animation* currentAnimation[NUM_VAMPIRE] = { nullptr };
	Animation idle;
	Animation dead;

	bool path = false;
	float timer3 = 0;
	float enemySpeed = 20;//Velocitat inversa, 0 es velocitat maxima i valor m�s gran, velocitat m�s lenta.
	float pathfindingtimer = 0;
	bool pathfindingaux = true;

	int VampireNum = NULL;

};

#endif // __VAMPIRENEM_H__
