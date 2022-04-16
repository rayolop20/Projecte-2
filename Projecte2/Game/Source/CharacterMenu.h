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
	bool inventory = false;
	bool exitInventory = false;
	bool init = true;
	bool blockExit = false;

	bool Charac1 = true;
	bool Charac2 = false;
	bool Charac3 = false;
	bool Charac4 = false;

private:

	int clickFx = 1;	
	int buttonCont = 0;

	SDL_Rect menu;
	SDL_Rect itemMenu;
	SDL_Rect Ch1;
	SDL_Rect Ch2;
	SDL_Rect Ch3;
	SDL_Rect Ch4;

	SDL_Rect Ch1Section;
	SDL_Rect Ch2Section;
	SDL_Rect Ch3Section;
	SDL_Rect Ch4Section;

	SDL_Texture* inventoryTex = nullptr;
	SDL_Texture* enter = nullptr;

	// L12b: Debug pathfing
	iPoint origin;

	GuiButton* Character1;
	GuiButton* Character2;
	GuiButton* Character3;
	GuiButton* Character4;

	GuiButton* Item1;
	GuiButton* Item2;
	GuiButton* Item3;

};

#endif // __MENU_SCENE_H__