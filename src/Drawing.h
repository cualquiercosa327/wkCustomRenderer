

#ifndef WKCUSTOMRENDERER_DRAWING_H
#define WKCUSTOMRENDERER_DRAWING_H

#include "BitmapImage.h"

class Drawing {
public:
	static int __stdcall hookDrawBitmapOnBitmap(int posX, int posY, int width, int height, BitmapImage *Src, int srcOffsetX, int srcOffsetY, int a9, int flags);
	static int callDrawBitmapOnBitmap(BitmapImage * dst, int posX, int posY, int width, int height, BitmapImage *src, int srcOffsetX, int srcOffsetY, int a9, int flags);

	static void install();
};


#endif //WKCUSTOMRENDERER_DRAWING_H
