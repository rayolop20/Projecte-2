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
#include "Menu.h"
#include "EntityNPC.h"
#include "Window.h"
#include "Fonts.h"
#include "CharacterMenu.h"

#include "Log.h"
#include "DynArray.h"
#include "BattleSystem.h"
#include <time.h>

EntityNPC::EntityNPC() :Entity(EntityType::NPC)
{
	name.Create("NPC");

	idle1.PushBack({ 39, 34, 46, 75 });
	idle1.loop = true;
	idle1.speed = 0.001f;
	
	idle2.PushBack({ 46, 38, 37, 65 });
	idle2.loop = true;
	idle2.speed = 0.001f;

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

	TextureNPC = app->tex->Load("Assets/Textures/NPC/npc1.png");
	TextureNPC2 = app->tex->Load("Assets/Textures/NPC/npc2.png");
	DialogueBox = app->tex->Load("Assets/Textures/UI/text_box.png");

	//text
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	FText = app->fonts->Load("Assets/Textures/Fonts/fonts.png", lookupTable, 1);
	door = app->tex->Load("Assets/Textures/Assets/door.png");
	door2 = app->tex->Load("Assets/Textures/Assets/door2.png");
	door3 = app->tex->Load("Assets/Textures/Assets/door3.png");

	for (int i = 0; i < NUM_NPC; i++)
	{
		currentAnimation[i] = &idle1;
	}

		npc[0] = CreateNPC(1050, 1364, app->characterMenu->frenchNpc);
		npc[1] = CreateNPC(957, 232, TextureNPC);
		npc[2] = CreateNPC(1357, 1937, TextureNPC2);
		npc[3] = CreateNPC(1357, 1500, TextureNPC4);
		npc[4] = CreateNPC(1657, 1500, TextureNPC5);
	
	porta_1 = app->collisions->AddCollider({ 1312, 1664, 96, 64 }, Collider::Type::KEY_SENSOR, (Module*)app->entityManager);
	porta_2 = app->collisions->AddCollider({ 1504, 2304,64, 96 }, Collider::Type::KEY_SENSOR, (Module*)app->entityManager);

	return false;
}

bool EntityNPC::Update(float dt)
{
	if (Dialogue1BranchYes < 1 && app->BTSystem->battle == false && app->BTSystem->InventoryEnable == false) {
		app->render->DrawTexture(app->characterMenu->frenchNpc, 1060 - 32, 1358 - 32);
	}
	if (Dialogue2Count != 0 && app->menu->config == false && app->BTSystem->battle == false && app->player->door3active == true && app->player->door3active_ == true) {
		porta_1->pendingToDelete = true;
		app->render->DrawTexture(door2, 1312, 1664);
		app->characterMenu->item6state = false;

	}
	else if (app->menu->config == false && app->BTSystem->battle == false){
		app->render->DrawTexture(door, 1312, 1664);
	}

	if (app->player->P2.IsAlive == true && app->player->P3.IsAlive == true && app->player->P4.IsAlive == true) {
		porta_2->pendingToDelete = true;
	}
	else if(app->menu->config == false && app->BTSystem->battle == false && app->BTSystem->battle1 == true){
		app->render->DrawTexture(door3, 1536, 2304);

	}

	timerNPC = SDL_GetTicks() / 1000;
	timerNPC2 = SDL_GetTicks() / 1000;
	timerNPC3 = SDL_GetTicks() / 1000;

	for (int i = 0; i < NUM_NPC; i++)
	{
		currentAnimation[i]->Update();
		

		if (npc[i].Destroyed == true)
		{
			npc[i].dead = true;
			npc[i].colliderNPC->pendingToDelete = true;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		npc[i].colliderNPC->SetPos(npc[i].Pos.x, npc[i].Pos.y);
		npc[i].colliderSNPC->SetPos(npc[i].Pos.x - 32, npc[i].Pos.y - 32);
	}
	//dialogue 1
	if (Dialogue1 == true) {
		app->scene->paused = true;
		if (Dialogue1Count == 1) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			sprintf_s(Text1, "who is there?");
			app->fonts->DrawTxt(300,  502, FText, Text1);

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1Count=2;
				timerNPC_ = timerNPC;
			}
		}
		if (Dialogue1Count == 2) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 500, app->player->P1.position.y + 160);
			sprintf_s(Text1, "we are a squad of alies, identify yourself now!");
			app->fonts->DrawTxt(190, 502, FText, Text1);

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1Count=3;
				timerNPC_ = timerNPC;
			}
		}
		if (Dialogue1Count == 3) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			sprintf_s(Text1, "dieu, mercii!, you are allies! i am a\n");
			sprintf_s(Text2, "french soldier, a german squad took me to");
			sprintf_s(Text3, "this castle.please help me! there are too");
			sprintf_s(Text4, "many creatures and i can not take them out on my own.");
			app->fonts->DrawTxt(290, 502, FText, Text1);
			app->fonts->DrawTxt(290, 542, FText, Text2);
			app->fonts->DrawTxt(290, 582, FText, Text3);
			app->fonts->DrawTxt(290, 622, FText, Text4);
			//3.�Dieu, merci�!, not only are you human beings, you are
			//allies! I am a french soldier, a german squad took me to
			//this castle and although I manage to scape my cell, i�m
			//still alone in the dungeon, please help me! There are too
			//many creatures in the next room and I can�t take them out on my own.
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1Count++;
				timerNPC_ = timerNPC;
			}
		}
		if (Dialogue1Count == 4) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 500, app->player->P1.position.y + 160);
			sprintf_s(Text1, "he looks well prepared, i think it would be useful");
			sprintf_s(Text2, "to have another soldier in our team. however, we just");
			sprintf_s(Text3, "find him here, he may not be someone trustworthy.");
			sprintf_s(Text4, "add to the team    y                dont add    n");
			app->fonts->DrawTxt(170, 502, FText, Text1);
			app->fonts->DrawTxt(170, 542, FText, Text2);
			app->fonts->DrawTxt(170, 582, FText, Text3);
			app->fonts->DrawTxt(170, 622, FText, Text4);


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
			sprintf_s(Text1, "please do not leave me alone! are you sure ");
			sprintf_s(Text2, "you do not want me to team up with you?");
			sprintf_s(Text3, "add to the team    y                dont add    n");
			app->fonts->DrawTxt(300, 502, FText, Text1);
			app->fonts->DrawTxt(300, 542, FText, Text2);
			app->fonts->DrawTxt(300, 582, FText, Text3);
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
			sprintf_s(Text1, "i ll stay here then and try to survive on my own,");
			sprintf_s(Text2, "if you need my help, talk with me.");
			app->fonts->DrawTxt(300, 502, FText, Text1);
			app->fonts->DrawTxt(300, 542, FText, Text2);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1 = false;
				app->scene->paused = false;
				Dialogue1Count++;
				timerNPC_ = timerNPC;
			}
		}

		if (Dialogue1BranchNo == 4) {

			sprintf_s(Text1, "have you changed your mind?");
			sprintf_s(Text2, "add to the team    y                dont add    n");
			app->fonts->DrawTxt(300, 502, FText, Text1);
			app->fonts->DrawTxt(300, 542, FText, Text2);
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
			sprintf_s(Text1, "then why did you ask?");
			app->fonts->DrawTxt(300, 502, FText, Text1);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				app->scene->paused = false;
				Dialogue1 = false;
				timerNPC_ = timerNPC;

			}

		}
		if (Dialogue1BranchNo == 6) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			sprintf_s(Text1, "have you changed your mind?");
			sprintf_s(Text2, "add to the team    y                dont add    n");
			app->fonts->DrawTxt(300, 502, FText, Text1);
			app->fonts->DrawTxt(300, 542, FText, Text2);
			if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchYes++;
				Dialogue1Count++;
				timerNPC_ = timerNPC;

			}
			if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchNo++;
				Dialogue1Count++;
				Dialogue1 = false;
				app->scene->paused = false;
				timerNPC_ = timerNPC;

			}
		}
		if (Dialogue1BranchNo > 6) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			sprintf_s(Text1, "have you changed your mind?");
			sprintf_s(Text2, "add to the team    y                dont add    n");
			app->fonts->DrawTxt(300, 502, FText, Text1);
			app->fonts->DrawTxt(300, 542, FText, Text2);
			if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchYes++;
				Dialogue1Count++;
				timerNPC_ = timerNPC;

			}
			if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				Dialogue1BranchNo++;
				Dialogue1Count++;
				Dialogue1 = false;
				app->scene->paused = false;
				timerNPC_ = timerNPC;

			}
		}

		if (Dialogue1BranchYes == 1) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			sprintf_s(Text1, "thank you monsieur, i promise to be helpful!");
			app->fonts->DrawTxt(300, 502, FText, Text1);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC > timerNPC_ + 2) {
				app->player->P4.position.x = app->player->P1.position.x;
				app->player->P4.position.y = app->player->P1.position.y;
				Dialogue1BranchYes++;
				app->player->P4.Move = true;
				app->player->P4.P4Active = true;
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
				app->scene->paused = false;
			}
		}

	}
	//dialogue 2
	if (Dialogue2 == true) {
		app->scene->paused = true;

		if (Dialogue2Count == 1) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			sprintf_s(Text1, "hey, luck i found you, i have lost my wife who is a ");
			sprintf_s(Text2, "nurse, if you help me find her, she may help you with your");
			sprintf_s(Text3, "injuries, i do not remember where it is, but I think this");
			sprintf_s(Text4, " key may be a clue");
			app->player->door3active = true;
			app->characterMenu->Item6->state = GuiControlState::NORMAL;
			app->characterMenu->item6state = true;
			app->fonts->DrawTxt(250, 502, FText, Text1);
			app->fonts->DrawTxt(250, 542, FText, Text2);
			app->fonts->DrawTxt(250, 582, FText, Text3);
			app->fonts->DrawTxt(250, 622, FText, Text4);
			//Hey, luck I found you, I have lost my wife who is a nurse,
			//if you help me find her, she may help you with your
			//injuries, I do not remember where it is, but I think this key may be a clue
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC2 > timerNPC2_ + 2) {
				Dialogue2 = false;
				app->scene->paused = false;
				Dialogue2Count = 2;
				timerNPC2_ = timerNPC2;
			}
		}
		if (Dialogue2Count == 2 && app->player->P1.medkit == false) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			//What? You did not find her?! I am sure this key must open some door...
			sprintf_s(Text1, "what? you did not find her?! i am sure this key must open some door...");
			app->fonts->DrawTxt(250, 502, FText, Text1);

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC2 > timerNPC2_ + 2) {
				Dialogue2 = false;
				app->scene->paused = false;
				timerNPC2_ = timerNPC2;
			}
		}
		if (Dialogue2Count == 3 && app->player->P1.medkit == true) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			sprintf_s(Text1, "there you go, almost new! see you soon and thanks a lot!");
			app->fonts->DrawTxt(250, 502, FText, Text1);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC2 > timerNPC2_ + 2) {
				Dialogue2Count = 3;
				app->player->P1.hp += 10;
				app->player->P2.hp += 10;
				app->player->P3.hp += 10;
				app->player->P4.hp += 10;
				Dialogue2 = false;
				app->scene->paused = false;
				timerNPC2_ = timerNPC2;
				npc[1].Destroyed = true;
			}
		}
		if (Dialogue2Count == 2 && app->player->P1.medkit == true) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			sprintf_s(Text1, "oh my god elisenda! i thought you where dead. these brave");
			sprintf_s(Text2, "soldiers reunited us, could you try to heal their injuries");
			sprintf_s(Text3, "so they have more probabilities to scape?");
			app->fonts->DrawTxt(250, 500, FText, Text1);
			app->fonts->DrawTxt(250, 550, FText, Text2);
			app->fonts->DrawTxt(250, 600, FText, Text3);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC2 > timerNPC2_ + 2) {
				Dialogue2Count = 3;
				timerNPC2_ = timerNPC2;
			}
		}
	}
	//dialogue 3
	if (Dialogue3 == true) {
		app->scene->paused = true;

		if (Dialogue3Count == 1) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			sprintf_s(Text1, "h...hey? who is there? please do not kill me...");
			app->fonts->DrawTxt(300, 502, FText, Text1);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC3 > timerNPC3_ + 2) {
 				Dialogue3Count = 2;
				timerNPC3_ = timerNPC3;
			}
		}
		if (Dialogue3Count == 2) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 500, app->player->P1.position.y + 160);
			sprintf_s(Text1, "we are alies do not worry, we have come to bring you");
			sprintf_s(Text2, " with your husband who sent us to you. are you injured?");
			app->fonts->DrawTxt(170, 502, FText, Text1);
			app->fonts->DrawTxt(170, 542, FText, Text2);
			//We are alies do not worry, we have come to bring you with your husband who sent us to you. Are you injured?
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC3 > timerNPC3_ + 2) {
				Dialogue3Count = 3;
				timerNPC3_ = timerNPC3;
			}
		}
		if (Dialogue3Count == 3) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			//Thanks god! I am fine, just a little in shock yet. I will follow you, hurry up please! They are everywhere...
			sprintf_s(Text1, "thanks god! i am fine, just a little in shock yet.");
			sprintf_s(Text2, "i will follow you, hurry up please! they are everywhere...");
			app->fonts->DrawTxt(300, 502, FText, Text1);
			app->fonts->DrawTxt(300, 542, FText, Text2);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && timerNPC3 > timerNPC3_ + 2) {
				Dialogue3 = false;
				app->scene->paused = false;
				timerNPC3_ = timerNPC3;
				npc[2].Destroyed = true;
				app->player->P1.medkit = true;
			}
		}
	}
	//dialogue 4
	if (Dialogue4 == true)
	{
		app->scene->Quest3active = true;
	}
	//dialogue 5
	if (Dialogue5 == true)
	{
		app->scene->paused = true;

		if (app->characterMenu->skeletonHead == false) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			sprintf_s(Text1, "Only the chosen one can obtain this...");
			sprintf_s(Text2, "if u are the Chosen one u know what i need");
			app->fonts->DrawTxt(250, 502, FText, Text1);
			app->fonts->DrawTxt(250, 542, FText, Text2);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
				Dialogue5 = false;
				app->scene->paused = false;
			}
		}
		
		if (app->characterMenu->skeletonHead == true && FinishQ5 == false) {
			app->render->DrawTexture(DialogueBox, app->player->P1.position.x - 360, app->player->P1.position.y + 160);
			sprintf_s(Text1, "oooh u are the Chosen one, can u give me the head?");
			sprintf_s(Text2, "Give The head?");
			sprintf_s(Text2, "Give   y                dont give    n");
			app->fonts->DrawTxt(250, 502, FText, Text1);
			app->fonts->DrawTxt(250, 542, FText, Text2);
			if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN) {
				Dialogue5 = false;
				app->scene->paused = false;
			}
			if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN) {
				Dialogue5 = false;
				app->scene->paused = false;
				FinishQ5 = true;
				//afegir suma variables personatge
			}
		}
	}

	return true;
}

bool EntityNPC::PostUpdate()
{
	LOG("FUNCIONA?");
	if (app->BTSystem->battle == false) {

		for (int i = 0; i < NUM_NPC; i++)
		{
			if (npc[i].dead == false && app->menu->config == false)
			{
				app->render->DrawTexture(npc[i].NPCT, npc[i].Pos.x, npc[i].Pos.y, &(currentAnimation[i]->GetCurrentFrame()));
			}
		}
	}
	return true;
}

void EntityNPC::OnCollision(Collider* c1, Collider* c2)
{

	for (uint i = 0; i < NUM_NPC; ++i)
	{
		if (npc[i].colliderSNPC == c1 && !npc[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER && app->input->GetKey(SDL_SCANCODE_E)==KEY_DOWN && Dialogue1 == false && Dialogue2 == false && Dialogue3 == false)
			{
				timerNPC_ = timerNPC;
				timerNPC2_ = timerNPC2;
				timerNPC3_ = timerNPC3;
				if (i == 0) {
					Dialogue1 = true;
					if (Dialogue1Count != 0) {
						Dialogue1BranchNo++;
					}
					Dialogue1Count++;
				}
				if (i == 1) {
					Dialogue2 = true;
					if (Dialogue2Count == 0) {
						Dialogue2Count = 1;
					}
				}
				if (i == 2) {
					Dialogue3 = true;
					if (Dialogue3Count == 0) {
						Dialogue3Count = 1;
					}
				}
				
				if (i == 3) {
					Dialogue4 = true;
					if (Dialogue4Count == 0) {
						Dialogue4Count = 1;
					}
				}
				
				if (i == 4) {
					Dialogue5 = true;
					if (Dialogue5Count == 0) {
						Dialogue5Count = 1;
					}
				}
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
