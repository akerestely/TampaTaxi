#include "math.h"
#include <iostream>
#include "Texture.h"
#include "Car.h"
#include "Tools.h"

#define CAR_SCALE 0.35

#define ACCELERATION 0.002
#define BREAK -0.004
#define FS 0.0001

#define ENGINFORCE 50.0
#define BREAKING 30.0
#define REVERSE 8.0
#define AIR_DRAG  0.3257
#define ROLLING_DRAG 20.8
#define MASS 6000

#define STEER_ANGLE 45

Car::Car(Point center) 
	:Movable(center,6.6*CAR_SCALE,13.6*CAR_SCALE)
{
	speed = 0;
	w = new Wheel*[4];

	w[0] = new Wheel(Point(-4.35, 0.0, 2.81), 1.12, 1);
	w[1] = new Wheel(Point(-4.35, 0.0, -2.81), 1.12, 1);
	w[2] = new Wheel(Point(4.61, 0.0, 2.81), 1.12, 1);
	w[3] = new Wheel(Point(4.61, 0.0, -2.81), 1.12, 1);

	SF3dVector axes = SF3dVector(w[0]->GetCenter(), w[2]->GetCenter());
	wheelBase = axes.GetMagnitude();

	Texture tex = Texture::GetInstance();
	side = tex.carSide;
	front = tex.carFront;
	back = tex.carBack;
}

double Car::GetSpeed()
{
	if(speed < 0)
		return -speed;
	return speed;
}

void Car::Accelerate()
{
	fTraction = viewDir * ENGINFORCE;
}
void Car::Break()
{
	fTraction = viewDir * -BREAKING;
}
void Car::Reverse()
{
	if(speed>0)
	{
		Break();
		return;
	}
	fTraction = viewDir * -REVERSE;
}

void Car::turn(double steerAngle)
{
	w[0]->IncrementAngle(steerAngle);
	w[1]->IncrementAngle(steerAngle);

	SF3dVector carLocation = SF3dVector(center.x, center.y, center.z);

	SF3dVector frontWheel = carLocation + viewDir * (wheelBase / 2);
	SF3dVector backWheel = carLocation + viewDir * (-wheelBase / 2);

	backWheel = backWheel + viewDir * speed;
	double steeringAngle=angle + steerAngle * PIdiv180 + PI/2;
	frontWheel = frontWheel + SF3dVector(cos(steeringAngle), 0, -sin(steeringAngle)) * speed;
	
	carLocation = (frontWheel + backWheel) / 2;
	angle = atan2( frontWheel.z - backWheel.z , -frontWheel.x + backWheel.x ) + PI/2;
	
	center.x = carLocation.x;
	center.z = carLocation.z;

	computeViewDir();

	//compute velocity vector
	velocity.x = speed *  cos(angle+PI/2);
	velocity.z = speed * -sin(angle+PI/2);
}
void Car::TurnLeft()
{
	turn(STEER_ANGLE);
}

void Car::TurnRight()
{
	turn(-STEER_ANGLE);
}

void Car::Update()
{
	SF3dVector fAirDrag = velocity * -AIR_DRAG * speed;
	SF3dVector fRollDrag = velocity * -ROLLING_DRAG;
	SF3dVector fTotal = fTraction+fAirDrag+fRollDrag;
	SF3dVector a = fTotal/MASS;
	velocity = velocity + a;
	speed = velocity.GetMagnitude() * Tools::Sign(viewDir*velocity);
	if(speed>0.01 || speed<-0.01)
	{
		MoveWith(velocity);
		for(int i=0; i<4; i++)
		{
			w[i]->IncrementRotationAngle( speed * 6 / 0.1 );
		}
	}
	fTraction=SF3dVector();
}

void Car::Draw()
{
	glPushMatrix();
	glTranslated(center.x, center.y, center.z);
	glRotated(angle * 180 / PI, 0.0, 1.0, 0.0);
	glScaled( CAR_SCALE, CAR_SCALE, CAR_SCALE);

	for (int i = 0; i < 4; i++)
		w[i]->Draw();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, side);
	glTranslatef(3.3, 0.0, 0.0);
	//right side
	//bottom panel
	//behind the back wheel
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.072, 0.185); glVertex3f(0.0, 0.9, 5.84);
		glTexCoord2f(0.034, 0.209); glVertex3f(0.0, 1.01, 6.36);
		glTexCoord2f(0.030, 0.290); glVertex3f(0.0, 1.41, 6.42);
		glTexCoord2f(0.026, 0.431); glVertex3f(0.0, 2.09, 6.47);
		glTexCoord2f(0.045, 0.482); glVertex3f(0.0, 2.36, 6.21);
		glTexCoord2f(0.072, 0.486); glVertex3f(0.0, 2.36, 5.84);//middle rear bumper
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.026, 0.431); glVertex3f(0.0, 2.09, 6.47);
		glTexCoord2f(0.030, 0.290); glVertex3f(0.0, 1.41, 6.42);
		glTexCoord2f(0.034, 0.209); glVertex3f(0.0, 1.01, 6.36);//under lip
		glTexCoord2f(0.008, 0.272); glVertex3f(-0.4, 1.32, 6.71);
		glTexCoord2f(0.005, 0.309); glVertex3f(-0.4, 1.50, 6.77);//bumper
		glTexCoord2f(0.004, 0.430); glVertex3f(-0.4, 2.09, 6.79);//bumper
		glTexCoord2f(0.023, 0.486); glVertex3f(-0.4, 2.36, 6.51);//bumper
		glTexCoord2f(0.045, 0.482); glVertex3f(0.0, 2.36, 6.21);
	}
	glEnd();

	//rear fender
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.073, 0.486); glVertex3f(0.0, 2.36, 5.84);//middle rear bumper
		glTexCoord2f(0.165, 0.486); glVertex3f(0.0, 2.36, 4.58);//middle rear bumper
		glTexCoord2f(0.165, 0.481); glVertex3f(-0.001, 2.33, 4.58);//upper fender
		glTexCoord2f(0.163, 0.228); glVertex3f(-0.01, 1.11, 4.60);//middle wheel
		glTexCoord2f(0.072, 0.185); glVertex3f(0.0, 0.9, 5.84);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.257, 0.486); glVertex3f(0.0, 2.36, 3.32);//middle door
		glTexCoord2f(0.165, 0.486); glVertex3f(0.0, 2.36, 4.58);//middle rear bumper
		glTexCoord2f(0.166, 0.481); glVertex3f(-0.001, 2.33, 4.58);//upper fender
		glTexCoord2f(0.163, 0.228); glVertex3f(-0.01, 1.11, 4.60);//middle wheel
		glTexCoord2f(0.257, 0.170); glVertex3f(0.0, 0.83, 3.32);
	}
	glEnd();

	//between the wheels
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.257, 0.170); glVertex3f(0.0, 0.83, 3.32);
		glTexCoord2f(0.257, 0.486); glVertex3f(0.0, 2.36, 3.32);
		glTexCoord2f(0.725, 0.486); glVertex3f(0.0, 2.36, -3.07);
		glTexCoord2f(0.725, 0.150); glVertex3f(0.0, 0.73, -3.07);
	}
	glEnd();

	//front fender
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.725, 0.486); glVertex3f(0.0, 2.36, -3.07);
		glTexCoord2f(0.820, 0.486); glVertex3f(0.0, 2.36, -4.37);//middle front fender
		glTexCoord2f(0.820, 0.482); glVertex3f(-0.01, 2.34, -4.37);//middle front fender
		glTexCoord2f(0.820, 0.231); glVertex3f(-0.1, 1.12, -4.37);
		glTexCoord2f(0.725, 0.150); glVertex3f(0.0, 0.73, -3.07);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.907, 0.331); glVertex3f(0.0, 1.61, -5.55);//middle front fender
		glTexCoord2f(0.866, 0.486); glVertex3f(0.0, 2.36, -4.99);//upper right front fender
		glTexCoord2f(0.820, 0.486); glVertex3f(0.0, 2.36, -4.37);//middle upper front fender
		glTexCoord2f(0.820, 0.482); glVertex3f(-0.01, 2.34, -4.37);//middle upper front fender
		glTexCoord2f(0.820, 0.231); glVertex3f(-0.1, 1.12, -4.37);
		glTexCoord2f(0.907, 0.144); glVertex3f(0.0, 0.70, -5.55);
	}
	glEnd();

	//in front of the front wheel
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.907, 0.331); glVertex3f(0.0, 1.61, -5.55);//middle front fender
		glTexCoord2f(0.866, 0.486); glVertex3f(0.0, 2.36, -4.99);//upper right front fender
		glTexCoord2f(0.907, 0.486); glVertex3f(-0.20, 2.36, -5.55);//middle left headlight
		glTexCoord2f(0.947, 0.405); glVertex3f(-0.40, 1.97, -6.10);//under headlight
		glTexCoord2f(0.952, 0.331); glVertex3f(-0.40, 1.61, -6.17);//front projector
		glTexCoord2f(0.952, 0.169); glVertex3f(-0.35, 0.82, -6.17);//under lip
		glTexCoord2f(0.907, 0.144); glVertex3f(0.0, 0.70, -5.55);//lower front fender
	}
	glEnd();
	//corner
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.952, 0.331); glVertex3f(-0.40, 1.61, -6.17);//front projector
		glTexCoord2f(0.947, 0.405); glVertex3f(-0.40, 1.97, -6.10);//under headlight
		glTexCoord2f(0.995, 0.396); glVertex3f(-1.20, 1.92, -6.76);//front bumper
		glTexCoord2f(0.997, 0.321); glVertex3f(-1.20, 1.56, -6.79);
		glTexCoord2f(0.993, 0.315); glVertex3f(-1.00, 1.53, -6.73);//projector area
		glTexCoord2f(0.986, 0.227); glVertex3f(-1.00, 1.10, -6.64);//projector area
		glTexCoord2f(0.997, 0.197); glVertex3f(-1.00, 0.97, -6.78);
		glTexCoord2f(0.952, 0.169); glVertex3f(-0.35, 0.82, -6.17);//under lip
	}
	glEnd();
	//headlight
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.947, 0.405); glVertex3f(-0.40, 1.97, -6.10);//under headlight
		glTexCoord2f(0.907, 0.486); glVertex3f(-0.20, 2.36, -5.55);//middle left headlight
		glTexCoord2f(0.910, 0.543); glVertex3f(-0.30, 2.63, -5.60);//upper left headlight
		glTexCoord2f(0.943, 0.530); glVertex3f(-0.70, 2.57, -6.05);//upper middle headlight
		glTexCoord2f(0.974, 0.486); glVertex3f(-1.00, 2.36, -6.47);//upper front headlight
		glTexCoord2f(0.982, 0.440); glVertex3f(-1.10, 2.13, -6.58);//lower front headlight
		glTexCoord2f(0.995, 0.396); glVertex3f(-1.20, 1.92, -6.76);//front bumper		
	}
	glEnd();

	//middle panel
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.866, 0.486); glVertex3f(0.0, 2.36, -4.99);//upper right front fender
		glTexCoord2f(0.725, 0.486); glVertex3f(0.0, 2.36, -3.07);//upper left front fender
		glTexCoord2f(0.045, 0.486); glVertex3f(0.0, 2.36, 6.21);
		glTexCoord2f(0.046, 0.563); glVertex3f(-0.18, 2.73, 6.19);
		glTexCoord2f(0.044, 0.669); glVertex3f(-0.36, 3.25, 6.23);
		glTexCoord2f(0.043, 0.709); glVertex3f(-0.43, 3.44, 6.24);//trunk door
		glTexCoord2f(0.722, 0.617); glVertex3f(-0.20, 2.99, -3.03);//front shoulder
		glTexCoord2f(0.783, 0.600); glVertex3f(-0.20, 2.91, -3.86);
		glTexCoord2f(0.861, 0.571); glVertex3f(-0.20, 2.77, -4.93);
		glTexCoord2f(0.910, 0.543); glVertex3f(-0.30, 2.63, -5.60);//upper left headlight
		glTexCoord2f(0.907, 0.486); glVertex3f(-0.20, 2.36, -5.55);//middle left headlight
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.046, 0.563); glVertex3f(-0.18, 2.73, 6.19);
		glTexCoord2f(0.045, 0.486); glVertex3f(0.0, 2.36, 6.21);
		glTexCoord2f(0.023, 0.486); glVertex3f(-0.4, 2.36, 6.51);//bumper
		glTexCoord2f(0.023, 0.578); glVertex3f(-0.4, 2.81, 6.51);//tail light
		glTexCoord2f(0.029, 0.657); glVertex3f(-0.45, 3.19, 6.44);
		glTexCoord2f(0.043, 0.709); glVertex3f(-0.43, 3.44, 6.24);//trunk door
		glTexCoord2f(0.044, 0.669); glVertex3f(-0.36, 3.25, 6.23);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.722, 0.617); glVertex3f(-0.20, 2.99, -3.03);//front shoulder
		glTexCoord2f(0.043, 0.709); glVertex3f(-0.43, 3.44, 6.24);//trunk door
		glTexCoord2f(0.715, 0.709); glVertex3f(-0.43, 3.44, -2.93);//lower windshield
		glTexCoord2f(0.728, 0.688); glVertex3f(-0.43, 3.34, -3.11);//bonet
		glTexCoord2f(0.783, 0.600); glVertex3f(-0.20, 2.91, -3.86);
	}
	glEnd();

	glBegin(GL_POLYGON);//upper bonnet 
	{
		glTexCoord2f(0.861, 0.571); glVertex3f(-0.20, 2.77, -4.93);
		glTexCoord2f(0.783, 0.600); glVertex3f(-0.20, 2.91, -3.86);
		glTexCoord2f(0.728, 0.688); glVertex3f(-0.43, 3.34, -3.11);//bonet
		glTexCoord2f(0.798, 0.670); glVertex3f(-0.50, 3.25, -4.07);
		glTexCoord2f(0.871, 0.633); glVertex3f(-0.55, 3.07, -5.06);
		glTexCoord2f(0.930, 0.582); glVertex3f(-0.75, 2.83, -5.87);
		glTexCoord2f(0.910, 0.543); glVertex3f(-0.30, 2.63, -5.60);//upper left headlight
	}
	glEnd();

	glBegin(GL_POLYGON);//upper front bonnet
	{
		glTexCoord2f(0.930, 0.582); glVertex3f(-0.75, 2.83, -5.87);
		glTexCoord2f(0.957, 0.541); glVertex3f(-0.90, 2.63, -6.23);
		glTexCoord2f(0.974, 0.486); glVertex3f(-1.00, 2.36, -6.47);//upper front headlight
		glTexCoord2f(0.943, 0.530); glVertex3f(-0.70, 2.57, -6.05);//upper middle headlight
		glTexCoord2f(0.910, 0.543); glVertex3f(-0.30, 2.63, -5.60);//upper left headlight
	}
	glEnd();

	//top panel
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.043, 0.709); glVertex3f(-0.43, 3.44, 6.24);//trunk door
		glTexCoord2f(0.075, 0.817); glVertex3f(-0.60, 3.97, 5.80);
		glTexCoord2f(0.109, 0.909); glVertex3f(-0.70, 4.41, 5.34);
		glTexCoord2f(0.134, 0.946); glVertex3f(-0.72, 4.59, 5.00);//tail
		glTexCoord2f(0.195, 0.967); glVertex3f(-0.72, 4.69, 4.16);//antena
		glTexCoord2f(0.281, 0.981); glVertex3f(-0.72, 4.76, 2.99);
		glTexCoord2f(0.366, 0.985); glVertex3f(-0.72, 4.78, 1.83);
		glTexCoord2f(0.450, 0.979); glVertex3f(-0.72, 4.75, 0.68);
		glTexCoord2f(0.506, 0.963); glVertex3f(-0.72, 4.67, -0.09);
		glTexCoord2f(0.561, 0.929); glVertex3f(-0.72, 4.51, -0.83);//windscreen
		glTexCoord2f(0.633, 0.838); glVertex3f(-0.60, 4.07, -1.81);
		glTexCoord2f(0.715, 0.709); glVertex3f(-0.43, 3.44, -2.93);
	}
	glEnd();
	//tail
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.109, 0.909); glVertex3f(-0.70, 4.41, 5.34);
		glTexCoord2f(0.103, 0.933); glVertex3f(-0.73, 4.53, 5.43);
		glTexCoord2f(0.134, 0.946); glVertex3f(-0.72, 4.59, 5.00);
	}
	glEnd();
	glTranslatef(-6.6, 0, 0);
	//left side
	//bottom panel
	//behind the back wheel
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.072, 0.185); glVertex3f(0.0, 0.9, 5.84);
		glTexCoord2f(0.034, 0.209); glVertex3f(0.0, 1.01, 6.36);
		glTexCoord2f(0.030, 0.290); glVertex3f(0.0, 1.41, 6.42);
		glTexCoord2f(0.026, 0.431); glVertex3f(0.0, 2.09, 6.47);
		glTexCoord2f(0.045, 0.482); glVertex3f(0.0, 2.36, 6.21);
		glTexCoord2f(0.072, 0.486); glVertex3f(0.0, 2.36, 5.84);//middle rear bumper
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.026, 0.431); glVertex3f(0.0, 2.09, 6.47);
		glTexCoord2f(0.030, 0.290); glVertex3f(0.0, 1.41, 6.42);
		glTexCoord2f(0.034, 0.209); glVertex3f(0.0, 1.01, 6.36);//under lip
		glTexCoord2f(0.008, 0.272); glVertex3f(0.4, 1.32, 6.71);
		glTexCoord2f(0.005, 0.309); glVertex3f(0.4, 1.50, 6.77);//bumper
		glTexCoord2f(0.004, 0.430); glVertex3f(0.4, 2.09, 6.79);//bumper
		glTexCoord2f(0.023, 0.486); glVertex3f(0.4, 2.36, 6.51);//bumper
		glTexCoord2f(0.045, 0.482); glVertex3f(0.0, 2.36, 6.21);
	}
	glEnd();

	//rear fender
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.073, 0.486); glVertex3f(0.0, 2.36, 5.84);//middle rear bumper
		glTexCoord2f(0.165, 0.486); glVertex3f(0.0, 2.36, 4.58);//middle rear bumper
		glTexCoord2f(0.165, 0.481); glVertex3f(0.001, 2.33, 4.58);//upper fender
		glTexCoord2f(0.163, 0.228); glVertex3f(0.01, 1.11, 4.60);//middle wheel
		glTexCoord2f(0.072, 0.185); glVertex3f(0.0, 0.9, 5.84);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.257, 0.486); glVertex3f(0.0, 2.36, 3.32);//middle door
		glTexCoord2f(0.165, 0.486); glVertex3f(0.0, 2.36, 4.58);//middle rear bumper
		glTexCoord2f(0.166, 0.481); glVertex3f(0.001, 2.33, 4.58);//upper fender
		glTexCoord2f(0.163, 0.228); glVertex3f(0.01, 1.11, 4.60);//middle wheel
		glTexCoord2f(0.257, 0.170); glVertex3f(0.0, 0.83, 3.32);
	}
	glEnd();

	//between the wheels
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.257, 0.170); glVertex3f(0.0, 0.83, 3.32);
		glTexCoord2f(0.257, 0.486); glVertex3f(0.0, 2.36, 3.32);
		glTexCoord2f(0.725, 0.486); glVertex3f(0.0, 2.36, -3.07);
		glTexCoord2f(0.725, 0.150); glVertex3f(0.0, 0.73, -3.07);
	}
	glEnd();

	//front fender
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.725, 0.486); glVertex3f(0.0, 2.36, -3.07);
		glTexCoord2f(0.820, 0.486); glVertex3f(0.0, 2.36, -4.37);//middle front fender
		glTexCoord2f(0.820, 0.482); glVertex3f(0.01, 2.34, -4.37);//middle front fender
		glTexCoord2f(0.820, 0.231); glVertex3f(0.1, 1.12, -4.37);
		glTexCoord2f(0.725, 0.150); glVertex3f(0.0, 0.73, -3.07);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.907, 0.331); glVertex3f(0.0, 1.61, -5.55);//middle front fender
		glTexCoord2f(0.866, 0.486); glVertex3f(0.0, 2.36, -4.99);//upper right front fender
		glTexCoord2f(0.820, 0.486); glVertex3f(0.0, 2.36, -4.37);//middle upper front fender
		glTexCoord2f(0.820, 0.482); glVertex3f(0.01, 2.34, -4.37);//middle upper front fender
		glTexCoord2f(0.820, 0.231); glVertex3f(0.1, 1.12, -4.37);
		glTexCoord2f(0.907, 0.144); glVertex3f(0.0, 0.70, -5.55);
	}
	glEnd();

	//in front of the front wheel
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.907, 0.331); glVertex3f(0.0, 1.61, -5.55);//middle front fender
		glTexCoord2f(0.866, 0.486); glVertex3f(0.0, 2.36, -4.99);//upper right front fender
		glTexCoord2f(0.907, 0.486); glVertex3f(0.20, 2.36, -5.55);//middle left headlight
		glTexCoord2f(0.947, 0.405); glVertex3f(0.40, 1.97, -6.10);//under headlight
		glTexCoord2f(0.952, 0.331); glVertex3f(0.40, 1.61, -6.17);//front projector
		glTexCoord2f(0.952, 0.169); glVertex3f(0.35, 0.82, -6.17);//under lip
		glTexCoord2f(0.907, 0.144); glVertex3f(0, 0.70, -5.55);//lower front fender
	}
	glEnd();
	//corner
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.952, 0.331); glVertex3f(0.40, 1.61, -6.17);//front projector
		glTexCoord2f(0.947, 0.405); glVertex3f(0.40, 1.97, -6.10);//under headlight
		glTexCoord2f(0.995, 0.396); glVertex3f(1.20, 1.92, -6.76);//front bumper
		glTexCoord2f(0.997, 0.321); glVertex3f(1.20, 1.56, -6.79);
		glTexCoord2f(0.993, 0.315); glVertex3f(1.00, 1.53, -6.73);//projector area
		glTexCoord2f(0.986, 0.227); glVertex3f(1.00, 1.10, -6.64);//projector area
		glTexCoord2f(0.997, 0.197); glVertex3f(1.00, 0.97, -6.78);
		glTexCoord2f(0.952, 0.169); glVertex3f(0.35, 0.82, -6.17);//under lip
	}
	glEnd();
	//headlight
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.947, 0.405); glVertex3f(0.40, 1.97, -6.10);//under headlight
		glTexCoord2f(0.907, 0.486); glVertex3f(0.20, 2.36, -5.55);//middle left headlight
		glTexCoord2f(0.910, 0.543); glVertex3f(0.30, 2.63, -5.60);//upper left headlight
		glTexCoord2f(0.943, 0.530); glVertex3f(0.70, 2.57, -6.05);//upper middle headlight
		glTexCoord2f(0.974, 0.486); glVertex3f(1.00, 2.36, -6.47);//upper front headlight
		glTexCoord2f(0.982, 0.440); glVertex3f(1.10, 2.13, -6.58);//lower front headlight
		glTexCoord2f(0.995, 0.396); glVertex3f(1.20, 1.92, -6.76);//front bumper		
	}
	glEnd();

	//middle panel
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.866, 0.486); glVertex3f(0.0, 2.36, -4.99);//upper right front fender
		glTexCoord2f(0.725, 0.486); glVertex3f(0.0, 2.36, -3.07);//upper left front fender
		glTexCoord2f(0.045, 0.486); glVertex3f(0.0, 2.36, 6.21);
		glTexCoord2f(0.046, 0.563); glVertex3f(0.18, 2.73, 6.19);
		glTexCoord2f(0.044, 0.669); glVertex3f(0.36, 3.25, 6.23);
		glTexCoord2f(0.043, 0.709); glVertex3f(0.43, 3.44, 6.24);//trunk door
		glTexCoord2f(0.722, 0.617); glVertex3f(0.20, 2.99, -3.03);//front shoulder
		glTexCoord2f(0.783, 0.600); glVertex3f(0.20, 2.91, -3.86);
		glTexCoord2f(0.861, 0.571); glVertex3f(0.20, 2.77, -4.93);
		glTexCoord2f(0.910, 0.543); glVertex3f(0.30, 2.63, -5.60);//upper left headlight
		glTexCoord2f(0.907, 0.486); glVertex3f(0.20, 2.36, -5.55);//middle left headlight
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.046, 0.563); glVertex3f(0.18, 2.73, 6.19);
		glTexCoord2f(0.045, 0.486); glVertex3f(0.0, 2.36, 6.21);
		glTexCoord2f(0.023, 0.486); glVertex3f(0.4, 2.36, 6.51);//bumper
		glTexCoord2f(0.023, 0.578); glVertex3f(0.4, 2.81, 6.51);//tail light
		glTexCoord2f(0.029, 0.657); glVertex3f(0.45, 3.19, 6.44);
		glTexCoord2f(0.043, 0.709); glVertex3f(0.43, 3.44, 6.24);//trunk door
		glTexCoord2f(0.044, 0.669); glVertex3f(0.36, 3.25, 6.23);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.722, 0.617); glVertex3f(0.20, 2.99, -3.03);//front shoulder
		glTexCoord2f(0.043, 0.709); glVertex3f(0.43, 3.44, 6.24);//trunk door
		glTexCoord2f(0.715, 0.709); glVertex3f(0.43, 3.44, -2.93);//lower windshield
		glTexCoord2f(0.728, 0.688); glVertex3f(0.43, 3.34, -3.11);//bonet
		glTexCoord2f(0.783, 0.600); glVertex3f(0.20, 2.91, -3.86);
	}
	glEnd();

	glBegin(GL_POLYGON);//upper bonnet 
	{
		glTexCoord2f(0.861, 0.571); glVertex3f(0.20, 2.77, -4.93);
		glTexCoord2f(0.783, 0.600); glVertex3f(0.20, 2.91, -3.86);
		glTexCoord2f(0.728, 0.688); glVertex3f(0.43, 3.34, -3.11);//bonet
		glTexCoord2f(0.798, 0.670); glVertex3f(0.50, 3.25, -4.07);
		glTexCoord2f(0.871, 0.633); glVertex3f(0.55, 3.07, -5.06);
		glTexCoord2f(0.930, 0.582); glVertex3f(0.75, 2.83, -5.87);
		glTexCoord2f(0.910, 0.543); glVertex3f(0.30, 2.63, -5.60);//upper left headlight
	}
	glEnd();

	glBegin(GL_POLYGON);//upper front bonnet
	{
		glTexCoord2f(0.930, 0.582); glVertex3f(0.75, 2.83, -5.87);
		glTexCoord2f(0.957, 0.541); glVertex3f(0.90, 2.63, -6.23);
		glTexCoord2f(0.974, 0.486); glVertex3f(1.00, 2.36, -6.47);//upper front headlight
		glTexCoord2f(0.943, 0.530); glVertex3f(0.70, 2.57, -6.05);//upper middle headlight
		glTexCoord2f(0.910, 0.543); glVertex3f(0.30, 2.63, -5.60);//upper left headlight
	}
	glEnd();

	//top panel
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.043, 0.709); glVertex3f(0.43, 3.44, 6.24);//trunk door
		glTexCoord2f(0.075, 0.817); glVertex3f(0.60, 3.97, 5.80);
		glTexCoord2f(0.109, 0.909); glVertex3f(0.70, 4.41, 5.34);
		glTexCoord2f(0.134, 0.946); glVertex3f(0.72, 4.59, 5.00);//tail
		glTexCoord2f(0.195, 0.967); glVertex3f(0.72, 4.69, 4.16);//antena
		glTexCoord2f(0.281, 0.981); glVertex3f(0.72, 4.76, 2.99);
		glTexCoord2f(0.366, 0.985); glVertex3f(0.72, 4.78, 1.83);
		glTexCoord2f(0.450, 0.979); glVertex3f(0.72, 4.75, 0.68);
		glTexCoord2f(0.506, 0.963); glVertex3f(0.72, 4.67, -0.09);
		glTexCoord2f(0.561, 0.929); glVertex3f(0.72, 4.51, -0.83);//windscreen
		glTexCoord2f(0.633, 0.838); glVertex3f(0.60, 4.07, -1.81);
		glTexCoord2f(0.715, 0.709); glVertex3f(0.43, 3.44, -2.93);
	}
	glEnd();
	//tail
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0.109, 0.909); glVertex3f(0.70, 4.41, 5.34);
		glTexCoord2f(0.103, 0.933); glVertex3f(0.73, 4.53, 5.43);
		glTexCoord2f(0.134, 0.946); glVertex3f(0.72, 4.59, 5.00);
	}
	glEnd();


	glBindTexture(GL_TEXTURE_2D, back);

	//middle part
	glBegin(GL_QUADS);
	{
		glVertex3f(0.0, 0.90, 5.84);
		glVertex3f(0.0, 1.01, 6.36);
		glVertex3f(6.6, 1.01, 6.36);
		glVertex3f(6.6, 0.90, 5.84);

		glTexCoord2f(0.090, 0.177); glVertex3f(0.0, 1.01, 6.36);
		glTexCoord2f(0.216, 0.255); glVertex3f(0.4, 1.32, 6.71);
		glTexCoord2f(0.787, 0.255); glVertex3f(6.2, 1.32, 6.71);
		glTexCoord2f(0.915, 0.176); glVertex3f(6.6, 1.01, 6.36);

		glTexCoord2f(0.216, 0.255); glVertex3f(0.4, 1.32, 6.71);
		glTexCoord2f(0.216, 0.287); glVertex3f(0.4, 1.50, 6.77);//bumper
		glTexCoord2f(0.787, 0.286); glVertex3f(6.2, 1.50, 6.77);//bumper
		glTexCoord2f(0.787, 0.255); glVertex3f(6.2, 1.32, 6.71);

		glTexCoord2f(0.176, 0.286); glVertex3f(0.4, 1.50, 6.77);//bumper
		glTexCoord2f(0.176, 0.426); glVertex3f(0.4, 2.09, 6.79);//bumper
		glTexCoord2f(0.838, 0.426); glVertex3f(6.2, 2.09, 6.79);//bumper
		glTexCoord2f(0.838, 0.286); glVertex3f(6.2, 1.50, 6.77);//bumper

		glTexCoord2f(0.176, 0.426); glVertex3f(0.4, 2.09, 6.79);//bumper
		glTexCoord2f(0.176, 0.503); glVertex3f(0.4, 2.36, 6.51);//bumper
		glTexCoord2f(0.838, 0.503); glVertex3f(6.2, 2.36, 6.51);//bumper
		glTexCoord2f(0.838, 0.426); glVertex3f(6.2, 2.09, 6.79);//bumper

		glTexCoord2f(0.176, 0.503); glVertex3f(0.4, 2.36, 6.51);//bumper
		glTexCoord2f(0.176, 0.581); glVertex3f(0.4, 2.81, 6.51);//tail light
		glTexCoord2f(0.838, 0.581); glVertex3f(6.2, 2.81, 6.51);//tail light
		glTexCoord2f(0.838, 0.503); glVertex3f(6.2, 2.36, 6.51);//bumper

		glTexCoord2f(0.176, 0.581); glVertex3f(0.4, 2.81, 6.51);//tail light
		glTexCoord2f(0.176, 0.692); glVertex3f(0.45, 3.19, 6.44);
		glTexCoord2f(0.838, 0.688); glVertex3f(6.15, 3.19, 6.44);
		glTexCoord2f(0.838, 0.581); glVertex3f(6.2, 2.81, 6.51);//tail light

		glTexCoord2f(0.100, 0.692); glVertex3f(0.45, 3.19, 6.44);
		glTexCoord2f(0.118, 0.729); glVertex3f(0.43, 3.44, 6.24);//trunk door
		glTexCoord2f(0.890, 0.724); glVertex3f(6.17, 3.44, 6.24);//trunk door
		glTexCoord2f(0.905, 0.690); glVertex3f(6.15, 3.19, 6.44);


		glTexCoord2f(0.118, 0.729); glVertex3f(0.43, 3.44, 6.24);//trunk door
		glTexCoord2f(0.187, 0.930); glVertex3f(0.70, 4.41, 5.34);
		glTexCoord2f(0.809, 0.930); glVertex3f(5.90, 4.41, 5.34);
		glTexCoord2f(0.890, 0.724); glVertex3f(6.17, 3.44, 6.24);//trunk door

		//	glVertex3f(0.60, 3.97, 5.80);
		//	glVertex3f(0.70, 4.41, 5.34);
		//	glVertex3f(5.90, 4.41, 5.34);
		//	glVertex3f(6.00, 3.97, 5.80);

		glTexCoord2f(0.187, 0.930); glVertex3f(0.70, 4.41, 5.34);
		glTexCoord2f(0.222, 0.969); glVertex3f(0.73, 4.53, 5.43);
		glTexCoord2f(0.775, 0.970); glVertex3f(5.87, 4.53, 5.43);
		glTexCoord2f(0.809, 0.930); glVertex3f(5.90, 4.41, 5.34);
	}
	glEnd();
		

	glBindTexture(GL_TEXTURE_2D, front);
	glBegin(GL_QUADS);
	{
		//glTexCoord2f(0.561, 0.929); glVertex3f(0.72, 4.51, -0.83);//windscreen
		//	glVertex3f(0.60, 4.07, -1.81);
		//	glVertex3f(6.0, 4.07, -1.81);
		//	glVertex3f(5.88, 4.51, -0.83);//windscreen

		glTexCoord2f(0.763, 0.944); glVertex3f(0.72, 4.51, -0.83);//windscreen
		glTexCoord2f(0.848, 0.738); glVertex3f(0.43, 3.34, -3.11);//bonet
		glTexCoord2f(0.142, 0.738); glVertex3f(6.17, 3.34, -3.11);//bonet
		glTexCoord2f(0.228, 0.944); glVertex3f(5.88, 4.51, -0.83);//windscreen

		glTexCoord2f(0.878, 0.728); glVertex3f(0.43, 3.34, -3.11);//bonet
		glTexCoord2f(0.853, 0.673); glVertex3f(0.5, 3.25, -4.07);
		glTexCoord2f(0.137, 0.673); glVertex3f(6.1, 3.25, -4.07);
		glTexCoord2f(0.112, 0.728); glVertex3f(6.17, 3.34, -3.11);//bonet


		glTexCoord2f(0.853, 0.673); glVertex3f(0.5, 3.25, -4.07);
		glTexCoord2f(0.839, 0.633); glVertex3f(0.55, 3.07, -5.06);
		glTexCoord2f(0.150, 0.648); glVertex3f(6.05, 3.07, -5.06);
		glTexCoord2f(0.137, 0.673); glVertex3f(6.1, 3.25, -4.07);

		glTexCoord2f(0.839, 0.633); glVertex3f(0.55, 3.07, -5.06);
		glTexCoord2f(0.825, 0.622); glVertex3f(0.75, 2.83, -5.87);
		glTexCoord2f(0.164, 0.622); glVertex3f(5.85, 2.83, -5.87);
		glTexCoord2f(0.150, 0.648); glVertex3f(6.05, 3.07, -5.06);

		glTexCoord2f(0.825, 0.622); glVertex3f(0.75, 2.83, -5.87);
		glTexCoord2f(0.810, 0.587); glVertex3f(0.9, 2.63, -6.23);
		glTexCoord2f(0.183, 0.587); glVertex3f(5.7, 2.63, -6.23);
		glTexCoord2f(0.164, 0.622); glVertex3f(5.85, 2.83, -5.87);
		//front bonnet
		glTexCoord2f(0.810, 0.587); glVertex3f(0.9, 2.63, -6.23);
		glTexCoord2f(0.771, 0.507); glVertex3f(1.0, 2.36, -6.47);//upper front headlight
		glTexCoord2f(0.219, 0.507); glVertex3f(5.6, 2.36, -6.47);//upper front headlight
		glTexCoord2f(0.183, 0.587); glVertex3f(5.7, 2.63, -6.23);
		//problem
		glTexCoord2f(0.771, 0.507); glVertex3f(0.9, 2.36, -6.47);//upper front headlight
		glTexCoord2f(0.747, 0.427); glVertex3f(1.1, 2.13, -6.58);
		glTexCoord2f(0.246, 0.426);	glVertex3f(5.5, 2.13, -6.58);
		glTexCoord2f(0.219, 0.507); glVertex3f(5.7, 2.36, -6.47);//upper front headlight

		glTexCoord2f(0.747, 0.427); glVertex3f(1.10, 2.13, -6.58);
		glTexCoord2f(0.747, 0.378); glVertex3f(1.20, 1.92, -6.76);//front bumper
		glTexCoord2f(0.246, 0.375); glVertex3f(5.4, 1.92, -6.76);//front bumper
		glTexCoord2f(0.246, 0.426);	glVertex3f(5.5, 2.13, -6.58);

		glTexCoord2f(0.747, 0.378); glVertex3f(1.20, 1.92, -6.76);//front bumper
		glTexCoord2f(0.747, 0.282); glVertex3f(1.20, 1.56, -6.79);
		glTexCoord2f(0.246, 0.279); glVertex3f(5.4, 1.56, -6.79);
		glTexCoord2f(0.246, 0.375); glVertex3f(5.4, 1.92, -6.76);//front bumper

		glTexCoord2f(0.747, 0.282); glVertex3f(1.20, 1.56, -6.79);
		glTexCoord2f(0.818, 0.265);	glVertex3f(1.0, 1.53, -6.73);//projector area
		glTexCoord2f(0.175, 0.265);	glVertex3f(5.6, 1.53, -6.73);//projector area
		glTexCoord2f(0.246, 0.279); glVertex3f(5.4, 1.56, -6.79);

		glTexCoord2f(0.830, 0.273); glVertex3f(1.0, 1.53, -6.73);//projector area
		glTexCoord2f(0.830, 0.169); glVertex3f(1.0, 1.10, -6.64);//projector area
		glTexCoord2f(0.164, 0.169); glVertex3f(5.6, 1.10, -6.64);//projector area
		glTexCoord2f(0.164, 0.273);	glVertex3f(5.6, 1.53, -6.73);//projector area

		glTexCoord2f(0.83, 0.169); glVertex3f(1.0, 1.10, -6.64);//projector area
		glTexCoord2f(0.83, 0.132); glVertex3f(1.0, 0.97, -6.78);
		glTexCoord2f(0.164, 0.132); glVertex3f(5.6, 0.97, -6.78);
		glTexCoord2f(0.164, 0.169); glVertex3f(5.6, 1.10, -6.64);//projector area

		glTexCoord2f(0.83, 0.132); glVertex3f(1.0, 0.97, -6.78);
		glTexCoord2f(0.95, 0.118); glVertex3f(0.35, 0.82, -6.17);//under lip
		glTexCoord2f(0.042, 0.118); glVertex3f(6.25, 0.82, -6.17);//under lip
		glTexCoord2f(0.164, 0.132); glVertex3f(5.6, 0.97, -6.78);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//roof
	glBegin(GL_QUADS);
	{
		glColor3f(0.309f, 0.580f, 0.745f);

		glVertex3f(0.73, 4.53, 5.43);
		glVertex3f(0.72, 4.59, 5.00);
		glVertex3f(5.88, 4.59, 5.00);
		glVertex3f(5.87, 4.53, 5.43);

		glVertex3f(0.72, 4.59, 5.00);
		glVertex3f(0.72, 4.69, 4.16);
		glVertex3f(5.88, 4.69, 4.16);
		glVertex3f(5.88, 4.59, 5.00);

		glVertex3f(0.72, 4.69, 4.16);
		glVertex3f(0.72, 4.76, 2.99);
		glVertex3f(5.88, 4.76, 2.99);
		glVertex3f(5.88, 4.69, 4.16);

		glVertex3f(0.72, 4.76, 2.99);
		glVertex3f(0.72, 4.78, 1.83);
		glVertex3f(5.88, 4.78, 1.83);
		glVertex3f(5.88, 4.76, 2.99);

		glVertex3f(0.72, 4.78, 1.83);
		glVertex3f(0.72, 4.75, 0.68);
		glVertex3f(5.88, 4.75, 0.68);
		glVertex3f(5.88, 4.78, 1.83);

		glVertex3f(0.72, 4.75, 0.68);
		glVertex3f(0.72, 4.67, -0.09);
		glVertex3f(5.88, 4.67, -0.09);
		glVertex3f(5.88, 4.75, 0.68);

		glVertex3f(0.72, 4.67, -0.09);
		glVertex3f(0.72, 4.51, -0.83);//windscreen
		glVertex3f(5.88, 4.51, -0.83);//windscreen
		glVertex3f(5.88, 4.67, -0.09);
	}
	glEnd();

	glPopMatrix();
}
Car::~Car()
{
}
