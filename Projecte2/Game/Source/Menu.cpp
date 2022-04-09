#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Scene.h"
#include "Menu.h"
#include "GuiManager.h"
#include "EntityManager.h"
#include "CharacterMenu.h"
#include "GameMenu.h"

#include "Defs.h"
#include "Log.h"

Menu_Screen::Menu_Screen() : Module()
{
	name.Create("Menu");
}

// Destructor
Menu_Screen::~Menu_Screen()
{

}

// Called before render is available
bool Menu_Screen::Awake()
{
	LOG("Loading Menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Menu_Screen::Start()
{
	if (app->scene->active == true)
	{
		app->scene->Disable();
	}
	
	if (app->player->active == true)
	{
		app->player->Disable();
	}
	
	if (app->gameMenu->active == true)
	{
		app->gameMenu->Disable();
	}

	/*if (app->entityManager->active == true)
	{
		app->entityManager->Disable();
	}*/

	return true;
}

// Called each loop iteration
bool Menu_Screen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Menu_Screen::Update(float dt)
{

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);

	if (!app->scene->paused && starting)
	{
		Menu();

		starting = false;

		btnMenuPlay->state = GuiControlState::NORMAL;
		btnMenuConfig->state = GuiControlState::NORMAL;
		btnMenuExit->state = GuiControlState::NORMAL;
		btnCredits->state = GuiControlState::NORMAL;
	}

	if (config)
	{
		MenuConfig();

		config = false;

		btnConfigEx1->state = GuiControlState::NORMAL;
		btnConfigBack->state = GuiControlState::NORMAL;
	}

	


	app->guiManager->Draw();

	return true;
}

// Called each loop iteration
bool Menu_Screen::PostUpdate()
{
	bool ret = true;
	if (exit == true) ret = false;

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	return ret;
}

void Menu_Screen::Menu()
{
	btnMenuPlay = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Play", { 150, 150, 194, 52 }, this);
	btnMenuConfig = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Config", { 150, 240, 144, 57 }, this);
	btnCredits = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Credits", { 150, 330, 144, 57 }, this);
	btnMenuExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Exit", { 150, 420, 78, 51 }, this);

	btnMenuPlay->state = GuiControlState::DISABLED;
	btnMenuConfig->state = GuiControlState::DISABLED;
	btnCredits->state = GuiControlState::DISABLED;
	btnMenuExit->state = GuiControlState::DISABLED;
}

void Menu_Screen::MenuConfig()
{
	btnConfigEx1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, "Ex1", { 150, 240, 150, 30 }, this);
	btnConfigBack = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "Back to menu", { 150, 285, 150, 30 }, this);

	btnConfigEx1->state = GuiControlState::DISABLED;
	btnConfigBack->state = GuiControlState::DISABLED;
}

bool Menu_Screen::OnGuiMouseClickEvent(GuiControl* control)
{
	if (app->guiManager->CheackA1 == true)
	{
			switch (control->type)
			{
			case GuiControlType::BUTTON:
			{
				//Checks the GUI element ID
				if (control->id == 1)
				{
					Disable();
					app->scene->Enable();
					//app->player->Enable();
					app->render->camera.x = (app->player->P1.position.x - 550) * -1;
					app->render->camera.y = (app->player->P1.position.y - 300) * -1;
					app->player->P1.position.x = app->player->resetPlayerPos.x;
					app->player->P1.position.y = app->player->resetPlayerPos.y;
					LOG("Click on button 1");
					btnMenuPlay->state = GuiControlState::DISABLED;
					btnMenuConfig->state = GuiControlState::DISABLED;
					btnMenuExit->state = GuiControlState::DISABLED;
					btnCredits->state = GuiControlState::DISABLED;

				}

				if (control->id == 2)
				{
					LOG("Config ON");
					config = true;
					btnMenuPlay->state = GuiControlState::DISABLED;
					btnMenuConfig->state = GuiControlState::DISABLED;
					btnMenuExit->state = GuiControlState::DISABLED;
				}

				if (control->id == 3)
				{
					exit = true;
				}
				
				if (control->id == 4)
				{
			
			
				}

				if (control->id == 7)
				{
					LOG("Press Ex1");
				}

				if (control->id == 8)
				{
					starting = true;

					btnConfigEx1->state = GuiControlState::DISABLED;
					btnConfigBack->state = GuiControlState::DISABLED;
				}
				default: break;
			}
		}
		return true;
	}
}

bool Menu_Screen::CleanUp()
{
		LOG("Freeing scene");

		return true;
}



