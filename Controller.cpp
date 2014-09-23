#include "Controller.h"

Controller::Controller(void)
{
	model = new Model;
	scene = new Scene(model);
	hud = new Hud(Point(),model);
	debugWindow = new DebugWindow(model);
	mainMenu = new MainMenu();
}

void Controller::RenderDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	
	Controller *ctrl=Controller::GetInstance();
	glLoadIdentity();
	ctrl->scene->Render();
	glLoadIdentity();
	
	ctrl->hud->Draw();
	if(ctrl->escPressed) 
	{
		ctrl->mainMenu->Draw();
	}
	if(ctrl->debugWindowPressed) 
	{
		ctrl->debugWindow->Draw();
	}
	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

void Controller::MouseClicked(int button, int state, int x, int y)
{
}
void Controller::MouseMovedPassive(int x,int y)
{
	Controller *ctrl=Controller::GetInstance();
	if(!ctrl->escPressed) 
	{
		if(x!=ctrl->windowWidth/2 || y!=ctrl->windowHeight/2)
		{
			ctrl->model->MouseMove(-(x-ctrl->windowWidth/2),-(y-ctrl->windowHeight/2));
			glutWarpPointer( ctrl->windowWidth/2 , ctrl->windowHeight/2 );
		}
	}
}
void Controller::KeyPressed (unsigned char key, int x, int y)
{
	Controller *ctrl=Controller::GetInstance();
	switch (key) 
	{
	case 'q':
	case 'Q':exit(1);
	case 27:ctrl->escPressed=!ctrl->escPressed;break;
	case 'w':ctrl->up=true;break;
	case 's':ctrl->down=true;break;
	case 'a':ctrl->left=true; break;
	case 'd':ctrl->right=true; break;
	case 'l':glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	case 'L':glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
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
	case GLUT_KEY_F3:ctrl->debugWindowPressed=!ctrl->debugWindowPressed;break;
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
	glutTimerFunc(15, Timer, 0);
	Controller *ctrl=Controller::GetInstance();
	if(!ctrl->escPressed) 
	{
		if (ctrl->left)
			ctrl->model->MoveLeft();		
		if (ctrl->right)
			ctrl->model->MoveRight();
		if (ctrl->up)		 
			ctrl->model->MoveUp();
		if (ctrl->down)		 
			ctrl->model->MoveDown();
		/*if(climbUp)
		{		
			cam.Move(SF3dVector(0,SPEED,0));
		}
		if(climbDown)
		{		
			cam.Move(SF3dVector(0,-SPEED,0));
		}*/
	}
	ctrl->model->Update();
	ctrl->hud->Update();
}

void Controller::WindowResize(GLsizei width, GLsizei height)
{
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	Controller *ctrl=Controller::GetInstance();
	ctrl->windowWidth=width;
	ctrl->windowHeight=height;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 20000.0f);
}

Controller::~Controller(void)
{
	delete model;
	delete scene;
	delete hud;
	delete debugWindow;
	delete mainMenu;
}
