#include "TextureManager.h"

vector<SDL_Texture*>& DPDrawing::TextureManager::getTextures() {
	return this->textures;
}

vector<SDL_Surface*>& DPDrawing::TextureManager::getSurfaces() {
	return this->surfaces;
}

void DPDrawing::TextureManager::addSurface(SDL_Renderer* r, string path, string name) {
	//this->surfaces_stored.push_back(*s);
	SDL_Surface* s = SDL_LoadBMP(path.c_str());
	this->surfaces.push_back(s);
	this->textures.push_back(SDL_CreateTextureFromSurface(r, s));
	SDL_FreeSurface(s);
	this->names.push_back(name);
}

SDL_Texture* DPDrawing::TextureManager::getTextureByName(string name) {
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

