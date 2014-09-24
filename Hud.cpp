#include "Hud.h"

#include<cmath>
#define GAUGE_RADIUS 0.6

Hud::Hud(Point center,Model* model)
	:Object3d(center),model(model)
{	
	this->hudTex=Texture::GetInstance().hudText;
	needleAngle=0;
	digits.push_back(HudDigit(Point(3*GAUGE_RADIUS/10,-GAUGE_RADIUS/1.35,0.0),0,GAUGE_RADIUS));
	digits.push_back(HudDigit(Point(GAUGE_RADIUS/10,-GAUGE_RADIUS/1.35,0.0),0,GAUGE_RADIUS));
	digits.push_back(HudDigit(Point(-GAUGE_RADIUS/10,-GAUGE_RADIUS/1.35,0.0),0,GAUGE_RADIUS));
	digits.push_back(HudDigit(Point(-3*GAUGE_RADIUS/10,-GAUGE_RADIUS/1.35,0.0),0,GAUGE_RADIUS));
	totalKilometers=0;	
}

void Hud::setSpeed(double speed)
{
	if(speed>0)
	{
		needleAngle=speed/MAX_SPEED*270;
		totalKilometers+=speed/10;
		int aux=(int)totalKilometers;
		int digitPos=-1;
		while(aux!=0)
		{
			int c=aux%10;
			digits[++digitPos].setDigit(c);
			aux=aux/10;
		}
	}
	else
		needleAngle=0;
}


void Hud::Draw()
{
	glPushMatrix();
		glScaled(0.18,0.18,1);
		glTranslatef(2.3,-1.7,0);
		glTranslatef(center.x,center.y,-1.0);
		DrawGauge(GAUGE_RADIUS);
		DrawTransparentCircle(GAUGE_RADIUS,0.0,0.0,1.0);
		DrawCircle(0.080,0.0,0.0,0.0);
		DrawCircle(0.045,1.0,0.0,0.0);
		DrawCircle(0.027,0.0,0.0,0.0);
		for(int i=0;i<digits.size();i++)
			digits.at(i).Draw();
		DrawNeedle(GAUGE_RADIUS);
	glPopMatrix();
}

void Hud::DrawGauge(double r)
{
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Texture::GetInstance().hudText);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5,0.5);glVertex3f( 0,0,0. ); 
	for(double t = 0; t<=360;t+=1)
	{	
		glTexCoord2d(0.5 * cos(2 * PI - t * PI / 180) + 0.5, 0.5 * sin(2 * PI - t * PI / 180) + 0.5);
		glVertex3d(r * cos(t * PI / 180),r * sin(t * PI / 180), 0.);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Hud::DrawTransparentCircle(double radius,double r, double g, double b)
{
	glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(r,g,b,1.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f( 0,0,0. ); 
	for(double t = 0; t<=360;t+=1)
	{	
		glColor4f(0.0,0.0,1.0,0);
		glVertex3d(radius/1.4 * cos(t * PI / 180),radius/1.4* sin(t * PI / 180), 0.);
	}
	glEnd();
}

void Hud::DrawCircle(double radius,double r,double g,double b)
{
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f( 0,0,0. ); 
	for(double t = 0; t<=360;t+=1)
		glVertex3d(radius * cos(t * PI / 180),radius * sin(t * PI / 180), 0.);
	glEnd();
}

void Hud::DrawNeedle(double circleRadius)
{
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(1.0,0.0,0.0);
	glRotated(225-needleAngle,0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-circleRadius/3.0,circleRadius/30,0.0);
	glVertex3f(-circleRadius/3.0,-circleRadius/30,0.0);
	glVertex3f(circleRadius/1.1,0.0,0);
	glEnd();
}


void Hud::Update()
{
	Car *car=model->GetPlayer()->GetCar();
	if(car != NULL)
	{
		setSpeed(car->GetSpeed());
	}
}
Hud::~Hud(void)
{
}
