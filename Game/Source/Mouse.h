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

private:

	SDL_Texture* cursor_img;
	SDL_Rect cursor;
	SDL_Rect point;

};

#endif //__MOUSE_H__