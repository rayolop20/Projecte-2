#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "GuiButton.h"
#include "Entity.h"

struct SDL_Texture;
struct S
{
	//bool moveXD = false, moveXA = false, moveYW = false, moveYS = false;
	Collider* colliderS = nullptr;
	iPoint Pos;
	bool Destroyed = false;
	uint vCount = 0;
	bool dead = false;
	int num;
};
class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	S CreateSimonSays(int x, int y, int num);

	void PrepareSimon();
	void One();
	void Two();
	void Three();
	void Four();
	void Five();
	void Six();

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//debug path
	void DebugPath();

	void Pause();

	bool debug = false;
	bool paused = false;
	bool cMenu = false;
	bool musicActive = true;

	bool puzzle1Active = true;
	bool puzzle2Active = true;

	bool pressurePlate1 = true;
	bool pressurePlate2 = true;
	bool pressurePlate3 = true;
	
	int pressurePlateTimer1 = 0;
	int pressurePlateTimer2 = 0;
	int pressurePlateTimer3 = 0;
	int pressurePlateTimer1_ = 0;
	int pressurePlateTimer2_ = 0;
	int pressurePlateTimer3_ = 0;
	
	Collider* Plate1;
	Collider* Plate2;
	Collider* Plate3;
	Collider* Plate4;

	
	Collider* Wall1;
	Collider* Wall2;
	Collider* Wall3;
	Collider* Wall4;
	Collider* Wall5;
	Collider* Wall6;
	Collider* Wall16;
	Collider* Wall17;
	Collider* Wall18;

	S Simon[7];

	SDL_Texture* door = nullptr;

	int firstSimon = 0;
	int secondSimon = 0;
	int thirdSimon = 0;
	int fourthSimon = 0;
	int fifthSimon = 0;
	int sixthSimon = 0;

	bool End0 = true;
	bool End1 = true;
	bool End2 = true;
	bool End3 = false;
	bool End4 = false;
	bool End5 = false;
	bool End6 = false;

	int phase = 0;
	int maxPhase = 0;

	int timerphase1 = 0;
	int timerphase1_ = 0;
	
	int timerphase2 = 0;
	int timerphase2_ = 0;

	bool prepared = false;

	int xCont = 0;
private:

	SDL_Texture* img;

	SDL_Texture* pathTex;
	SDL_Texture* originTex;
	// L13: TODO 2: Declare an Item and create it using the EntityManager

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	GuiButton* btn1;
	GuiButton* btn2;

	SDL_Rect block;
 
	iPoint origin;
	bool originSelected = false;
};

#endif // __SCENE_H__