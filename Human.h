#pragma once
#include "Movable.h"
#include "Drawable.h"
#include "Texture.h"
 
class Human : public Movable, public Drawable
{
	bool walk;
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
public:
	Human(Point base);
	~Human(void);
	void Draw();
	void DrawLeftLeg(double angleRotation);
	void DrawRightLeg(double angleRotation);
	void DrawBody();
	void DrawNeck();
	void DrawLeftArm(double angleRotation);
	void DrawRightArm(double angleRotation);
	void DrawHead();

	void Animate(double &angleAnim,const double angleLimit);
	
	bool WalkForward();
	bool WalkBackward();
};
