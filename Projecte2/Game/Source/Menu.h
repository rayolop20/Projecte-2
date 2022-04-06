#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "Module.h"
#include "Point.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"
struct SDL_Texture;

class Menu_Screen : public Module
{
public:

	Menu_Screen();

	// Destructor
	virtual ~Menu_Screen();

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

	bool OnGuiMouseClickEvent(GuiControl* control);

	void Menu();

	void MenuConfig();

	// Called before quitting
	bool CleanUp();
	bool EScreen = true;
	bool menuScreen = true;
	bool exit = false;
	bool starting = true;
	bool config = false;

private:

	int clickFx = 1;

	

	SDL_Texture* enter = nullptr;
	SDL_Texture* AdventureText = nullptr;

	// L12b: Debug pathfing
	iPoint origin;
	GuiButton* btnMenuPlay;
	GuiButton* btnMenuConfig;
	GuiButton* btnMenuExit;

	GuiButton* btnConfigEx1;
	GuiButton* btnConfigBack;


};

#endif // __MENU_SCENE_H__