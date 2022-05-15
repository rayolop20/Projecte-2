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

	void Stats();

	void MenuConfig();

	void ShowStats(int a);

	// Called before quitting
	bool CleanUp();
	GuiControl* btnResume;
	GuiControl* btnMenu;
	GuiControl* btnExit;
	bool active = false;
	bool IsPJ4 = true;
	int FText = -1;
private:

	int clickFx = 1;

	SDL_Texture* StatsText = nullptr;
	SDL_Texture* American_S = nullptr;
	SDL_Texture* Russian_S = nullptr;
	SDL_Texture* French_S = nullptr;
	SDL_Texture* Britain_S = nullptr;
	SDL_Texture* Italian_S = nullptr;
	SDL_Texture* enter = nullptr;

	// L12b: Debug pathfing
	iPoint origin;

	char PJName[150] = { "\0" };
	char PJAttack1[150] = { "\0" };
	char PJAttack2[150] = { "\0" };
	char PJHp[150] = { "\0" };
	char PJDmg[150] = { "\0" };
	char PJSpeed[150] = { "\0" };
	char PJMana[150] = { "\0" };


};

#endif // __STATS_SCENE_H__