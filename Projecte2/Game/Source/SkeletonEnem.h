#ifndef __SKELETONENEM_H__
#define __SKELETONENEM_H__

#include "Entity.h"
#include "Animation.h"
#include "GuiButton.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

#define NUM_SKELETON 100

struct Skeleton
{
	//bool moveXD = false, moveXA = false, moveYW = false, moveYS = false;
	Collider* colliderSK = nullptr;
	Collider* colliderS = nullptr;
	SDL_Texture* skeletonT = nullptr;
	iPoint Pos;
	bool Destroyed = false;
	uint vCount = 0;
	bool dead = false;
	float hp = 72.0;
	float damage = 17.0;
	float speed = 12.0;
	float basehp = 72.0;
	float basedamage = 17.0;
	float basespeed = 12.0;
	int numEnemies = 3;
	bool poisoned = false;
	bool onFire = false;
};

class SkeletonEnem : public Entity
{
public:
	// Constructor
	SkeletonEnem();

	// Destructor
	~SkeletonEnem();


	//bool Awake(pugi::xml_node&);
	// Called when the module is activated
	// Loads the necessary textures for the player
	//bool LoadState(pugi::xml_node&);

	//bool SaveState(pugi::xml_node&) const;


	bool Start();

	void Combat();
	void SpawnEnemies();
	void DrawEnemies();
	void ChooseEnemy();
	void EnemyPhase();
	void CheckEnemy();
	void DrawHpBars();

	// Called at the middle of the application loop
	// Processes new input and handles player movement

	bool Update(float dt);

	bool PostUpdate();

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	void OnCollision(Collider* c1, Collider* c2) override;

	Skeleton CreateSkeleton(int x, int y, SDL_Texture* v);

	void PathFindVamp(int i);

	SDL_Texture* selectSkeleton = nullptr;
	SDL_Texture* skeletonEnem = nullptr;
	SDL_Rect* Choose = new SDL_Rect();

public:
	iPoint position;

	SDL_Texture* TextureSkeleton = nullptr;

	Skeleton Ston[NUM_SKELETON] = { nullptr };

	Animation* currentAnimation[NUM_SKELETON] = { nullptr };
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;
	Animation deadAnim;

	

	float randomEnemyhp = 0.0;
	float randomEnemySpeed = 0.0;
	float randomEnemyDamage = 0.0;
	bool path = false;
	float timer3 = 0;
	float enemySpeed = 20;//Velocitat inversa, 0 es velocitat maxima i valor m�s gran, velocitat m�s lenta.
	float pathfindingtimer = 0;
	bool pathfindingaux = true;
	int WhichSkeleton = NULL; 
	int SkeletonNum = NULL; 
	bool randomstats = true;

};

#endif // __SKELETONENEM_H__
