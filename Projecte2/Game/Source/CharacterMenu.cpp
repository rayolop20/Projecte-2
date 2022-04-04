#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Scene.h"
#include "Menu.h"
#include "CharacterMenu.h"
#include "GuiManager.h"

#include "Defs.h"
#include "Log.h"

CharacterMenu_Screen::CharacterMenu_Screen() : Module()
{
	name.Create("Menu");
}

// Destructor
CharacterMenu_Screen::~CharacterMenu_Screen()
{

}

// Called before render is available
bool CharacterMenu_Screen::Awake()
{
	LOG("Loading Menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool CharacterMenu_Screen::Start()
{
	return true;
}

// Called each loop iteration
bool CharacterMenu_Screen::PreUpdate()
{
	if (!app->scene->cMenu) Disable();
	return true;
}

// Called each loop iteration
bool CharacterMenu_Screen::Update(float dt)
{
	menu = { 100, 100, 100, 100 };
	app->render->DrawRectangle(menu, 0, 250, 0);

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);

	app->guiManager->Draw();

	return true;
}

// Called each loop iteration
bool CharacterMenu_Screen::PostUpdate()
{
	bool ret = true;
	if (exit == true) ret = false;

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	return ret;
}

void CharacterMenu_Screen::Menu()
{
	btnMenuPlay = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Play", { 150, 150, 150, 60 }, this);
	btnMenuConfig = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Config", { 150, 240, 150, 30 }, this);
	btnMenuExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Exit", { 150, 285, 150, 30 }, this);

	btnMenuPlay->state = GuiControlState::DISABLED;
	btnMenuConfig->state = GuiControlState::DISABLED;
	btnMenuExit->state = GuiControlState::DISABLED;
}

bool CharacterMenu_Screen::OnGuiMouseClickEvent(GuiControl* control)
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
				

				}

				if (control->id == 2)
				{
					
				}

				if (control->id == 3)
				{
				}

				if (control->id == 7)
				{
				}

				if (control->id == 8)
				{
				}
				default: break;
			}
		}
		return true;
	}
}

bool CharacterMenu_Screen::CleanUp()
{
		LOG("Freeing scene");

		return true;
}



