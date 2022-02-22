#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 15

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		PLAYER,
		WALL,
		ROOF,
		GROUND,
		ATTACK,
		ECENTIPIDE,
		HEAL,
		AUTOSAVE,
		DETECTOR1,
		DETECTOR2,
		BIRD,
		COINS,
		MAX

	};
public:
	// Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);
	bool Intersects(const SDL_Rect& r) const;
	void AddListener(Module* listener);

	// Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__