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
	GuiButton* MiniEnemyButton;

	GuiButton* Item1;
	GuiButton* Item2;
	GuiButton* Item3;
	GuiButton* Item4;

	GuiButton* Ch1;
	GuiButton* Ch2;
	GuiButton* Ch3;
	GuiButton* Ch4;

	float n = 0;

	int VampireTarget = 0;
	int ZombieTarget = 0;
	int SkeletonTarget = 0;
	int playerTarget = 0;
	int playerTarget_ = 0;

	int invenCont = 0;

	int AttackPlayer = 0;

	int AttackType = 0;
	bool battle;
	bool battle1 = true;
	bool battleAux = false;
	bool AttackPhaseActive;
	bool AttackPhaseEnable = false;
	bool battleWin = NULL;

	bool increaseDmg = false;
	bool increaseSpeed = false;
	bool increaseLuck = false;
	bool healing = false;

	bool choosingPlayer = false;

	int POSQTE2Y = 0;
	int POSQTE2X = 0;

	int CombatDeaths = 0;

	void AttackPhase();
	void AttackPhaseDisabled();
	void AttackPhaseDisabled2();

	void InventoryPhase();
	void InventoryButtons();
	void SpecialAttackPhase();

	void ChoosePlayer();
	void CheckAllies();
	void DrawHpBars();
	void MaxHp();
	void MaxMana();

	bool ChoosePlayerPhase = true;

	int alliesDead = 0;

	float timer1 = 0;
	float timer1_ = 0;
	float _timer1_ = 0;
	float timer2 = 0;
	float timer2_ = 0;
	float AttackAux;
	int randomAttack = 0;

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
	int onFireCount;

	bool SpeacialAttackEnd = false;

	bool SpawnedEnemies = false;

	int randomLetterGenerator = 0;
	bool LetterGenerator = true;

	bool Zombiebattle = false;
	bool Vampirebattle = false;
	bool Skeletonbattle = false;

	SDL_Texture* AttackTexture;
	SDL_Texture* Tutorial;
	SDL_Texture* PopQTE2 = nullptr;
	SDL_Texture* QTE4;

	SDL_Texture* selectPlayer = nullptr;
	SDL_Rect* Choose = new SDL_Rect();
private:



};

#endif // __BATTLESYSTEM_H__