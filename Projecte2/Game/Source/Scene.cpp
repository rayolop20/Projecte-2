#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "GuiManager.h"
#include "EntityManager.h"
#include "Player.h"
#include "VampirEnem.h"
#include "Collisions.h"
#include "Menu.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// L03: DONE: Load map
	app->map->Load("Mapa_Prova.tmx");
	
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	//L13: TODO 2: Declare an Item and create it using the EntityManager
	VampirEnem* Vampir = (VampirEnem*)app->entityManager->CreateEntity(EntityType::VAMPYRENEM, 0, {10, 10});
	
	//L13: TODO 4: Create multiple Items

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	//btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { (app->win->GetWidth() / 2) - 300, app->win->GetWidth() / 10, 160, 40 }, this);
	//btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (app->win->GetWidth() / 2) + 300, app->win->GetWidth() / 10, 160, 40 }, this);

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	app->map->DColisions();
    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
		app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		debug = !debug;
	
	}
	app->render->camera.x = (app->player->P1.position.x - 550) * -1;
	app->render->camera.y = (app->player->P1.position.y - 300) * -1;


	// L08: TODO 6: Make the camera movement independent of framerate
	/*float speed = 1;
	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= speed;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += speed;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= speed;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += speed;
		*/
	// Draw map
	app->map->Draw();

	//Draw GUI
	
	//Draw Entities
	//L13 
	app->entityManager->Draw();

	if (debug == true) {
		//Debug Collisions
		app->collisions->DebugDraw();
	}

	//InGameMenu
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
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
	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->menu->exit)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void Scene::Pause()
{

	btnResume = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Resume", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 250, 160, 40 }, this);
	btnMenu = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Exit", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 320, 160, 40 }, this);
	btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Exit", { -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 390, 160, 40 }, this);

	btnResume->state = GuiControlState::DISABLED;
	btnMenu->state = GuiControlState::DISABLED;
	btnExit->state = GuiControlState::DISABLED;
}

bool Scene::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID		

		if (control->id == 2)
		{
			paused = false;
			btnResume->state = GuiControlState::DISABLED;
			btnMenu->state = GuiControlState::DISABLED;
			btnExit->state = GuiControlState::DISABLED;
		}

		if (control->id == 3)
		{
			paused = false;
			Disable();
			app->menu->Enable();
			app->player->Disable();
			app->render->camera.x = 0;
			app->render->camera.y = 0;
			btnResume->state = GuiControlState::DISABLED;
			btnMenu->state = GuiControlState::DISABLED;
			btnExit->state = GuiControlState::DISABLED;

			
		}

		if (control->id == 4)
		{
			app->menu->exit = true;
		}

	}
	//Other cases here

	default: break;
	}

	return true;
}