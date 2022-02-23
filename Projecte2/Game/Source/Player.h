#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

struct play
{
	iPoint position;
	Collider* Pcol = nullptr;
}P1;

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


	// Draws gamepad debug info in the screen
	//void DebugDrawGamepadInfo();

public:
	// Position of the player in the map
	SDL_Rect player;

	// Countdown to handle shot spacing

	// The player spritesheet loaded into an SDL_Texture

	// A flag to detect when the player has been destroyed
};

#endif // __MODULEPLAYER_H__