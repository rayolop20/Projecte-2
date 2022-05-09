#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"
#include "List.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class Audio : public Module
{
public:

	Audio();

	// Destructor
	virtual ~Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fadeTime = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	void MusicVolumeControl(int index);

	void FxVolumeControl(int index);

	int musicVolume = 25;

	int fxVolume = 120;

	int maxMusicValue = 125;

	int maxFxValue = 125;
private:
	SString fxFolder;
	_Mix_Music* music;
	List<Mix_Chunk *>	fx;
};

#endif // __AUDIO_H__