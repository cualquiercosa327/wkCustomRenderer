
#include "DrawingQueue.h"
#include "Hooks.h"

void (__stdcall *origRenderDrawingQueue)(DWORD dddisplay, DWORD a3);
void __stdcall DrawingQueue::hookRenderDrawingQueue(DWORD dddisplay, DWORD a3) {
	DWORD GameScene;
	_asm mov GameScene, eax

	insideRenderDrawingQueue = true;

	_asm mov eax, GameScene
	_asm push a3
	_asm push dddisplay
	_asm call origRenderDrawingQueue

	insideRenderDrawingQueue = false;
}


void DrawingQueue::install() {
	DWORD addrRenderDrawingQueue = _ScanPattern("RenderDrawingQueue", "\x83\xEC\x1C\x53\x55\x8B\x6C\x24\x28\x56\x57\x8B\xF0\x8B\x86\x00\x00\x00\x00\x68\x00\x00\x00\x00\x6A\x04\x50\x8D\x8E\x00\x00\x00\x00\x51\xE8\x00\x00\x00\x00", "??????xxxxxxxxx????x????xxxxx????xx????");
	_HookDefault(RenderDrawingQueue);
}

bool DrawingQueue::isInsideRenderDrawingQueue() {
	return insideRenderDrawingQueue;
}
