#include <Engine/AssetLoader.h>

ReadFileResult readFileIntoBuffer(const char* path) {
	ReadFileResult Result{};

	HANDLE FileHandle = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if (FileHandle != INVALID_HANDLE_VALUE) {
		LARGE_INTEGER FileSize;
		if (GetFileSizeEx(FileHandle, &FileSize)) {
			assert(FileSize.QuadPart <= 0xFFFFFFFF);
			uint32_t FileSize32 = (uint32_t)FileSize.QuadPart;
			Result.content = VirtualAlloc(0, FileSize32, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			if (Result.content) {
				DWORD BytesRead = 0;
				if (ReadFile(FileHandle, Result.content, FileSize.QuadPart, &BytesRead, 0)) {
					Result.contentSize = BytesRead;
				}
				else {
					VirtualFree(Result.content, BytesRead, MEM_RELEASE);
				}
			}
		}

		CloseHandle(FileHandle);
	}

	return Result;
}


BitmapInfo getEmptyBitmap(u32 width, u32 height, bool clear) {
	BitmapInfo Result{};
	
	u32 size = width * height * BITMAP_BYTES_PER_PIXEL;

	u8* data = new u8[size];
	
	if (clear) {
		memset(data, 0, size * sizeof(*data));
	}

	Result.contents = data;
	Result.width = width;
	Result.height = height;
	Result.pitch = width * BITMAP_BYTES_PER_PIXEL;

	return Result;
}