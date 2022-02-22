#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"
#include "Render.h"
#include "Audio.h"

#include "Point.h"
#include "SString.h"

class GuiSlider : public GuiControl
{
public:

    GuiSlider(uint32 id, SDL_Rect bounds, const char* text);
    virtual ~GuiSlider();

    bool Update(float dt);
    bool Draw(bool camera, Render* render, Input* input);

    int GetValue();

    int mouseX, mouseY;
    int minValue;
    int maxValue;

    bool debugDraw = false;

private:

    // GuiSlider specific properties
    // Maybe some animation properties for state change?
    SDL_Rect slider;
    int value;



    SDL_Rect sliderRect = { 0, 0, 0, 0 };
    SDL_Rect innerRect;
};

#endif // __GUISLIDER_H__
