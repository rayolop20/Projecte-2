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

	bool item1state = false;
	bool item2state = false;
	bool item3state = false;
	bool item4state = false;
	bool item5state = true;
	bool item6state = false;
	bool item7state = false;

	bool typingTxt = false;

	SDL_Texture* inventoryTex = nullptr;
	SDL_Texture* inventoryTexBack = nullptr;
	SDL_Texture* russian = nullptr;
	SDL_Texture* american = nullptr;
	SDL_Texture* russianNpc = nullptr;
	SDL_Texture* americanNpc = nullptr;
	SDL_Texture* british = nullptr;
	SDL_Texture* french = nullptr;
	SDL_Texture* frenchNpc = nullptr;
	SDL_Texture* italian = nullptr;
	SDL_Texture* italianNpc = nullptr;
	SDL_Texture* items = nullptr;


	int increaseDmg = 2;
	int increaseSpeed = 2;
	int increaseMana = 2;
	int healing = 2;
	int increaseHP = 2;
	bool skeletonHead = false;
	int smoke = 3;

	GuiButton* Character1;
	GuiButton* Character2;
	GuiButton* Character3;
	GuiButton* Character4;

	GuiButton* Item1;
	GuiButton* Item2;
	GuiButton* Item3;
	GuiButton* Item4;
	GuiButton* Item5;
	GuiButton* Item6;
	GuiButton* Item7;

private:

	int clickFx = 1;	
	int buttonCont = 0;
	int FText = -1;
	int TxtCont = 0;

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

	SDL_Rect Item1Pos;
	SDL_Rect Item2Pos;
	SDL_Rect Item3Pos;
	SDL_Rect Item4Pos;
	SDL_Rect Item5Pos;
	SDL_Rect Item6Pos;
	SDL_Rect Item7Pos;

	SDL_Rect Item1Rect;
	SDL_Rect Item2Rect;
	SDL_Rect Item3Rect;
	SDL_Rect Item4Rect;
	SDL_Rect Item5Rect;
	SDL_Rect Item6Rect;
	SDL_Rect Item7Rect;

	SDL_Texture* enter = nullptr;

	// L12b: Debug pathfing
	iPoint origin;

	char HP1[150] = { "\0" };
	char Damage1[150] = { "\0" };
	char Mana1[150] = { "\0" };
	char HP2[150] = { "\0" };
	char Damage2[150] = { "\0" };
	char Mana2[150] = { "\0" };
	char HP3[150] = { "\0" };
	char Damage3[150] = { "\0" };
	char Mana3[150] = { "\0" };
	char HP4[150] = { "\0" };
	char Damage4[150] = { "\0" };
	char Mana4[150] = { "\0" };
	char adviceTxt[150] = { "\0" };

};

#endif // __MENU_SCENE_H__