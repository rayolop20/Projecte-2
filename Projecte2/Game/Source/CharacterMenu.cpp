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
	menu = { -app->render->camera.x + (app->win->GetWidth() / 2 - 300), -app->render->camera.y + (app->win->GetHeight() / 2 - 200), 600, 400 };
	app->render->DrawRectangle(menu, 0, 250, 0);
	if (Charac1)
	{
		Ch1 = { -app->render->camera.x + (app->win->GetWidth() / 2 - 90), -app->render->camera.y + (app->win->GetHeight() / 2 - 170), 180, 280 };
		app->render->DrawRectangle(Ch1, 0, 0, 250);
	}
	else if (Charac2)
	{
		Ch2 = { -app->render->camera.x + (app->win->GetWidth() / 2 - 90), -app->render->camera.y + (app->win->GetHeight() / 2 - 170), 180, 280 };
		app->render->DrawRectangle(Ch2, 250, 0, 250);
	}
	else if (Charac3)
	{
		Ch3 = { -app->render->camera.x + (app->win->GetWidth() / 2 - 90), -app->render->camera.y + (app->win->GetHeight() / 2 - 170), 180, 280 };
		app->render->DrawRectangle(Ch3, 250, 250, 0);
	}
	else if (Charac4)
	{
		Ch4 = { -app->render->camera.x + (app->win->GetWidth() / 2 - 90), -app->render->camera.y + (app->win->GetHeight() / 2 - 170), 180, 280 };
		app->render->DrawRectangle(Ch4, 0, 250, 250);
	}

	itemMenu = { -app->render->camera.x + (app->win->GetWidth() / 2 - 175), -app->render->camera.y + (app->win->GetHeight() / 2 - 150), 350, 300 };

	if (Helmet)
	{
		app->render->DrawRectangle(itemMenu, 100, 100, 100);
		if (buttonCont == 0)
		{
			Helmet1->state = GuiControlState::NORMAL;
			Helmet2->state = GuiControlState::NORMAL;
			Helmet3->state = GuiControlState::NORMAL;

			HelmetItem->state = GuiControlState::DISABLED;
			ArmorItem->state = GuiControlState::DISABLED;
			WeaponItem->state = GuiControlState::DISABLED;
			BootsItem->state = GuiControlState::DISABLED;

			Character1->state = GuiControlState::DISABLED;
			Character2->state = GuiControlState::DISABLED;
			Character3->state = GuiControlState::DISABLED;
			Character4->state = GuiControlState::DISABLED;

			buttonCont = 1;
		}
	}
	else if (Armor)
	{
		app->render->DrawRectangle(itemMenu, 100, 100, 100);
		if (buttonCont == 0)
		{
			Armor1->state = GuiControlState::NORMAL;
			Armor2->state = GuiControlState::NORMAL;
			Armor3->state = GuiControlState::NORMAL;

			HelmetItem->state = GuiControlState::DISABLED;
			ArmorItem->state = GuiControlState::DISABLED;
			WeaponItem->state = GuiControlState::DISABLED;
			BootsItem->state = GuiControlState::DISABLED;

			Character1->state = GuiControlState::DISABLED;
			Character2->state = GuiControlState::DISABLED;
			Character3->state = GuiControlState::DISABLED;
			Character4->state = GuiControlState::DISABLED;

			buttonCont = 1;
		}
	}
	else if (Weapon)
	{
		app->render->DrawRectangle(itemMenu, 100, 100, 100);
		if (buttonCont == 0)
		{
			Weapon1->state = GuiControlState::NORMAL;
			Weapon2->state = GuiControlState::NORMAL;
			Weapon3->state = GuiControlState::NORMAL;

			HelmetItem->state = GuiControlState::DISABLED;
			ArmorItem->state = GuiControlState::DISABLED;
			WeaponItem->state = GuiControlState::DISABLED;
			BootsItem->state = GuiControlState::DISABLED;

			Character1->state = GuiControlState::DISABLED;
			Character2->state = GuiControlState::DISABLED;
			Character3->state = GuiControlState::DISABLED;
			Character4->state = GuiControlState::DISABLED;

			buttonCont = 1;
		}
	}
	else if (Boots)
	{
		app->render->DrawRectangle(itemMenu, 100, 100, 100);
		if (buttonCont == 0)
		{
			Boots1->state = GuiControlState::NORMAL;
			Boots2->state = GuiControlState::NORMAL;
			Boots3->state = GuiControlState::NORMAL;

			HelmetItem->state = GuiControlState::DISABLED;
			ArmorItem->state = GuiControlState::DISABLED;
			WeaponItem->state = GuiControlState::DISABLED;
			BootsItem->state = GuiControlState::DISABLED;

			Character1->state = GuiControlState::DISABLED;
			Character2->state = GuiControlState::DISABLED;
			Character3->state = GuiControlState::DISABLED;
			Character4->state = GuiControlState::DISABLED;

			buttonCont = 1;
		}
	}
	else
	{
		if (buttonCont == 0 && !init)
		{
			Helmet1->state = GuiControlState::DISABLED;
			Helmet2->state = GuiControlState::DISABLED;
			Helmet3->state = GuiControlState::DISABLED;

			Armor1->state = GuiControlState::DISABLED;
			Armor2->state = GuiControlState::DISABLED;
			Armor3->state = GuiControlState::DISABLED;

			Weapon1->state = GuiControlState::DISABLED;
			Weapon2->state = GuiControlState::DISABLED;
			Weapon3->state = GuiControlState::DISABLED;

			Boots1->state = GuiControlState::DISABLED;
			Boots2->state = GuiControlState::DISABLED;
			Boots3->state = GuiControlState::DISABLED;

			HelmetItem->state = GuiControlState::NORMAL;
			ArmorItem->state = GuiControlState::NORMAL;
			WeaponItem->state = GuiControlState::NORMAL;
			BootsItem->state = GuiControlState::NORMAL;

			Character1->state = GuiControlState::NORMAL;
			Character2->state = GuiControlState::NORMAL;
			Character3->state = GuiControlState::NORMAL;
			Character4->state = GuiControlState::NORMAL;

			buttonCont = 1;
		}
	}

	if (inventory == false)
	{
		Menu();
		inventory = true;
	}	

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);

	app->guiManager->Draw();

	if (Helmet || Armor || Weapon || Boots) blockExit = true;
	else blockExit = false;

	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && blockExit || app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && blockExit)
	{
		Helmet = false;
		Armor = false;
		Weapon = false;
		Boots = false;
		buttonCont = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && app->scene->xCont == 1 && !blockExit || app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && app->scene->xCont == 1 && !blockExit)
	{
		HelmetItem->state = GuiControlState::DISABLED;
		ArmorItem->state = GuiControlState::DISABLED;
		WeaponItem->state = GuiControlState::DISABLED;
		BootsItem->state = GuiControlState::DISABLED;

		Character1->state = GuiControlState::DISABLED;
		Character2->state = GuiControlState::DISABLED;
		Character3->state = GuiControlState::DISABLED;
		Character4->state = GuiControlState::DISABLED;

		exitInventory = true;
		inventory = false;
	}

	if (inventory) app->scene->xCont = 1;

	init = false;

	return true;
}

// Called each loop iteration
bool CharacterMenu_Screen::PostUpdate()
{
	bool ret = true;

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	return ret;
}

void CharacterMenu_Screen::Menu()
{
	HelmetItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Helmet", { -app->render->camera.x + app->win->GetWidth()/2 - 200, -app->render->camera.y + app->win->GetHeight()/2 - 120, 50, 50 }, this);
	ArmorItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Armor", { -app->render->camera.x + app->win->GetWidth() / 2 - 200, -app->render->camera.y + app->win->GetHeight() / 2 + 20, 50, 50 }, this);
	WeaponItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Weapon", { -app->render->camera.x + app->win->GetWidth() / 2 + 150, -app->render->camera.y + app->win->GetHeight() / 2 - 120, 50, 50 }, this);
	BootsItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Boots", { -app->render->camera.x + app->win->GetWidth() / 2 + 150, -app->render->camera.y + app->win->GetHeight() / 2 + 20, 50, 50 }, this);

	Character1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Ch1", { -app->render->camera.x + app->win->GetWidth() / 2 - 175, -app->render->camera.y + app->win->GetHeight() / 2 + 130, 50, 50 }, this);
	Character2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Ch2", { -app->render->camera.x + app->win->GetWidth() / 2 - 75, -app->render->camera.y + app->win->GetHeight() / 2 + 130, 50, 50 }, this);
	Character3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, "Ch3", { -app->render->camera.x + app->win->GetWidth() / 2 + 25, -app->render->camera.y + app->win->GetHeight() / 2 + 130, 50, 50 }, this);
	Character4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "Ch4", { -app->render->camera.x + app->win->GetWidth() / 2 + 125, -app->render->camera.y + app->win->GetHeight() / 2 + 130, 50, 50 }, this);

	Helmet1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 9, "Helmet1", { -app->render->camera.x + app->win->GetWidth() / 2 - 125, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);
	Helmet2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, "Helmet2", { -app->render->camera.x + app->win->GetWidth() / 2 - 25, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);
	Helmet3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, "Helmet3", { -app->render->camera.x + app->win->GetWidth() / 2 + 75, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);

	Armor1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 12, "Armor1", { -app->render->camera.x + app->win->GetWidth() / 2 - 125, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);
	Armor2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 13, "Armor2", { -app->render->camera.x + app->win->GetWidth() / 2 - 25, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);
	Armor3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 14, "Armor3", { -app->render->camera.x + app->win->GetWidth() / 2 + 75, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);

	Weapon1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 15, "Weapon1", { -app->render->camera.x + app->win->GetWidth() / 2 - 125, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);
	Weapon2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 16, "Weapon2", { -app->render->camera.x + app->win->GetWidth() / 2 - 25, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);
	Weapon3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 17, "Weapon3", { -app->render->camera.x + app->win->GetWidth() / 2 + 75, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);

	Boots1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 18, "Boots1", { -app->render->camera.x + app->win->GetWidth() / 2 - 125, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);
	Boots2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 19, "Boots2", { -app->render->camera.x + app->win->GetWidth() / 2 - 25, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);
	Boots3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 20, "Boots3", { -app->render->camera.x + app->win->GetWidth() / 2 + 75, -app->render->camera.y + app->win->GetHeight() / 2 - 130, 50, 50 }, this);

	HelmetItem->state = GuiControlState::NORMAL;
	ArmorItem->state = GuiControlState::NORMAL;
	WeaponItem->state = GuiControlState::NORMAL;
	BootsItem->state = GuiControlState::NORMAL;

	Character1->state = GuiControlState::NORMAL;
	Character2->state = GuiControlState::NORMAL;
	Character3->state = GuiControlState::NORMAL;
	Character4->state = GuiControlState::NORMAL;

	Helmet1->state = GuiControlState::DISABLED;
	Helmet2->state = GuiControlState::DISABLED;
	Helmet3->state = GuiControlState::DISABLED;

	Armor1->state = GuiControlState::DISABLED;
	Armor2->state = GuiControlState::DISABLED;
	Armor3->state = GuiControlState::DISABLED;

	Weapon1->state = GuiControlState::DISABLED;
	Weapon2->state = GuiControlState::DISABLED;
	Weapon3->state = GuiControlState::DISABLED;

	Boots1->state = GuiControlState::DISABLED;
	Boots2->state = GuiControlState::DISABLED;
	Boots3->state = GuiControlState::DISABLED;
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
				if (control->id == 1)
				{		
					Helmet = true;
					buttonCont = 0;
				}

				if (control->id == 2)
				{
					Armor = true;
					buttonCont = 0;
				}

				if (control->id == 3)
				{
					Weapon = true;
					buttonCont = 0;
				}

				if (control->id == 4)
				{
					Boots = true;
					buttonCont = 0;
				}
				//characters
				if (control->id == 5)
				{
					Charac1 = true;
					Charac2 = false;
					Charac3 = false;
					Charac4 = false;
				}

				if (control->id == 6)
				{
					Charac1 = false;
					Charac2 = true;
					Charac3 = false;
					Charac4 = false;
				}

				if (control->id == 7)
				{
					Charac1 = false;
					Charac2 = false;
					Charac3 = true;
					Charac4 = false;
				}

				if (control->id == 8)
				{
					Charac1 = false;
					Charac2 = false;
					Charac3 = false;
					Charac4 = true;
				}

				//helemet items
				if (control->id == 9)
				{
					Helmet = false;
					buttonCont = 0;
				}
				
				if (control->id == 10)
				{
					Helmet = false;
					buttonCont = 0;
				}
				
				if (control->id == 11)
				{
					Helmet = false;
					buttonCont = 0;
				}

				//armor items
				if (control->id == 12)
				{
					Armor = false;
					buttonCont = 0;
				}

				if (control->id == 13)
				{
					Armor = false;
					buttonCont = 0;
				}

				if (control->id == 14)
				{
					Armor = false;
					buttonCont = 0;
				}

				//weapon items
				if (control->id == 15)
				{
					Weapon = false;
					buttonCont = 0;
				}
				if (control->id == 16)
				{
					Weapon = false;
					buttonCont = 0;
				}
				if (control->id == 17)
				{
					Weapon = false;
					buttonCont = 0;
				}

				//boots items
				if (control->id == 18)
				{
					Boots = false;
					buttonCont = 0;
				}
				if (control->id == 19)
				{
					Boots = false;
					buttonCont = 0;
				}
				if (control->id == 20)
				{
					Boots = false;
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



