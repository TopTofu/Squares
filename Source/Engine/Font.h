#pragma once

#include <string>

#include <iostream>
#include <fstream>

#include <Windows.h>

#include <stb/stb_truetype.h>

#include <Engine/AssetLoader.h>
#include <Engine/Texture.h>


struct FontInfo {
	std::string name;
	stbtt_fontinfo font;
};

FontInfo loadFont(const char* filename);

BitmapInfo getCodePoint(FontInfo info, char c);

void freeSTBBitmap(unsigned char* bitmap);

