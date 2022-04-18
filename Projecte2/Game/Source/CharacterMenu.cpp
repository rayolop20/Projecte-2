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
#include "BattleSystem.h"
#include "GuiManager.h"

#include "Defs.h"
#include "Log.h"

CharacterMenu_Screen::CharacterMenu_Screen() : Module()
{
	name.Create("CharacterMenu");
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
	int a;

	inventoryTex = app->tex->Load("Assets/Textures/UI/inventory.png");
	inventoryTexBack = app->tex->Load("Assets/Textures/UI/inventory_bg.png");
	russian = app->tex->Load("Assets/Textures/Soldiers/soldier_rusian.png");
	british = app->tex->Load("Assets/Textures/Soldiers/soldier_1.png");
	french = app->tex->Load("Assets/Textures/Soldiers/soldier_french.png");
	frenchNpc = app->tex->Load("Assets/Textures/Soldiers/soldier_french_npc.png");
	russianNpc = app->tex->Load("Assets/Textures/Soldiers/soldier_rusian_npc.png");
	italian = app->tex->Load("Assets/Textures/Soldiers/soldier_italian.png");
	italianNpc = app->tex->Load("Assets/Textures/Soldiers/soldier_italian_npc.png");
	 

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
	menu = { -app->render->camera.x + (app->win->GetWidth() / 2 - 500), -app->render->camera.y + (app->win->GetHeight() / 2 - 300), 1000, 600 };
	//app->render->DrawRectangle(menu, 0, 250, 0);
	app->render->DrawTexture(app->characterMenu->inventoryTexBack, -app->render->camera.x, -app->render->camera.y);

	if (Charac1)
	{
		Ch1 = { -app->render->camera.x + (app->win->GetWidth() / 2 - 460), -app->render->camera.y + (app->win->GetHeight() / 2 - 200), 180, 280 };
		app->render->DrawTexture(british, -app->render->camera.x + (app->win->GetWidth() / 2 - 460), -app->render->camera.y + (app->win->GetHeight() / 2 - 200));

	}
	else if (Charac2 && app->player->P2.IsAlive == true)
	{
		app->render->DrawTexture(russian, -app->render->camera.x + (app->win->GetWidth() / 2 - 460), -app->render->camera.y + (app->win->GetHeight() / 2 - 200));
	}
	else if (Charac3 && app->player->P3.IsAlive == true) {
		//app->render->DrawTexture(american, -app->render->camera.x + (app->win->GetWidth() / 2 - 460), -app->render->camera.y + (app->win->GetHeight() / 2 - 200));
	}
	else if (Charac4 && app->BTSystem->battle1 == true && app->player->P4.IsAlive == true)
	{
		app->render->DrawTexture(italian, -app->render->camera.x + (app->win->GetWidth() / 2 - 460), -app->render->camera.y + (app->win->GetHeight() / 2 - 200));
	}
	else if (Charac4 && app->BTSystem->battle1 == false && app->player->P4.IsAlive == true)
	{
		app->render->DrawTexture(french, -app->render->camera.x + (app->win->GetWidth() / 2 - 460), -app->render->camera.y + (app->win->GetHeight() / 2 - 200));
	}

	itemMenu = { -app->render->camera.x + (app->win->GetWidth() / 2 - 40), -app->render->camera.y + (app->win->GetHeight() / 2 - 170), 300, 280 };
	//app->render->DrawRectangle(itemMenu, 250, 0, 0);

	if (buttonCont == 0 && !init)
	{
		Character1->state = GuiControlState::NORMAL;
		Character2->state = GuiControlState::NORMAL;
		Character3->state = GuiControlState::NORMAL;
		Character4->state = GuiControlState::NORMAL;

		Item1->state = GuiControlState::NORMAL;
		Item2->state = GuiControlState::NORMAL;
		Item3->state = GuiControlState::NORMAL;

		buttonCont = 1;
	}
	

	if (inventory == false)
	{
		Menu();
		inventory = true;
	}	

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);


	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && blockExit || app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && blockExit)
	{
		buttonCont = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && app->scene->xCont == 1 && !blockExit || app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && app->scene->xCont == 1 && !blockExit)
	{

		Character1->state = GuiControlState::DISABLED;
		Character2->state = GuiControlState::DISABLED;
		Character3->state = GuiControlState::DISABLED;
		Character4->state = GuiControlState::DISABLED;

		Item1->state = GuiControlState::DISABLED;
		Item2->state = GuiControlState::DISABLED;
		Item3->state = GuiControlState::DISABLED;

		exitInventory = true;
		inventory = false;
	}

	if (inventory)
	{

		app->scene->xCont = 1;

		Ch1Section = { -app->render->camera.x + app->win->GetWidth() / 2 - 445, -app->render->camera.y + app->win->GetHeight() / 2 + 100, 60, 60 };
		Ch2Section = { -app->render->camera.x + app->win->GetWidth() / 2 - 355, -app->render->camera.y + app->win->GetHeight() / 2 + 100, 60, 60 };
		Ch3Section = { -app->render->camera.x + app->win->GetWidth() / 2 - 445, -app->render->camera.y + app->win->GetHeight() / 2 + 180, 60, 60 };
		Ch4Section = { -app->render->camera.x + app->win->GetWidth() / 2 - 355, -app->render->camera.y + app->win->GetHeight() / 2 + 180, 60, 60 };
		app->render->DrawRectangle(Ch1Section, 250, 0, 0);
		app->render->DrawRectangle(Ch2Section, 250, 0, 0);
		app->render->DrawRectangle(Ch3Section, 250, 0, 0);
		app->render->DrawRectangle(Ch4Section, 250, 0, 0);
		SDL_Rect* bagSection = new SDL_Rect();
		bagSection->x = 13;
		bagSection->y = 26;
		bagSection->w = 612;
		bagSection->h = 479;
		
		app->render->DrawTexture(inventoryTex, -app->render->camera.x + (app->win->GetWidth() / 2 - 180), -app->render->camera.y + (app->win->GetHeight() / 2 - 230), bagSection);

		Item1Section = { -app->render->camera.x + app->win->GetWidth() / 2 - 99, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 };
		Item2Section = { -app->render->camera.x + app->win->GetWidth() / 2 - 4, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 };
		Item3Section = { -app->render->camera.x + app->win->GetWidth() / 2 + 91, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 };

		app->render->DrawRectangle(Item1Section, 250, 0, 0);
		app->render->DrawRectangle(Item2Section, 250, 0, 0);
		app->render->DrawRectangle(Item3Section, 250, 0, 0);
	}
	app->guiManager->Draw();
	


	if (init) init = false;
	

	return true;
}

// Called each loop iteration
bool CharacterMenu_Screen::PostUpdate()
{
	bool ret = true;

	if (inventory)
	{
		
	}

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	return ret;
}

void CharacterMenu_Screen::Menu()
{
	Character1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 50, "Ch1", { -app->render->camera.x + app->win->GetWidth() / 2 - 445, -app->render->camera.y + app->win->GetHeight() / 2 + 100, 60, 60 }, this);
	Character2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 51, "Ch2", { -app->render->camera.x + app->win->GetWidth() / 2 - 355, -app->render->camera.y + app->win->GetHeight() / 2 + 100, 60, 60 }, this);
	Character3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 52, "Ch3", { -app->render->camera.x + app->win->GetWidth() / 2 - 445, -app->render->camera.y + app->win->GetHeight() / 2 + 180, 60, 60 }, this);
	Character4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 53, "Ch4", { -app->render->camera.x + app->win->GetWidth() / 2 - 355, -app->render->camera.y + app->win->GetHeight() / 2 + 180, 60, 60 }, this);

	Item1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 54, "Boots1", { -app->render->camera.x + app->win->GetWidth() / 2 - 99, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 }, this);
	Item2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 55, "Boots2", { -app->render->camera.x + app->win->GetWidth() / 2 - 4, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 }, this);
	Item3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 56, "Boots3", { -app->render->camera.x + app->win->GetWidth() / 2 + 91, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 }, this);

	Character1->state = GuiControlState::NORMAL;
	Character2->state = GuiControlState::NORMAL;
	Character3->state = GuiControlState::NORMAL;
	Character4->state = GuiControlState::NORMAL;

	Item1->state = GuiControlState::NORMAL;
	Item2->state = GuiControlState::NORMAL;
	Item3->state = GuiControlState::NORMAL;
}

bool CharacterMenu_Screen::OnGuiMouseClickEvent(GuiControl* control)
{
	if (app->guiManager->CheackA1 == true)
	{
			switch (control->type)
			{
			case GuiControlType::BUTTON:
			{
				//Item type
				if (control->id == 50)
				{		
					Charac1 = true;
					Charac2 = false;
					Charac3 = false;
					Charac4 = false;
				}

				if (control->id == 51)
				{					
					Charac1 = false;
					Charac2 = true;
					Charac3 = false;
					Charac4 = false;
				}

				if (control->id == 52)
				{					
					Charac1 = false;
					Charac2 = false;
					Charac3 = true;
					Charac4 = false;
				}

				if (control->id == 53)
				{					
					Charac1 = false;
					Charac2 = false;
					Charac3 = false;
					Charac4 = true;
				}
				//characters
				if (control->id == 54)
				{
					buttonCont = 0;
				}
				if (control->id == 55)
				{
					buttonCont = 0;
				}
				if (control->id == 56)
				{
					buttonCont = 0;
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



