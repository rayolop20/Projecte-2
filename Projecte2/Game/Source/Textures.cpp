#include "App.h"
#include "Render.h"
#include "Textures.h"

#include "Defs.h"
#include "Log.h"
#include "Assetsmanager.h"

#include "SDL_image/include/SDL_image.h"
//#pragma comment(lib, "../Game/Source/External/SDL_image/libx86/SDL2_image.lib")

Textures::Textures() : Module()
{
	name.Create("textures");
}

// Destructor
Textures::~Textures()
{}

// Called before render is available
bool Textures::Awake(pugi::xml_node& config)
{
	LOG("Init Image library");
	bool ret = true;

	// Load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before the first frame
bool Textures::Start()
{
	LOG("start textures");
	bool ret = true;
	return ret;
}

// Called before quitting
bool Textures::CleanUp()
{
	LOG("Freeing textures and Image library");
	ListItem<SDL_Texture*>* item;

	for(item = textures.start; item != NULL; item = item->next)
	{
		SDL_DestroyTexture(item->data);
	}
	textureP.clear();
	textures.clear();
	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const Textures::Load(const char* path)
{
		for (int i = 0, count = textureP.count(); i < count; i++)
		{
			if (textureP[i].path == path)
			{
				return textures[textureP[i].index];
			}
		}

	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path);

	surface = IMG_Load_RW(app->assetManager->Load(path), 1);


	if (surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{

		texture = SDL_CreateTextureFromSurface(app->render->renderer,surface);

		if (texture == nullptr)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			textures.add(texture);
			TexturePath tp = { path, textures.count() - 1, (int)&texture };
			textureP.add(tp);
			//texturePath.insert(std::pair<std::string, int>(path, textures.count() - 1));
			//printf("direccion in memory : %#x || path: %s \n", texture, path.c_str());
		}

		SDL_FreeSurface(surface);
	}
	/*
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if(surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = LoadSurface(surface);
		SDL_FreeSurface(surface);
	}
	*/
	return texture;
}

// Unload texture
bool Textures::UnLoad(SDL_Texture* texture)
{
	ListItem<SDL_Texture*>* item;

	for(item = textures.start; item != NULL; item = item->next)
	{
		if(texture == item->data)
		{
			SDL_DestroyTexture(item->data);
			textures.del(item);
			return true;
		}
	}

	return false;
}

// Translate a surface into a texture
SDL_Texture* const Textures::LoadSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(app->render->renderer, surface);

	if(texture == NULL)
	{
		LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		textures.add(texture);
	}

	return texture;
}

// Retrieve size of a texture
void Textures::GetSize(const SDL_Texture* texture, uint& width, uint& height) const
{
	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, (int*) &width, (int*) &height);
}
