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
	std::vector<HudDigit> feeDigits;
	std::vector<HudDigit> totalFeesDigits;
	bool showFeeDigits;
	double totalKilometers;
	double totalFees;
	int clientKilometersIn,clientKilometersOut;
	bool isHudBusy;

	Model* model;
	char* streetName;
	void setSpeed(double speed);
	void setFeeDigits(double value);
	void updateTotalFeesDigits();

public:
	Hud(Point center, Model *model);

	void Draw();
	void DrawGauge(double gaugeRadius);
	void DrawCircle(double radius,double r, double g, double b);
	void DrawTransparentCircle(double radius,double r, double g, double b);
	void DrawNeedle(double circleRadius);
	void DrawKilometers();
	void DrawCurrentStreet();
	void DrawFeeDigits();
	void DrawTotalFeesDigits();

	void Update(char* streetName);


	~Hud(void);
};
