#ifndef __MENU_OPCION_H__
#define __MENU_OPCION_H__

#include "Module.h"
#include "Point.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"
struct SDL_Texture;

class Opcion_Menu : public Module
{
public:

	Opcion_Menu();

	// Destructor
	virtual ~Opcion_Menu();

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

	// L12b: Debug pathfing
	iPoint origin;
	GuiButton* btnMenuPlay;
	GuiButton* btnMenuConfig;
	GuiButton* btnMenuExit;

	GuiButton* btnConfigEx1;
	GuiButton* btnConfigBack;


};

#endif // __MENU_OPCION_H__