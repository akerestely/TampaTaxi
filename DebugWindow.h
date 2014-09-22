#pragma once
#include <vector>
#include "Model.h"
#include "Point.h"
class DebugWindow
{
private:
	Model *model;
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
	DebugWindow(Model *model);
	void Draw();
	~DebugWindow(void);
};
