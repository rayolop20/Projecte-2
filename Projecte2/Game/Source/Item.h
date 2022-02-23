#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"
#include "Point.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;

class Item : public Entity
{
public:

	Item(uint32 id, SDL_Rect bounds);
	virtual ~Item();

	bool Update(float dt);

	bool Draw(Render* render);

	bool CleanUp();

public:

	SDL_Texture* texture;
	iPoint pos;
	bool isPicked = false;
	unsigned int fx;

private:



};

#endif // __ITEM_H__