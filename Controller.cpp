#include "Controller.h"

Controller::Controller(void)
{
	model = new Model;
	scene = new Scene(model);
	hud = new Hud(Point(),model);
	
	debugWindow = new DebugWindow(model);
	mainMenu = new MainMenu(model);
	lastWayName = new char[70];
}

void Controller::RenderDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	
	Controller *ctrl=Controller::GetInstance();
	glLoadIdentity();
	if(!ctrl->mainMenu->GetMapMenu()) {
		ctrl->scene->Render();
		glLoadIdentity();
		
		
		if(ctrl->mainMenu->GetEscPressed()) 
		{
			ctrl->mainMenu->Draw();
		}
		else
		{
			ctrl->hud->Draw();
		}
		if(ctrl->debugWindowPressed) 
		{
			ctrl->debugWindow->Draw();
		}
	}
	else {
		ctrl->model->GetMap()->GetMinimap()->Draw();
	}
	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

void Controller::MouseClicked(int button, int state, int x, int y)
{
	Controller *ctrl=Controller::GetInstance();
	if(ctrl->mainMenu->GetEscPressed()) 
	{
		ctrl->mainMenu->MouseClicked(button,state,x,y);
	}
}
void Controller::MouseMovedPassive(int x,int y)
{
	Controller *ctrl=Controller::GetInstance();
	if(!ctrl->mainMenu->GetEscPressed()) 
	{
		glutSetCursor( GLUT_CURSOR_NONE );
		if(x!=ctrl->windowWidth/2 || y!=ctrl->windowHeight/2)
		{
			ctrl->model->MouseMove(-(x-ctrl->windowWidth/2),-(y-ctrl->windowHeight/2));
			glutWarpPointer( ctrl->windowWidth/2 , ctrl->windowHeight/2 );
		}
	}
	else 
	{
		glutSetCursor( GLUT_CURSOR_RIGHT_ARROW );
		ctrl->mainMenu->MouseMove(x,y);
	}
}
void Controller::KeyPressed (unsigned char key, int x, int y)
{
	Controller *ctrl=Controller::GetInstance();
	switch (key) 
	{
	case 'q':
	case 'Q':exit(1);
	case 27:ctrl->mainMenu->EscPressed();break;
	case 'w':ctrl->up=true;break;
	case 's':ctrl->down=true;break;
	case 'a':ctrl->left=true; break;
	case 'd':ctrl->right=true; break;
	case 'l':glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	case 'L':glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
	case ' ':ctrl->jump=true; break;
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
	case ' ':ctrl->jump=false; break;
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
	glutTimerFunc(25, Timer, 0);
	glutPostRedisplay();
	Controller *ctrl=Controller::GetInstance();
	if(!ctrl->mainMenu->GetEscPressed()) 
	{
		if (ctrl->left)
			ctrl->model->MoveLeft();		
		if (ctrl->right)
			ctrl->model->MoveRight();
		if (ctrl->up)		 
			ctrl->model->MoveUp();
		if (ctrl->down)		 
			ctrl->model->MoveDown();
		if (ctrl->jump)
			ctrl->model->Jump();
		ctrl->model->Update();
		char *currentWayName = ctrl->model->GetMap()->GetCurrentWayName();
		if(currentWayName)
		{
			if(strcmp(currentWayName, ctrl->lastWayName) != 0 && strcmp(currentWayName, "unknown") != 0)
			{
				strcpy(ctrl->lastWayName, currentWayName);
				char *p = new char[70];
				strcpy(p, currentWayName);
				ctrl->waysNames.push_back(p);
				if((ctrl->waysNames).size() > 5)
				{
					Tools::WriteHadoopStreetsFiles(ctrl->waysNames);
					ctrl->waysNames.clear();
				}
			}
			ctrl->hud->Update(currentWayName);
		}
		else
		{
			if (ctrl->model->GetPlayer()->LastVisitedNodeIndex == START_MODAROM)
				ctrl->hud->Update("Modarom");
			if (ctrl->model->GetPlayer()->LastVisitedNodeIndex == START_LIVADA)
				ctrl->hud->Update("Livada Postei");
			if (ctrl->model->GetPlayer()->LastVisitedNodeIndex == START_DRUMUL_VECHI)
				ctrl->hud->Update("Drumul vechi");
		}
	}
	
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
