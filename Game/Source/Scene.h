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

	void CheckPuzzle3();

	void Drawtorch1();
	void Drawtorch2();
	void Drawtorch3();
	void Drawtorch4();

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
	bool puzzle3Active = true;

	bool pressurePlate1 = true;
	bool pressurePlate2 = true;
	bool pressurePlate3 = true;

	bool Quest3active = false;
	
	int pressurePlateTimer1 = 0;
	int pressurePlateTimer2 = 0;
	int pressurePlateTimer3 = 0;
	int pressurePlateTimer1_ = 0;
	int pressurePlateTimer2_ = 0;
	int pressurePlateTimer3_ = 0;
	
	int torchCount1 = 0;
	int torchCount2 = 0;
	int torchCount3 = 0;
	int torchCount4 = 0;

	Collider* Plate1;
	Collider* Plate2;
	Collider* Plate3;

	Collider* Torch1;
	Collider* Torch2;
	Collider* Torch3;
	Collider* Torch4;

	
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
	bool End3 = true;
	bool End4 = true;
	bool End5 = true;
	bool End6 = true;

	int phase = 0;
	int maxPhase = 0;

	int timerphase1 = 0;
	int timerphase1_ = 0;
	
	int timerphase2 = 0;
	int timerphase2_ = 0;

	bool prepared = false;

	int xCont = 0;
	int Open_Door = 1;
private:

	SDL_Texture* img;

	SDL_Texture* pathTex;
	SDL_Texture* torch1Texture;
	SDL_Texture* torch2Texture;
	SDL_Texture* torch3Texture;
	SDL_Texture* torch4Texture;
	SDL_Texture* torch5Texture;
	SDL_Texture* torch6Texture;
	SDL_Texture* torch7Texture;
	SDL_Texture* originTex;
	SDL_Texture* pressed;
	SDL_Texture* nonPressed;
	SDL_Texture* greyButton;
	SDL_Texture* greenButton;
	SDL_Texture* blueButton;
	SDL_Texture* redButton;
	SDL_Texture* purpleButton;
	SDL_Texture* turquoiseButton;
	SDL_Texture* yellowButton;
	// L13: TODO 2: Declare an Item and create it using the EntityManager

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	GuiButton* btn1;
	GuiButton* btn2;

	SDL_Rect block;
 
	iPoint origin;
	bool originSelected = false;

	int Puzle_Fail = 1;
	int Pressure_plate = 1;
	int Puzle_Complete = 1;

};

#endif // __SCENE_H__