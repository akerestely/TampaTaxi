#include "Car.h"

Car::Car(Point center) :Drawable(center)
{
	wheelRadius = 1.5;
	w = new Wheel*[4];
	w[0] = new Wheel(Point(-4, 0, 3), wheelRadius, 1);
	w[1] = new Wheel(Point(4, 0, 3), wheelRadius, 1);
	w[2] = new Wheel(Point(-4, 0, -3), wheelRadius, 1);
	w[3] = new Wheel(Point(4, 0, -3), wheelRadius, 1);
}

void Car::Draw()
{
	glPushMatrix();
	glTranslated(center.x, center.y-wheelRadius/2, center.z);
	glScaled(0.25,0.25,0.25);
	for (int i = 0; i < 4; i++)
		w[i]->Draw();
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(3.5, 0, 0);
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		//behind the back wheel
		glVertex3f(0, 1, 7); //a
		glVertex3f(0, 3, 7); //b
		glVertex3f(0, 3, 5.6);  //c
		glVertex3f(0, 0.8, 5.6);  //d

		//between the wheels
		glVertex3f(0, 0.8, 2.4); //a
		glVertex3f(0, 3, 2.4); //b
		glVertex3f(0, 3, -2.4);  //c
		glVertex3f(0, 0.8, -2.4);  //

		//in front of the front wheel
		glVertex3f(0, 0.8, -5.6); //a
		glVertex3f(0, 3, -5.6); //b
		glVertex3f(0, 3, -7.3);  //c
		glVertex3f(0, 1, -8);  //

		//1st part middle panel
		glVertex3f(0, 3, 7); //a
		glVertex3f(-0.4, 3.25, 6.8); //b
		glVertex3f(-0.4, 3.25, -6.8);  //c
		glVertex3f(0, 3, -7);  //

		//2nd part middle panel
		glVertex3f(-0.4, 3.25, 6.8); //a
		glVertex3f(-0.7, 3.65, 6.7); //b
		glVertex3f(-0.7, 3.65, -5.7);  //c
		glVertex3f(-0.4, 3.25, -6.8);  //

		//3rd part middle panel
		glVertex3f(-0.7, 3.65, 6.7); //a
		glVertex3f(-0.9, 4, 6.5); //b
		glVertex3f(-0.9, 4, -5.5);  //c
		glVertex3f(-0.7, 3.65, -5.7);  //

		//upper panel
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.9, 4, 6.5); //a
		glVertex3f(-1.2, 6, 1); //b
		glVertex3f(-1.2, 6, -2);  //c
		glVertex3f(-0.9, 4, -4);  //
	}
	glEnd();

	glTranslatef(-7, 0, 0);
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		//behind the back wheel
		glVertex3f(0, 1, 7); //a
		glVertex3f(0, 3, 7); //b
		glVertex3f(0, 3, 5.6);  //c
		glVertex3f(0, 0.8, 5.6);  //d

		//between the wheels		
		glVertex3f(0, 0.8, 2.4); //a
		glVertex3f(0, 3, 2.4); //b
		glVertex3f(0, 3, -2.4);  //c
		glVertex3f(0, 0.8, -2.4);  //

		//in front of the front wheel	
		glVertex3f(0, 0.8, -5.6); //a
		glVertex3f(0, 3, -5.6); //b
		glVertex3f(0, 3, -7.3);  //c
		glVertex3f(0, 1, -8);  //

		//1st part middle panel
		glVertex3f(0, 3, 7); //a
		glVertex3f(0.4, 3.25, 6.8); //b
		glVertex3f(0.4, 3.25, -6.8);  //c
		glVertex3f(0, 3, -7);  //

		//2nd part middle panel
		glVertex3f(0.4, 3.25, 6.8); //a
		glVertex3f(0.7, 3.65, 6.7); //b
		glVertex3f(0.7, 3.65, -5.7);  //c
		glVertex3f(0.4, 3.25, -6.8);  //

		//3rd part middle panel
		glVertex3f(0.7, 3.65, 6.7); //a
		glVertex3f(0.9, 4, 6.5); //b
		glVertex3f(0.9, 4, -5.5);  //c
		glVertex3f(0.7, 3.65, -5.7);  //

		//upper panel
		glVertex3f(0.9, 4, 6.5); //a
		glVertex3f(1.2, 6, 1); //b
		glVertex3f(1.2, 6, -2);  //c
		glVertex3f(0.9, 4, -4);  //
	}
	glEnd();

	//top
	glBegin(GL_QUADS);
	{
		glColor3f(0.0f, 0.0f, 1.0f);

		//lower back
		glVertex3f(7, 1, 7); //a
		glVertex3f(0, 1, 7); //a
		glVertex3f(0, 3, 7); //b
		glVertex3f(7, 3, 7); //b

		//1st part middle panel back
		glVertex3f(7, 3, 7); //a
		glVertex3f(0, 3, 7); //b
		glVertex3f(0.4, 3.25, 6.8);  //c
		glVertex3f(6.6, 3.25, 6.8);  //

		//2nd part middle panel back
		glVertex3f(6.6, 3.25, 6.8); //a
		glVertex3f(0.4, 3.25, 6.8); //b
		glVertex3f(0.7, 3.65, 6.7);  //c
		glVertex3f(6.3, 3.65, 6.7);  //

		//3rd part middle panel
		glVertex3f(6.3, 3.65, 6.7); //a
		glVertex3f(0.7, 3.65, 6.7); //b
		glVertex3f(0.9, 4, 6.5);  //c
		glVertex3f(6.1, 4, 6.5);  //

		//top back
		glVertex3f(6.1, 4, 6.5); //a
		glVertex3f(0.9, 4, 6.5); //b
		glVertex3f(1.2, 6, 1);  //c
		glVertex3f(5.8, 6, 1);  //

		//top
		glVertex3f(5.8, 6, 1); //a
		glVertex3f(1.2, 6, 1); //b
		glVertex3f(1.2, 6, -2);  //c
		glVertex3f(5.8, 6, -2);  //

		//windshield
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(5.8, 6, -2);  //c
		glVertex3f(1.2, 6, -2);  //c
		glVertex3f(0.9, 4, -4);  //
		glVertex3f(6.1, 4, -4);  //

		glColor3f(0.0f, 0.0f, 1.0f);
		//bonet
		glVertex3f(6.1, 4, -4);  //
		glVertex3f(0.9, 4, -4);  //
		glVertex3f(0.9, 4, -5.5);  //
		glVertex3f(6.1, 4, -5.5);

		//upper front
		glVertex3f(6.1, 4, -5.5);  //
		glVertex3f(0.9, 4, -5.5);  //
		glVertex3f(0.7, 3.65, -5.7);  //
		glVertex3f(6.3, 3.65, -5.7);

		//middle front
		glVertex3f(6.3, 3.65, -5.7);  //
		glVertex3f(0.7, 3.65, -5.7);  //
		glVertex3f(0.4, 3.25, -6.8);  //
		glVertex3f(6.6, 3.25, -6.8);

		//lower front
		glVertex3f(6.6, 3.25, -6.8);  //
		glVertex3f(0.4, 3.25, -6.8);  //
		glVertex3f(0, 3, -7);  //
		glVertex3f(7, 3, -7);

		//low
		glVertex3f(7, 3, -7);  //
		glVertex3f(0, 3, -7);  //
		glVertex3f(0, 3, -7.3);  //
		glVertex3f(7, 3, -7.3);

		//front
		glVertex3f(7, 3, -7.3);  //
		glVertex3f(0, 3, -7.3);  //
		glVertex3f(0, 1, -8);  //
		glVertex3f(7, 1, -8);
	}
	glEnd();
	glPopMatrix();
}

Car::~Car()
{
}
