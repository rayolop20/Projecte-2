#ifndef __CHARACTERMENU_SCENE_H__
#define __CHARACTERMENU_SCENE_H__

#include "Module.h"
#include "Point.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"
struct SDL_Texture;

class CharacterMenu_Screen : public Module
{
public:

	CharacterMenu_Screen();

	// Destructor
	virtual ~CharacterMenu_Screen();

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

	SDL_Rect menu;

	SDL_Texture* enter = nullptr;

	// L12b: Debug pathfing
	iPoint origin;
	GuiButton* btnMenuPlay;
	GuiButton* btnMenuConfig;
	GuiButton* btnMenuExit;

	GuiButton* btnConfigEx1;
	GuiButton* btnConfigBack;


};

#endif // __MENU_SCENE_H__