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
#include "Win.h"

#define SPEED 0.3
#define ROTATION 3

CCamera cam;
SkyCube skyCube;
Map brasovMap;
Ball *ball;
bool up,down,left,right,climbUp,climbDown,rotLeft,rotRight, jump;
int texNr=0;
Card card,miniCard;
int lastCheckPointKey;
std::vector<Building> buildings;
bool canWin;
Win win;
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
		Point checkPointPosition = brasovMap.GetPoint(CHECKPOINT).getCenter();
		card = Card(Point(checkPointPosition.x, checkPointPosition.y + 0.5, checkPointPosition.z),false);
		miniCard=Card(Point(0.95,0.55,-2),true);
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
      miniCard.Draw();
  
   //glTranslatef(0.0f, -1.0f, -10.0f); 
   //glRotatef(5.0,1,0,0);
	
   cam.Render();
   skyCube.Draw();
   brasovMap.Draw();
   
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
	if (jump)
	{
		//ball->Jump(jump);
	}
	if (left)
	{
		cam.MoveX(-SPEED); 
		ball->MoveX(-SPEED);		
	}
	if (right)
	{
		cam.MoveX(SPEED); 
		ball->MoveX(SPEED);
	}
	if (up)
	{
		cam.MoveZ(-SPEED); 
		ball->MoveZ(SPEED);
	}
	if (down)
	{
		cam.MoveZ(SPEED); 
		ball->MoveZ(-SPEED);
	}
	if(climbUp)
	{		
		cam.Move(SF3dVector(0,SPEED,0));
	}
	if(climbDown)
	{		
		cam.Move(SF3dVector(0,-SPEED,0));
	}
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
	   buildings[i].SwitchMode(cam.GetPosition(), -cam.GetRotY());
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
void mouse(int button, int state, int x, int y)
{
	std::cout<<x<<" "<<y<<"\n";
}
void mouseMove(int x,int y)
{
	if(x!=1024/2 || y!=768/2)
	{
		std::cout<<x<<" "<<y<<"\n";
		double rotY=-(x-1024/2)*0.12;
		double rotX=-(y-768/2)*0.12;
		cam.RotateY(rotY);
		cam.RotateX(rotX);

		glutWarpPointer( 1024/2 , 768/2 );
	}
}
void keyboardPressed (unsigned char key, int x, int y)
{
	switch (key) 
	{
		//  case 'w':cam.RotateX(-5);break;
		//  case 's':cam.RotateX(5);break;
	case 'q':exit(1);
	//case 'a':rotLeft=true; break;
	//case 'd':rotRight=true; break;
	//case ' ':cam.RotateX(5);break;
	//case ' ':jump=true; break;
	case 't':if(texNr==4)
				 texNr=0;
			 else
			     texNr++;
			 break;
	case 'w':up=true;break;
	case 's':down=true;break;
	case 'a':left=true; break;
	case 'd':right=true; break;
	case ' ':
	if(!glutGetModifiers())
		climbUp=true; 
	else
		climbDown=true;
	break;
	}
}
void keyboardReleased (unsigned char key, int x, int y)
{
	switch (key) 
	{
	//case 'a':rotLeft=false; break;
	//case 'd':rotRight=false; break;
	case 'w':up=false;break;
	case 's':down=false;break;
	case 'a':left=false; break;
	case 'd':right=false; break;
	case ' ':climbUp=climbDown=false; break;
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
		glutInitWindowSize(1024, 768);   // Set the window's initial width & height
		glutInitWindowPosition(250, 50); // Position the window's initial top-left corner
		glutCreateWindow("Test");          // Create window with the given title
		glutDisplayFunc(display);       // Register callback handler for window re-paint event
		glutReshapeFunc(reshape);       // Register callback handler for window re-size event
		initGL();                       // Our own OpenGL initialization
		glutKeyboardFunc(keyboardPressed);
   		glutKeyboardUpFunc(keyboardReleased);
  		glutSpecialFunc(handleSpecialKeyPressed);
   		glutSpecialUpFunc(handleSpecialKeyReleased);
		glutMouseFunc(mouse);
		glutSetCursor( GLUT_CURSOR_NONE );
		//glutMotionFunc(mouseMove);
		glutPassiveMotionFunc(mouseMove);
		glutTimerFunc(0, timer, 0);     // First timer call immediately
		//glutFullScreen();				// Enter FullScreen. Remove for windowed mode.
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