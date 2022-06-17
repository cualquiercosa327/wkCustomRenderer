
#include "Drawing.h"
#include "Hooks.h"
#include "Debugf.h"
#include "W2App.h"
#include <GL/glew.h>

int (__stdcall*origDrawBitmapOnBitmap)(int posX, int posY, int width, int height, BitmapImage *src, int srcOffsetX, int srcOffsetY, int a9, int flags);
int __stdcall Drawing::hookDrawBitmapOnBitmap(int posX, int posY, int width, int height, BitmapImage *src, int srcOffsetX, int srcOffsetY, int a9, int flags) {
	BitmapImage * dst;
	int retv;
	_asm mov dst, esi


	auto dddisplay = W2App::getAddrDdDisplay();
	bool drawToScreen = (!dst || (dddisplay && (dst == *(BitmapImage **) (dddisplay + 0x3D9C))));

	if(drawToScreen) {
		// pulled from jellyworm
		int srcWidth = src->max_width_dword14;
		int srcHeight = src->max_height_dword18;
		int glOffsetX = srcOffsetX;
		int glOffsetY = srcOffsetY;
		int glWidth = width;
		int glHeight = height;

		GLfloat startx = (float) glOffsetX / (float) srcWidth;
		GLfloat starty = (float) glOffsetY / (float) srcHeight;
		GLfloat endx = (float) (glOffsetX + width) / (float) srcWidth;
		GLfloat endy = (float) (glOffsetY + height) / (float) srcHeight;

		int sPosX = posX;
		int sPosY = posY;

//		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glBegin(GL_QUADS);
		//glTexCoord2f(startx, starty);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2i(sPosX, sPosY);
		//glTexCoord2f(endx, starty);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(sPosX + glWidth, sPosY);
		//glTexCoord2f(endx, endy);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2i(sPosX + glWidth, sPosY + glHeight);
		//glTexCoord2f(startx, endy);
		glColor3f(1.0, 0.0, 1.0);
		glVertex2i(sPosX, sPosY + glHeight);
		glEnd();
//		glPopAttrib();
	} else {
		callDrawBitmapOnBitmap(dst, posX, posY, width, height, src, srcOffsetX, srcOffsetY, a9, flags);
	}

	return retv;
}

int Drawing::drawBitbucket(int a1, DWORD *a2, Backend::CustomBitbucket *src, int posX, int posY, int offsetX, int offsetY, int width, int height, int flag) {

	int srcWidth = width;
	int srcHeight = height;
	int glOffsetX = offsetX;
	int glOffsetY = offsetY;
	int glWidth = width;
	int glHeight = height;

	GLfloat startx = (float) glOffsetX / (float) srcWidth;
	GLfloat starty = (float) glOffsetY / (float) srcHeight;
	GLfloat endx = (float) (glOffsetX + width) / (float) srcWidth;
	GLfloat endy = (float) (glOffsetY + height) / (float) srcHeight;

	int sPosX = posX;
	int sPosY = posY;

//		glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBegin(GL_QUADS);
	//glTexCoord2f(startx, starty);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(sPosX, sPosY);
	//glTexCoord2f(endx, starty);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(sPosX + glWidth, sPosY);
	//glTexCoord2f(endx, endy);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(sPosX + glWidth, sPosY + glHeight);
	//glTexCoord2f(startx, endy);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2i(sPosX, sPosY + glHeight);
	glEnd();

	return 0;
}



void Drawing::install() {
	DWORD addrDrawBitmapOnBitmap = _ScanPattern("DrawBitmapOnBitmap", "\x55\x8B\xEC\x83\xE4\xF8\x8B\x4D\x10\x8B\x45\x18\x83\xEC\x38\x85\xC9\x53\x57\x0F\x84\x00\x00\x00\x00\x83\x7D\x14\x00\x0F\x84\x00\x00\x00\x00\x8B\x50\x08\x8B\x78\x10\x8B\x46\x20\x8B\x5E\x1C", "??????xxxxxxxxxxxxxxx????xxxxxx????xxxxxxxxxxxx");
	DWORD addrDrawChunk = _ScanPattern("DrawChunk", "\x55\x8B\xEC\x83\xE4\xF8\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xEC\x30\x53\x56\x57\x8B\xD9\x8B\x4D\x08\x8B\xFA", "??????xxx????xx????xxxx????xxxxxxxxxxxxx");
	_HookDefault(DrawBitmapOnBitmap);
}

int Drawing::callDrawBitmapOnBitmap(BitmapImage *dst, int posX, int posY, int width, int height, BitmapImage *src, int srcOffsetX, int srcOffsetY, int a9, int flags) {
	int retv;
	_asm push flags
	_asm push a9
	_asm push srcOffsetY
	_asm push srcOffsetX
	_asm push src
	_asm push height
	_asm push width
	_asm push posY
	_asm push posX
	_asm mov esi, dst
	_asm call origDrawBitmapOnBitmap
	_asm mov retv, eax

	return retv;
}


