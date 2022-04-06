#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Scene.h"
#include "Menu.h"
#include "GameMenu.h"
#include "GuiManager.h"

#include "Defs.h"
#include "Log.h"

GameMenu_Screen::GameMenu_Screen() : Module()
{
	name.Create("GameMenu");
}

// Destructor
GameMenu_Screen::~GameMenu_Screen()
{

}

// Called before render is available
bool GameMenu_Screen::Awake()
{
	LOG("Loading Menu");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool GameMenu_Screen::Start()
{
	return true;
}

// Called each loop iteration
bool GameMenu_Screen::PreUpdate()
{
	if (!app->scene->cMenu) Disable();
	return true;
}

// Called each loop iteration
bool GameMenu_Screen::Update(float dt)
{
	Menu();

	return true;
}

// Called each loop iteration
bool GameMenu_Screen::PostUpdate()
{
	bool ret = true;

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	return ret;
}

void GameMenu_Screen::Menu()
{
	btnResume = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Resume", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 250, 193, 51 }, this);
	btnMenu = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Menu", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 320, 160, 40 }, this);
	btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 9, "Exit", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 390, 160, 40 }, this);

	btnResume->state = GuiControlState::NORMAL;
	btnMenu->state = GuiControlState::NORMAL;
	btnExit->state = GuiControlState::NORMAL;
}

bool GameMenu_Screen::OnGuiMouseClickEvent(GuiControl* control)
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
					btnResume->state = GuiControlState::DISABLED;
					btnMenu->state = GuiControlState::DISABLED;
					btnExit->state = GuiControlState::DISABLED;
				}

				if (control->id == 6)
				{
					app->scene->paused = false;
					Disable();
					app->menu->Enable();
					app->player->Disable();
					app->render->camera.x = 0;
					app->render->camera.y = 0;
					app->menu->starting = true;
					btnResume->state = GuiControlState::DISABLED;
					btnMenu->state = GuiControlState::DISABLED;
					btnExit->state = GuiControlState::DISABLED;
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

bool GameMenu_Screen::CleanUp()
{
		LOG("Freeing scene");
		return true;
}



