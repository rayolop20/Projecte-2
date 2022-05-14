#include "GuiSlider.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Scene.h"
#include "Window.h"
#include "Textures.h"
#include "Player.h"
#include "Animation.h"
#include "BattleSystem.h"
#include "Menu.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::SLIDER, id)
{
    this->bounds = bounds;
    this->text = text;
    this->maxValue = 128;
    this->minValue = 0;
    innerRect = bounds;
    innerRect.h = 40;
    innerRect.w = 40;
    innerRect.y += bounds.h / 4;
}

GuiSlider::~GuiSlider()
{
}

bool GuiSlider::Update(float dt)
{
    if (state != GuiControlState::DISABLED)
    {
        // L14: TODO 3: Update the state of the GUiButton according to the mouse position
        int mouseX, mouseY;
        app->input->GetMousePosition(mouseX, mouseY);
        
        if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
            (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
        {
            state = GuiControlState::FOCUSED;

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
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

bool GuiSlider::Draw(bool camera, Render* render, Input* input)
{
    input->GetMousePosition(mouseX, mouseY);

    if (camera == true)
    {
        mouseX = mouseX + render->camera.x * -1;
        mouseY = mouseY + render->camera.y * -1;
    }

    // Draw the right button depending on state
    if (!debugDraw)
    {
        switch (state)
        {
        case GuiControlState::DISABLED: render->DrawRectangle(bounds,  0, 0, 0, 100 );
            break;
        case GuiControlState::NORMAL: render->DrawRectangle(bounds, 0, 255, 0, 0 );
            break;
        case GuiControlState::FOCUSED: render->DrawRectangle(bounds,  0, 0, 255, 0 );
            break;
        case GuiControlState::PRESSED:
            render->DrawRectangle(bounds, 155, 103, 60, 0 );
            sliderRect = { bounds.x, bounds.y, mouseX - bounds.x, bounds.h };
            innerRect.x = sliderRect.w + sliderRect.x;
            innerRect.x -= innerRect.w / 2;
            innerRect.y = sliderRect.y + sliderRect.h / 4;
            innerRect.h = sliderRect.h - sliderRect.h / 2;
            innerRect.w = innerRect.h;
            break;
        case GuiControlState::SELECTED: render->DrawRectangle(bounds,  0, 255, 0, 0 );
            break;
        default:
            break;
        }
    }

    else
    {
        switch (state)
        {
        case GuiControlState::DISABLED: render->DrawRectangle(bounds,  0, 0, 0, 0 );
            break;
        case GuiControlState::NORMAL: render->DrawRectangle(bounds, 0, 255, 0, 0 );
            break;
        case GuiControlState::FOCUSED: render->DrawRectangle(bounds,  0, 0, 255, 0 );
            break;
        case GuiControlState::PRESSED:
            render->DrawRectangle(bounds,  255, 0, 255, 0 );
            sliderRect = { bounds.x, bounds.y, mouseX - bounds.x, bounds.h };
            innerRect.x = sliderRect.w + sliderRect.x;
            innerRect.x -= innerRect.w / 2;
            innerRect.y = sliderRect.y + sliderRect.h / 4;
            innerRect.h = sliderRect.h - sliderRect.h / 2;
            innerRect.w = innerRect.h;
            break;
        case GuiControlState::SELECTED: render->DrawRectangle(bounds,  0, 255, 0, 0 );
            break;
        default:
            break;
        }
    }

    if (state == GuiControlState::PRESSED)
        value = (int)((float)sliderRect.w / (float)((float)bounds.w / (float)maxValue));

    if (!debugDraw)
    {
        render->DrawRectangle(sliderRect,  0, 0, 255, 0 );
        if (sliderRect.x == bounds.x) render->DrawRectangle(innerRect, 155, 103, 60, 255 );
    }

    else
    {
        render->DrawRectangle(sliderRect, 0, 255, 255, 0 );
        if (sliderRect.x == bounds.x) render->DrawRectangle(innerRect, 155, 103, 60, 255 );
    }

    return false;
}

int GuiSlider::GetValue()
{
    return value;
}