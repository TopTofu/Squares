#pragma once

#include <string>
#include <filesystem>
#include <map>

#include <glad/glad.h>

#include "Util/Utilities.h"
#include "Engine/AssetLoader.h"


struct Texture {
	std::string name;
	GLuint id;
};

struct TextureLoaderInfo {
	std::map<std::string, Texture> textures;
};

extern TextureLoaderInfo TextureLoader;

void loadTextures(std::string texturesDirectory);
Texture* getTextureByName(std::string name);
Texture* createTextureFromBitmap(BitmapInfo* bitmap, bool emplace = false, std::string name = "");
