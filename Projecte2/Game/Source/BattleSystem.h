#ifndef __BATTLESYSTEM_H__
#define __BATTLESYSTEM_H__

#include "Module.h"
#include "GuiButton.h"
#include "Entity.h"

struct SDL_Texture;

class battleSystem : public Module
{
public:

	battleSystem();

	// Destructor
	virtual ~battleSystem();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

	void Pause();
	bool debug = false;

	GuiButton* Attack;
	GuiButton* Attack1;
	GuiButton* Attack2;
	GuiButton* SpecialAttack;
	GuiButton* Inventory;
	GuiButton* Run;
	GuiButton* CloseInventory;
	GuiButton* QTE2;
	GuiButton* MiniPlayerButton1;
	GuiButton* MiniPlayerButton2;
	GuiButton* MiniPlayerButton3;
	GuiButton* MiniPlayerButton4;

	int AttackPlayer = 0;

	int AttackType = 0;
	bool battle;
	bool AttackPhaseActive;
	bool AttackPhaseEnable = false;

	void AttackPhase();
	void AttackPhaseDisabled();

	void InventoryPhase();
	void SpecialAttackPhase();

	void ChoosePlayer();
	bool ChoosePlayerPhase = true;

	float timer1 = 0;
	float timer1_ = 0;
	float timer2 = 0;
	float timer2_ = 0;
	float AttackAux;
	int randomAttack = 0;

	bool randomAux = true;

	int PlayerTurn = 1; 
	int randomx = 0, randomy = 0;
	int EnemyTurn = 0;

	bool rectDirection = true;
	int randomtargetRect = 0;
	int randomtargetRect_ = 0;
	float finalpos = 0;

	bool Delay = true;

	bool SpecialAttackEnable = false;
	bool InventoryEnable = false;

	int randomLetterGenerator = 0;
	bool LetterGenerator = true;

	SDL_Texture* TypoSpecialAttack;
private:



};

#endif // __BATTLESYSTEM_H__