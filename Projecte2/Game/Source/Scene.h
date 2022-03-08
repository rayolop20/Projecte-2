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

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

	void Pause();

	bool debug = false;
	bool paused = false;
private:

	SDL_Texture* img;

	// L13: TODO 2: Declare an Item and create it using the EntityManager
	EntityType* Vampire;
	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	GuiButton* btn1;
	GuiButton* btn2;

	GuiButton* btnResume;
	GuiButton* btnMenu;
	GuiButton* btnExit;

	SDL_Rect block;
 

};

#endif // __SCENE_H__