#include "App.h"

#include "Defs.h"
#include "Log.h"
#include "Input.h"

#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
using namespace std;
// NOTE: SDL redefines main function
#include "SDL/include/SDL.h"

// NOTE: Library linkage is configured in Linker Options
//#pragma comment(lib, "../Game/Source/External/SDL/libx86/SDL2.lib")
//#pragma comment(lib, "../Game/Source/External/SDL/libx86/SDL2main.lib")


#include <stdlib.h>

enum MainState
{
	CREATE = 1,
	AWAKE,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

App* app = NULL;

int main(int argc, char* args[])
{

	LOG("Engine starting ...");
	float dt = 16.0f;
	MainState state = CREATE;
	int result = EXIT_FAILURE;

	while (state != EXIT)
	{
		auto start = chrono::steady_clock::now();
		switch (state)
		{
			// Allocate the engine --------------------------------------------
		case CREATE:
			LOG("CREATION PHASE ===============================");

			app = new App(argc, args);

			if (app != NULL)
				state = AWAKE;
			else
				state = FAIL;

			break;

			// Awake all modules -----------------------------------------------
		case AWAKE:
			LOG("AWAKE PHASE ===============================");
			if (app->Awake() == true)
				state = START;
			else
			{
				LOG("ERROR: Awake failed");
				state = FAIL;
			}

			break;

			// Call all modules before first frame  ----------------------------
		case START:
			LOG("START PHASE ===============================");
			if (app->Start() == true)
			{
				state = LOOP;
				LOG("UPDATE PHASE ===============================");
			}
			else
			{
				state = FAIL;
				LOG("ERROR: Start failed");
			}
			break;

			// Loop all modules until we are asked to leave ---------------------
		case LOOP:
			if (app->Update() == false)
				state = CLEAN;
			break;

			// Cleanup allocated memory -----------------------------------------
		case CLEAN:
			LOG("CLEANUP PHASE ===============================");
			if (app->CleanUp() == true)
			{
				RELEASE(app);
				result = EXIT_SUCCESS;
				state = EXIT;
			}
			else
				state = FAIL;

			break;

			// Exit with errors and shame ---------------------------------------
		case FAIL:
			LOG("Exiting with errors :(");
			result = EXIT_FAILURE;
			state = EXIT;
			break;
		}
		auto end = chrono::steady_clock::now();
		auto CelapsetTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

		if (dt - CelapsetTime > 0.0f) {
			SDL_Delay(dt - CelapsetTime);
		}
		LOG("delta time is: %f ms", dt - CelapsetTime);
	}


	LOG("... Bye! :)\n");

	// Dump memory leaks
	return result;
}