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
#include "Menu.h"

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
	if (active == true)
	{
	btnMenu = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Menu", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -1390, 160, 51 }, this);
	btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 9, "Exit", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -1480, 160, 51 }, this);
	btnResume = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Resume", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -1250, 193, 51 }, this);

	btnResume->state = GuiControlState::DISABLED;
	btnExit->state = GuiControlState::DISABLED;
	btnMenu->state = GuiControlState::DISABLED;
	}
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
	else  {
		app->menu->btnConfigBack->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) - 150;
		app->menu->btnConfigBack->bounds.y = -app->render->camera.y + 650;
		app->menu->btnMenuConfig->state = GuiControlState::DISABLED;
		btnResume->state = GuiControlState::DISABLED;
		btnMenu->state = GuiControlState::DISABLED;
		btnExit->state = GuiControlState::DISABLED;
	}
}

bool GameMenu_Screen::OnGuiMouseClickEvent(GuiControl* control)
{
	if (app->guiManager->CheackA1 == true)
	{
			switch (control->type)
			{
			case GuiControlType::BUTTON:
			{
				if (control->id == 2) {
					app->menu->config = true;
					app->menu->btnConfigBack->state = GuiControlState::NORMAL;
					
					app->menu->btnMenuPlay->state = GuiControlState::DISABLED;
					app->menu->btnMenuConfig->state = GuiControlState::DISABLED;
					app->menu->btnMenuExit->state = GuiControlState::DISABLED;
					app->menu->btnCredits->state = GuiControlState::DISABLED;
					btnResume->state = GuiControlState::DISABLED;
					btnMenu->state = GuiControlState::DISABLED;
					btnExit->state = GuiControlState::DISABLED;
				}
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
					app->guiManager->DestroyAllGui();
					app->menu->Start();
					active = false;
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

bool GameMenu_Screen::CleanUp()
{

		LOG("Freeing scene");
		return true;
}



