#ifndef __VAMPIRENEM_H__
#define __VAMPIRENEM_H__

#include "Entity.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

struct Vampire
{
	iPoint position;
	Collider* Vcol = nullptr;
	//bool moveXD = false, moveXA = false, moveYW = false, moveYS = false;
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

	// Called at the end of the application loop
	// Performs the render call of the player sprite


public:

	Vampire Vpir;

};

#endif // __VAMPIRENEM_H__
