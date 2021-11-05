#include "Font.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.h"
#include <glad/glad.h>


FontInfo loadFont(const char* filename)
{
	FontInfo info;
	ReadFileResult ttfBuffer = readFileIntoBuffer(filename);

	stbtt_InitFont(&info.font, (unsigned char*)ttfBuffer.content, stbtt_GetFontOffsetForIndex((unsigned char*)ttfBuffer.content, 0));

	return info;
}

BitmapInfo getCodePoint(FontInfo info, char c) {
	int width, height;
	int xOffset, yOffset;

	// 8bpp single channel
	u8* bitmap = stbtt_GetCodepointBitmap(&info.font, 0, stbtt_ScaleForPixelHeight(&info.font, 150.f), c, &width, &height, &xOffset, &yOffset);

	BitmapInfo Result = getEmptyBitmap(width, height, false);

	u8* Source = bitmap;
	u8* Row = (u8*)Result.contents + Result.pitch * (height - 1);

	for (int y = 0; y < height; y++) {
		u32* Pixel = (u32*)Row;
		for (int x = 0; x < width; x++) {
			u8 alpha = *Source++;
			*Pixel++ = ((alpha << 24) | (alpha << 16) | (alpha << 8) | (alpha << 0));
		}
		Row -= Result.pitch;
	}

	freeSTBBitmap(bitmap);

	return Result;
}

void freeSTBBitmap(unsigned char* bitmap) {
	stbtt_FreeBitmap(bitmap, 0);
}

