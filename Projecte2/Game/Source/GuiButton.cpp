#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Scene.h"
#include "Window.h"
#include "Textures.h"
#include "Player.h"
#include "Animation.h"
#include "BattleSystem.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;

	canClick = true;
	drawBasic = false;

	UIText = app->tex->Load("Assets/textures/UI/MainMenu.png");
	BTLText = app->tex->Load("Assets/textures/UI/CombatUI.png");

}

GuiButton::~GuiButton()
{
}

bool GuiButton::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		mouseX += -app->render->camera.x / app->win->GetScale();
		mouseY += -app->render->camera.y / app->win->GetScale();

		if ((mouseX > bounds.x ) && (mouseX < (bounds.x + bounds.w )) &&
			(mouseY > bounds.y ) && (mouseY < (bounds.y + bounds.h )))
		{
			state = GuiControlState::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = GuiControlState::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}
		}
		else state = GuiControlState::NORMAL;
	}

	return false;
}

bool GuiButton::Draw(Render* render)
{

	// Draw the right button depending on state
	switch (state)
	{

	case GuiControlState::DISABLED: 
	{

		render->DrawRectangle(bounds, 0, 0, 0, 0);

	} break;

	case GuiControlState::NORMAL:
	{
		//new game
		if (id == 1)
		{
			uitext->x = 160;
			uitext->y = 930;
			uitext->w = 194;
			uitext->h = 52;
			app->render->DrawTexture(UIText, 150, 150, uitext);
		}
		//Options
		if (id == 2)
		{
			uitext->x = 188;
			uitext->y = 295;
			uitext->w = 144;
			uitext->h = 57;
			app->render->DrawTexture(UIText, 150, 240, uitext);
		}
		//Exit
		if (id == 3)
		{
			uitext->x = 256;
			uitext->y = 627;
			uitext->w = 78;
			uitext->h = 51;
			app->render->DrawTexture(UIText, 150, 420, uitext);
		}
		//resume
		if (id == 5)
		{
			uitext->x = 198;
			uitext->y = 125;
			uitext->w = 193;
			uitext->h = 51;
			app->render->DrawTexture(UIText, -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 250, uitext);
		}
		//return menu
		if (id == 6)
		{
			uitext->x = 228;
			uitext->y = 1075;
			uitext->w = 144;
			uitext->h = 57;
			app->render->DrawTexture(UIText, -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 320, uitext);
		}
		//Exit
		if (id == 9)
		{
			uitext->x = 256;
			uitext->y = 627;
			uitext->w = 78;
			uitext->h = 51;
			app->render->DrawTexture(UIText, -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 390, uitext);
		}
		
		//Atack
		if (id == 31 && app->BTSystem->battle == true)
		{
			uitext->x = 26;
			uitext->y = 2;
			uitext->w = 152;
			uitext->h = 59;
			app->render->DrawTexture(BTLText, app->player->P1.position.x - 165, app->player->P1.position.y + 210, uitext);
		}
		
		//Special
		if (id == 34 && app->BTSystem->battle == true)
		{
			uitext->x = 198;
			uitext->y = 2;
			uitext->w = 152;
			uitext->h = 59;
			app->render->DrawTexture(BTLText, app->player->P1.position.x + 15, app->player->P1.position.y + 210, uitext);
		}
		
		//Inventory
		if (id == 35 && app->BTSystem->battle == true)
		{
			uitext->x = 26;
			uitext->y = 82;
			uitext->w = 153;
			uitext->h = 59;
			app->render->DrawTexture(BTLText, app->player->P1.position.x - 165, app->player->P1.position.y + 285, uitext);
		}
		
		//Run
		if (id == 36 && app->BTSystem->battle == true)
		{
			uitext->x = 198;
			uitext->y = 82;
			uitext->w = 152;
			uitext->h = 59;
			app->render->DrawTexture(BTLText, app->player->P1.position.x + 15, app->player->P1.position.y + 285, uitext);
		}
		else
		{
			
			render->DrawRectangle(bounds, 255, 255, 255, 160);
		}
	} break;

	//L14: TODO 4: Draw the button according the GuiControl State
	case GuiControlState::FOCUSED:
	{
		//new game
		if (id == 1)
		{
			uitext->x = 790;
			uitext->y = 930;
			uitext->w = 194;
			uitext->h = 52;
			app->render->DrawTexture(UIText, 150, 150, uitext);

			/*uitext->x = 1211; //Blood drop
			uitext->y = 150;
			uitext->w = 70;
			uitext->h = 70;
			app->render->DrawTexture(UIText, 80, 150, uitext);*/
		}
		//options
		if (id == 2)
		{
			uitext->x = 825;
			uitext->y = 295;
			uitext->w = 144;
			uitext->h = 57;
			app->render->DrawTexture(UIText, 150, 240, uitext);
		}
		//Exit
		if (id == 3)
		{
			uitext->x = 893;
			uitext->y = 627;
			uitext->w = 78;
			uitext->h = 51;
			app->render->DrawTexture(UIText, 150, 420, uitext);
		}
		//resume
		if (id == 5)
		{
			uitext->x = 832;
			uitext->y = 125;
			uitext->w = 193;
			uitext->h = 51;
			app->render->DrawTexture(UIText, -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 250, uitext);
		}

		//return menu
		if (id == 6)
		{
			uitext->x = 858;
			uitext->y = 1075;
			uitext->w = 144;
			uitext->h = 57;
			app->render->DrawTexture(UIText, -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 320, uitext);
		}
		//Exit
		if (id == 9)
		{
			uitext->x = 893;
			uitext->y = 627;
			uitext->w = 78;
			uitext->h = 51;
			app->render->DrawTexture(UIText, -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 390, uitext);
		}

		//Atack
		if (id == 31 && app->BTSystem->battle == true)
		{
			uitext->x = 25;
			uitext->y = 187;
			uitext->w = 152;
			uitext->h = 59;
			app->render->DrawTexture(BTLText, app->player->P1.position.x - 165, app->player->P1.position.y + 210, uitext);
		}

		//Special
		if (id == 34 && app->BTSystem->battle == true)
		{
			uitext->x = 198;
			uitext->y = 187;
			uitext->w = 152;
			uitext->h = 59;
			app->render->DrawTexture(BTLText, app->player->P1.position.x + 15, app->player->P1.position.y + 210, uitext);
		}

		//Inventory
		if (id == 35 && app->BTSystem->battle == true)
		{
			uitext->x = 25;
			uitext->y = 267;
			uitext->w = 153;
			uitext->h = 59;
			app->render->DrawTexture(BTLText, app->player->P1.position.x - 165, app->player->P1.position.y + 285, uitext);
		}

		//Run
		if (id == 36 && app->BTSystem->battle == true)
		{
			uitext->x = 197;
			uitext->y = 267;
			uitext->w = 152;
			uitext->h = 59;
			app->render->DrawTexture(BTLText, app->player->P1.position.x + 15, app->player->P1.position.y + 285, uitext);
		}
		else
		{
			render->DrawRectangle(bounds, 255, 255, 255, 160);
		}
		
	} break;
	case GuiControlState::PRESSED:
	{
		//new game
		if (id == 1)
		{
			uitext->x = 339;
			uitext->y = 854;
			uitext->w = 194;
			uitext->h = 52;
			app->render->DrawTexture(UIText, 150, 150, uitext);
		}
		//options
		if (id == 2)
		{
			uitext->x = 373;
			uitext->y = 222;
			uitext->w = 144;
			uitext->h = 57;
			app->render->DrawTexture(UIText, 150, 240, uitext);
		}
		//Exit
		if (id == 3)
		{
			uitext->x = 442;
			uitext->y = 553;
			uitext->w = 78;
			uitext->h = 51;
			app->render->DrawTexture(UIText, 150, 420, uitext);
		}
		//resume
		if (id == 5)
		{
			uitext->x = 327;
			uitext->y = 51;
			uitext->w = 193;
			uitext->h = 51;
			app->render->DrawTexture(UIText, -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 250, uitext);
		}

		//return menu
		if (id == 6)
		{
			uitext->x = 373;
			uitext->y = 222;
			uitext->w = 144;
			uitext->h = 57;
			app->render->DrawTexture(UIText, -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 320, uitext);
		}
		//Exit
		if (id == 9)
		{
			uitext->x = 442;
			uitext->y = 553;
			uitext->w = 78;
			uitext->h = 51;
			app->render->DrawTexture(UIText, -app->render->camera.x + (app->win->GetWidth() / 2 - 80), -app->render->camera.y + 390, uitext);
		}
		//Atack
		if (id == 31 && app->BTSystem->battle == true)
		{
			uitext->x = 25;
			uitext->y = 187;
			uitext->w = 152;
			uitext->h = 59;
			app->render->DrawTexture(BTLText, app->player->P1.position.x - 165, app->player->P1.position.y + 210, uitext);
		}

		//Special
		if (id == 34 && app->BTSystem->battle == true)
		{
			uitext->x = 198;
			uitext->y = 187;
			uitext->w = 152;
			uitext->h = 59;
			app->render->DrawTexture(BTLText, app->player->P1.position.x + 15, app->player->P1.position.y + 210, uitext);
		}

		//Inventory
		if (id == 35 && app->BTSystem->battle == true)
		{
			uitext->x = 25;
			uitext->y = 267;
			uitext->w = 153;
			uitext->h = 59;
			app->render->DrawTexture(BTLText, app->player->P1.position.x - 165, app->player->P1.position.y + 285, uitext);
		}

		//Run
		if (id == 36 && app->BTSystem->battle == true)
		{
			uitext->x = 197;
			uitext->y = 267;
			uitext->w = 152;
			uitext->h = 59;
			app->render->DrawTexture(BTLText, app->player->P1.position.x + 15, app->player->P1.position.y + 285, uitext);
		}
		else
		{
			render->DrawRectangle(bounds, 255, 255, 255, 160);
		}
	} break;

	/******/

	case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
		break;

	default:
		break;
	}


	return false;
}