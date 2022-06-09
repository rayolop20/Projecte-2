#ifndef __INPUT_H__
#define __INPUT_H__

#include "Module.h"

//#define NUM_KEYS 352
#define NUM_MOUSE_BUTTONS 5
#define MAX_BUTTONS 15
//#define LAST_KEYS_PRESSED_BUFFER 50

struct SDL_Rect;
struct _SDL_GameController;
struct _SDL_Haptic;

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class GamePad
{
public:
	GamePad();
	virtual ~GamePad();

	inline KeyState GetButton(int id) const
	{
		if (this != nullptr) return buttons[id];
	}

	void HandleDeviceConnection(int index);

	void HandleDeviceRemoval(int index);

	void UpdateGamepadInput();

	bool ShakeController(int id, int duration, float strength = 0.5f);
	const char* GetControllerName(int id) const;

public:
	bool start, back, guide;
	bool x, y, a, b, l1, r1, l3, r3;
	bool up, down, left, right;
	float l2, r2;
	float l_x, l_y, r_x, r_y, l_dz, r_dz;

	KeyState* buttons;
	SDL_GameControllerButton btns[MAX_BUTTONS];

	bool enabled;
	int index;
	_SDL_GameController* controller;
	_SDL_Haptic* haptic;

	int rumble_countdown;
	float rumble_strength;
};

class Input : public Module
{

public:

	Input();

	// Destructor
	virtual ~Input();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called before quitting
	bool CleanUp();

	// Check key states (includes mouse and joy buttons)
	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	KeyState GetMouseButtonDown(int id) const
	{
		return mouseButtons[id - 1];
	}

	// Check if a certain window event happened
	bool GetWindowEvent(EventWindow ev);

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);

	GamePad* Pad;

private:
	bool windowEvents[WE_COUNT];
	KeyState*	keyboard;
	KeyState mouseButtons[NUM_MOUSE_BUTTONS];
	int	mouseMotionX;
	int mouseMotionY;
	int mouseX;
	int mouseY;
};

#endif // __INPUT_H__