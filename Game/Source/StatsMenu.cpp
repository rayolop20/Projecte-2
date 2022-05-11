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


	if (app->BTSystem->StatsEnable == false) {
		Disable();
	}
	return true;
}

// Called each loop iteration
bool StatsMenu_Screen::PreUpdate()
{
	if (!app->scene->cMenu) Disable();
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
		app->BTSystem->CloseStatsMenu->state = GuiControlState::NORMAL;
		app->BTSystem->CloseStatsMenu->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2 - 80);
		app->BTSystem->CloseStatsMenu->bounds.y = -app->render->camera.y + 250;

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



