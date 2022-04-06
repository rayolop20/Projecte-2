#ifndef _DIALOGUESYSTEM_
#define _DIALOGUESYSTEM_

#include "Module.h"
#include "GuiButton.h"
#include "Entity.h"
#include "Fonts.h"

class DialogueSystem :public Module
{
public:
	DialogueSystem();

	virtual ~DialogueSystem();

	bool Start();

	bool Update(float dt);
	bool CleanUp();
	int scoreFont = -1;
	char scoreText[150] = { "\0" };
	int score;
};

#endif