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
#include "Fonts.h"

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

	inventoryTex = app->tex->Load("Assets/Textures/UI/Inventory.png");
	inventoryTexBack = app->tex->Load("Assets/Textures/UI/inventory_bg.png");
	russian = app->tex->Load("Assets/Textures/Soldiers/soldier_rusian.png");
	american = app->tex->Load("Assets/Textures/Soldiers/soldier_american_dogmaster.png");
	british = app->tex->Load("Assets/Textures/Soldiers/soldier_1.png");
	french = app->tex->Load("Assets/Textures/Soldiers/soldier_french.png");
	frenchNpc = app->tex->Load("Assets/Textures/Soldiers/soldier_french_npc.png");
	russianNpc = app->tex->Load("Assets/Textures/Soldiers/soldier_rusian_npc.png");
	americanNpc = app->tex->Load("Assets/Textures/Soldiers/soldier_american_dogmaster_npc.png");
	italian = app->tex->Load("Assets/Textures/Soldiers/soldier_italian.png");
	italianNpc = app->tex->Load("Assets/Textures/Soldiers/soldier_italian_npc.png");
	items = app->tex->Load("Assets/Textures/UI/items.png");
	 
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	FText = app->fonts->Load("Assets/Textures/Fonts/fonts.png", lookupTable, 1);

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
		app->render->DrawTexture(american, -app->render->camera.x + (app->win->GetWidth() / 2 - 460), -app->render->camera.y + (app->win->GetHeight() / 2 - 200));
	}
	else if (Charac3 && app->player->P3.IsAlive == true) {
		app->render->DrawTexture(russian, -app->render->camera.x + (app->win->GetWidth() / 2 - 460), -app->render->camera.y + (app->win->GetHeight() / 2 - 200));
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
		Item4->state = GuiControlState::NORMAL;
		Item5->state = GuiControlState::NORMAL;
		Item6->state = GuiControlState::NORMAL;
		Item7->state = GuiControlState::NORMAL;

		buttonCont = 1;
	}
	

	if (inventory == false)
	{
		Menu();
		inventory = true;
	}	

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);


	if (app->BTSystem->InventoryEnable == false && (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN || app->input->Pad->GetButton(SDL_CONTROLLER_BUTTON_Y) == KEY_DOWN) && blockExit || app->BTSystem->InventoryEnable)
	{
		app->BTSystem->AttackPhaseEnable = false;
		app->BTSystem->AttackPhaseActive = false;
		app->BTSystem->InventoryEnable = true;
		app->BTSystem->CloseInventory->state = GuiControlState::NORMAL;
		buttonCont = 0;
	}

	if (app->BTSystem->InventoryEnable == false && (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN || app->input->Pad->GetButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) && app->scene->xCont == 1 && !blockExit  && app->scene->xCont == 1 && !blockExit)
	{

		Character1->state = GuiControlState::DISABLED;
		Character2->state = GuiControlState::DISABLED;
		Character3->state = GuiControlState::DISABLED;
		Character4->state = GuiControlState::DISABLED;

		Item1->state = GuiControlState::DISABLED;
		Item2->state = GuiControlState::DISABLED;
		Item3->state = GuiControlState::DISABLED;
		Item4->state = GuiControlState::DISABLED;
		Item5->state = GuiControlState::DISABLED;
		Item6->state = GuiControlState::DISABLED;
		Item7->state = GuiControlState::DISABLED;
		app->BTSystem->CloseInventory->state = GuiControlState::DISABLED;

		exitInventory = true;
		inventory = false;
	}

	if (inventory || app->BTSystem->InventoryEnable)
	{

		app->scene->xCont = 1;
		Ch1Section = { -app->render->camera.x + app->win->GetWidth() / 2 - 265, -app->render->camera.y + app->win->GetHeight() / 2 - 200, 60, 60 };
		Ch2Section = { -app->render->camera.x + app->win->GetWidth() / 2 - 265, -app->render->camera.y + app->win->GetHeight() / 2 - 100, 60, 60 };
		Ch3Section = { -app->render->camera.x + app->win->GetWidth() / 2 - 265, -app->render->camera.y + app->win->GetHeight() / 2		, 60, 60 };
		Ch4Section = { -app->render->camera.x + app->win->GetWidth() / 2 - 265, -app->render->camera.y + app->win->GetHeight() / 2 + 100, 60, 60 };
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
		//first row
		Item1Pos = { -app->render->camera.x + app->win->GetWidth() / 2 - 99, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 };
		Item2Pos = { -app->render->camera.x + app->win->GetWidth() / 2 - 4, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 };
		Item3Pos = { -app->render->camera.x + app->win->GetWidth() / 2 + 91, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 };
		Item4Pos = { -app->render->camera.x + app->win->GetWidth() / 2 + 186, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 };
		Item5Pos = { -app->render->camera.x + app->win->GetWidth() / 2 + 281, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 };
		//second row
		Item6Pos = { -app->render->camera.x + app->win->GetWidth() / 2 - 99, -app->render->camera.y + app->win->GetHeight() / 2 - 64, 70, 70 };
		Item7Pos = { -app->render->camera.x + app->win->GetWidth() / 2 - 4, -app->render->camera.y + app->win->GetHeight() / 2 - 64, 70, 70 };

		if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			increaseDmg = 2;
		}
		if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			healing = 2;
		}
		if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{
			increaseMana = 2;
		}
		if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		{
			increaseHP = 2;
		}
		if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		{
			smoke = 2;
		}
		if (app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		{
			app->player->door3active = true;
		}
		if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
		{
			item7state = true;
		}

		if (increaseDmg > 0) item1state = true;
		else item1state = false;

		if (healing > 0) item2state = true;
		else item2state = false;
		
		if (increaseMana > 0) item3state = true;
		else item3state = false;

		if (increaseHP > 0)	item4state = true;
		else item4state = false;

		if (smoke > 0)	item5state = true;
		else item5state = false;

		if (item1state) {
			Item1Rect = Item1Pos;
			SDL_Rect* damage = new SDL_Rect();
			damage->x = 336;
			damage->y = 0;
			damage->w = 50;
			damage->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item1Rect.x+10, Item1Rect.y-10,damage);

			//app->render->DrawRectangle(Item1Rect, 250, 0, 0);
		}


		if (!item1state && item2state) {
			Item2Rect = Item1Pos;
			SDL_Rect* hp = new SDL_Rect();
			hp->x = 109;
			hp->y = 114;
			hp->w = 73;
			hp->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item2Rect.x, Item2Rect.y - 10, hp);
			//app->render->DrawRectangle(Item2Rect, 0, 250, 0);�
		}
		else if (item1state && item2state) {
			Item2Rect = Item2Pos; 
			SDL_Rect* hp = new SDL_Rect();
			hp->x = 109;
			hp->y = 114;
			hp->w = 73;
			hp->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item2Rect.x, Item2Rect.y - 10, hp);
			//app->render->DrawRectangle(Item2Rect, 0, 250, 0);
		}


		if (!item1state && !item2state && item3state) {
			Item3Rect = Item1Pos;
			SDL_Rect* mana = new SDL_Rect();
			mana->x = 215;
			mana->y = 0;
			mana->w = 80;
			mana->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item3Rect.x + 5, Item3Rect.y - 5, mana);
			//app->render->DrawRectangle(Item3Rect, 0, 0, 250);
		}
		else if (!item1state && item2state && item3state) {
			Item3Rect = Item2Pos;
			SDL_Rect* mana = new SDL_Rect();
			mana->x = 215;
			mana->y = 0;
			mana->w = 80;
			mana->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item3Rect.x + 5, Item3Rect.y - 5, mana);
		}
		else if (item1state && !item2state && item3state) {
			Item3Rect = Item2Pos; 
			SDL_Rect* mana = new SDL_Rect();
			mana->x = 215;
			mana->y = 0;
			mana->w = 80;
			mana->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item3Rect.x + 5, Item3Rect.y - 5, mana);
		}
		else if (item1state && item2state && item3state) {
			Item3Rect = Item3Pos; 
			SDL_Rect* mana = new SDL_Rect();
			mana->x = 215;
			mana->y = 0;
			mana->w = 80;
			mana->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item3Rect.x + 5, Item3Rect.y - 5, mana);
		}

		
		if (!item1state && !item2state && !item3state && item4state)
		{
			Item4Rect = Item1Pos;			
			SDL_Rect* hp = new SDL_Rect();
			hp->x = 415;
			hp->y = 115;
			hp->w = 40;
			hp->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item4Rect.x + 5, Item4Rect.y - 5, hp);
		}
		else if (item1state && !item2state && !item3state && item4state)
		{
			Item4Rect = Item2Pos; SDL_Rect* hp = new SDL_Rect();
			hp->x = 415;
			hp->y = 115;
			hp->w = 40;
			hp->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item4Rect.x + 5, Item4Rect.y - 5, hp);
		}
		else if (!item1state && item2state && !item3state && item4state)
		{
			Item4Rect = Item2Pos;
			SDL_Rect* hp = new SDL_Rect();
			hp->x = 415;
			hp->y = 115;
			hp->w = 40;
			hp->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item4Rect.x + 5, Item4Rect.y - 5, hp);
		}
		else if (!item1state && !item2state && item3state && item4state)
		{
			Item4Rect = Item2Pos; 
			SDL_Rect* hp = new SDL_Rect();
			hp->x = 415;
			hp->y = 115;
			hp->w = 40;
			hp->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item4Rect.x + 5, Item4Rect.y - 5, hp);
		}
		else if (item1state && item2state && !item3state && item4state)
		{
			Item4Rect = Item3Pos; 
			SDL_Rect* hp = new SDL_Rect();
			hp->x = 415;
			hp->y = 115;
			hp->w = 40;
			hp->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item4Rect.x + 5, Item4Rect.y - 5, hp);
		}
		else if (item1state && !item2state && item3state && item4state)
		{
			Item4Rect = Item3Pos; 
			SDL_Rect* hp = new SDL_Rect();
			hp->x = 415;
			hp->y = 115;
			hp->w = 40;
			hp->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item4Rect.x + 5, Item4Rect.y - 5, hp);
		}
		else if (!item1state && item2state && item3state && item4state)
		{
			Item4Rect = Item3Pos;
			SDL_Rect* hp = new SDL_Rect();
			hp->x = 415;
			hp->y = 115;
			hp->w = 40;
			hp->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item4Rect.x + 5, Item4Rect.y - 5, hp);
		}
		else if (item1state && item2state && item3state && item4state)
		{
			Item4Rect = Item4Pos; 
			SDL_Rect* hp = new SDL_Rect();
			hp->x = 415;
			hp->y = 115;
			hp->w = 40;
			hp->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item4Rect.x + 5, Item4Rect.y - 5, hp);
		}
		

		if (!item1state && !item2state && !item3state && !item4state && item5state)
		{
			Item5Rect = Item1Pos;	
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (item1state && !item2state && !item3state && !item4state && item5state)
		{
			Item5Rect = Item2Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (!item1state && item2state && !item3state && !item4state && item5state)
		{
			Item5Rect = Item2Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (!item1state && !item2state && item3state && !item4state && item5state)
		{
			Item5Rect = Item2Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (!item1state && !item2state && !item3state && item4state && item5state)
		{
			Item5Rect = Item2Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (item1state && item2state && !item3state && !item4state && item5state)
		{
			Item5Rect = Item3Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (item1state && !item2state && item3state && !item4state && item5state)
		{
			Item5Rect = Item3Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (item1state && !item2state && !item3state && item4state && item5state)
		{
			Item5Rect = Item3Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (!item1state && item2state && item3state && !item4state && item5state)
		{
			Item5Rect = Item3Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (!item1state && item2state && !item3state && item4state && item5state)
		{
			Item5Rect = Item3Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (!item1state && !item2state && item3state && item4state && item5state)
		{
			Item5Rect = Item3Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (item1state && !item2state && item3state && item4state && item5state)
		{
			Item5Rect = Item4Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (item1state && item2state && !item3state && item4state && item5state)
		{
			Item5Rect = Item4Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (item1state && item2state && item3state && !item4state && item5state)
		{
			Item5Rect = Item4Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (!item1state && item2state && item3state && item4state && item5state)
		{
			Item5Rect = Item4Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else if (item1state && item2state && item3state && item4state && item5state)
		{
			Item5Rect = Item5Pos;
			SDL_Rect* smoke = new SDL_Rect();
			smoke->x = 425;
			smoke->y = 0;
			smoke->w = 50;
			smoke->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item5Rect.x + 5, Item5Rect.y - 5, smoke);
		}
		else
		{
			item5state = false;
		}


		if (!item1state && !item2state && !item3state && !item4state && !item5state && item6state)
		{
			Item6Rect = Item1Pos;
			SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && !item2state && !item3state && !item4state && !item5state && item6state)
		{
			Item6Rect = Item2Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && item2state && !item3state && !item4state && !item5state && item6state)
		{
			Item6Rect = Item2Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && !item2state && item3state && !item4state && !item5state && item6state)
		{
			Item6Rect = Item2Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && !item2state && !item3state && item4state && !item5state && item6state)
		{
			Item6Rect = Item2Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && !item2state && !item3state && !item4state && item5state && item6state)
		{
			Item6Rect = Item2Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && item2state && !item3state && !item4state && !item5state && item6state)
		{
			Item6Rect = Item3Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && !item2state && item3state && !item4state && !item5state && item6state)
		{
			Item6Rect = Item3Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && !item2state && !item3state && item4state && !item5state && item6state)
		{
			Item6Rect = Item3Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && !item2state && !item3state && !item4state && item5state && item6state)
		{
			Item6Rect = Item3Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && item2state && !item3state && !item4state && item5state && item6state)
		{
			Item6Rect = Item3Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && item2state && !item3state && item4state && !item5state && item6state)
		{
			Item6Rect = Item3Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && item2state && item3state && !item4state && !item5state && item6state)
		{
			Item6Rect = Item3Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && !item2state && item3state && item4state && !item5state && item6state)
		{
			Item6Rect = Item3Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && !item2state && item3state && !item4state && item5state && item6state)
		{
			Item6Rect = Item3Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && !item2state && !item3state && item4state && item5state && item6state)
		{
			Item6Rect = Item3Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && item2state && item3state && !item4state && !item5state && item6state)
		{
			Item6Rect = Item4Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && item2state && !item3state && item4state && !item5state && item6state)
		{
			Item6Rect = Item4Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && item2state && !item3state && !item4state && item5state && item6state)
		{
			Item6Rect = Item4Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && !item2state && item3state && item4state && !item5state && item6state)
		{
			Item6Rect = Item4Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && !item2state && item3state && !item4state && item5state && item6state)
		{
			Item6Rect = Item4Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && item2state && item3state && !item4state && item5state && item6state)
		{
			Item6Rect = Item4Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && item2state && item3state && item4state && !item5state && item6state)
		{
			Item6Rect = Item4Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && !item2state && item3state && item4state && item5state && item6state)
		{
			Item6Rect = Item4Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && item2state && item3state && item4state && !item5state && item6state)
		{
			Item6Rect = Item5Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && item2state && item3state && !item4state && item5state && item6state)
		{
			Item6Rect = Item5Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && item2state && !item3state && item4state && item5state && item6state)
		{
			Item6Rect = Item5Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && !item2state && item3state && item4state && item5state && item6state)
		{
			Item6Rect = Item5Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (!item1state && item2state && item3state && item4state && item5state && item6state)
		{
			Item6Rect = Item5Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else if (item1state && item2state && item3state && item4state && item5state && item6state)
		{
			Item6Rect = Item6Pos; SDL_Rect* key = new SDL_Rect();
			key->x = 340;
			key->y = 126;
			key->w = 30;
			key->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item6Rect.x + 10, Item6Rect.y - 5, key);
		}
		else 
		{
			item6state = false;
		}

		if (!item1state && !item2state && !item3state && !item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item1Pos;
			SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && !item3state && !item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item2Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && !item3state && !item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item2Pos;SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && item3state && !item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item2Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && !item3state && item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item2Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && !item3state && !item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item2Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && !item3state && !item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item2Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && !item3state && !item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && item3state && !item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && !item3state && item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && !item3state && !item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && !item3state && !item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && item3state && !item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && !item3state && item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && !item3state && !item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && !item3state && !item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && item3state && item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && item3state && !item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && item3state && !item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && !item3state && item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && !item3state && item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && !item3state && !item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item3Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && item3state && !item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && !item3state && item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && !item3state && !item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && !item3state && !item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && !item3state && !item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && item3state && item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && item3state && !item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && item3state && !item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && !item3state && item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && !item3state && item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && !item3state && !item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && item3state && item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && item3state && !item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && item3state && !item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && !item3state && item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && !item3state && item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && !item3state && !item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && item3state && item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && item3state && item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && item3state && !item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && !item3state && item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item4Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && item3state && item4state && !item5state && !item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && item3state && !item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && item3state && !item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && !item3state && item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && !item3state && item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && !item3state && !item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && item3state && item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && item3state && item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && item3state && !item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && !item3state && item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && item3state && item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && item3state && item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && item3state && !item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && !item3state && item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && !item2state && item3state && item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item5Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (!item1state && item2state && item3state && item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item6Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && !item2state && item3state && item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item6Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && !item3state && item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item6Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && item3state && !item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item6Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && item3state && item4state && !item5state && item6state && item7state)
		{
			Item7Rect = Item6Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && item3state && item4state && item5state && !item6state && item7state)
		{
			Item7Rect = Item6Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else if (item1state && item2state && item3state && item4state && item5state && item6state && item7state)
		{
			Item7Rect = Item7Pos; SDL_Rect* skull = new SDL_Rect();
			skull->x = 219;
			skull->y = 130;
			skull->w = 70;
			skull->h = 86;
			app->render->DrawTexture(app->characterMenu->items, Item7Rect.x + 10, Item7Rect.y - 5, skull);
		}
		else
		{
			item7state = false;
		}
	}
	app->guiManager->Draw();
	
	if (Charac1)
	{
		sprintf_s(HP1, "hp %.2f / %.2f", app->player->P1.hp, app->BTSystem->p1MaxHP);
		app->fonts->DrawTxt(10, 10, FText, HP1);

		sprintf_s(Damage1, "damage %.2f", app->player->P1.damage);
		app->fonts->DrawTxt(10, 40, FText, Damage1);

		sprintf_s(Mana1, "mana %.2f", app->player->P1.mana);
		app->fonts->DrawTxt(10, 70, FText, Mana1);
	}if (Charac2 && app->player->P2.IsAlive)
	{
		sprintf_s(HP2, "hp %.2f / %.2f", app->player->P2.hp, app->BTSystem->p2MaxHP);
		app->fonts->DrawTxt(10, 10, FText, HP2);

		sprintf_s(Damage2, "damage %.2f", app->player->P2.damage);
		app->fonts->DrawTxt(10, 40, FText, Damage2);

		sprintf_s(Mana2, "mana %.2f", app->player->P2.mana);
		app->fonts->DrawTxt(10, 70, FText, Mana2);
	}if (Charac3 && app->player->P3.IsAlive)
	{
		sprintf_s(HP3, "hp %.2f / %.2f", app->player->P3.hp, app->BTSystem->p3MaxHP);
		app->fonts->DrawTxt(10, 10, FText, HP3);

		sprintf_s(Damage3, "damage %.2f", app->player->P3.damage);
		app->fonts->DrawTxt(10, 40, FText, Damage3);

		sprintf_s(Mana3, "mana %.2f", app->player->P3.mana);
		app->fonts->DrawTxt(10, 70, FText, Mana3);
	}
	if (Charac4 && app->player->P3.IsAlive)
	{
		sprintf_s(HP4, "hp %.2f / %.2f", app->player->P4.hp, app->BTSystem->p4MaxHP);
		app->fonts->DrawTxt(10, 10, FText, HP4);

		sprintf_s(Damage4, "damage %.2f", app->player->P4.damage);
		app->fonts->DrawTxt(10, 40, FText, Damage4);

		sprintf_s(Mana4, "mana %.2f", app->player->P4.mana);
		app->fonts->DrawTxt(10, 70, FText, Mana4);
	}
	if (typingTxt && !typingTxt2)
	{
		sprintf_s(adviceTxt, "try to use this item in a fight to run away");
		app->fonts->DrawTxt(390, 620, FText, adviceTxt);
		if (TxtCont < 2)
		{
			TxtCont++;
		}
	}
	if (typingTxt2 && !typingTxt)
	{
		sprintf_s(adviceTxt, "this skull seems to be used in an altar");
		app->fonts->DrawTxt(430, 620, FText, adviceTxt);
		if (TxtCont < 2)
		{
			TxtCont++;
		}
	}

	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP && (typingTxt || typingTxt2) && TxtCont == 2)
	{
		typingTxt = false;
		typingTxt2 = false;
		TxtCont = 0;
	}

	if (init) init = false;
	

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
	Character1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 50, "Ch1", { -app->render->camera.x + app->win->GetWidth() / 2 - 265, -app->render->camera.y + app->win->GetHeight() / 2 - 200, 60, 60 }, this);
	Character2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 51, "Ch2", { -app->render->camera.x + app->win->GetWidth() / 2 - 265, -app->render->camera.y + app->win->GetHeight() / 2 - 100, 60, 60 }, this);
	Character3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 52, "Ch3", { -app->render->camera.x + app->win->GetWidth() / 2 - 265, -app->render->camera.y + app->win->GetHeight() / 2		 , 60, 60 }, this);
	Character4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 53, "Ch4", { -app->render->camera.x + app->win->GetWidth() / 2 - 265, -app->render->camera.y + app->win->GetHeight() / 2 + 100, 60, 60 }, this);

	Item1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 54, "item1", { -app->render->camera.x + app->win->GetWidth() / 2 - 99, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 }, this);
	Item2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 55, "item2", { -app->render->camera.x + app->win->GetWidth() / 2 - 4, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 }, this);
	Item3 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 56, "item3", { -app->render->camera.x + app->win->GetWidth() / 2 + 91, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 }, this);
	Item4 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 57, "item4", { -app->render->camera.x + app->win->GetWidth() / 2 + 186, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 }, this);
	Item5 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 58, "item5", { -app->render->camera.x + app->win->GetWidth() / 2 + 281, -app->render->camera.y + app->win->GetHeight() / 2 - 160, 70, 70 }, this);
	Item6 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 59, "item6", { -app->render->camera.x + app->win->GetWidth() / 2 - 99, -app->render->camera.y + app->win->GetHeight() / 2 - 64, 70, 70 }, this);
	Item7 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 60, "item7", { -app->render->camera.x + app->win->GetWidth() / 2 - 4, -app->render->camera.y + app->win->GetHeight() / 2 - 64, 70, 70 }, this);

	Character1->state = GuiControlState::NORMAL;
	Character2->state = GuiControlState::NORMAL;
	Character3->state = GuiControlState::NORMAL;
	Character4->state = GuiControlState::NORMAL;

	Item1->state = GuiControlState::NORMAL;
	Item2->state = GuiControlState::NORMAL;
	Item3->state = GuiControlState::NORMAL;
	Item4->state = GuiControlState::NORMAL;
	Item5->state = GuiControlState::NORMAL;
	Item6->state = GuiControlState::NORMAL;
	Item7->state = GuiControlState::NORMAL;
}

bool CharacterMenu_Screen::OnGuiMouseClickEvent(GuiControl* control)
{
	if (app->guiManager->CheackA1 == true)
	{
			switch (control->type)
			{
			case GuiControlType::BUTTON:
			{
				//Characters
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
				//Items
				//------------------1st grid pos----------------------
				if (control->id == 54 && increaseDmg > 0 && item1state)
				{
					if (Charac1 == true) {
						app->player->P1.damage += 10;
						increaseDmg -= 1;

					}
					if (Charac2 == true && app->player->P2.IsAlive == true) {
						app->player->P2.damage += 10;
						increaseDmg -= 1;

					}
					if (Charac3 == true && app->player->P3.IsAlive == true) {
						app->player->P3.damage += 10;
						increaseDmg -= 1;

					}
					if (Charac4 == true && app->player->P4.IsAlive == true) {
						app->player->P4.damage += 10;
						increaseDmg -= 1;

					}
					buttonCont = 0;
				}
				else if (control->id == 54 && healing > 0 && !item1state && item2state)
				{
					if (Charac1 == true) {
						app->player->P1.hp += 10;
						healing -= 1;

					}
					if (Charac2 == true && app->player->P2.IsAlive == true) {
						app->player->P2.hp += 10;
						healing -= 1;

					}
					if (Charac3 == true && app->player->P3.IsAlive == true) {
						app->player->P3.hp += 10;
						healing -= 1;

					}
					if (Charac4 == true && app->player->P4.IsAlive == true) {
						app->player->P4.hp += 10;
						healing -= 1;

					}
					buttonCont = 0;
				}
				else if (control->id == 54 && increaseMana > 0 && !item1state && !item2state && item3state)
				{
					if (Charac1 == true) {
						app->player->P1.mana += 10;
						increaseMana -= 1;
					}
					if (Charac2 == true && app->player->P2.IsAlive == true) {
						app->player->P2.mana += 10;
						increaseMana -= 1;
					}
					if (Charac3 == true && app->player->P3.IsAlive == true) {
						increaseMana -= 1;
						app->player->P3.mana += 10;
					}
					if (Charac4 == true && app->player->P4.IsAlive == true) {
						app->player->P4.mana += 10;
						increaseMana -= 1;
					}
					buttonCont = 0;
				}
				else if (control->id == 54 && increaseHP > 0 && !item1state && !item2state && !item3state && item4state)
				{
					if (Charac1 == true) {
						app->BTSystem->p1MaxHP += 20;
						app->player->P1.hp += 100;
						increaseHP--;
					}
					if (Charac2 == true && app->player->P2.IsAlive == true) {
						app->BTSystem->p2MaxHP += 20;
						app->player->P2.hp += 100;		
						increaseHP--;
					}
					if (Charac3 == true && app->player->P3.IsAlive == true) {
						app->BTSystem->p3MaxHP += 20;
						app->player->P3.hp += 100;		
						increaseHP--;
					}
					if (Charac4 == true && app->player->P4.IsAlive == true) {
						app->BTSystem->p4MaxHP += 20;
						app->player->P4.hp += 100;			
						increaseHP--;
					}
					buttonCont = 0;
				}
				else if (control->id == 54 && !item1state && !item2state && !item3state && !item4state && item5state)
				{
					if (app->BTSystem->battle == true)
					{
						app->BTSystem->transitionRep = 1;
						app->BTSystem->Delay = false;
						app->BTSystem->InventoryEnable = false;
						app->BTSystem->battleEnd = true;
						Character1->state = GuiControlState::DISABLED;
						Character2->state = GuiControlState::DISABLED;
						Character3->state = GuiControlState::DISABLED;
						Character4->state = GuiControlState::DISABLED;

						Item1->state = GuiControlState::DISABLED;
						Item2->state = GuiControlState::DISABLED;
						Item3->state = GuiControlState::DISABLED;
						Item4->state = GuiControlState::DISABLED;
						Item5->state = GuiControlState::DISABLED;
						Item6->state = GuiControlState::DISABLED;
						Item7->state = GuiControlState::DISABLED;
						app->BTSystem->CloseInventory->state = GuiControlState::DISABLED;

						exitInventory = true;
						inventory = false;
						smoke--;
					}
					else if (app->BTSystem->battle == false)
					{
						typingTxt = true;
					}

					buttonCont = 0;
				}
				else if (control->id == 54 && !item1state && !item2state && !item3state && !item4state && !item5state && item7state)
				{
					typingTxt2 = true;

					buttonCont = 0;
				}

				//------------------2nd grid pos----------------------
				if (control->id == 55 && healing > 0 && item1state && item2state)
				{
					if (Charac1 == true) {
						app->player->P1.hp += 10;
						healing -= 1;

					}
					if (Charac2 == true && app->player->P2.IsAlive == true) {
						app->player->P2.hp += 10;
						healing -= 1;

					}
					if (Charac3 == true && app->player->P3.IsAlive == true) {
						app->player->P3.hp += 10;
						healing -= 1;

					}
					if (Charac4 == true && app->player->P4.IsAlive == true) {
						app->player->P4.hp += 10;
						healing -= 1;

					}

					buttonCont = 0;
				}
				else if (control->id == 55 && increaseMana > 0 && item1state && !item2state && item3state || control->id == 55 && increaseMana > 0 && !item1state && item2state && item3state)
				{
					if (Charac1 == true) {
						app->player->P1.mana += 10;
						increaseMana -= 1;
					}
					if (Charac2 == true && app->player->P2.IsAlive == true) {
						app->player->P2.mana += 10;
						increaseMana -= 1;
					}
					if (Charac3 == true && app->player->P3.IsAlive == true) {
						increaseMana -= 1;
						app->player->P3.mana += 10;
					}
					if (Charac4 == true && app->player->P4.IsAlive == true) {
						app->player->P4.mana += 10;
						increaseMana -= 1;
					}
					buttonCont = 0;
				}
				else if (control->id == 55 && increaseHP > 0 && item1state && !item2state && !item3state && item4state || control->id == 55 && increaseHP > 0 && !item1state && item2state && !item3state && item4state || control->id == 55 && increaseHP > 0 && !item1state && !item2state && item3state && item4state)
				{				
					if (Charac1 == true) {
						app->BTSystem->p1MaxHP += 20;
						app->player->P1.hp += 100;
						increaseHP--;
					}
					if (Charac2 == true && app->player->P2.IsAlive == true) {
						app->BTSystem->p2MaxHP += 20;
						app->player->P2.hp += 100;
						increaseHP--;
					}
					if (Charac3 == true && app->player->P3.IsAlive == true) {
						app->BTSystem->p3MaxHP += 20;
						app->player->P3.hp += 100;
						increaseHP--;
					}
					if (Charac4 == true && app->player->P4.IsAlive == true) {
						app->BTSystem->p4MaxHP += 20;
						app->player->P4.hp += 100;
						increaseHP--;
					}
					buttonCont = 0;
				}
				else if (control->id == 55 && item1state && !item2state && !item3state && !item4state && item5state || control->id == 55 && !item1state && item2state && !item3state && !item4state && item5state ||	control->id == 55 && !item1state && !item2state && item3state && !item4state && item5state ||	control->id == 55 && !item1state && !item2state && !item3state && item4state && item5state)
				{
					if (app->BTSystem->battle == true)
					{
						app->BTSystem->transitionRep = 1;
						app->BTSystem->Delay = false;
						app->BTSystem->InventoryEnable = false;
						app->BTSystem->battleEnd = true;
						Character1->state = GuiControlState::DISABLED;
						Character2->state = GuiControlState::DISABLED;
						Character3->state = GuiControlState::DISABLED;
						Character4->state = GuiControlState::DISABLED;

						Item1->state = GuiControlState::DISABLED;
						Item2->state = GuiControlState::DISABLED;
						Item3->state = GuiControlState::DISABLED;
						Item4->state = GuiControlState::DISABLED;
						Item5->state = GuiControlState::DISABLED;
						Item6->state = GuiControlState::DISABLED;
						Item7->state = GuiControlState::DISABLED;
						app->BTSystem->CloseInventory->state = GuiControlState::DISABLED;

						exitInventory = true;
						inventory = false;
						smoke--;
					}
					else if (app->BTSystem->battle == false)
					{
						typingTxt = true;
					}

					buttonCont = 0;
				}
				else if (control->id == 55 && !item1state && !item2state && !item3state && !item4state && item5state && item7state ||control->id == 55 && !item1state && !item2state && !item3state && item4state && !item5state && item7state ||control->id == 55 && !item1state && !item2state && item3state && !item4state && !item5state && item7state ||control->id == 55 && !item1state && item2state && !item3state && !item4state && !item5state && item7state ||control->id == 55 && item1state && !item2state && !item3state && !item4state && !item5state && item7state)
				{
					typingTxt2 = true;

					buttonCont = 0;
				}

				//------------------3rd grid pos----------------------
				if (control->id == 56 && increaseMana > 0 && item1state && item2state && item3state)
				{
					if (Charac1 == true) {
						app->player->P1.mana += 10;
						increaseMana -= 1;
					}
					if (Charac2 == true && app->player->P2.IsAlive == true) {
						app->player->P2.mana += 10;
						increaseMana -= 1;
					}
					if (Charac3 == true && app->player->P3.IsAlive == true) {
						increaseMana -= 1;
						app->player->P3.mana += 10;					}
					if (Charac4 == true && app->player->P4.IsAlive == true) {
						app->player->P4.mana += 10;
						increaseMana -= 1;
					}
					buttonCont = 0;
				}
				else if (control->id == 56 && increaseHP > 0 && !item1state && item2state && item3state && item4state || control->id == 56 && increaseHP > 0 && item1state && !item2state && item3state && item4state ||	control->id == 56 && increaseHP > 0 && item1state && item2state && !item3state && item4state)
				{
					if (Charac1 == true) {
						app->BTSystem->p1MaxHP += 20;
						app->player->P1.hp += 100;
						increaseHP--;
					}
					if (Charac2 == true && app->player->P2.IsAlive == true) {
						app->BTSystem->p2MaxHP += 20;
						app->player->P2.hp += 100;
						increaseHP--;
					}
					if (Charac3 == true && app->player->P3.IsAlive == true) {
						app->BTSystem->p3MaxHP += 20;
						app->player->P3.hp += 100;
						increaseHP--;
					}
					if (Charac4 == true && app->player->P4.IsAlive == true) {
						app->BTSystem->p4MaxHP += 20;
						app->player->P4.hp += 100;
						increaseHP--;
					}
					buttonCont = 0;
				}
				else if (control->id == 56 && item1state && item2state && !item3state && !item4state && item5state|| control->id == 56 && item1state && !item2state && item3state && !item4state && item5state || control->id == 56 && item1state && !item2state && !item3state && item4state && item5state || control->id == 56 && !item1state && item2state && !item3state && item4state && item5state || control->id == 56 && !item1state && item2state && item3state && !item4state && item5state || control->id == 56 && !item1state && !item2state && item3state && item4state && item5state)
				{
					if (app->BTSystem->battle == true)
					{
						app->BTSystem->transitionRep = 1;
						app->BTSystem->Delay = false;
						app->BTSystem->InventoryEnable = false;
						app->BTSystem->battleEnd = true;
						Character1->state = GuiControlState::DISABLED;
						Character2->state = GuiControlState::DISABLED;
						Character3->state = GuiControlState::DISABLED;
						Character4->state = GuiControlState::DISABLED;

						Item1->state = GuiControlState::DISABLED;
						Item2->state = GuiControlState::DISABLED;
						Item3->state = GuiControlState::DISABLED;
						Item4->state = GuiControlState::DISABLED;
						Item5->state = GuiControlState::DISABLED;
						Item6->state = GuiControlState::DISABLED;
						Item7->state = GuiControlState::DISABLED;
						app->BTSystem->CloseInventory->state = GuiControlState::DISABLED;

						exitInventory = true;
						inventory = false;
						smoke--;
					}
					else if (app->BTSystem->battle == false)
					{
						typingTxt = true;
					}

					buttonCont = 0;
				}
				else if (control->id == 56 && item1state && !item2state && !item3state && !item4state && item5state && item7state || control->id == 56 && item1state && !item2state && !item3state && item4state && !item5state && item7state || control->id == 56 && item1state && !item2state && item3state && !item4state && !item5state && item7state || control->id == 56 && item1state && item2state && !item3state && !item4state && !item5state && item7state || control->id == 56 && !item1state && item2state && item3state && !item4state && !item5state && item7state ||	control->id == 56 && !item1state && item2state && !item3state && item4state && !item5state && item7state ||	control->id == 56 && !item1state && item2state && !item3state && !item4state && item5state && item7state ||	control->id == 56 && !item1state && !item2state && item3state && !item4state && item5state && item7state ||	control->id == 56 && !item1state && !item2state && item3state && item4state && !item5state && item7state ||	control->id == 56 && !item1state && !item2state && !item3state && item4state && item5state && item7state)
				{
					typingTxt2 = true;

					buttonCont = 0;
				}

				//------------------4th grid pos----------------------
				if (control->id == 57 && increaseHP > 0 && item1state && item2state && item3state && item4state)
				{
					if (Charac1 == true) {
						app->BTSystem->p1MaxHP += 20;
						app->player->P1.hp += 100;
						increaseHP--;
					}
					if (Charac2 == true && app->player->P2.IsAlive == true) {
						app->BTSystem->p2MaxHP += 20;
						app->player->P2.hp += 100;
						increaseHP--;
					}
					if (Charac3 == true && app->player->P3.IsAlive == true) {
						app->BTSystem->p3MaxHP += 20;
						app->player->P3.hp += 100;
						increaseHP--;
					}
					if (Charac4 == true && app->player->P4.IsAlive == true) {
						app->BTSystem->p4MaxHP += 20;
						app->player->P4.hp += 100;
						increaseHP--;
					}
					buttonCont = 0;
				}
				else if (control->id == 57 && !item1state && item2state && item3state && item4state && item5state || control->id == 57 && item1state && !item2state && item3state && item4state && item5state || control->id == 57 && item1state && item2state && !item3state && item4state && item5state || control->id == 57 && item1state && item2state && item3state && !item4state && item5state)
				{
					if (app->BTSystem->battle == true)
					{
						app->BTSystem->transitionRep = 1;
						app->BTSystem->Delay = false;
						app->BTSystem->InventoryEnable = false;
						app->BTSystem->battleEnd = true;
						Character1->state = GuiControlState::DISABLED;
						Character2->state = GuiControlState::DISABLED;
						Character3->state = GuiControlState::DISABLED;
						Character4->state = GuiControlState::DISABLED;

						Item1->state = GuiControlState::DISABLED;
						Item2->state = GuiControlState::DISABLED;
						Item3->state = GuiControlState::DISABLED;
						Item4->state = GuiControlState::DISABLED;
						Item5->state = GuiControlState::DISABLED;
						Item6->state = GuiControlState::DISABLED;
						Item7->state = GuiControlState::DISABLED;
						app->BTSystem->CloseInventory->state = GuiControlState::DISABLED;

						exitInventory = true;
						inventory = false;
						smoke--;
					}
					else if (app->BTSystem->battle == false)
					{
						typingTxt = true;
					}

					buttonCont = 0;
				}
				else if (control->id == 57 && item1state && item2state && item3state && !item4state && !item5state && item7state ||control->id == 57 && item1state && item2state && !item3state && item4state && !item5state && item7state ||control->id == 57 && item1state && item2state && !item3state && !item4state && item5state && item7state ||control->id == 57 && item1state && !item2state && item3state && item4state && !item5state && item7state ||control->id == 57 && item1state && !item2state && item3state && !item4state && item5state && item7state ||control->id == 57 && item1state && !item2state && !item3state && item4state && item5state && item7state ||control->id == 57 && !item1state && item2state && item3state && !item4state && item5state && item7state ||control->id == 57 && !item1state && item2state && item3state && item4state && !item5state && item7state ||control->id == 57 && !item1state && item2state && !item3state && item4state && item5state && item7state || control->id == 57 && !item1state && !item2state && item3state && item4state && item5state && item7state)
				{
					typingTxt2 = true;

					buttonCont = 0;
				}

				//------------------5th grid pos----------------------
				if (control->id == 58 && item1state && item2state && item3state && item4state  && item5state)
				{
					if (app->BTSystem->battle == true)
					{
						app->BTSystem->transitionRep = 1;
						app->BTSystem->Delay = false;
						app->BTSystem->InventoryEnable = false;
						app->BTSystem->battleEnd = true;		
						Character1->state = GuiControlState::DISABLED;
						Character2->state = GuiControlState::DISABLED;
						Character3->state = GuiControlState::DISABLED;
						Character4->state = GuiControlState::DISABLED;

						Item1->state = GuiControlState::DISABLED;
						Item2->state = GuiControlState::DISABLED;
						Item3->state = GuiControlState::DISABLED;
						Item4->state = GuiControlState::DISABLED;
						Item5->state = GuiControlState::DISABLED;
						Item6->state = GuiControlState::DISABLED;
						Item7->state = GuiControlState::DISABLED;
						app->BTSystem->CloseInventory->state = GuiControlState::DISABLED;

						exitInventory = true;
						inventory = false;
						smoke--;
					}
					else if (app->BTSystem->battle == false)
					{
						typingTxt = true;
					}

					buttonCont = 0;
				}
				else if (control->id == 58 && item1state && item2state && item3state && item4state && !item5state && item7state || control->id == 58 && item1state && item2state && item3state && !item4state && item5state && item7state || control->id == 58 && item1state && item2state && !item3state && item4state && item5state && item7state || control->id == 58 && item1state && !item2state && item3state && item4state && item5state && item7state || control->id == 58 && !item1state && item2state && item3state && item4state && item5state && item7state)
				{
					typingTxt2 = true;

					buttonCont = 0;
				}

				//------------------6th grid pos----------------------
				if (control->id == 59 && item1state && item2state && item3state && item4state && item5state && item7state)
				{
					typingTxt2 = true;

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



