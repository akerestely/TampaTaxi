#pragma once
#include <vector>

#include "Texture.h"
#include "HudDigit.h"
#include "Object3d.h"
#include "Drawable.h"
#include "Model.h"

class Hud :  public Object3d, public Drawable
{
	GLuint hudTex;
	GLuint needleTex;
	double needleAngle;
	std::vector<HudDigit> digits;
	double totalKilometers;
	Model* model;
public:
	Hud(Point center, Model *model);

	void Draw();
	void DrawGauge(double gaugeRadius);
	void DrawCircle(double radius,double r, double g, double b);
	void DrawTransparentCircle(double radius,double r, double g, double b);
	void DrawNeedle(double circleRadius);
	void DrawKilometers();

	void setSpeed(double speed);
	void Update();

	~Hud(void);
};
