#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Scene.h"
#include "Menu.h"
#include "StatsMenu.h"
#include "BattleSystem.h"
#include "GuiManager.h"
#include "Menu.h"
#include "Fonts.h"


#include "DynArray.h"
#include "BattleSystem.h"
#include <time.h>
#include "Defs.h"
#include "Log.h"

StatsMenu_Screen::StatsMenu_Screen() : Module()
{
	name.Create("GameMenu");
}

// Destructor
StatsMenu_Screen::~StatsMenu_Screen()
{

}

// Called before render is available
bool StatsMenu_Screen::Awake()
{
	LOG("Loading Menu");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool StatsMenu_Screen::Start()
{

	StatsText = app->tex->Load("Assets/Textures/UI/stats_menu.png");
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	FText = app->fonts->Load("Assets/Textures/Fonts/fonts.png", lookupTable, 1);

	if (app->BTSystem->StatsEnable == false) {
		Disable();
	}
	return true;
}

// Called each loop iteration
bool StatsMenu_Screen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool StatsMenu_Screen::Update(float dt)
{
	Stats();
	return true;
}

// Called each loop iteration
bool StatsMenu_Screen::PostUpdate()
{
	bool ret = true;

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	return ret;
}

void StatsMenu_Screen::Stats()
{

	if (app->BTSystem->StatsEnable == true) {
		/*app->BTSystem->CloseStatsMenu->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2 - 80);
		app->BTSystem->CloseStatsMenu->bounds.y = -app->render->camera.y + 250;*/

		SDL_Rect* StatsPJ1 = new SDL_Rect();
		StatsPJ1->x = 70;
		StatsPJ1->y = 56;
		StatsPJ1->w = 278;
		StatsPJ1->h = 424;
		app->render->DrawTexture(StatsText, app->player->P1.position.x - 610 + 32, app->player->P1.position.y - 220 + 32, StatsPJ1);
		sprintf_s(PJHp, "%0.f", app->player->P1.hp);
		app->fonts->DrawTxt(190, 207, FText, PJHp);
		sprintf_s(PJDmg, "%0.f", app->player->P1.damage);
		app->fonts->DrawTxt(190, 233, FText, PJDmg);
		sprintf_s(PJSpeed, "%0.f", app->player->P1.speed);
		app->fonts->DrawTxt(190, 261, FText, PJSpeed);
		sprintf_s(PJMana, "%0.f", app->player->P1.mana);
		app->fonts->DrawTxt(190, 291, FText, PJMana);

		SDL_Rect* StatsPJ2 = new SDL_Rect();
		StatsPJ2->x = 70;
		StatsPJ2->y = 56;
		StatsPJ2->w = 278;
		StatsPJ2->h = 424;
		app->render->DrawTexture(StatsText, app->player->P1.position.x - 332 + 64, app->player->P1.position.y - 220 + 32, StatsPJ2);
		sprintf_s(PJHp, "%0.f", app->player->P2.hp);
		app->fonts->DrawTxt(500, 207, FText, PJHp);
		sprintf_s(PJDmg, "%0.f", app->player->P2.damage);
		app->fonts->DrawTxt(500, 233, FText, PJDmg);
		sprintf_s(PJSpeed, "%0.f", app->player->P2.speed);
		app->fonts->DrawTxt(500, 261, FText, PJSpeed);
		sprintf_s(PJMana, "%0.f", app->player->P2.mana);
		app->fonts->DrawTxt(500, 291, FText, PJMana);

		SDL_Rect* StatsPJ3 = new SDL_Rect();
		StatsPJ3->x = 70;
		StatsPJ3->y = 56;
		StatsPJ3->w = 278;
		StatsPJ3->h = 424;
		app->render->DrawTexture(StatsText, app->player->P1.position.x - 54 + 96, app->player->P1.position.y - 220 + 32, StatsPJ3);
		sprintf_s(PJHp, "%0.f", app->player->P3.hp);
		app->fonts->DrawTxt(805, 207, FText, PJHp);
		sprintf_s(PJDmg, "%0.f", app->player->P3.damage);
		app->fonts->DrawTxt(805, 233, FText, PJDmg);
		sprintf_s(PJSpeed, "%0.f", app->player->P3.speed);
		app->fonts->DrawTxt(805, 261, FText, PJSpeed);
		sprintf_s(PJMana, "%0.f", app->player->P3.mana);
		app->fonts->DrawTxt(805, 291, FText, PJMana);

		SDL_Rect* StatsPJ4 = new SDL_Rect();
		StatsPJ4->x = 70;
		StatsPJ4->y = 56;
		StatsPJ4->w = 278;
		StatsPJ4->h = 424;
		app->render->DrawTexture(StatsText, app->player->P1.position.x + 224 + 128, app->player->P1.position.y - 220 + 32, StatsPJ4);
		sprintf_s(PJHp, "%0.f", app->player->P4.hp);
		app->fonts->DrawTxt(1110, 207, FText, PJHp);
		sprintf_s(PJDmg, "%0.f", app->player->P4.damage);
		app->fonts->DrawTxt(1110, 233, FText, PJDmg);
		sprintf_s(PJSpeed, "%0.f", app->player->P4.speed);
		app->fonts->DrawTxt(1110, 261, FText, PJSpeed);
		sprintf_s(PJMana, "%0.f", app->player->P4.mana);
		app->fonts->DrawTxt(1110, 291, FText, PJMana);
	
	}
}

bool StatsMenu_Screen::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}

void StatsMenu_Screen::ShowStats(int a)
{
}

bool StatsMenu_Screen::CleanUp()
{

	LOG("Freeing scene");
	return true;
}



