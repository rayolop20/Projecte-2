#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Particles.h"


Particle::Particle() : Module()
{
	name.Create("particles");

	fire_particles.PushBack({ 0,0,130,150 });
	fire_particles.PushBack({ 180,0,130,150 });
	fire_particles.PushBack({ 360,0,130,150 });
	fire_particles.PushBack({ 520,0,130,150 });
	fire_particles.loop = true;
	fire_particles.speed = 0.1f;

}

// Destructor
Particle::~Particle()
{

}

// Called before the first frame
bool Particle::Start()
{
	firepart = app->tex->Load("Assets/Particles/fire_particle.png");

	currentFire = &fire_particles;

	return true;
}

// Called each loop iteration
bool Particle::Update(float dt)
{
	app->particle->currentFire = &app->particle->fire_particles;
	app->render->DrawTexture(app->particle->firepart, app->player->P1.position.x, app->player->P1.position.y, &app->particle->fireparticv);
	app->particle->currentFire->Update();
	return true;
}

// Called each loop iteration
bool Particle::PostUpdate()
{
	bool ret = true;
	fireparticv = currentFire->GetCurrentFrame();


	return ret;
}

