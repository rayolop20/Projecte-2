#ifndef __ENTITYNPC_H__
#define __ENTITYNPC_H__

#include "Entity.h"
#include "Animation.h"
#include "GuiButton.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

#define NUM_NPC 100

struct NPC
{
	//bool moveXD = false, moveXA = false, moveYW = false, moveYS = false;
	Collider* colliderNPC = nullptr;
	Collider* colliderSNPC = nullptr;
	SDL_Texture* NPCT = nullptr;
	iPoint Pos;
	bool Destroyed = false;
	uint vCount = 0;
	bool dead = false;
};

class EntityNPC : public Entity
{
public:
	// Constructor
	EntityNPC();

	// Destructor
	~EntityNPC();


	//bool Awake(pugi::xml_node&);
	// Called when the module is activated
	// Loads the necessary textures for the player
	//bool LoadState(pugi::xml_node&);

	//bool SaveState(pugi::xml_node&) const;


	bool Start();

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	bool Update(float dt);

	bool PostUpdate();

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	void OnCollision(Collider* c1, Collider* c2) override;

	NPC CreateNPC(int x, int y, SDL_Texture* v);


public:
	iPoint position;

	SDL_Texture* TextureNPC = nullptr;
	SDL_Texture* DialogueBox = nullptr;
	SDL_Texture* door = nullptr;
	SDL_Texture* door2 = nullptr;
	SDL_Texture* door3 = nullptr;

	NPC npc[NUM_NPC] = { nullptr };

	Animation* currentAnimation[NUM_NPC] = { nullptr };
	Animation idle;
	Animation dead;

	int NPCNum = NULL;
	bool klk = true;
	bool Dialogue1 = false;
	bool Dialogue2 = false;
	bool Dialogue3 = false;
	int Dialogue1Count = 0;
	int Dialogue2Count = 0;
	int Dialogue3Count = 0;
	int Dialogue1BranchYes = 0;
	int Dialogue1BranchNo = 0;


	Collider* KLK;
	Collider* KLK2;

	float timerNPC = 0.0;
	float timerNPC2 = 0.0;
	float timerNPC_ = 0.0;
	float timerNPC2_ = 0.0;
	float timerNPC3 = 0.0;
	float timerNPC3_ = 0.0;

};

#endif // __ENTITYNPC_H__
#pragma once
