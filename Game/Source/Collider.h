#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 18

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		PLAYER,
		VAMPIRE,
		ZOMBIE,
		SKELETON,
		NPC,
		WALLV,
		WALLH,
		KEY_SENSOR,
		PRESSURE_PLATE1,
		PRESSURE_PLATE2,
		PRESSURE_PLATE3,
		SIMON1,
		SIMON2,
		SIMON3,
		SIMON4,
		SIMON5,
		SIMON6,
		TORCH1,
		TORCH2,
		TORCH3,
		TORCH4,
		WIN,
		//Sensors
		SENSOR,
		SENSOR_PLAYER2,
		SENSOR_PLAYER3,
		SENSOR_PLAYER4,
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