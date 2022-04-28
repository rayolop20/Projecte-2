#pragma once
#ifndef __STATS_SCENE_H__
#define __STATS_SCENE_H__

#include "Module.h"
#include "Point.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"
struct SDL_Texture;

class StatsMenu_Screen : public Module
{
public:

	StatsMenu_Screen();

	// Destructor
	virtual ~StatsMenu_Screen();

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
	GuiControl* btnResume;
	GuiControl* btnMenu;
	GuiControl* btnExit;
	bool active = false;
private:

	int clickFx = 1;

	SDL_Texture* enter = nullptr;

	// L12b: Debug pathfing
	iPoint origin;



};

#endif // __STATS_SCENE_H__