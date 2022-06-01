#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Scene.h"
#include "Menu.h"
#include "StatsMenu.h"
#include "BattleSystem.h"
#include "EntityNPC.h"
#include "GuiManager.h"
#include "Menu.h"
#include "Fonts.h"


#include "DynArray.h"
#include "BattleSystem.h"
#include <time.h>
#include "Defs.h"
#include "Log.h"

StatsMenu_Screen::StatsMenu_Screen() : Module()
{
	name.Create("GameMenu");
}

// Destructor
StatsMenu_Screen::~StatsMenu_Screen()
{

}

// Called before render is available
bool StatsMenu_Screen::Awake()
{
	LOG("Loading Menu");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool StatsMenu_Screen::Start()
{

	StatsText = app->tex->Load("Assets/Textures/UI/stats_menu.png");
	American_S = app->tex->Load("Assets/Textures/Soldiers/american_dogmaster_attack_animation.png");
	Britain_S = app->tex->Load("Assets/Textures/Soldiers/soldier_britain_attack_animation.png");
	Italian_S = app->tex->Load("Assets/Textures/Soldiers/characters_italian_attack_animation.png");
	Russian_S = app->tex->Load("Assets/Textures/Soldiers/russian_attack_animation.png");
	French_S = app->tex->Load("Assets/Textures/Soldiers/french_attack_animation.png");
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	FText = app->fonts->Load("Assets/Textures/Fonts/fonts.png", lookupTable, 1);

	if (app->BTSystem->StatsEnable == false) {
		Disable();
	}
	return true;
}

// Called each loop iteration
bool StatsMenu_Screen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool StatsMenu_Screen::Update(float dt)
{
	Stats();
	return true;
}

// Called each loop iteration
bool StatsMenu_Screen::PostUpdate()
{
	bool ret = true;

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	return ret;
}

void StatsMenu_Screen::Stats()
{

	if (app->BTSystem->StatsEnable == true) {
		/*app->BTSystem->CloseStatsMenu->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2 - 80);
		app->BTSystem->CloseStatsMenu->bounds.y = -app->render->camera.y + 250;*/
		if (app->player->P1.IsAlive == true)
		{
			SDL_Rect* StatsPJ1 = new SDL_Rect();
			StatsPJ1->x = 70;
			StatsPJ1->y = 56;
			StatsPJ1->w = 278;
			StatsPJ1->h = 424;
			SDL_Rect* NamePJ1 = new SDL_Rect();
			NamePJ1->x = 7;
			NamePJ1->y = 17;
			NamePJ1->w = 99;
			NamePJ1->h = 110;
			app->render->DrawTexture(StatsText, app->player->P1.position.x - 610 + 32, app->player->P1.position.y - 220 + 32, StatsPJ1);
			app->render->DrawTexture(Britain_S, app->player->P1.position.x - 580 + 32, app->player->P1.position.y - 145 + 32, NamePJ1);
			sprintf_s(PJName, "britsh captain");
			app->fonts->DrawTxt(50, 158, FText, PJName);
			sprintf_s(PJAttack2, "lewis machine");
			app->fonts->DrawTxt(50, 350, FText, PJAttack2);
			sprintf_s(PJAttack2, "gun %0.f/3enem", app->player->P1.damage2);
			app->fonts->DrawTxt(50, 380, FText, PJAttack2);
			sprintf_s(PJAttack1, "lee enfild %0.f", app->player->P1.damage1);
			app->fonts->DrawTxt(50, 430, FText, PJAttack1);
			sprintf_s(PJSpecial, "_____________");
			app->fonts->DrawTxt(50, 450, FText, PJSpecial);
			sprintf_s(PJSpecial, "special atack");
			app->fonts->DrawTxt(50, 480, FText, PJSpecial);
			sprintf_s(PJSpecial, "poison enemy 2");
			app->fonts->DrawTxt(50, 510, FText, PJSpecial);
			sprintf_s(PJHp, "%0.f", app->player->P1.hp);
			app->fonts->DrawTxt(190, 207, FText, PJHp);
			sprintf_s(PJMana, "%0.f", app->player->P1.mana);
			app->fonts->DrawTxt(190, 233, FText, PJMana);
			sprintf_s(PJDmg, "%0.f", app->player->P1.damage);
			app->fonts->DrawTxt(190, 261, FText, PJDmg);
			sprintf_s(PJSpeed, "%0.f", app->player->P1.speed);
			app->fonts->DrawTxt(190, 291, FText, PJSpeed);
		}
		if (app->player->P2.IsAlive == true)
		{
			SDL_Rect* StatsPJ2 = new SDL_Rect();
			StatsPJ2->x = 70;
			StatsPJ2->y = 56;
			StatsPJ2->w = 278;
			StatsPJ2->h = 424;
			SDL_Rect* NamePJ2 = new SDL_Rect();
			NamePJ2->x = 4;
			NamePJ2->y = 2;
			NamePJ2->w = 131;
			NamePJ2->h = 110;
			app->render->DrawTexture(StatsText, app->player->P1.position.x - 332 + 64, app->player->P1.position.y - 220 + 32, StatsPJ2);
			app->render->DrawTexture(American_S, app->player->P1.position.x - 330 + 64, app->player->P1.position.y - 145 + 32, NamePJ2);
			sprintf_s(PJName, "american master");
			app->fonts->DrawTxt(355, 158, FText, PJName);
			sprintf_s(PJAttack2, "stubby %0.f", app->player->P2.damage2);
			app->fonts->DrawTxt(360, 350, FText, PJAttack2);
			sprintf_s(PJAttack1, "bar %0.f/3enem", app->player->P2.damage1);
			app->fonts->DrawTxt(360, 400, FText, PJAttack1);
			sprintf_s(PJSpecial, "_____________");
			app->fonts->DrawTxt(360, 450, FText, PJSpecial);
			sprintf_s(PJSpecial, "special atack");
			app->fonts->DrawTxt(360, 480, FText, PJSpecial);
			sprintf_s(PJSpecial, "burn enemy 30");
			app->fonts->DrawTxt(360, 510, FText, PJSpecial);
			sprintf_s(PJHp, "%0.f", app->player->P2.hp);
			app->fonts->DrawTxt(500, 207, FText, PJHp);
			sprintf_s(PJMana, "%0.f", app->player->P2.mana);
			app->fonts->DrawTxt(500, 233, FText, PJMana);
			sprintf_s(PJDmg, "%0.f", app->player->P2.damage);
			app->fonts->DrawTxt(500, 261, FText, PJDmg);
			sprintf_s(PJSpeed, "%0.f", app->player->P2.speed);
			app->fonts->DrawTxt(500, 291, FText, PJSpeed);
		}
		if (app->player->P3.IsAlive == true)
		{
			SDL_Rect* StatsPJ3 = new SDL_Rect();
			StatsPJ3->x = 70;
			StatsPJ3->y = 56;
			StatsPJ3->w = 278;
			StatsPJ3->h = 424;
			SDL_Rect* NamePJ3 = new SDL_Rect();
			NamePJ3->x = 35;
			NamePJ3->y = 7;
			NamePJ3->w = 134;
			NamePJ3->h = 110;
			app->render->DrawTexture(StatsText, app->player->P1.position.x - 54 + 96, app->player->P1.position.y - 220 + 32, StatsPJ3);
			app->render->DrawTexture(Russian_S, app->player->P1.position.x - 25 + 96, app->player->P1.position.y - 145 + 32, NamePJ3);
			sprintf_s(PJName, "russian sinper");
			app->fonts->DrawTxt(670, 158, FText, PJName);
			sprintf_s(PJAttack2, "revolver");
			app->fonts->DrawTxt(660, 350, FText, PJAttack2);
			sprintf_s(PJAttack2, "nagant %0.f", app->player->P3.damage2);
			app->fonts->DrawTxt(660, 380, FText, PJAttack2);
			sprintf_s(PJAttack1, "mosin_nagant %0.f", app->player->P3.damage1);
			app->fonts->DrawTxt(660, 430, FText, PJAttack1);
			sprintf_s(PJSpecial, "_____________");
			app->fonts->DrawTxt(660, 450, FText, PJSpecial);
			sprintf_s(PJSpecial, "special atack");
			app->fonts->DrawTxt(660, 480, FText, PJSpecial);
			sprintf_s(PJSpecial, "heal you 18");
			app->fonts->DrawTxt(660, 510, FText, PJSpecial);
			sprintf_s(PJHp, "%0.f", app->player->P3.hp);
			app->fonts->DrawTxt(805, 207, FText, PJHp);
			sprintf_s(PJMana, "%0.f", app->player->P3.mana);
			app->fonts->DrawTxt(805, 233, FText, PJMana);
			sprintf_s(PJDmg, "%0.f", app->player->P3.damage);
			app->fonts->DrawTxt(805, 261, FText, PJDmg);
			sprintf_s(PJSpeed, "%0.f", app->player->P3.speed);
			app->fonts->DrawTxt(805, 291, FText, PJSpeed);
		}
		if (app->player->P4.IsAlive == true && IsPJ4 == true)
		{
			SDL_Rect* StatsPJ4 = new SDL_Rect();
			StatsPJ4->x = 70;
			StatsPJ4->y = 56;
			StatsPJ4->w = 278;
			StatsPJ4->h = 424;
			SDL_Rect* NamePJ4 = new SDL_Rect();
			NamePJ4->x = 12;
			NamePJ4->y = 62;
			NamePJ4->w = 105;
			NamePJ4->h = 110;
			app->render->DrawTexture(StatsText, app->player->P1.position.x + 224 + 128, app->player->P1.position.y - 220 + 32, StatsPJ4);
			app->render->DrawTexture(Italian_S, app->player->P1.position.x + 248 + 128, app->player->P1.position.y - 145 + 32, NamePJ4);
			sprintf_s(PJName, "italian arditti");
			app->fonts->DrawTxt(970, 158, FText, PJName);
			sprintf_s(PJAttack2, "carcano");
			app->fonts->DrawTxt(970, 350, FText, PJAttack2);
			sprintf_s(PJAttack2, "rifle %0.f", app->player->P4.damage2);
			app->fonts->DrawTxt(970, 380, FText, PJAttack2);
			sprintf_s(PJAttack1, "vilar");
			app->fonts->DrawTxt(970, 430, FText, PJAttack1);
			sprintf_s(PJAttack1, "perosa %0.f/2enem", app->player->P4.damage1);
			app->fonts->DrawTxt(970, 460, FText, PJAttack1);
			sprintf_s(PJHp, "%0.f", app->player->P4.hp);
			app->fonts->DrawTxt(1110, 207, FText, PJHp);
			sprintf_s(PJMana, "%0.f", app->player->P4.mana);
			app->fonts->DrawTxt(1110, 233, FText, PJMana);
			sprintf_s(PJDmg, "%0.f", app->player->P4.damage);
			app->fonts->DrawTxt(1110, 261, FText, PJDmg);
			sprintf_s(PJSpeed, "%0.f", app->player->P4.speed);
			app->fonts->DrawTxt(1110, 291, FText, PJSpeed);
		}
		if (app->player->P4.IsAlive == true && IsPJ4 == false)
		{
			SDL_Rect* StatsPJ5 = new SDL_Rect();
			StatsPJ5->x = 70;
			StatsPJ5->y = 56;
			StatsPJ5->w = 278;
			StatsPJ5->h = 424;
			SDL_Rect* NamePJ5 = new SDL_Rect();
			NamePJ5->x = 29;
			NamePJ5->y = 9;
			NamePJ5->w = 121;
			NamePJ5->h = 110;
			app->render->DrawTexture(StatsText, app->player->P1.position.x + 224 + 128, app->player->P1.position.y - 220 + 32, StatsPJ5);
			app->render->DrawTexture(French_S, app->player->P1.position.x + 233 + 128, app->player->P1.position.y - 145 + 32, NamePJ5);
			sprintf_s(PJName, "french rusher");
			app->fonts->DrawTxt(985, 158, FText, PJName);

			sprintf_s(PJAttack2, "clous");
			app->fonts->DrawTxt(980, 350, FText, PJAttack2);
			sprintf_s(PJAttack2, "francais %0.f", app->player->P5.damage1);
			app->fonts->DrawTxt(980, 380, FText, PJAttack2);
			sprintf_s(PJAttack1, "revolver %0.f", app->player->P5.damage2);
			app->fonts->DrawTxt(980, 430, FText, PJAttack1);

			sprintf_s(PJSpecial, "_____________");
			app->fonts->DrawTxt(970, 450, FText, PJSpecial);
			sprintf_s(PJSpecial, "special atack");
			app->fonts->DrawTxt(970, 480, FText, PJSpecial);
			sprintf_s(PJSpecial, "crit hit 75");
			app->fonts->DrawTxt(970, 510, FText, PJSpecial);

			sprintf_s(PJHp, "%0.f", app->player->P5.hp);
			app->fonts->DrawTxt(1110, 207, FText, PJHp);
			sprintf_s(PJMana, "%0.f", app->player->P5.mana);
			app->fonts->DrawTxt(1110, 233, FText, PJMana);
			sprintf_s(PJDmg, "%0.f", app->player->P5.damage);
			app->fonts->DrawTxt(1110, 261, FText, PJDmg);
			sprintf_s(PJSpeed, "%0.f", app->player->P5.speed);
			app->fonts->DrawTxt(1110, 291, FText, PJSpeed);
		}
	}
}

bool StatsMenu_Screen::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}

void StatsMenu_Screen::ShowStats(int a)
{
}

bool StatsMenu_Screen::CleanUp()
{

	LOG("Freeing scene");
	return true;
}
