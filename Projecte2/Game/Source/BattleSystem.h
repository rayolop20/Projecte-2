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
<<<<<<< HEAD
	bool battle = false;

	int x, y;
	bool turn = false;
	bool enemyTurn = false;
private:

	int interactionButtons[16] = {	50,300,100,40,
									175,300,100,40,
									50,350,100,40,
									175,350,100,40 };
	
=======

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
	GuiButton* MiniEnemyButton;

	int VampireTarget = 0;
	int playerTarget = 0;
	int playerTarget_ = 0;

	int AttackPlayer = 0;

	int AttackType = 0;
	bool battle;
	bool battle1 = true;
	bool battleAux = false;
	bool AttackPhaseActive;
	bool AttackPhaseEnable = false;
	bool battleWin = NULL;

	int CombatDeaths = 0;

	void AttackPhase();
	void AttackPhaseDisabled();
	void AttackPhaseDisabled2();

	void InventoryPhase();
	void SpecialAttackPhase();

	void ChoosePlayer();
	void CheckAllies();
	void MaxHp();

	bool ChoosePlayerPhase = true;

	int alliesDead = 0;

	float timer1 = 0;
	float timer1_ = 0;
	float timer2 = 0;
	float timer2_ = 0;
	float AttackAux;
	int randomAttack = 0;
	bool randomAttackEnd = false;


	bool randomAux = true;

	bool PlayerTurn = true; 

	int randomx = 0, randomy = 0;

	bool rectDirection = true;
	int randomtargetRect = 0;
	int randomtargetRect_ = 0;
	float finalpos = 0;

	bool Delay = true;

	bool SpecialAttackEnable = false;
	bool InventoryEnable = false;
	int* waitPlayer = new int(4 - alliesDead);
	int* poisonCount = new int(4 - CombatDeaths);


	bool SpawnedEnemies = false;

	int randomLetterGenerator = 0;
	bool LetterGenerator = true;

	SDL_Texture* TypoSpecialAttack;
	SDL_Texture* AttackTexture;
private:



>>>>>>> 13b939b3562eaf3555f2e5d4e2c64adb850d4b86
};

#endif // __BATTLESYSTEM_H__