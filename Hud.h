#pragma once
#include "Drawable.h"
#include"Texture.h"
#include<vector>
#include"HudDigit.h"
#define MAX_SPEED 1.0

class Hud :public Drawable
{
	GLuint hudTex;
	GLuint needleTex;
	double needleAngle;
	std::vector<HudDigit> digits;
	double totalKilometers;
public:
	Hud();
	Hud(Point center);

	void Draw();
	void DrawGauge(double gaugeRadius);
	void DrawCircle(double radius,double r, double g, double b);
	void DrawTransparentCircle(double radius,double r, double g, double b);
	void DrawNeedle(double circleRadius);
	void DrawKilometers();

	void setSpeed(double speed);

	~Hud(void);
};
