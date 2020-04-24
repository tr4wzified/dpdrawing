#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
using std::vector;
using std::string;

namespace DPDrawing {
class TextureManager {
public:
	vector<SDL_Texture*>& getTextures();
	vector<SDL_Surface*>& getSurfaces();
	void addSurface(SDL_Renderer* r, string path, string name);
	SDL_Texture* getTextureByName(string name);

    private:
	vector<SDL_Texture*> textures;
	vector<SDL_Surface*> surfaces;
	vector<string> names;
    };
}
