#ifndef __ZOMBIEENEM_H__
#define __ZOMBIEENEM_H__

#include "Entity.h"
#include "Animation.h"
#include "GuiButton.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

#define NUM_ZOMBIE 100

struct Zombie
{
	//bool moveXD = false, moveXA = false, moveYW = false, moveYS = false;
	Collider* colliderZ = nullptr;
	Collider* colliderS = nullptr;
	SDL_Texture* zombieT = nullptr;
	iPoint Pos;
	bool Destroyed = false;
	uint vCount = 0;
	bool dead = false;
	float hp = 35.0;
	float damage = 7.0;
	float speed = 7.0;
	int numEnemies = 4;
	bool poisoned = false;
	bool onFire = false;
};

class ZombieEnem : public Entity
{
public:
	// Constructor
	ZombieEnem();

	// Destructor
	~ZombieEnem();


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

	Zombie CreateZombie(int x, int y, SDL_Texture* v);

	void PathFindVamp(int i);

	SDL_Texture* selectZombie = nullptr;
	SDL_Rect* Choose = new SDL_Rect();

public:
	iPoint position;

	SDL_Texture* TextureZombie = nullptr;
	SDL_Texture* zombieEnem = nullptr;

	Zombie Zbie[NUM_ZOMBIE] = { nullptr };

	Animation* currentAnimation[NUM_ZOMBIE] = { nullptr };
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;
	Animation dead;

	float randomEnemyhp = 0.0;
	float randomEnemySpeed = 0.0;
	float randomEnemyDamage = 0.0;
	bool path = false;
	float timer3 = 0;
	float enemySpeed = 20;//Velocitat inversa, 0 es velocitat maxima i valor més gran, velocitat més lenta.
	float pathfindingtimer = 0;
	bool pathfindingaux = true;

	int ZombieNum = NULL;
	bool klk = true;



};

#endif // __ZOMBIEENEM_H__
