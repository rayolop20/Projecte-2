#ifndef __VAMPIRENEM_H__
#define __VAMPIRENEM_H__

#include "Entity.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;


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
	bool PostUpdate();

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2);


public:

};

#endif // __VAMPIRENEM_H__
