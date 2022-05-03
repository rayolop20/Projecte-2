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
	btnMenu = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Menu", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -1390, 160, 51 }, this);
	btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 9, "Exit", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -1480, 160, 51 }, this);
	btnResume = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Resume", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -1250, 193, 51 }, this);

	btnResume->state = GuiControlState::DISABLED;
	btnExit->state = GuiControlState::DISABLED;
	btnMenu->state = GuiControlState::DISABLED;
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
	Menu();
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

void StatsMenu_Screen::Menu()
{
	if (app->scene->paused == true && app->menu->playing == true) {
		app->menu->btnMenuConfig->state = GuiControlState::NORMAL;
		btnResume->state = GuiControlState::NORMAL;
		btnMenu->state = GuiControlState::NORMAL;
		btnExit->state = GuiControlState::NORMAL;
		btnResume->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2 - 80);
		btnResume->bounds.y = -app->render->camera.y + 250;

		if (app->menu->menuScreen == true && app->scene->paused == true) {

			app->menu->btnMenuConfig->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2 - 80);
			app->menu->btnMenuConfig->bounds.y = -app->render->camera.y + 320;

		}
		if (app->menu->menuScreen == false) {

			app->menu->btnMenuConfig->bounds.x = 150;
			app->menu->btnMenuConfig->bounds.y = 240;
		}

		btnMenu->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2 - 80);
		btnMenu->bounds.y = -app->render->camera.y + 390;
		btnExit->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2 - 80);
		btnExit->bounds.y = -app->render->camera.y + 480;
	}
	else {
		app->menu->btnConfigBack->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) - 150;
		app->menu->btnConfigBack->bounds.y = -app->render->camera.y + 650;
		app->menu->btnMenuConfig->state = GuiControlState::DISABLED;
		btnResume->state = GuiControlState::DISABLED;
		btnMenu->state = GuiControlState::DISABLED;
		btnExit->state = GuiControlState::DISABLED;
	}
}

bool StatsMenu_Screen::OnGuiMouseClickEvent(GuiControl* control)
{
	if (app->guiManager->CheackA1 == true)
	{
		switch (control->type)
		{
		case GuiControlType::BUTTON:
		{
			if (control->id == 5)
			{

				app->scene->paused = false;
				app->menu->btnMenuConfig->state = GuiControlState::DISABLED;

				btnResume->state = GuiControlState::DISABLED;
				btnMenu->state = GuiControlState::DISABLED;
				btnExit->state = GuiControlState::DISABLED;
			}

			if (control->id == 6)
			{
				app->menu->musicActive = true;
				app->scene->paused = false;
				app->menu->playing = false;
				Disable();
				app->menu->Enable();
				app->player->Disable();
				app->scene->Disable();
				app->render->camera.x = 0;
				app->render->camera.y = 0;
				app->menu->starting = true;
				btnResume->state = GuiControlState::DISABLED;
				btnMenu->state = GuiControlState::DISABLED;
				btnExit->state = GuiControlState::DISABLED;;
				app->menu->btnMenuConfig->state = GuiControlState::NORMAL;
				app->menu->btnMenuConfig->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2 - 80) - 420;
				app->menu->btnMenuConfig->bounds.y = -app->render->camera.y + 320 - 75;
				app->menu->btnMenuPlay->state = GuiControlState::NORMAL;
				app->menu->btnMenuExit->state = GuiControlState::NORMAL;
				app->menu->btnConfigBack->state = GuiControlState::DISABLED;
			}

			if (control->id == 9)
			{
				app->menu->exit = true;
			}
		default: break;
		}
		}
		return true;
	}
}

void StatsMenu_Screen::ShowStats(int a)
{
}

bool StatsMenu_Screen::CleanUp()
{

	LOG("Freeing scene");
	return true;
}


