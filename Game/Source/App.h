#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "PerfTimer.h"
#include "Timer.h"

#include "List.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene;
class Map;
class GuiManager;
class Menu_Screen;
class Collisions;
class Player;
class EntityManager; 
class battleSystem; 
class PathFinding;
class ModuleFonts;
class CharacterMenu_Screen;
class GameMenu_Screen;
class StatsMenu_Screen;
class DialogueSystem;
class ModuleAssetsManager;
class Mouse;
class Particle;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	// L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest();
	void SaveGameRequest() const;

private:

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

public:

	// Modules
	Window* win = nullptr;
	Input* input = nullptr;
	Render* render = nullptr;
	Textures* tex = nullptr;
	Audio* audio = nullptr;
	Scene* scene = nullptr;
	Map* map = nullptr;
	GuiManager* guiManager = nullptr;
	Player* player = nullptr;
	EntityManager* entityManager = nullptr;
	Collisions* collisions = nullptr;
	ModuleFonts* fonts = nullptr;
	Menu_Screen* menu = nullptr;
	battleSystem* BTSystem = nullptr;
	PathFinding* pathfinding = nullptr;
	CharacterMenu_Screen* characterMenu = nullptr;
	GameMenu_Screen* gameMenu = nullptr;
	StatsMenu_Screen* statsMenu = nullptr;
	DialogueSystem* dialogues = nullptr;
	ModuleAssetsManager* assetManager = nullptr;
	Mouse* mouse = nullptr;
	Particle* particle = nullptr;


	float dt = 16.0f;
	bool Maxfps = false;
private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module*> modules;

	// L01: DONE 2: Create new variables from pugui namespace
	// NOTE: Redesigned LoadConfig() to avoid storing this variables
	//pugi::xml_document configFile;
	//pugi::xml_node config;
	//pugi::xml_node configApp;

	mutable bool saveGameRequested;
	bool loadGameRequested;

	// L07: DONE 4: Calculate some timing measures
	// required variables are provided:
	PerfTimer ptimer;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;

	float averageFps = 0.0f;

};

extern App* app;

#endif	// __APP_H__