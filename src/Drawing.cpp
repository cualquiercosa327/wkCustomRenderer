
#include "Drawing.h"
#include "Hooks.h"
#include "Debugf.h"
#include "W2App.h"

int (__stdcall*origDrawBitmapOnBitmap)(int posX, int posY, int width, int height, BitmapImage *src, int srcOffsetX, int srcOffsetY, int a9, int flags);
int __stdcall Drawing::hookDrawBitmapOnBitmap(int posX, int posY, int width, int height, BitmapImage *src, int srcOffsetX, int srcOffsetY, int a9, int flags) {
	BitmapImage * dst;
	int retv;
	_asm mov dst, esi


	auto dddisplay = W2App::getAddrDdDisplay();
	bool drawToScreen = (!dst || (dddisplay && (dst == *(BitmapImage **) (dddisplay + 0x3D9C))));

//	if(!drawToScreen) {
	_asm mov esi, dst
	origDrawBitmapOnBitmap(posX, posY, width, height, src, srcOffsetX, srcOffsetY, a9, flags);
	_asm mov retv, eax
//	}

	return retv;
}

void Drawing::install() {
	DWORD addrDrawBitmapOnBitmap = _ScanPattern("DrawBitmapOnBitmap", "\x55\x8B\xEC\x83\xE4\xF8\x8B\x4D\x10\x8B\x45\x18\x83\xEC\x38\x85\xC9\x53\x57\x0F\x84\x00\x00\x00\x00\x83\x7D\x14\x00\x0F\x84\x00\x00\x00\x00\x8B\x50\x08\x8B\x78\x10\x8B\x46\x20\x8B\x5E\x1C", "??????xxxxxxxxxxxxxxx????xxxxxx????xxxxxxxxxxxx");
	DWORD addrDrawChunk = _ScanPattern("DrawChunk", "\x55\x8B\xEC\x83\xE4\xF8\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xEC\x30\x53\x56\x57\x8B\xD9\x8B\x4D\x08\x8B\xFA", "??????xxx????xx????xxxx????xxxxxxxxxxxxx");
	_HookDefault(DrawBitmapOnBitmap);
}
