
#ifndef WKCUSTOMRENDERER_DRAWINGQUEUE_H
#define WKCUSTOMRENDERER_DRAWINGQUEUE_H

typedef unsigned long DWORD;
class DrawingQueue {
private:
	static void __stdcall hookRenderDrawingQueue(DWORD dddisplay, DWORD a3);
	static inline bool insideRenderDrawingQueue = false;
public:
	static void install();

	static bool isInsideRenderDrawingQueue();
};


#endif //WKCUSTOMRENDERER_DRAWINGQUEUE_H
