

#ifndef WKCUSTOMRENDERER_DRAWING_H
#define WKCUSTOMRENDERER_DRAWING_H

#include "BitmapImage.h"
#include "Backend.h"

class Drawing {
public:
	static int __stdcall hookDrawBitmapOnBitmap(int posX, int posY, int width, int height, BitmapImage *Src, int srcOffsetX, int srcOffsetY, int a9, int flags);
	static int callDrawBitmapOnBitmap(BitmapImage * dst, int posX, int posY, int width, int height, BitmapImage *src, int srcOffsetX, int srcOffsetY, int a9, int flags);
	static int drawBitbucket(int a1, DWORD *a2, Backend::CustomBitbucket * src, int posX, int posY, int offsetX, int offsetY, int width, int height, int flag);

	static void install();
};


#endif //WKCUSTOMRENDERER_DRAWING_H
