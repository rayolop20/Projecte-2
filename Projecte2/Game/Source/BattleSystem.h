#ifndef __BATTLESYSTEM_H__
#define __BATTLESYSTEM_H__

#include "Module.h"
#include "GuiButton.h"
#include "Entity.h"

struct SDL_Texture;

class battleSystem : public Module
{
public:

	battleSystem();

	// Destructor
	virtual ~battleSystem();

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
	bool battle = false;

	int x, y;
	bool turn = false;
	bool enemyTurn = false;
private:

	int interactionButtons[16] = {	50,300,100,40,
									175,300,100,40,
									50,350,100,40,
									175,350,100,40 };
	
};

#endif // __BATTLESYSTEM_H__