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

#include "Defs.h"
#include "Log.h"
#include "GameMenu.h"

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
	fonsMenu = app->tex->Load("Assets/textures/Assets/GameTitle.png");
	Logo = app->tex->Load("Assets/textures/Assets/LogoProjecte.png");
	EnterLogo = app->audio->LoadFx("Assets/audio/fx/EnterLogo.wav");
	options = app->tex->Load("Assets/textures/UI/Pause_Menu.png");
	btnMenuPlay = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Play", { 150, 150, 194, 52 }, this);
	btnMenuConfig = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Config", { 150, 240, 144, 57 }, this);
	btnCredits = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Credits", { 150, 330, 144, 57 }, this);
	btnMenuExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Exit", { 150, 420, 78, 51 }, this);
	btnConfigBack = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "Back to menu", { 450, 625, 418, 62 }, this);

	btnMenuPlay->state = GuiControlState::DISABLED;
	btnMenuConfig->state = GuiControlState::DISABLED;
	btnCredits->state = GuiControlState::DISABLED;
	btnMenuExit->state = GuiControlState::DISABLED;

	if (app->scene->active == true)
	{
		app->scene->Disable();
	}
	
	if (app->player->active == true)
	{
		app->player->Disable();
	}
	
	if (app->characterMenu->active == true)
	{
		app->characterMenu->Disable();
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

	//music
	if (musicActive == true && menuScreen == false)
	{
		app->audio->PlayMusic("Assets/audio/music/music_retro_forest.ogg");
		musicActive = false;
	}


	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		menuScreen = false;
	}
	if (menuScreen == false)
	{
		app->render->DrawTexture(fonsMenu, 0, 0);
		app->guiManager->Draw();
	}
	else
	{
		app->render->DrawTexture(Logo, 0, 0);
		if (FXActive == true)
		{
			app->audio->PlayFx(EnterLogo);
			FXActive = false;
		}
	}
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
		SDL_Rect* OptionsTxt = new SDL_Rect();
		OptionsTxt->x = 0;
		OptionsTxt->y = 0;
		OptionsTxt->w = 918;
		OptionsTxt->h = 559;
		if (menuScreen == false) {
			app->render->DrawTexture(options, 200, 50, OptionsTxt);
		}
		btnConfigBack->state = GuiControlState::NORMAL;
	}
	
	//logo i fons de pantalla


	
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
	if (app->scene->paused == true) {
		btnConfigBack->state = GuiControlState::DISABLED;
		btnMenuPlay->state = GuiControlState::NORMAL;
		btnMenuConfig->state = GuiControlState::NORMAL;
		btnCredits->state = GuiControlState::NORMAL;
		btnMenuExit->state = GuiControlState::NORMAL;
	}
	else {
		btnConfigBack->state = GuiControlState::DISABLED;
		btnMenuPlay->state = GuiControlState::DISABLED;
		btnMenuConfig->state = GuiControlState::DISABLED;
		btnCredits->state = GuiControlState::DISABLED;
		btnMenuExit->state = GuiControlState::DISABLED;
	}
}

void Menu_Screen::MenuConfig()
{
	btnConfigBack->state = GuiControlState::NORMAL;
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
					playing = true;
					menuScreen = true;
					Disable();
					app->scene->Enable();
					app->player->Enable();
					app->render->camera.x = (app->player->P1.position.x - 550) * -1;
					app->render->camera.y = (app->player->P1.position.y - 300) * -1;
					app->scene->musicActive = true;
					LOG("Click on button 1");
					btnMenuPlay->state = GuiControlState::DISABLED;
					btnMenuConfig->state = GuiControlState::DISABLED;
					btnMenuExit->state = GuiControlState::DISABLED;
					btnCredits->state = GuiControlState::DISABLED;

				}

				if (control->id == 2 && playing == false)
				{
					LOG("Config ON");
					config = true;
					btnConfigBack->state = GuiControlState::NORMAL;
					btnMenuPlay->state = GuiControlState::DISABLED;
					btnMenuConfig->state = GuiControlState::DISABLED;
					btnMenuExit->state = GuiControlState::DISABLED;
					btnCredits->state = GuiControlState::DISABLED;
				}
				if (control->id == 2 && playing == true)
				{
					LOG("Config ON");
					config = true;
					btnConfigBack->state = GuiControlState::NORMAL;

					app->menu->btnMenuConfig->state = GuiControlState::DISABLED;
					app->gameMenu->btnResume->state = GuiControlState::DISABLED;
					app->gameMenu->btnMenu->state = GuiControlState::DISABLED;
					app->gameMenu->btnExit->state = GuiControlState::DISABLED;
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
			

				if (control->id == 8 && app->menu->config == true && playing == false)
				{
					starting = true;
					config = false;
					btnConfigBack->state = GuiControlState::DISABLED;
				}
				if (control->id == 8 && app->menu->config == true && app->scene->paused == true && playing == false)
				{
					config = false;
					btnConfigBack->state = GuiControlState::DISABLED;
					app->menu->btnMenuConfig->state = GuiControlState::NORMAL;
					app->menu->btnCredits->state = GuiControlState::NORMAL;
					app->gameMenu->btnResume->state = GuiControlState::NORMAL;
					app->gameMenu->btnMenu->state = GuiControlState::NORMAL;
					app->gameMenu->btnExit->state = GuiControlState::NORMAL;
					app->menu->btnMenuPlay->state = GuiControlState::NORMAL;
					app->menu->btnMenuExit->state = GuiControlState::NORMAL;
				}
				if (control->id == 8 && app->menu->config == true && app->scene->paused == true && playing == true)
				{
					config = false;
					btnConfigBack->state = GuiControlState::DISABLED;
					app->menu->btnMenuConfig->state = GuiControlState::NORMAL;
					app->gameMenu->btnResume->state = GuiControlState::NORMAL;
					app->gameMenu->btnMenu->state = GuiControlState::NORMAL;
					app->gameMenu->btnExit->state = GuiControlState::NORMAL;
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
	//app->tex->UnLoad(fonsMenu);
	//app->tex->UnLoad(Logo);
	//app->tex->UnLoad(options);

	return true;
}



