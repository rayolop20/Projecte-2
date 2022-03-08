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
	// L03: DONE: Load map
	// L12b: Create walkability map on map loading


	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	btnPlay = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { 150, 150, 150, 90 }, this);

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
bool Menu_Screen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Menu_Screen::Update(float dt)
{
	btnPlay->state = GuiControlState::NORMAL;

	SDL_Rect Play{ 150, 150, 150, 90 };
	app->render->DrawRectangle(Play, 200, 200, 200);

	
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);

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
					app->player->Enable();
					app->render->camera.x = (app->player->P1.position.x - 550) * -1;
					app->render->camera.y = (app->player->P1.position.y - 300) * -1;
					LOG("Click on button 1");
					btnPlay->state = GuiControlState::DISABLED;
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


