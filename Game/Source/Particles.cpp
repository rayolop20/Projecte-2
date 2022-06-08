#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Particles.h"
#include "ZombieEnem.h"
#include "EntityManager.h"


Particle::Particle() : Module()
{
	name.Create("particles");

	fire_particles.PushBack({ 0,0,33,150 });
	fire_particles.PushBack({ 60,0,36,150 });
	fire_particles.PushBack({ 130,0,47,150 });
	fire_particles.PushBack({ 194,0,54,150 });
	fire_particles.loop = true;
	fire_particles.speed = 0.05f;
	
	Venom_particles.PushBack({ 0,0,160,192 });
	Venom_particles.PushBack({ 160,0,160,192 });
	Venom_particles.PushBack({ 320,0,160,192 });
	Venom_particles.PushBack({ 480,0,160,192 });
	Venom_particles.PushBack({ 640,0,160,192 });
	Venom_particles.PushBack({ 800,0,160,192 });
	Venom_particles.PushBack({ 960,0,160,192 });
	Venom_particles.PushBack({ 1120,0,160,192 });
	Venom_particles.PushBack({ 1280,0,160,192 });
	Venom_particles.PushBack({ 1440,0,160,192 });
	Venom_particles.PushBack({ 1600,0,160,192 });
	Venom_particles.PushBack({ 1760,0,160,192 });
	Venom_particles.PushBack({ 1920,0,160,192 });
	Venom_particles.PushBack({ 2080,0,160,192 });
	Venom_particles.PushBack({ 2240,0,160,192 });
	Venom_particles.PushBack({ 2400,0,160,192 });
	Venom_particles.PushBack({ 2560,0,160,192 });
	Venom_particles.PushBack({ 2720,0,160,192 });
	Venom_particles.PushBack({ 2880,0,160,192 });
	Venom_particles.PushBack({ 3040,0,160,192 });
	Venom_particles.loop = true;
	Venom_particles.speed = 0.2f;

	Blood_particles.PushBack({ 0,0,160,192 });
	Blood_particles.PushBack({ 160,0,160,192 });
	Blood_particles.PushBack({ 320,0,160,192 });
	Blood_particles.PushBack({ 480,0,160,192 });
	Blood_particles.PushBack({ 640,0,160,192 });
	Blood_particles.PushBack({ 800,0,160,192 });
	Blood_particles.PushBack({ 960,0,160,192 });
	Blood_particles.PushBack({ 1120,0,160,192 });
	Blood_particles.loop = false;
	Blood_particles.speed = 0.2f;

}

// Destructor
Particle::~Particle()
{

}

// Called before the first frame
bool Particle::Start()
{
	firepart = app->tex->Load("Assets/Particles/fire_particle.png");
	Venompart = app->tex->Load("Assets/Particles/poison_particle.png");
	Bloodpart = app->tex->Load("Assets/Particles/blood_particle.png");

	currentFire = &fire_particles;
	currentVenom = &Venom_particles;
	currentBlood = &Blood_particles;

	return true;
}

// Called each loop iteration
bool Particle::Update(float dt)
{

	return true;
}

// Called each loop iteration
bool Particle::PostUpdate()
{
	bool ret = true;
	return ret;
}

