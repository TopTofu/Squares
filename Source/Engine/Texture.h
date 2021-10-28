#pragma once

#include <string>
#include <map>

#include <glad/glad.h>

#include <Util/Utilities.h>


struct Texture {
	std::string name;
	GLuint id;
};

struct TextureLoaderInfo {
	std::map<std::string, Texture> textures;
};

extern TextureLoaderInfo TextureLoader;

void loadTextures();
Texture* getTextureByName(std::string name);
