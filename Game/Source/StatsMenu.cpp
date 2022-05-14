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
		SDL_Rect* StatsPJ2 = new SDL_Rect();
		StatsPJ2->x = 70;
		StatsPJ2->y = 56;
		StatsPJ2->w = 278;
		StatsPJ2->h = 424;
		app->render->DrawTexture(StatsText, app->player->P1.position.x - 332 + 64, app->player->P1.position.y - 220 + 32, StatsPJ2);
		SDL_Rect* StatsPJ3 = new SDL_Rect();
		StatsPJ3->x = 70;
		StatsPJ3->y = 56;
		StatsPJ3->w = 278;
		StatsPJ3->h = 424;
		app->render->DrawTexture(StatsText, app->player->P1.position.x - 54 + 96, app->player->P1.position.y - 220 + 32, StatsPJ3);
		SDL_Rect* StatsPJ4 = new SDL_Rect();
		StatsPJ4->x = 70;
		StatsPJ4->y = 56;
		StatsPJ4->w = 278;
		StatsPJ4->h = 424;
		app->render->DrawTexture(StatsText, app->player->P1.position.x + 224 + 128, app->player->P1.position.y - 220 + 32, StatsPJ4);

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



