#pragma once
#ifndef __STATS_SCENE_H__
#define __STATS_SCENE_H__

#include "Module.h"
#include "Point.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"
#include "EasingFunctions.h"
#include <vector>

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

	void Stats(float dt);

	void MenuConfig();

	void ShowStats(int a);

	float EaseCameraBetweenPoints(iPoint posA, iPoint posB);

	// Called before quitting
	bool CleanUp();
	GuiControl* btnResume;
	GuiControl* btnMenu;
	GuiControl* btnExit;
	bool active = false;
	bool IsPJ4 = true;
	int FText = -1;

	SDL_Rect* StatsPJ1 = new SDL_Rect();
	SDL_Rect* StatsPJ2 = new SDL_Rect();
	SDL_Rect* StatsPJ3 = new SDL_Rect();
	SDL_Rect* StatsPJ4 = new SDL_Rect();
	SDL_Rect* StatsPJ5 = new SDL_Rect();

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
	char PJSpecial[150] = { "\0" };


	iPoint MenuA;
	iPoint MenuB;

	int iterations;
	int total_iterations_Stats;
	bool easing_active = false;
	float speedX, speedY;
	EasingFunctions function;

};

#endif // __STATS_SCENE_H__
