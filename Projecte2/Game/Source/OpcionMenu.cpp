#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Scene.h"
#include "OpcionMenu.h"
#include "GuiManager.h"

#include "Defs.h"
#include "Log.h"

Opcion_Menu::Opcion_Menu() : Module()
{
	name.Create("Menu");
}

// Destructor
Opcion_Menu::~Opcion_Menu()
{

}

// Called before render is available
bool Opcion_Menu::Awake()
{
	LOG("Loading Menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Opcion_Menu::Start()
{

	if (app->scene->active == true)
	{
		app->scene->Disable();
	}

	if (app->player->active == true)
	{
		app->player->Disable();
	}
	return true;
}

// Called each loop iteration
bool Opcion_Menu::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Opcion_Menu::Update(float dt)
{
	if (!app->scene->paused && starting)
	{
		Menu();

		starting = false;

		btnMenuPlay->state = GuiControlState::NORMAL;
		btnMenuConfig->state = GuiControlState::NORMAL;
		btnMenuExit->state = GuiControlState::NORMAL;
	}

	if (config)
	{
		MenuConfig();

		config = false;

		btnConfigEx1->state = GuiControlState::NORMAL;
		btnConfigBack->state = GuiControlState::NORMAL;
	}
	//btnMenuPlay->state = GuiControlState::NORMAL;
	//btnMenuConfig->state = GuiControlState::NORMAL;
	//btnMenuExit->state = GuiControlState::NORMAL;

	//SDL_Rect Play{ 150, 150, 150, 90 };
	//app->render->DrawRectangle(Play, 200, 200, 200);

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);

	app->guiManager->Draw();

	return true;
}

// Called each loop iteration
bool Opcion_Menu::PostUpdate()
{
	bool ret = true;
	if (exit == true) ret = false;

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	return ret;
}

void Opcion_Menu::Menu()
{
	btnMenuPlay = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Play", { 150, 150, 150, 60 }, this);
	btnMenuConfig = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Config", { 150, 240, 150, 30 }, this);
	btnMenuExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Exit", { 150, 285, 150, 30 }, this);

	btnMenuPlay->state = GuiControlState::DISABLED;
	btnMenuConfig->state = GuiControlState::DISABLED;
	btnMenuExit->state = GuiControlState::DISABLED;
}

void Opcion_Menu::MenuConfig()
{
	btnConfigEx1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, "Ex1", { 150, 240, 150, 30 }, this);
	btnConfigBack = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "Back to menu", { 150, 285, 150, 30 }, this);

	btnConfigEx1->state = GuiControlState::DISABLED;
	btnConfigBack->state = GuiControlState::DISABLED;
}

bool Opcion_Menu::OnGuiMouseClickEvent(GuiControl* control)
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
				app->player->Enable();
				app->render->camera.x = (app->player->P1.position.x - 550) * -1;
				app->render->camera.y = (app->player->P1.position.y - 300) * -1;
				app->player->P1.position.x = app->player->resetPlayerPos.x;
				app->player->P1.position.y = app->player->resetPlayerPos.y;
				LOG("Click on button 1");
				btnMenuPlay->state = GuiControlState::DISABLED;
				btnMenuConfig->state = GuiControlState::DISABLED;
				btnMenuExit->state = GuiControlState::DISABLED;

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

bool Opcion_Menu::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

