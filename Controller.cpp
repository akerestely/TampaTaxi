#include "Controller.h"

Controller::Controller(void)
{
	model = new Model;
	scene = new Scene(model,&cam);
}

void Controller::RenderDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	
	Controller *ctrl=Controller::GetInstance();

	glLoadIdentity();
	ctrl->scene->Render();

	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

void Controller::MouseClicked(int button, int state, int x, int y)
{
}
void Controller::MouseMovedPassive(int x,int y)
{
	Controller *ctrl=Controller::GetInstance();
	if(x!=1024/2 || y!=768/2)
	{
		double rotY=-(x-1024/2)*0.12;
		double rotX=-(y-768/2)*0.12;
		ctrl->cam.RotateY(rotY);
		ctrl->cam.RotateX(rotX);

		glutWarpPointer( 1024/2 , 768/2 );
	}
}
void Controller::KeyPressed (unsigned char key, int x, int y)
{
	Controller *ctrl=Controller::GetInstance();
	switch (key) 
	{
		//  case 'w':cam.RotateX(-5);break;
		//  case 's':cam.RotateX(5);break;
	case 'q':exit(1);
	//case 'a':rotLeft=true; break;
	//case 'd':rotRight=true; break;
	//case ' ':cam.RotateX(5);break;
	//case ' ':jump=true; break;
	case 'w':ctrl->up=true;break;
	case 's':ctrl->down=true;break;
	case 'a':ctrl->left=true; break;
	case 'd':ctrl->right=true; break;
	case ' ':
	if(!glutGetModifiers())
		ctrl->climbUp=true; 
	else
		ctrl->climbDown=true;
	break;
	}
}
void Controller::KeyReleased (unsigned char key, int x, int y)
{
	Controller *ctrl=Controller::GetInstance();
	switch (key) 
	{
	//case 'a':rotLeft=false; break;
	//case 'd':rotRight=false; break;
	case 'w':ctrl->up=false;break;
	case 's':ctrl->down=false;break;
	case 'a':ctrl->left=false; break;
	case 'd':ctrl->right=false; break;
	case ' ':ctrl->climbUp=ctrl->climbDown=false; break;
	}
}

void Controller::KeyPressedSpecial(int key, int x, int y)
{
	Controller *ctrl=Controller::GetInstance();
	switch (key) 
	{
	case GLUT_KEY_LEFT:ctrl->left = true; break;
	case GLUT_KEY_RIGHT:ctrl->right = true; break;
	case GLUT_KEY_UP:ctrl->up = true; break;
	case GLUT_KEY_DOWN:ctrl->down = true; break;
	}
}
void Controller::KeyReleasedSpecial(int key, int x, int y) 
{
	Controller *ctrl=Controller::GetInstance();
	switch (key) 
	{
	case GLUT_KEY_LEFT:ctrl->left = false; break;
	case GLUT_KEY_RIGHT:ctrl->right = false; break;
	case GLUT_KEY_UP:ctrl->up = false; break;
	case GLUT_KEY_DOWN:ctrl->down = false; break;
	}
}

void Controller::Timer(int value)
{
	Controller *ctrl=Controller::GetInstance();
	ctrl->model->Update();
	glutTimerFunc(15, Timer, 0);
	/*if (left)
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
	}*/	
}

void Controller::WindowResize(GLsizei width, GLsizei height)
{
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

Controller::~Controller(void)
{
	delete model;
	delete scene;
}
