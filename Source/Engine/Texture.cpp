#include <Engine/Texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

TextureLoaderInfo TextureLoader;

std::string texturePaths[] = {
	"./Resources/Textures/alphaBMP.bmp",
	"./Resources/Textures/alphaJPG.jpg",
	"./Resources/Textures/alphaPNG.png",
	"./Resources/Textures/Splash/house02.jpg",
	"./Resources/Textures/Splash/house03.png",
	"./Resources/Textures/Splash/house04.png",
	"./Resources/Textures/Splash/road.jpg",
};


void loadTextures() {
	int x, y, c;
	stbi_set_flip_vertically_on_load(true);

	for (auto path : texturePaths) {
		unsigned char* data = stbi_load(path.c_str(), &x, &y, &c, 0);

		if (!data) {
			printf("Failed to load texture file [%s]\n", path.c_str());
			continue;
		}

		GLuint texID;

		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (c == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else if (c == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else {
			printf("No support for %i number of color channels in texture file [%s]\n", c, path.c_str());
			stbi_image_free(data);
			continue;
		}

		stbi_image_free(data);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		Texture texture;

		texture.name = getFileNameFromPath(path);
		texture.id = texID;

		TextureLoader.textures.emplace(texture.name, texture);
	}
}


Texture* getTextureByName(std::string name) {
	return &TextureLoader.textures[name];
}


Texture* createTextureFromBitmap(BitmapInfo* bitmap, bool emplace, std::string name) {
	Texture texture;
	
	GLuint texID;

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->width, bitmap->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->contents);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.id = texID;

	if (emplace) {
		TextureLoader.textures.emplace(name, texture);
	}

	return &texture;
}