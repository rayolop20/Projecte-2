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
	bool musicActive = true;
	bool FXActive = true;
	bool playing = false;
	bool On = false;
	bool fps30 = true;

	GuiButton* btnMenuConfig;
	GuiButton* btnMenuPlay;
	GuiButton* btnCredits;
	GuiButton* btnMenuExit;

	GuiButton* btnConfigEx1;
	GuiButton* btnConfigBack;
	GuiButton* btnFullscreen;
	GuiButton* btnFPS;


	SDL_Texture* options = nullptr;
private:

	int EnterLogo = 1;

	SDL_Texture* fonsMenu = nullptr;
	SDL_Texture* Logo = nullptr;


	// L12b: Debug pathfing
	iPoint origin;
	


};

#endif // __MENU_SCENE_H__