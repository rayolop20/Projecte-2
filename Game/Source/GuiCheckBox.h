#ifndef __GUICHECKBOX_H__
#define __GUICHECKBOX_H__

#include "GuiControl.h"
#include "Render.h"
#include "Audio.h"

#include "Point.h"
#include "SString.h"

class GuiCheckBox : public GuiControl
{
public:

    GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text);
    virtual ~GuiCheckBox();

    bool Update(float dt);
    bool Draw(Render* render);

    int mouseX, mouseY;
    unsigned int click;

    bool checked;

    bool debugDraw = false;

private:

    // GuiCheckBox specific properties
    // Maybe some animation properties for state change?

};

#endif // __GUICHECKBOX_H__
