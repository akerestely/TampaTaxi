#include "Human.h"
#include "math.h"

#define MOVE_SPEED 0.3
#define ANIM_SPEED 2.0

Human::~Human(void)
{
}

Human::Human(Point base)
	:Movable(base,0.55/*body_width*/,0.55/*body_width*/)
{
	walk=false;
	goForward=false;
	angleLeftLeg=0;
	angleRightLeg=0;
	angleLeftArm=0;
	angleRightArm=0;
//	dz=0;
}

bool Human::WalkForward()
{
	if(Movable::MoveWith(-MOVE_SPEED))
	{
		walk=true;
		return true;
	}
	return false;
}
bool Human::WalkBackward()
{
	if(Movable::MoveWith(MOVE_SPEED))
	{
		walk=true;
		return true;
	}
	return false;
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
			angleAnim+=ANIM_SPEED;
		}
		else
			if(angleAnim>-angleLimit && goForward==false)
			{
				angleAnim-=ANIM_SPEED;
			}
}

void Human::Draw()
{
    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(center.x,center.y,center.z);
	glRotatef(angle*180/PI, 0,1,0);
	
	glPushMatrix();
	Animate(angleLeftLeg,35.0);
	DrawLeftLeg(angleLeftLeg);
	glPopMatrix();

	glPushMatrix();
	Animate(angleRightLeg,35.0);
	DrawRightLeg(angleRightLeg);
	glPopMatrix();

	glPushMatrix();
    DrawBody();
	glPopMatrix();

	glPushMatrix();
	DrawNeck();
	glPopMatrix();

	glPushMatrix();
	Animate(angleLeftArm,15.0);
	DrawLeftArm(angleLeftArm);
	glPopMatrix();

	glPushMatrix();
	Animate(angleRightArm,15.0);
	DrawRightArm(angleRightArm);
	glPopMatrix();

	glPushMatrix();
	DrawHead();
	glPopMatrix();
	
	glPopMatrix();
	if(walk)
		walk=false;
	else
		angleLeftArm=angleRightArm=angleLeftLeg=angleRightLeg=0;
}

void Human::DrawLeftLeg(double angleRotation)
{
	Texture tex=Texture::GetInstance();
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.jeansTex);

	leg_radius=0.10;
	leg_height=0.70;
	
	//draw left leg
	glPushMatrix();

	glTranslatef(-feet_radius-distance,feet_height+leg_height,0);
	glRotatef(-angleRotation,1,0,0);
	glRotatef(90, 1,0,0);

	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, leg_radius, leg_radius, leg_height, 30, 30);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.ballTex[0]);

	//draw left foot
	feet_radius=0.15;
	feet_height=0.075;
	distance=0.025;
	glPushMatrix();
	glTranslatef(0,feet_height+leg_height,0);
	glRotatef(-angleRotation,1,0,0);
	glTranslatef(0,-feet_height-leg_height,0);
	glTranslatef(-feet_radius-distance,feet_height,0);
	glRotatef(-angleRotation,1,0,0);
	glRotatef(90, 1,0,0);

	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricTexture(quadric, GL_TRUE); 

	gluCylinder(quadric, feet_radius, feet_radius, feet_height, 30, 30);
	glRotatef(180, 1,0,0);
	gluDisk(quadric, 0.0f, feet_radius, 30,1);
	glRotatef(180, 1,0,0);
	glTranslatef(0.0, 0.0, feet_height);
	gluDisk(quadric, 0.0, feet_radius, 30, 1);

	glPopMatrix();
}

void Human::DrawRightLeg(double angleRotation)
{
	Texture tex=Texture::GetInstance();
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.jeansTex);

	leg_radius=0.10;
	leg_height=0.70;	
	
	//draw right leg
	glPushMatrix();

	glTranslatef(feet_radius+distance,feet_height+leg_height,0);
	glRotatef(angleRotation,1,0,0);
	glRotatef(90, 1,0,0);

	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, leg_radius, leg_radius, leg_height, 30, 30);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.ballTex[0]);

	//draw right foot
	feet_radius=0.15;
	feet_height=0.075;
	distance=0.025;
	glPushMatrix();
	glTranslatef(0,feet_height+leg_height,0);
	glRotatef(angleRotation,1,0,0);
	glTranslatef(0,-feet_height-leg_height,0);
	glTranslatef(feet_radius+distance,feet_height,0);
	glRotatef(angleRotation,1,0,0);
	glRotatef(90, 1,0,0);

	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricTexture(quadric, GL_TRUE); 
	
	gluCylinder(quadric, feet_radius, feet_radius, feet_height, 30, 30);
	glRotatef(180, 1,0,0);
	gluDisk(quadric, 0.0f, feet_radius, 30,1);
	glRotatef(180, 1,0,0);
	glTranslatef(0.0, 0.0, feet_height);
	gluDisk(quadric, 0.0, feet_radius, 30, 1);

	glPopMatrix();
}

void Human::DrawBody()
{
	Texture tex=Texture::GetInstance();
	//draw the body
	glPushMatrix();	
	
	this->body_height=0.8;
	this->body_width=0.55;
	this->body_thickness=0.15;
	glTranslatef(0,feet_height+leg_height-0.02+body_height/2,0);

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.tshirtTex[0]);
	glBegin(GL_QUADS);  
	//front face
	glTexCoord2f(0.0,1.0); glVertex3f(-body_width/2, -body_height/2,-body_thickness);
	glTexCoord2f(1.0,1.0); glVertex3f(body_width/2, -body_height/2,-body_thickness);
	glTexCoord2f(1.0,0.0); glVertex3f(body_width/2, body_height/2,-body_thickness);
	glTexCoord2f(0.0,0.0); glVertex3f(-body_width/2, body_height/2,-body_thickness);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.tshirtTex[1]);
	//back face
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(-body_width/2, -body_height/2,body_thickness);
	glTexCoord2f(1.0,0.0); glVertex3f(body_width/2, -body_height/2,body_thickness);
	glTexCoord2f(1.0,1.0); glVertex3f(body_width/2, body_height/2,body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(-body_width/2, body_height/2,body_thickness);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.tshirtTex[1]);
	//left face
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(-body_width/2, -body_height/2,-body_thickness);
	glTexCoord2f(1.0,0.0); glVertex3f(-body_width/2, -body_height/2,body_thickness);
	glTexCoord2f(1.0,1.0); glVertex3f(-body_width/2, body_height/2,body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(-body_width/2, body_height/2,-body_thickness);
	glEnd();

	//right face
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.tshirtTex[1]);
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(body_width/2, -body_height/2,-body_thickness);
	glTexCoord2f(1.0,0.0); glVertex3f(body_width/2, -body_height/2,body_thickness);
	glTexCoord2f(1.0,1.0); glVertex3f(body_width/2, body_height/2,body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(body_width/2, body_height/2,-body_thickness);
	glEnd();

	//up face
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.tshirtTex[1]);
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0); glVertex3f(-body_width/2, body_height/2,body_thickness);
	glTexCoord2f(1.0,0.0); glVertex3f(body_width/2, body_height/2,body_thickness);
	glTexCoord2f(1.0,1.0); glVertex3f(body_width/2, body_height/2,-body_thickness);
	glTexCoord2f(0.0,1.0); glVertex3f(-body_width/2, body_height/2,-body_thickness);
	glEnd();

	//bottom face

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.tshirtTex[1]);
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
	Texture tex=Texture::GetInstance();
	
	neck_height=0.1;
	neck_radius=0.085;
	glDisable(GL_TEXTURE_2D);
	glColor3f(1,207./255, 175./255);
	glPushMatrix();
	glRotatef(-90, 1,0,0);

	glTranslatef(0,0,feet_height+leg_height+body_height-0.02);
	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, neck_radius, neck_radius, neck_height, 30, 30);
	glPopMatrix();
}

void Human::DrawHead()
{
	//draw head
	Texture tex=Texture::GetInstance();

	//head_height=0.5;
	head_radius=0.22;
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.faceTex);
	glPushMatrix();
	glRotatef(-270, 1,0,0);

	glTranslatef(0,0,-(feet_height+leg_height+body_height+neck_height+head_radius/2+0.05));
	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluSphere(quadric,head_radius, 30,30); 

	glPopMatrix();
}


void Human::DrawLeftArm(double angleRotation)
{
	
	
	arm_radius=0.08;
	arm_height=0.60;
	glDisable(GL_TEXTURE_2D);
	glColor3f(1,207./255, 175./255);
	
	//draw left arm
	glPushMatrix();
	glTranslatef(-body_width/2+arm_radius,feet_height+leg_height+body_height-arm_radius,0);
	glRotatef(angleRotation,1,0,0);
	glRotatef(65, 0,0,1);
	glRotatef(270, 0,1,0);
	
	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, arm_radius, arm_radius, arm_height, 30, 30);
	glPopMatrix();
}

void Human::DrawRightArm(double angleRotation)
{
	glDisable(GL_TEXTURE_2D);
	glColor3f(1,207./255, 175./255);

	//draw right arm
	glPushMatrix();
	glTranslatef(body_width/2-arm_radius,feet_height+leg_height+body_height-arm_radius,0);
	glRotatef(-angleRotation,1,0,0);
	glRotatef(-65, 0,0,1);
	glRotatef(90, 0,1,0);

	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, arm_radius, arm_radius, arm_height, 30, 30);
	glPopMatrix();
	
}