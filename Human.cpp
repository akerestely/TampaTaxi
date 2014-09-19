#include "Human.h"
#include "math.h"

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

void Human::WalkLegs(double &angleAnim)
{
	if(angleAnim>=35)
		goForward=false;
	if(angleAnim<=-35)
		goForward=true;
	if(walk==true)
		if(angleAnim<35 && goForward==true)
		{
			angleAnim+=0.5;
		}
		else
			if(angleAnim>-35 && goForward==false)
			{
				angleAnim-=0.5;
			}
}

void Human::WalkArms(double &angleAnim)
{
	if(angleAnim>=15)
		goForward=false;
	if(angleAnim<=-15)
		goForward=true;
	if(walk==true)
		if(angleAnim<15 && goForward==true)
		{
			angleAnim+=0.5;
		}
		else
			if(angleAnim>-15 && goForward==false)
			{
				angleAnim-=0.5;
			}
}

void Human::Draw()
{
    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(center.x,center.y,center.z);
	glRotatef(angle*180/PI, 0,1,0);
	
	glPushMatrix();
	WalkLegs(angleLeftLeg);
	DrawLeftLeg(angleLeftLeg);
	glPopMatrix();

	glPushMatrix();
	WalkLegs(angleRightLeg);
	DrawRightLeg(angleRightLeg);
	glPopMatrix();

	glPushMatrix();
    DrawBody();
	glPopMatrix();

	glPushMatrix();
	DrawNeck();
	glPopMatrix();

	glPushMatrix();
	WalkArms(angleLeftArm);
	DrawLeftArm(angleLeftArm);
	glPopMatrix();

	glPushMatrix();
	WalkArms(angleRightArm);
	DrawRightArm(angleRightArm);
	glPopMatrix();

	glPushMatrix();
	DrawHead();
	glPopMatrix();
	
	glPopMatrix();
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
	glBindTexture(GL_TEXTURE_2D, tex.ballTex[1]);

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
	glBindTexture(GL_TEXTURE_2D, tex.ballTex[1]);

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
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.skinTex);
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
	glBindTexture(GL_TEXTURE_2D, tex.skinTex);
	glPushMatrix();
	glRotatef(-90, 1,0,0);

	glTranslatef(0,0,feet_height+leg_height+body_height+neck_height+head_radius/2+0.05);
	quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluSphere(quadric,head_radius, 30,30); 

	glPopMatrix();
}


void Human::DrawLeftArm(double angleRotation)
{
	Texture tex=Texture::GetInstance();
	
	arm_radius=0.08;
	arm_height=0.60;
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.skinTex);
	
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
	Texture tex=Texture::GetInstance();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.skinTex);

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
	glDisable(GL_TEXTURE_2D);
}
void Human::setWalk(bool walk)
{
	this->walk=walk;
}


void Human::setCenter(Point center)
{
	this->center.x=center.x;
	this->center.y=center.y;
	this->center.z=center.z;
}

void Human::Walk(double speed)
{
	if(walk==true)
	{
		center.x=center.x+speed*cos(-angleAnim*PI/180);
		center.z=center.z+speed*sin(-angleAnim*PI/180);
	}
}



