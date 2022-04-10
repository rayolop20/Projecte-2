#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "GuiButton.h"
#include "Entity.h"

struct SDL_Texture;

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