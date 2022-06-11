
#include "Sprites.h"
#include "Hooks.h"
#include <set>
#include "Config.h"
#include "W2App.h"
#include "WaLibc.h"
#include "Debugf.h"



DWORD __fastcall Sprites::hookLoadSpriteFromVFS(DWORD DD_Display, int EDX, int palette, int index, int a4, int vfs_a5, const char *filename) {
	if(Config::isDebugSpriteImg()) debugf("Loading sprite: index: %d filename: %s\n", index, filename);
	DWORD ret =origLoadSpriteFromVFS(DD_Display, EDX, palette, index, a4, vfs_a5, filename);
	if(Config::isDebugSpriteImg()) debugf("\t%s loading result: %d\n", filename, ret);
	return ret;
}


int Sprites::install() {
	DWORD addrConstructSprite = _ScanPattern("ConstructSprite", "\x89\x48\x04\x33\xC9\xC7\x00\x00\x00\x00\x00\xC7\x40\x00\x00\x00\x00\x00\x89\x48\x48\x89\x48\x4C\x89\x48\x44\x89\x48\x3C\x89\x48\x50\x89\x48\x54\x89\x48\x58\x89\x48\x5C\xC7\x40\x00\x00\x00\x00\x00", "??????x????xx?????xxxxxxxxxxxxxxxxxxxxxxxxxx?????");
	DWORD *addrSpriteVTable = *(DWORD**)(addrConstructSprite + 0x7);
	DWORD addrDestroySprite = addrSpriteVTable[0];
	DWORD addrLoadSpriteFromVFS = _ScanPattern("LoadSpriteFromVFS", "\x55\x8B\x6C\x24\x0C\xF7\xC5\x00\x00\x00\x00\x56\x8B\xF1\x74\x0A\x5E\xB8\x00\x00\x00\x00\x5D\xC2\x14\x00\x53\x8B\x5C\x24\x10\x8D\x43\xFF\x83\xF8\x02\x0F\x87\x00\x00\x00\x00\x83\xBC\x9E\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00", "??????x????xxxxxxx????xxxxxxxxxxxxxxxxx????xxx?????xx????");

	_HookDefault(LoadSpriteFromVFS);
	return 0;
}
