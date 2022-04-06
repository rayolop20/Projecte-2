#ifndef _DIALOGUESYSTEM_
#define _DIALOGUESYSTEM_

#include "Module.h"
#include "GuiButton.h"
#include "Entity.h"

class DialogueSystem :public Module
{
public:
	DialogueSystem();

	virtual ~DialogueSystem();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

};

#endif