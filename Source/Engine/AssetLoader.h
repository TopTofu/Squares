#pragma once

#include <Windows.h>
#include <iostream>
#include <assert.h>

#include "Util/Utilities.h"

#define BITMAP_BYTES_PER_PIXEL 4


struct ReadFileResult {
	u32 contentSize;
	void* content;
};

struct BitmapInfo {
	u32 width;
	u32 height;

	u8* contents;
};

ReadFileResult readFileIntoBuffer(const char* path);

BitmapInfo getEmptyBitmap(u32 width, u32 height, bool clear = true);