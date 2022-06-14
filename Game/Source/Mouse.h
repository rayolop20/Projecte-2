#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "Module.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class Mouse : public Module
{
public:

	Mouse();

	virtual ~Mouse();

	bool Start();

	bool Update(float dt);

	bool PostUpdate();

	bool Draw();

	SDL_Rect cursor;

private:

	SDL_Texture* cursor_img;
	SDL_Rect point;

	int mouseV = 10;

	bool MouseOn = true;
	bool ControllerOn = false;

};

#endif //__MOUSE_H__