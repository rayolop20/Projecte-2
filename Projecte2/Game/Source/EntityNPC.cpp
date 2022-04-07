#include "Entity.h"
#include "App.h"
#include "Textures.h"
#include "EntityManager.h"
#include "GuiManager.h"
#include "Scene.h"
#include "Collisions.h"
#include "Player.h"
#include "PathFinding.h"
#include "Map.h"
#include "EntityNPC.h"
#include "Window.h"

#include "Log.h"
#include "DynArray.h"
#include "BattleSystem.h"
#include <time.h>

EntityNPC::EntityNPC() :Entity(EntityType::NPC)
{
	name.Create("NPC");
	
	idle.PushBack({ 5, 6, 16, 17 });
	idle.PushBack({ 28, 6, 12, 17 });
	idle.PushBack({ 11, 29, 5, 16 });
	idle.PushBack({ 28, 28, 12, 17 });
	idle.loop = true;
	idle.speed = 0.001f;
	
}

EntityNPC::~EntityNPC()
{
	name.Create("NPC");
}

/*
bool VampirEnem::Awake(pugi::xml_node& config)
{
	LOG("Loading VampirEnem");
	bool ret = true;


	Vpir[0].Pos.x = config.child("Position").attribute("PositionX").as_int();
	Vpir[0].Pos.y = config.child("Position").attribute("PositionY").as_int();


	return false;
}


bool VampirEnem::LoadState(pugi::xml_node& data)
{
	Vpir[0].Pos.x = data.child("Vampire").attribute("x").as_int();
	Vpir[0].Pos.y = data.child("Vampire").attribute("y").as_int();
	return false;
}

bool VampirEnem::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node VPyr = data.append_child("Vampire");

	VPyr.append_attribute("x") = Vpir[0].Pos.x;
	VPyr.append_attribute("y") = Vpir[0].Pos.y;
	return false;
}
*/
bool EntityNPC::Start()
{

	TextureNPC = app->tex->Load("Assets/textures/coins.png");
	//coinFx = app->audio->LoadFx("Assets/audio/fx/coin.wav");
	DialogueBox = app->tex->Load("Assets/textures/UI/TextBox.png");

	for (int i = 0; i < NUM_NPC; i++)
	{
		currentAnimation[i] = &idle;
	}

	npc[0] = CreateNPC(500, 500, TextureNPC);

	return false;
}

bool EntityNPC::Update(float dt)
{
	timerNPC = SDL_GetTicks() / 1000;
	timerNPC2 = SDL_GetTicks() / 1000;

	for (int i = 0; i < NUM_NPC; i++)
	{
		currentAnimation[i]->Update();

		if (npc[i].Destroyed == true)
		{
			npc[i].dead = true;
			npc[i].colliderNPC->pendingToDelete = true;
		}
	}
	for (int i = 0; i < 1; i++)
	{
		npc[i].colliderNPC->SetPos(npc[i].Pos.x, npc[i].Pos.y);
		npc[i].colliderSNPC->SetPos(npc[i].Pos.x - 32, npc[i].Pos.y - 32);
	}
	if (Dialogue1 == true) {
		if (Dialogue1Count == 1) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			//Who’s there?
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1Count=2;
				timerNPC_ = timerNPC;
			}
		}
		if (Dialogue1Count == 2) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 500, app->player->P1.position.y + 160);
			//We are a squad of alies, identify yourself now!

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1Count=3;
				timerNPC_ = timerNPC;
			}
		}
		if (Dialogue1Count == 3) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			//3.”Dieu, merci”!, not only are you human beings, you are
			//allies! I am a french soldier, a german squad took me to
			//this castle and although I manage to scape my cell, i’m
			//still alone in the dungeon, please help me! There are too
			//many creatures in the next room and I can’t take them out on my own.
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1Count++;
				timerNPC_ = timerNPC;
			}
		}
		if (Dialogue1Count == 4) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 500, app->player->P1.position.y + 160);
			// (He looks well prepared, i think it would be useful to have another soldier in our  
			// team.However, we just find him here, he may not be someone trustworthy).
			//Escollir: Si(francés s’uneix).No(francés no s’uneix).

			if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchYes++;
				Dialogue1Count++;
				timerNPC_ = timerNPC;

			}
			if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchNo++;
				Dialogue1Count++;
				timerNPC_ = timerNPC;

			}

		}

		if (Dialogue1BranchNo == 1 && Dialogue1BranchYes == 0) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			//Please don’t leave me alone!Are you sure you don’t want me to team up with you ?
			if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchYes++;
				Dialogue1Count++;
				timerNPC_ = timerNPC;

			}
			if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchNo++;
				Dialogue1Count++;
				timerNPC_ = timerNPC;

			}
		}

		if (Dialogue1BranchNo == 2) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			//I’ll stay here then and try to survive on my own, if you need my help, talk with me. 
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1 = false;
				Dialogue1Count++;
				timerNPC_ = timerNPC;
			}
		}

		if (Dialogue1BranchNo == 4) {
			// Have you changed your mind?
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchYes++;
				Dialogue1Count++;
				timerNPC_ = timerNPC;

			}
			if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchNo++;
				Dialogue1Count++;
				timerNPC_ = timerNPC;

			}
		}
		if (Dialogue1BranchNo == 5) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			// Then why did you ask?
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1 = false;
				timerNPC_ = timerNPC;

			}

		}
		if (Dialogue1BranchNo == 6) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			// Have you changed your mind?
			if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchYes++;
				Dialogue1Count++;
				timerNPC_ = timerNPC;

			}
			if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchNo++;
				Dialogue1Count++;
				Dialogue1 = false;
				timerNPC_ = timerNPC;

			}
		}
		if (Dialogue1BranchNo > 6) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			// Have you changed your mind?
			if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchYes++;
				Dialogue1Count++;
				timerNPC_ = timerNPC;

			}
			if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchNo++;
				Dialogue1Count++;
				Dialogue1 = false;
				timerNPC_ = timerNPC;

			}
		}

		if (Dialogue1BranchYes == 1) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			//Thank you monsieur, I promise to be helpful!
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				app->player->P4.position.x = 500;
				app->player->P4.position.y = 500;
				Dialogue1BranchYes++;
				app->player->P4.Move = true;
				app->player->P4.hp = app->player->P5.hp;
				app->player->P4.speed1 = app->player->P5.speed1;
				app->player->P4.speed2 = app->player->P5.speed2;
				app->player->P4.speed = app->player->P5.speed;
				app->player->P4.damage = app->player->P5.damage;
				app->player->P4.damage1 = app->player->P5.damage1;
				app->player->P4.damage2 = app->player->P5.damage2;
				app->player->P4.mana = app->player->P5.mana;
				app->player->P4.mana1 = app->player->P5.mana1;
				app->player->P4.mana2 = app->player->P5.mana2;
				app->player->P4.luck = app->player->P5.luck;
				app->player->P4.IsAlive = true;
				npc[0].Destroyed = true;
				timerNPC_ = timerNPC;
				Dialogue1 = false;
			}
		}

	}
	if (Dialogue2 == true) {
		if (Dialogue2Count == 1) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			//Hey, luck I found you, I am a doctor and I have lost my medkit,
			//if you help me find it, I may heal myself and help you with your
			//injuries, I do not remember where it is, but I think this key may be a clue
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC2 > timerNPC2_ + 2) {
				Dialogue2 = false;
				Dialogue2Count = 2;
				timerNPC2_ = timerNPC2;
			}
		}
		if (Dialogue2Count == 2 && app->player->P1.medkit == false) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			//What? You did not find anything, I am sure this key must open some door...
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC2 > timerNPC2_ + 2) {
				Dialogue2 = false;
				timerNPC2_ = timerNPC2;
			}
		}
		if (Dialogue2Count = 3 && app->player->P1.medkit == true) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			//Fine! I am done! I have some extra bandages I can give you so we can all try to leave this place by our own.
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC2 > timerNPC2_ + 2) {
				Dialogue2Count = 3;
				app->player->P1.hp += 10;
				app->player->P2.hp += 10;
				app->player->P3.hp += 10;
				app->player->P4.hp += 10;
				Dialogue2 = false;
				timerNPC2_ = timerNPC2;
				//npc[1].Destroyed = true;
			}		
		}
		if (Dialogue2Count = 3 && app->player->P1.medkit == false) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			//Nice! Let me hear my bounds for a second...
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC2 > timerNPC2_ + 2) {
				Dialogue2Count = 3;
				timerNPC2_ = timerNPC2;
			}
		}
	}
	return true;
}



bool EntityNPC::PostUpdate()
{
	LOG("FUNCIONA?");
	for (int i = 0; i < NUM_NPC; i++)
	{
		if (npc[i].dead == false)
		{
			app->render->DrawTexture(npc[i].NPCT, npc[i].Pos.x, npc[i].Pos.y, &(currentAnimation[i]->GetCurrentFrame()));
		}
	}
	return true;
}



void EntityNPC::OnCollision(Collider* c1, Collider* c2)
{

	for (uint i = 0; i < NUM_NPC; ++i)
	{
		if (npc[i].colliderNPC == c1 && !npc[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
				//Vpir[0].Destroyed = true;
				LOG("Polla");
			}
		}
		else if (npc[i].colliderSNPC == c1 && !npc[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER && app->input->GetKey(SDL_SCANCODE_E)==KEY_DOWN)
			{
				timerNPC_ = timerNPC;
				timerNPC2_ = timerNPC2;
				//Dialogue1 = true;
				Dialogue2 = true;
				if (Dialogue2Count == 0) {
					Dialogue2Count = 1;
				}
				
				if (Dialogue1Count != 0) {
					Dialogue1BranchNo++;
				}
				Dialogue1Count++;

				LOG("Polla");
			}
		}
	}
	
}



NPC EntityNPC::CreateNPC(int x, int y, SDL_Texture* t)
{
	NPC Npc;

	Npc.colliderNPC = app->collisions->AddCollider({ x, y, 32, 32 }, Collider::Type::NPC, (Module*)app->entityManager);
	Npc.colliderSNPC = app->collisions->AddCollider({ x, y, 96, 96 }, Collider::Type::SENSOR, (Module*)app->entityManager);
	Npc.NPCT = t;
	Npc.Pos.x = x;
	Npc.Pos.y = y;

	return Npc;
}

