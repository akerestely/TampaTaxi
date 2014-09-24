#pragma once
#include "Movable.h"
#include "Drawable.h"
#include "Texture.h"
 
class Human : public Movable, public Drawable
{
	bool walk;
	GLUquadricObj *quadric;
	static const double feet_height, feet_radius;
	static const double leg_height, leg_radius;
	static const double body_height, body_width, body_thickness;
	static const double neck_height, neck_radius;
	static const double arm_height, arm_radius;
	static const double head_radius;
	static const double dist_legs;
	static const double skirt_height, skirt_dist;
	static const double hair_strands;
	
	GLuint fBodyTexFrontH;
	GLuint fBodyTexBackH;
	GLuint mBodyTexFrontH;
	GLuint mBodyTexBackH;
	GLuint skirtTexH;
	GLuint mLegsTexH;
	GLuint fFeetTexH;
	GLuint mFeetTexH;
	GLuint fFaceTexH;
	GLuint mFaceTexH;
	GLuint skinTexH;

	double hair_length;
	bool goForward;
	double angleLeftLeg, angleRightLeg, angleLeftArm, angleRightArm;
	double collision_speed;
	bool right_change_direction;
	bool left_change_direction;
	bool female;
	int position_on_sidewalk;
public:
	Human(Point base);
	~Human(void);
	void Draw();
	void DrawLeftLeg(double angleRotation);
	void DrawRightLeg(double angleRotation);
	void DrawBody();
	void DrawSkirt();
	void DrawNeck();
	void DrawLeftArm(double angleRotation);
	void DrawRightArm(double angleRotation);
	void DrawHead();
	void DrawHair();

	void Animate(double &angleAnim,const double angleLimit);
	
	bool WalkForward();
	bool WalkBackward();

	void Update();
};

