#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#include "Module.h"
#include "Animation.h"

#define NUM_ZOMBIEF 100

struct SDL_Texture;

class Particle : public Module
{
public:

	Particle();

	virtual ~Particle();

	bool Start();

	bool Update(float dt);

	bool PostUpdate();

	Animation* currentAnimationF[NUM_ZOMBIEF] = { nullptr };

	SDL_Texture* firepart = nullptr;
	Animation fire_particles;
	SDL_Rect fireparticv;
	Animation* currentFire = nullptr;
private:


};

#endif //__PARTICLES_H__