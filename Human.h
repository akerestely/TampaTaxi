#pragma once
#include "Drawable.h"
#include "Texture.h"
 
class Human : public Drawable
{
	bool walk;
	double angle;
	GLUquadricObj *quadric;
	double feet_height, feet_radius;
	double leg_height, leg_radius;
	double body_height, body_width, body_thickness;
	double neck_height, neck_radius;
	double arm_height, arm_radius;
	double head_height, head_radius;
	double distance;
	bool goForward;
	double angleLeftLeg, angleRightLeg, angleLeftArm, angleRightArm;
	double  turnAlpha;
public:
	Human(void);
	~Human(void);
	Human(Point base);
	void Draw();
	void DrawLeftLeg(double angleRotation);
	void DrawRightLeg(double angleRotation);
	void DrawBody();
	void DrawNeck();
	void DrawLeftArm(double angleRotation);
	void DrawRightArm(double angleRotation);
	void DrawHead();

	void WalkArms(double &angle);
	void WalkLegs(double &angle);
	void setWalk(bool walk);

	void setCenter(Point center);

	void Walk(double speed);
	void Turn(double alpha);
};
