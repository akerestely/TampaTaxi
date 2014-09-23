#include "Controller.h"

void initGL() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void init()
{
	//handle display
	glutDisplayFunc(Controller::RenderDisplay);
	glutReshapeFunc(Controller::WindowResize);
	glutIdleFunc(Controller::RenderDisplay);

	//handle input
	glutKeyboardFunc(Controller::KeyPressed);
	glutKeyboardUpFunc(Controller::KeyReleased);
	glutSpecialFunc(Controller::KeyPressedSpecial);
	glutSpecialUpFunc(Controller::KeyReleasedSpecial);
	glutPassiveMotionFunc(Controller::MouseMovedPassive);
	glutSetCursor( GLUT_CURSOR_NONE );
	glutMouseFunc(Controller::MouseClicked);

	//handle timer(update)
	glutTimerFunc(0, Controller::Timer, 0);
	
	//graphic init
	initGL();
}
int main(int argc, char** argv) 
{
	try
	{
		glutInit(&argc, argv);            // Initialize GLUT
		glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
		glutInitWindowSize(1024, 768);   // Set the window's initial width & height
		glutInitWindowPosition(250, 50); // Position the window's initial top-left corner
		glutCreateWindow("Taxi Mania");          // Create window with the given title
		init();
		glutFullScreen();				// Enter FullScreen. Remove for windowed mode.
		glutMainLoop();                 // Enter the infinite event-processing loop
	}
	catch(char* message)
	{
		std::cout<<message<<"\n";
	}
	catch(...)
	{
		return -1;
	}
	return 0;
}