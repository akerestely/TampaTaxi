#include "ctime"
#include "Human.h"
#include "math.h"

const double Human::feet_height=0.065, Human::feet_radius=0.15;
const double Human::leg_height=0.85, Human::leg_radius=0.08;
const double Human::body_height=0.6, Human::body_width=0.55, Human::body_thickness=0.15;
const double Human::neck_height=0.1, Human::neck_radius=0.085;
const double Human::arm_height=0.5, Human::arm_radius=0.08;
const double Human::head_radius=0.22;
const double Human::dist_legs=0.015;
const double Human::skirt_height=0.4, Human::skirt_dist=0.08;
const double Human::hair_strands=PI/8;

Human::~Human(void)
{
}

Human::Human(Point base)
	:Movable(base, body_width, body_width)
{
	hair_length=0.03;

	walk=false;
	goForward=false;
	angleLeftLeg=0;
	angleRightLeg=0;
	angleLeftArm=0;
	angleRightArm=0;
	collision_speed=0;
	right_change_direction=false;
	left_change_direction=false;
	position_on_sidewalk=0;
	callTaxi=false;
	inTaxi=false;

	int random;
	
	random=rand()%6+7;
	move_speed=random/100.0;
	anim_speed=random/2.;

	random=rand()%2;

	Texture tex=Texture::GetInstance();
	if(random==0)
	{
		female=true;
		random=rand()%3;
		fBodyTexFrontH=tex.fBodyTex[random][0];
		fBodyTexBackH=tex.fBodyTex[random][1];
		
		random=rand()%3;
		skirtTexH=tex.skirtTex[random];
		
		fFeetTexH=tex.fFeetTex[0];
		fFaceTexH=tex.fFaceTex[0];

	}
	else
	{
		female=false;
		random=rand()%3;
		mBodyTexFrontH=tex.mBodyTex[random][0];
		mBodyTexBackH=tex.mBodyTex[random][1];
		
		random=rand()%3;
		mLegsTexH=tex.mLegsTex[random];
		
		mFeetTexH=tex.mFeetTex[0];
		mFaceTexH=tex.mFaceTex[0];

	}
	skinTexH=tex.skinTex;
	getTaxiTex=tex.getTaxiTex;
}

bool Human::WalkForward()
{
	if(callTaxi==false)
	{
		if(MoveWith(-move_speed))
		{
			walk=true;
			return true;
		}
	}
	return false;
}

bool Human::WalkBackward()
{
	if(callTaxi==false)
	{
		if(MoveWith(move_speed))
		{
			walk=true;
			return true;
		}
	}
	return false;
}

void Human::setLimits(Point limit1, Point limit2)
{
	this->limit1=limit1;
	this->limit2=limit2;
}

void Human::Update()
{	
	SF3dVector canWalk(center,limit1);
	SF3dVector canWalk2(limit2,center);
    if((canWalk.GetMagnitude() < 2 || canWalk2.GetMagnitude() < 2))
	{
		IncrementAngle(180);
	    WalkForward();
	}
	if(WalkForward()==false && callTaxi==false){
		if(position_on_sidewalk==0)
			{
				int random=rand()%2;
				if(random==0)
				{
					right_change_direction=true;
					IncrementAngle(90);
					position_on_sidewalk+=1;
					return;
				}
				if(random==1)
				{
					left_change_direction=true;
					IncrementAngle(-90);
					position_on_sidewalk-=1;
					return;
				}
			}
			if(position_on_sidewalk==1)
			{
				left_change_direction=true;
				IncrementAngle(-90);
				position_on_sidewalk-=1;
				return;
			}
			if(position_on_sidewalk==-1)
			{
				right_change_direction=true;
				IncrementAngle(90);
				position_on_sidewalk+=1;
				return;
			}
	}
	if(right_change_direction==true || left_change_direction==true)
	{
		collision_speed+=move_speed;
		if(collision_speed <= body_width)
			WalkForward();
		else
		{
			if(right_change_direction==true)
			{
				IncrementAngle(-90);
				collision_speed=0;
				right_change_direction=false;
				return;
			}
			if(left_change_direction==true)
			{
				IncrementAngle(+90);
				collision_speed=0;
				left_change_direction=false;
				return;
			}
		}
	}
}

void Human::Animate(double &angleAnim,const double angleLimit)
{
	if(angleAnim>=angleLimit)
		goForward=false;
	if(angleAnim<=-angleLimit)
		goForward=true;
	if(walk==true)
		if(angleAnim<angleLimit && goForward==true)
		{
			angleAnim+=anim_speed;
		}
		else
			if(angleAnim>-angleLimit && goForward==false)
			{
				angleAnim-=anim_speed;
			}
}

void Human::Draw()
{
	glPushMatrix();

	glTranslatef(center.x,center.y,center.z);
	glRotatef(angle*180/PI, 0,1,0);
	
	if(callTaxi==false)
	{
		glPushMatrix();
		Animate(angleLeftLeg,15.0);
		DrawLeftLeg(angleLeftLeg);
		glPopMatrix();

		glPushMatrix();
		Animate(angleRightLeg,15.0);
		DrawRightLeg(angleRightLeg);
		glPopMatrix();
	}
	else
	{
		DrawLeftLeg(0);
		DrawRightLeg(0);
	}

	DrawBody();

	if(female==true)
	{
		DrawSkirt();
	}

	DrawNeck();

	
	if(callTaxi==false)
	{
		glPushMatrix();
		Animate(angleLeftArm,15.0);
		DrawLeftArm(angleLeftArm);
		glPopMatrix();

		glPushMatrix();
		Animate(angleRightArm,15.0);
		DrawRightArm(angleRightArm);
		glPopMatrix();
	}
	else
	{
		DrawLeftArm(0);
		DrawRightArm(0);
	}

	DrawHead();

	if(female==true)
	{
		DrawHair();
	}
	if(callTaxi==true)
	{
		DrawCallTaxi();
	}

	glPopMatrix();
	if(walk)
		walk=false;
	else
		angleLeftArm=angleRightArm=angleLeftLeg=angleRightLeg=0;
}

void Human::SetCallTaxi(bool callTaxi)
{
	if(callTaxi==false)
	{
		SF3dVector viewTheRoad(limit1,limit2);
		SetViewDir(viewTheRoad.GetNormalized());
	}
	this->callTaxi=callTaxi;
}

bool Human::GetCallTaxi()
{
	return callTaxi;
}


void Human::DrawCallTaxi()
{
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTaxiTex);
	
	glTranslatef(0,(feet_height+leg_height+body_height+neck_height+(2*head_radius)+0.2),0);
	glRotatef(180, 0,0,1);

	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDisk(quadric, 0.0f, 0.2, 30, 1);
	glPopMatrix();
}


void Human::SetInTaxi(bool inTaxi)
{
	this->inTaxi=inTaxi;
}

bool Human::GetInTaxi()
{
	return inTaxi;
}

void Human::DrawLeftLeg(double angleRotation)
{
	glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
	if(female==true)
		glBindTexture(GL_TEXTURE_2D, skinTexH);
	else
		glBindTexture(GL_TEXTURE_2D, mLegsTexH);

	//draw left leg
	glPushMatrix();

	double distance_from_ground=feet_height+leg_height;

	glTranslatef(-feet_radius-dist_legs,distance_from_ground,0);
	glRotatef(-angleRotation,1,0,0);
	glRotatef(90, 1,0,0);

	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, leg_radius, leg_radius, leg_height, 5, 1);
	glPopMatrix();

	//draw left foot
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);

	if(female==true)
		glBindTexture(GL_TEXTURE_2D, fFeetTexH);
	else
		glBindTexture(GL_TEXTURE_2D, mFeetTexH);

	glPushMatrix();
	glTranslatef(0,distance_from_ground,0);
	glRotatef(-angleRotation,1,0,0);
	glTranslatef(0,-distance_from_ground,0);
	glTranslatef(-feet_radius-dist_legs,feet_height,0);
	glRotatef(-angleRotation,1,0,0);
	glRotatef(90, 1,0,0);

	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricTexture(quadric, GL_TRUE); 

	gluCylinder(quadric, leg_radius, feet_radius, feet_height, 5, 1);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.51,0.47,0.4);
	glRotatef(180, 1,0,0);
	gluDisk(quadric, 0.0f, leg_radius, 30,1);
	glRotatef(180, 1,0,0);
	glColor3f(1.,1.,1.);
	glTranslatef(0.0, 0.0, feet_height);
	gluDisk(quadric, 0.0, feet_radius, 30, 1);

	glPopMatrix();
}

void Human::DrawRightLeg(double angleRotation)
{
	glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
	if(female==true)
		glBindTexture(GL_TEXTURE_2D, skinTexH);
	else
		glBindTexture(GL_TEXTURE_2D, mLegsTexH);
	
	//draw right leg
	glPushMatrix();
	double distance_from_ground=feet_height+leg_height;

	glTranslatef(feet_radius+dist_legs,distance_from_ground,0);
	glRotatef(angleRotation,1,0,0);
	glRotatef(90, 1,0,0);

	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, leg_radius, leg_radius, leg_height, 5, 1);
	glPopMatrix();

	//draw right foot
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	if(female==true)
		glBindTexture(GL_TEXTURE_2D, fFeetTexH);
	else
		glBindTexture(GL_TEXTURE_2D, mFeetTexH);

	glPushMatrix();
	glTranslatef(0,distance_from_ground,0);
	glRotatef(angleRotation,1,0,0);
	glTranslatef(0,-distance_from_ground,0);
	glTranslatef(feet_radius+dist_legs,feet_height,0);
	glRotatef(angleRotation,1,0,0);
	glRotatef(90, 1,0,0);

	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricTexture(quadric, GL_TRUE); 
	
	gluCylinder(quadric, leg_radius, feet_radius, feet_height, 5, 1);

	glDisable(GL_TEXTURE_2D);
	glColor3f(0.51,0.47,0.4);
	glRotatef(180, 1,0,0);
	gluDisk(quadric, 0.0f, leg_radius, 30,1);
	glRotatef(180, 1,0,0);
	glColor3f(1.,1.,1.);
	glTranslatef(0.0, 0.0, feet_height);
	gluDisk(quadric, 0.0, feet_radius, 30, 1);

	glPopMatrix();
}

void Human::DrawSkirt()
{
	
	glPushMatrix();	
	
	double distance_from_ground=feet_height+leg_height-skirt_height/2;
	glTranslatef(0,distance_from_ground,0);

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, skirtTexH);
	glBegin(GL_QUADS);  
	double half_width=body_width/2;
	double half_height=skirt_height/2;
	
	//front face
	glBegin(GL_QUADS);

	glTexCoord2f(0.0,1.0); glVertex3f(-half_width-skirt_dist, -half_height,-body_thickness-skirt_dist);
	glTexCoord2f(1.0,1.0); glVertex3f(half_width+skirt_dist, -half_height, -body_thickness-skirt_dist);
	glTexCoord2f(1.0,0.0); glVertex3f(half_width, half_height,-body_thickness);
	glTexCoord2f(0.0,0.0); glVertex3f(-half_width, half_height,-body_thickness);
	glEnd();

	//back face
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(-half_width-skirt_dist, -half_height, body_thickness+skirt_dist);
	glTexCoord2f(1.0,0.0); glVertex3f(half_width+skirt_dist, -half_height, body_thickness+skirt_dist);
	glTexCoord2f(1.0,1.0); glVertex3f(half_width, half_height, body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(-half_width, half_height ,body_thickness);
	glEnd();

		
	//left face
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(-half_width, -half_height, -body_thickness-skirt_dist);
	glTexCoord2f(1.0,0.0); glVertex3f(-half_width, -half_height, body_thickness+skirt_dist);
	glTexCoord2f(1.0,1.0); glVertex3f(-half_width, half_height, body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(-half_width, half_height, -body_thickness);
	glEnd();

	//right face
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(half_width, -half_height, -body_thickness-skirt_dist);
	glTexCoord2f(1.0,0.0); glVertex3f(half_width, -half_height, body_thickness+skirt_dist);
	glTexCoord2f(1.0,1.0); glVertex3f(half_width, half_height, body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(half_width, half_height, -body_thickness);
	glEnd();

	//up face
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(-half_width, half_height, body_thickness);
	glTexCoord2f(1.0,0.0); glVertex3f(half_width, half_height, body_thickness);
	glTexCoord2f(1.0,1.0); glVertex3f(half_width, half_height, -body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(-half_width, half_height, -body_thickness);
	glEnd();

	//bottom face
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(-half_width-skirt_dist, -half_height, body_thickness+skirt_dist);
	glTexCoord2f(1.0,0.0); glVertex3f(half_width+skirt_dist, -half_height, body_thickness+skirt_dist);
	glTexCoord2f(1.0,1.0); glVertex3f(half_width+skirt_dist, -half_height, -body_thickness-skirt_dist);
	glTexCoord2f(0.0,1.0); glVertex3f(-half_width-skirt_dist, -half_height, -body_thickness-skirt_dist);
	glEnd();
	glPopMatrix();
}

void Human::DrawBody()
{
	//draw the body
	glPushMatrix();	
	double distance_from_ground=feet_height+leg_height-0.02+body_height/2;
	glTranslatef(0,distance_from_ground,0);

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	if(female==true)
		glBindTexture(GL_TEXTURE_2D, fBodyTexFrontH);
	else
		glBindTexture(GL_TEXTURE_2D, mBodyTexFrontH);
		
	glBegin(GL_QUADS);  
	//front face
	glTexCoord2f(1.0,1.0); glVertex3f(-body_width/2, -body_height/2,-body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(body_width/2, -body_height/2,-body_thickness);
	glTexCoord2f(0.0,0.0); glVertex3f(body_width/2, body_height/2,-body_thickness);
	glTexCoord2f(1.0,0.0); glVertex3f(-body_width/2, body_height/2,-body_thickness);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	if(female==true)
		glBindTexture(GL_TEXTURE_2D, fBodyTexBackH);
	else
		glBindTexture(GL_TEXTURE_2D, mBodyTexBackH);
		
	//back face
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(-body_width/2, -body_height/2,body_thickness);
	glTexCoord2f(1.0,0.0); glVertex3f(body_width/2, -body_height/2,body_thickness);
	glTexCoord2f(1.0,1.0); glVertex3f(body_width/2, body_height/2,body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(-body_width/2, body_height/2,body_thickness);
	glEnd();
		
	//left face
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(-body_width/2, -body_height/2,-body_thickness);
	glTexCoord2f(1.0,0.0); glVertex3f(-body_width/2, -body_height/2,body_thickness);
	glTexCoord2f(1.0,1.0); glVertex3f(-body_width/2, body_height/2,body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(-body_width/2, body_height/2,-body_thickness);
	glEnd();

	//right face
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(body_width/2, -body_height/2,-body_thickness);
	glTexCoord2f(1.0,0.0); glVertex3f(body_width/2, -body_height/2,body_thickness);
	glTexCoord2f(1.0,1.0); glVertex3f(body_width/2, body_height/2,body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(body_width/2, body_height/2,-body_thickness);
	glEnd();

	//up face
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(-body_width/2, body_height/2,body_thickness);
	glTexCoord2f(1.0,0.0); glVertex3f(body_width/2, body_height/2,body_thickness);
	glTexCoord2f(1.0,1.0); glVertex3f(body_width/2, body_height/2,-body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(-body_width/2, body_height/2,-body_thickness);
	glEnd();

	//bottom face
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(-body_width/2, -body_height/2,body_thickness);
	glTexCoord2f(1.0,0.0); glVertex3f(body_width/2, -body_height/2,body_thickness);
	glTexCoord2f(1.0,1.0); glVertex3f(body_width/2, -body_height/2,-body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(-body_width/2, -body_height/2,-body_thickness);
	glEnd();
	glPopMatrix();
}

void Human::DrawNeck()
{
	//draw the neck
	
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 0.81, 0.68);
	glPushMatrix();
	glRotatef(-90, 1,0,0);
	
	glTranslatef(0,0,feet_height+leg_height+body_height-0.02);
	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, neck_radius, neck_radius, neck_height, 5, 1);
	glPopMatrix();
}

void Human::DrawHead()
{
	//draw head

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	if(female==true)
		glBindTexture(GL_TEXTURE_2D, fFaceTexH);
	else
		glBindTexture(GL_TEXTURE_2D, mFaceTexH);
	glPushMatrix();
	glRotatef(-270, 1,0,0);

	glTranslatef(0,0,-(feet_height+leg_height+body_height+neck_height+head_radius/2+0.05));
	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluSphere(quadric,head_radius, 5,5); 

	glPopMatrix();
}

void Human::DrawHair()
{

	glDisable(GL_TEXTURE_2D);
	glPushMatrix();

	double sum_angle=-PI/8;
	glTranslatef(0,(feet_height+leg_height+body_height+neck_height+head_radius/2+0.05),0);
	glColor3f(0.28, 0.17, 0.11);



	for(int i=0; i<5; i++)
	{
		glBegin(GL_QUADS);  
		glTexCoord2f(0.0,0.0); glVertex3f(head_radius*cos(sum_angle), -head_radius-hair_length, head_radius* sin(sum_angle));
		glTexCoord2f(1.0,0.0); glVertex3f(head_radius*cos(sum_angle+hair_strands), -head_radius-hair_length,head_radius* sin(sum_angle+hair_strands));
		glTexCoord2f(1.0,1.0); glVertex3f(head_radius *cos(sum_angle+hair_strands), 0, head_radius* sin(sum_angle+hair_strands));
		glTexCoord2f(0.0,1.0); glVertex3f(head_radius*cos(sum_angle), 0, head_radius* sin(sum_angle));
		glEnd();
		hair_length+=0.02;
		sum_angle+=hair_strands;
	}

	for(int i=0; i<5; i++)
	{
		hair_length-=0.02;

		glBegin(GL_QUADS);  
		glTexCoord2f(0.0,0.0); glVertex3f(head_radius*cos(sum_angle), -head_radius-hair_length, head_radius* sin(sum_angle));
		glTexCoord2f(1.0,0.0); glVertex3f(head_radius*cos(sum_angle+hair_strands), -head_radius-hair_length,head_radius* sin(sum_angle+hair_strands));
		glTexCoord2f(1.0,1.0); glVertex3f(head_radius *cos(sum_angle+hair_strands), 0, head_radius* sin(sum_angle+hair_strands));
		glTexCoord2f(0.0,1.0); glVertex3f(head_radius*cos(sum_angle), 0, head_radius* sin(sum_angle));
		glEnd();
		sum_angle+=hair_strands;
	}
	glPopMatrix();
}


void Human::DrawLeftArm(double angleRotation)
{
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 0.81, 0.68);
	
	//draw left arm
	glPushMatrix();
	glTranslatef(-body_width/2+arm_radius,feet_height+leg_height+body_height-arm_radius,0);
	glRotatef(angleRotation,1,0,0);

	glPushMatrix();
	glTranslatef(-body_width/2+arm_radius/2,-arm_height,0);
	gluSphere(quadric, arm_radius+0.02, 30,30);
	glPopMatrix();

	glRotatef(65, 0,0,1);
	glRotatef(270, 0,1,0);
	
	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, arm_radius, arm_radius, arm_height, 5, 1);

	glPopMatrix();
}

void Human::DrawRightArm(double angleRotation)
{
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 0.81, 0.68);

	//draw right arm
	glPushMatrix();
	glTranslatef(body_width/2-arm_radius,feet_height+leg_height+body_height-arm_radius,0);
	glRotatef(-angleRotation,1,0,0);

	glPushMatrix();
	glTranslatef(body_width/2-arm_radius/2,-arm_height,0);
	gluSphere(quadric, arm_radius+0.02, 30,30);
	glPopMatrix();

	glRotatef(-65, 0,0,1);
	glRotatef(90, 0,1,0);

	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricDrawStyle(quadric, GLU_FILL);

	gluCylinder(quadric, arm_radius, arm_radius, arm_height, 5, 1);
	
	glPopMatrix();
}

