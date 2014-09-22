#pragma once
#include <vector>
#include "Point.h"
class DebugWindow
{
private:
	int timebase;
	int frame;
	int timeFrame;
	Point camPosition;
	char textFrame[50];
	char textCam[50];
	void setOrthographicProjection();
	void restorePerspectiveProjection();
	void renderBitmapString(float x,float y,float z,void *font,	char *string);
	void DrawText(Point center,char* s);
	void DrawFPS(Point fpsPosition);
	void DrawCameraPosition(Point textPosition);
public:
	void setCamPosition(Point camPosition);
	DebugWindow(void);
	void Draw();
	~DebugWindow(void);
};
