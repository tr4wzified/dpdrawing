#include "TextureManager.h"

vector<SDL_Texture*>& DPDrawing::TextureManager::getTextures() {
	return this->textures;
}

vector<SDL_Surface*>& DPDrawing::TextureManager::getSurfaces() {
	return this->surfaces;
}

void DPDrawing::TextureManager::addSurface(SDL_Renderer* r, string path, string name) {
	SDL_Surface* s = SDL_LoadBMP(path.c_str());
	this->surfaces.push_back(s);
	this->textures.push_back(SDL_CreateTextureFromSurface(r, s));
	SDL_FreeSurface(s);
	this->names.push_back(name);
}

void DPDrawing::TextureManager::addSurface(SDL_Renderer* r, SDL_Color c, string name) {
	SDL_Log("Calling color function of addSurface() - experimental!");
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
	#else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
	#endif

	SDL_Surface* s = SDL_CreateRGBSurface(0, 640, 480, 32, rmask, gmask, bmask, amask);
	this->surfaces.push_back(s);
	this->textures.push_back(SDL_CreateTextureFromSurface(r, s));
	SDL_FreeSurface(s);
	this->names.push_back(name);
}

void DPDrawing::TextureManager::addText(SDL_Renderer* r, SDL_Surface* surfaceMessage, string name) {
	this->textures.push_back(SDL_CreateTextureFromSurface(r, surfaceMessage));
	this->names.push_back(name);
}

SDL_Texture* DPDrawing::TextureManager::getTextureByName(string name) {
	SDL_Log("Getting texture %s", name.c_str()) ;
	SDL_Log("Names size: %s", std::to_string(names.size()).c_str());
	int amount_names = names.size();
	if(amount_names > 0) {
		for(int i = 0; i < amount_names; i++) {
			if (names.at(i) == name) {
				return textures.at(i);
			}
		}
	}
	SDL_Log("ERROR: Could not retrieve texture!");
	return nullptr;
}

SDL_Texture* DPDrawing::TextureManager::getTextureById(int id) {
	return textures.at(id);
}

