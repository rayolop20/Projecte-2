#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "GuiManager.h"
#include "EntityManager.h"
#include "Player.h"
#include "VampirEnem.h"
#include "Collisions.h"
#include "BattleSystem.h"

#include "Defs.h"
#include "Log.h"

battleSystem::battleSystem() : Module()
{
	name.Create("scene");
}

// Destructor
battleSystem::~battleSystem()
{}

// Called before render is available
bool battleSystem::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool battleSystem::Start()
{
	// L03: DONE: Load map
	
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	//L13: TODO 2: Declare an Item and create it using the EntityManager
	VampirEnem* Vampir = (VampirEnem*)app->entityManager->CreateEntity(EntityType::VAMPYRENEM, 0, { 20,20 });

	//L13: TODO 4: Create multiple Items

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	//btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { (app->win->GetWidth() / 2) - 300, app->win->GetWidth() / 10, 160, 40 }, this);
	//btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (app->win->GetWidth() / 2) + 300, app->win->GetWidth() / 10, 160, 40 }, this);

	return true;
}

// Called each loop iteration
bool battleSystem::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool battleSystem::Update(float dt)
{

	//app->map->DColisions();
	// L02: DONE 3: Request Load / Save when pressing L/S

	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		debug = !debug;

	}
	app->render->camera.x = (app->player->P1.position.x - 550) * -1;
	app->render->camera.y = (app->player->P1.position.y - 300) * -1;

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN && battle == false) {
		battle = true;
		/*if (player.speed >= enemy.speed) {
			turn = true;
		}
		else {
			enemyTurn = true;
		}*/
	}
	else if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN && battle == true) {
		battle = false;
	}
	app->input->GetMousePosition(x, y);
	if (battle) {
		SDL_Rect battleScreen = { 0,0,600,400 };
		SDL_Rect battleAtack = { 50,300,100,40 };
		SDL_Rect battleDefense = { 175,300,100,40 };
		SDL_Rect battleSpecial = { 50,350,100,40 };
		SDL_Rect battleRun = { 175,350,100,40 };
		app->render->DrawRectangle(battleScreen, 250, 250, 250);
		app->render->DrawRectangle(battleAtack, 250, 0, 0);
		app->render->DrawRectangle(battleDefense, 0, 0, 250);
		app->render->DrawRectangle(battleSpecial, 250, 250, 0);
		app->render->DrawRectangle(battleRun, 123, 123, 123);
		
		//Colisions interaction buttons
			for (int i = 0; i > 16; i+=4) {
				if (x > interactionButtons[i] + 355 && x < interactionButtons[i + 2] + interactionButtons[i] + 355 && y > interactionButtons[i + 1] + 180 && y < interactionButtons[i + 3] + interactionButtons[i + 1]+ 180) {
					if (i == 0) {
						//Atack();
						turn = false;
						enemyTurn = true;
					}
					if (i == 4) {
						//Defense();
						turn = false;
						enemyTurn = true;
					}
					if (i == 8) {
						//Special();
						turn = false;
						enemyTurn = true;
					}
					if (i == 12) {
						//Run();
						turn = false;
						enemyTurn = false;
						battle = false;
					}
					
				}
			}
		
	
	}
	// Draw map
	//app->map->Draw();

	//Draw GUI

	//Draw Entities
	//L13 
	app->entityManager->Draw();

	if (debug == true) {
		//Debug Collisions
		app->collisions->DebugDraw();
	}

	//InGameMenu
	/*if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		paused = true;

		Pause();

		btnResume->state = GuiControlState::NORMAL;
		btnMenu->state = GuiControlState::NORMAL;
		btnExit->state = GuiControlState::NORMAL;
		//rendered on last layer(collision.cpp)
	}
	if (paused)
	{
		btnResume->Update(dt);
		btnExit->Update(dt);
	}*/

	return true;
}

bool battleSystem::PostUpdate()
{
	bool ret = true;

//	if (app->menu->exit)
		//ret = false;

	return ret;
}

bool battleSystem::CleanUp()
{
	LOG("Freeing scene");

	return false;
}

bool battleSystem::OnGuiMouseClickEvent(GuiControl* control)
{
	/*switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID

		if (control->id == 4)
		{
			paused = false;
			btnResume->state = GuiControlState::DISABLED;
			btnMenu->state = GuiControlState::DISABLED;
			btnExit->state = GuiControlState::DISABLED;
		}

		if (control->id == 5)
		{
			paused = false;
			Disable();
			app->menu->Enable();
			app->player->Disable();
			app->render->camera.x = 0;
			app->render->camera.y = 0;
			app->menu->starting = true;
			btnResume->state = GuiControlState::DISABLED;
			btnMenu->state = GuiControlState::DISABLED;
			btnExit->state = GuiControlState::DISABLED;


		}

		if (control->id == 6)
		{
			app->menu->exit = true;
		}

	}
	//Other cases here

	default: break;
	}
	*/
	return false;
}

void battleSystem::Pause()
{
	//btnResume = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Resume", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 250, 160, 40 }, this);
	//btnMenu = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Menu", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 320, 160, 40 }, this);
	//btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Exit", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 390, 160, 40 }, this);

	//btnResume->state = GuiControlState::DISABLED;
	//btnMenu->state = GuiControlState::DISABLED;
	//btnExit->state = GuiControlState::DISABLED;
}
