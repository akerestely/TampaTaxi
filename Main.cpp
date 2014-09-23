#include <Windows.h>
#include <ctime>
#include "iostream"
#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "CameraSpectator.h"
#include "Tools.h"
#include "vector"
#include "Map.h"
#include "Building.h"
#include "Ball.h"
#include "Card.h"
#include "SkyCube.h"
#include"Hud.h"
#include "Win.h"

#define ACCELERATION 0.007

#define ROTATION 3
#define SPEED 0.3

double speed=0;

CCamera cam;
SkyCube skyCube;
Map brasovMap;
Ball *ball;
bool up,down,left,right,rotLeft,rotRight, jump;
int texNr=0;
Card card,miniCard;
int lastCheckPointKey;
std::vector<Building> buildings;
bool canWin;
Win win;
Hud hud;
void initGL() 
{
 	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	try
	{
		
		brasovMap = Map("Map.xml");
		ball = new Ball(BALL_RADIUS / 8, Point(0, 0, 0));
		Point checkPointPosition = brasovMap.GetPoint(4).getCenter();
		card = Card(Point(checkPointPosition.x, checkPointPosition.y + 0.5, checkPointPosition.z),false);
		miniCard=Card(Point(0.95,0.55,-2),true);
		hud=Hud(Point(0,0,0)); 
		//presupunem ca ne am luat masina
		lastCheckPointKey = STARTPOINT;
		canWin = false;
		Point endPoint = brasovMap.GetPoint(ENDPOINT).getCenter();
		win = Win(Point(endPoint.x, endPoint.y + 2, endPoint.z));
	}
	catch(char* message)
	{
		throw message;
	}

	srand(time(NULL));
	if(!Tools::ReadBuildingsFromXML("Buildings.xml", buildings))
		throw "Invalid buildings file!";
	
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
   
   glLoadIdentity();                 // Reset the model-view matrix
 
   if(canWin)
   {
      miniCard.Draw();
		
   }
	hud.Draw();   
   glTranslatef(0.0f, -1.0f, -10.0f); 
    glRotatef(5.0,1,0,0);
	
   ball->SetTexNr(texNr);
   ball->Draw();
   cam.Render();
   skyCube.Draw();
   //win.Draw();
   brasovMap.Draw();
   
   if(!canWin)
	  card.Draw();
	
   Point startPos = brasovMap.GetPoint(STARTPOINT).getCenter();
   Point endPos = brasovMap.GetPoint(ENDPOINT).getCenter();
   glPushMatrix();
   glTranslated(endPos.x - startPos.x, startPos.y, endPos.z - startPos.z);
   for(int i=0;i<buildings.size();i++) {
	   buildings[i].Draw();
   }
   glPopMatrix();
  
   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}
void timer(int value) 
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 0);
	Point center = cam.GetPosition();
	//Point center = ball->GetPosition();
	if (jump)
	{
		ball->Jump(jump);
	}
	if(speed)
	{
		speed-=Tools::Sign(speed)*0.002;
		if(abs(speed)<0.00005)
			speed=0;
	}
	if(up)
	{
		if(speed<MAX_SPEED)
			speed+=ACCELERATION;
		/*if(speed>MAXSPEED)
			speed=MAXSPEED;*/
	}
	if(down)
	{
		if(speed>-0.05)
			speed-=ACCELERATION;
	}
	if (left)
	{
		cam.MoveX(-SPEED); 
		ball->MoveX(-SPEED);
		center = cam.GetPosition();
		if (brasovMap.BallCollision(lastCheckPointKey, Point(center.x, center.y, center.z)) == BallStreetPosition::Outside)
		{
			cam.MoveX(SPEED); 
			ball->MoveX(SPEED);
		}		
	}
	if (right)
	{
		cam.MoveX(SPEED); 
		ball->MoveX(SPEED);
		center = cam.GetPosition();
		if (brasovMap.BallCollision(lastCheckPointKey, Point(center.x, center.y, center.z)) == BallStreetPosition::Outside)
		{
			cam.MoveX(-SPEED);
			ball->MoveX(-SPEED);
		}
	}
	if (speed!=0)
	{
		cam.MoveZ(-speed); 
		ball->MoveZ(speed);
		center = cam.GetPosition();
		if (brasovMap.BallCollision(lastCheckPointKey, Point(center.x, center.y, center.z)) == BallStreetPosition::Outside)
		{
			cam.MoveZ(speed);
			ball->MoveZ(-speed);
			speed=0;
		}
	}
	hud.setSpeed(speed);
	if(rotLeft)
	{
		cam.RotateY(ROTATION);
	}
	if(rotRight)
	{
		cam.RotateY(-ROTATION);
	}
	skyCube.SetPoz(Point(cam.GetPosition().x,0,cam.GetPosition().z));
	for(int i=0;i<buildings.size();i++) 
	{
	   buildings[i].SwitchMode(cam.GetPosition(), -cam.GetRotY());
   }
	if (!canWin)
	{
		if(lastCheckPointKey == CHECKPOINT)
			canWin = true;
	}
	else
	{
		if(lastCheckPointKey == ENDPOINT)
		{
			win.SetWin(true);
		}
		else
		{
			win.SetWin(false);
		}
	}
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 300.0f);
}

void keyboardPressed (unsigned char key, int x, int y)
{
	switch (key) 
	{
		//  case 'w':cam.RotateX(-5);break;
		//  case 's':cam.RotateX(5);break;
	case 'q':exit(1);
	case 'a':rotLeft=true; break;
	case 'd':rotRight=true; break;
	//case 'w':cam.RotateX(5);break;
	//case 's':cam.RotateX(-5);break;
	case ' ':jump=true; break;
	case 't':if(texNr==4)
				 texNr=0;
			 else
			     texNr++;
			 break;
	}
}
void keyboardReleased (unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 'a':rotLeft=false; break;
	case 'd':rotRight=false; break;
	}
}

void handleSpecialKeyPressed(int key, int x, int y)
{
	switch (key) 
	{
	case GLUT_KEY_LEFT:left = true; break;
	case GLUT_KEY_RIGHT:right = true; break;
	case GLUT_KEY_UP:up = true; break;
	case GLUT_KEY_DOWN:down = true; break;
	}
}
void handleSpecialKeyReleased(int key, int x, int y) 
{
	switch (key) 
	{
	case GLUT_KEY_LEFT:left = false; break;
	case GLUT_KEY_RIGHT:right = false; break;
	case GLUT_KEY_UP:up = false; break;
	case GLUT_KEY_DOWN:down = false; break;
	}
}
int main(int argc, char** argv) 
{
	try
	{
		glutInit(&argc, argv);            // Initialize GLUT
		glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
<<<<<<< Updated upstream
		glutInitWindowSize(640, 480);   // Set the window's initial width & height
		glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
		glutCreateWindow("Test");          // Create window with the given title
		glutDisplayFunc(display);       // Register callback handler for window re-paint event
		glutReshapeFunc(reshape);       // Register callback handler for window re-size event
		initGL();                       // Our own OpenGL initialization
		glutKeyboardFunc(keyboardPressed);
   		glutKeyboardUpFunc(keyboardReleased);
  		glutSpecialFunc(handleSpecialKeyPressed);
   		glutSpecialUpFunc(handleSpecialKeyReleased);
		glutTimerFunc(0, timer, 0);     // First timer call immediately
=======
		glutInitWindowSize(1024, 768);   // Set the window's initial width & height
		glutInitWindowPosition(250, 50); // Position the window's initial top-left corner
		glutCreateWindow("Taxi Mania");          // Create window with the given title
		init();
>>>>>>> Stashed changes
		glutFullScreen();				// Enter FullScreen. Remove for windowed mode.
		glutMainLoop();                 // Enter the infinite event-processing loop
	}
	catch(char* message)
	{
		std::cout<<message<<"\n";
	}
	catch(...)
	{
		return -5;
	}
	return 0;
}