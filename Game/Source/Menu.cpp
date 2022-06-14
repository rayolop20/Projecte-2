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
#include "AssetsManager.h"
#include "EasingFunctions.h"

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
	// no ens fa falta i no se Pk
	{
	/*
	char* buffer = 0;
	pugi::xml_document dataFile;

	int bytesFile = app->assetManager->LoadData("data.xml", &buffer);

	// Loading from memory with PUGI: https://pugixml.org/docs/manual.html#loading.memory
	pugi::xml_parse_result result = dataFile.load_buffer(buffer, bytesFile);

	RELEASE_ARRAY(buffer);

	LoadTexFile(dataFile);
	LoadFxFile(dataFile);
	LoadMusFile(dataFile);
	*/
	speedX = 0;

	total_iterations = 64;

	pointA = { -20, 0 };
	pointB = { 2, 0 };
	MenuA = {0 , 0};
	MenuB = {5, 0};
	easing_active = true;
	app->render->camera.x -= 500;
	}
	EnterLogo = app->audio->LoadFx("Assets/Audio/Fx/enter_logo.wav");
	fonsMenu = app->tex->Load("Assets/Textures/Assets/game_title.png");
	creditsTexture = app->tex->Load("Assets/Textures/UI/credits.png");
	Logo = app->tex->Load("Assets/Textures/Assets/logo_projecte.png");
	options = app->tex->Load("Assets/Textures/UI/Pause_Menu.png");
	btnMenuPlay = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Play", { 150, 150, 194, 52 }, this);
	btnMenuConfig = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Config", { 150, 240, 144, 57 }, this);
	btnCredits = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Credits", { 150, 330, 144, 57 }, this);
	btnMenuExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Exit", { 150, 420, 78, 51 }, this);
	btnConfigBack = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "Back to menu", { 450, 625, 418, 62 }, this);
	btnFullscreen = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 81, "Fullscreen", { 0, 0, 263, 78 }, this);
	btnFPS = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 82, "FPS", { 0, 0, 263, 78 }, this);
	btnVsync = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 84, "Fullscreen", { 0, 0, 263, 78 }, this);

	Volume = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 83, "Volumen", { 585, 125, 460, 30 }, this);
	Volume->maxValue = app->audio->maxMusicValue;
	Volume->minValue = 0;
	
	OptionsTxt->x = 0;
	OptionsTxt->y = 0;
	OptionsTxt->w = 0;
	OptionsTxt->h = 559;

	btnFPS->state = GuiControlState::DISABLED;
	btnConfigBack->state = GuiControlState::DISABLED;
	btnFullscreen->state = GuiControlState::DISABLED;
	btnMenuPlay->state = GuiControlState::DISABLED;
	btnMenuConfig->state = GuiControlState::DISABLED;
	btnCredits->state = GuiControlState::DISABLED;
	btnMenuExit->state = GuiControlState::DISABLED;
	Volume->state = GuiControlState::DISABLED;

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
	timerCredits = SDL_GetTicks() / 10;
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);

	//music
	if (musicActive == true && menuScreen == false)
	{
		app->audio->PlayMusic("Assets/Audio/Music/music_retro_forest.ogg");
		musicActive = false;
	}


	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->Pad->GetButton(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN)
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

		controlCursor = true;
	}

		
	
	if (easing_active == true) {
		app->render->camera.x -= EaseCameraBetweenPoints(pointA, pointB) * dt;
	}
	if (app->menu->config == false && easing_active == false) {
		app->render->DrawTexture(app->menu->options, 215, 65, OptionsTxt);
		if (OptionsTxt->w <= 918 && OptionsTxt->w >= 0) {
			OptionsTxt->w -= EaseCameraBetweenPoints(MenuA, MenuB) * dt;
		}
	}
	if (app->menu->config == true) {
		
		/*SDL_Rect* OptionsTxt = new SDL_Rect();
		OptionsTxt->x = 0;
		OptionsTxt->y = 0;
		OptionsTxt->w = 0;
		OptionsTxt->h = 559;
		*/
		SDL_Rect* OptionsOn = new SDL_Rect();
		OptionsOn->x = 8;
		OptionsOn->y = 650;
		OptionsOn->w = 263;
		OptionsOn->h = 78;
		SDL_Rect* OptionsOff = new SDL_Rect();
		OptionsOff->x = 8;
		OptionsOff->y = 568;
		OptionsOff->w = 263;
		OptionsOff->h = 78;
		SDL_Rect* Options60 = new SDL_Rect();
		Options60->x = 272;
		Options60->y = 568;
		Options60->w = 263;
		Options60->h = 78;
		SDL_Rect* Options30 = new SDL_Rect();
		Options30->x = 274;
		Options30->y = 650;
		Options30->w = 263;
		Options30->h = 78;

		if (OptionsTxt->w < 918 && OptionsTxt->w >= 0) {
			OptionsTxt->w += EaseCameraBetweenPoints(MenuA, MenuB) * dt;
		}
		if (OptionsTxt->w < 0) {
			OptionsTxt->w ++;
		}
		else if (OptionsTxt->w > 918)
		{
			OptionsTxt->w--;
		}
	
		app->render->DrawTexture(app->menu->options, 215, 65, OptionsTxt);
		app->menu->btnConfigBack->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) - 150;
		app->menu->btnConfigBack->bounds.y = -app->render->camera.y + 650;
		if (app->menu->On == true) {
			app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 242, OptionsOn);
			//Activar Fullscreen
			SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN);
		}
		if (app->menu->On == false) {
			app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 242, OptionsOff);
			//Desactivar Fullscreen
			SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_MAXIMIZED);
		}
		if (app->menu->fps30 == true) {
			app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 375, Options60);

			//app->dt = 32.0f;
			app->Maxfps = false;
		}
		if (app->menu->fps30 == false) {
			app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 375, Options30);
			//Desactivar 60fps
			//app->dt = 16.0f;
			app->Maxfps = true;
		}
		
		if (app->menu->VsyncEnable == true) {
			app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 505, OptionsOn);
			app->render->VsyncActive = true;
		}
		if (app->menu->VsyncEnable == false) {
			app->render->DrawTexture(app->menu->options, -app->render->camera.x + (app->win->GetWidth() / 2) + 190, -app->render->camera.y + 500, OptionsOff);
			app->render->VsyncActive = false;
		}
		btnFullscreen->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) + 190;
		btnFullscreen->bounds.y = -app->render->camera.y + 240;
		btnFullscreen->state = GuiControlState::NORMAL;
		btnFPS->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) + 175;
		btnFPS->bounds.y = -app->render->camera.y + 375;
		btnFPS->state = GuiControlState::NORMAL;
		btnVsync->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) + 175;
		btnVsync->bounds.y = -app->render->camera.y + 500;
		btnVsync->state = GuiControlState::NORMAL;
		Volume->Draw(true, app->render, app->input);
		Volume->state = GuiControlState::NORMAL;

	}
	//logo i fons de pantalla

	if (credits == true) {
		CreditPhase();
	}

	return true;
}

void Menu_Screen::CreditPhase() {
	if (timerCreditCount == 0) {
		timerCreditsaux = timerCredits;
		timerCreditCount = 1;
	}
	app->render->DrawTexture(creditsTexture, 0, -(timerCredits - timerCreditsaux));
	if ((timerCredits - timerCreditsaux) > 4000 || app->input->GetKey(SDL_SCANCODE_RETURN)==KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->Pad->GetButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) {
 		credits = false;
		timerCreditCount = 0;
	}
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
	app->menu->btnConfigBack->bounds.x = -app->render->camera.x + (app->win->GetWidth() / 2) - 200;
	app->menu->btnConfigBack->bounds.y = -app->render->camera.y + 625;
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
				if (control->id == 1 && credits == false)
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

					controlCursor = false;

					//CleanUp();
				}

				if (control->id == 2 && playing == false && credits == false)
				{
					LOG("Config ON");
					config = true;
					btnConfigBack->state = GuiControlState::NORMAL;
					btnMenuPlay->state = GuiControlState::DISABLED;
					btnMenuConfig->state = GuiControlState::DISABLED;
					btnMenuExit->state = GuiControlState::DISABLED;
					btnCredits->state = GuiControlState::DISABLED;

					controlCursor = false;
				}
				if (control->id == 2 && playing == true && credits == false)
				{
					LOG("Config ON");
					config = true;
					btnConfigBack->state = GuiControlState::NORMAL;
					app->menu->btnMenuConfig->state = GuiControlState::DISABLED;
					app->gameMenu->btnResume->state = GuiControlState::DISABLED;
					app->gameMenu->btnMenu->state = GuiControlState::DISABLED;
					app->gameMenu->btnExit->state = GuiControlState::DISABLED;

					controlCursor = false;
				}
				
				if (control->id == 3 && credits == false)
				{
					exit = true;

					controlCursor = false;
				}
				
				if (control->id == 4 && credits == false)
				{
					credits = true;

					controlCursor = false;
				}

				if (control->id == 7 && credits == false)
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
				if (control->id == 81 && On == true) {
					On = false;
				}
				else if (control->id == 81 && On == false) {
					On = true;
				}
				if (control->id == 82 && fps30 == true) {
					fps30 = false;
				}
				else if (control->id == 82 && fps30 == false) {
					fps30 = true;
				}
				
				if (control->id == 84 && VsyncEnable == true) {
					VsyncEnable = false;
				}
				else if (control->id == 84 && VsyncEnable == false) {
					VsyncEnable = true;
				}
			case GuiControlType::SLIDER:
			{
				if (control->id == 83)
				{
					app->audio->MusicVolumeControl(Volume->GetValue());
					app->audio->FxVolumeControl(Volume->GetValue());
				}
				break;
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
		/*
		app->guiManager->DestroyGuiControl(btnMenuConfig);
		app->guiManager->DestroyGuiControl(btnConfigBack);
		app->guiManager->DestroyGuiControl(btnCredits);
		app->guiManager->DestroyGuiControl(btnMenuExit);
		app->guiManager->DestroyGuiControl(btnMenuPlay);
		app->guiManager->DestroyGuiControl(btnConfigEx1);
		app->tex->UnLoad(options);
		app->tex->UnLoad(fonsMenu);
		app->tex->UnLoad(Logo);
		*/
	return true;
}

float Menu_Screen::EaseCameraBetweenPoints(iPoint posA, iPoint posB)
{
	float value = function.backEaseOut(iterations, posA.x, posB.x - posA.x, total_iterations);


	//speedY = function.linearEaseNull(iterations, 472, 572, 300);

	//App->render->camera.y += speedY;

	if (iterations < total_iterations) {
		iterations++;
	}

	else {
		iterations = 0;
		easing_active = false;
	}

	return value;
}