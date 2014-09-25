#pragma once
#include <iostream>
#include <glut.h> /*!< OpenGL Utility Toolkit. */

/**
* Class used to load, generate and bind all textures used in this project. The compatible format for textures is tga.
* The class uses the singleton design pattern; it can be instantiated only once, so the textures will be loaded only once during the game.
*/
class Texture
{
private:
	/**
	* This method is used to load a tga file and get the file attributes : width and height
	* @param fileName - the name of the file used to load a texture
	* @param width - the width of the texture
	* @param height - the height of the texture
	*/
	char* esLoadTGA(char *fileName, double *width, double *height);

	/**
	* This a class private constructor loads, generates and binds all the textures used in this project.
	*/
	Texture();
public:
	/**
	* This method is used get an instance to the class. 
	*/
	static Texture& GetInstance();

	GLuint fBodyTex[3][2];
	GLuint mBodyTex[3][2];
	
	GLuint skirtTex[3];
	GLuint mLegsTex[3];
	
	GLuint fFeetTex[1];
	GLuint mFeetTex[1];

	GLuint fFaceTex[1];
	GLuint mFaceTex[1];

	GLuint getTaxiTex;

	GLuint skinTex;
	GLuint mainMenu[10];
	GLuint mainMenuOver[5];
	GLuint newGameMenu[10];
	GLuint secondMenu[3];
	
	GLuint skyCube[6];  /*!<Public variable which represents a GLuint array with 6 textures used to design the sky and the ground. */
	GLuint roadTex;  /*!<Public variable which represents a GLuint value containing a texture used to design the road. */
	GLuint textures[10]; /*!<Public variable which represents a GLuint array with 10 textures used to design the buildings drawn on the map. */
	
	GLuint wheelSide;
	GLuint wheelBase;
	GLuint carSide;
	GLuint carFront;
	GLuint carBack;
	
	GLuint hudText;
	GLuint hudNumbers;
	GLuint moneyTex;
	GLuint nodeTex;
	GLuint sidewayTex;
};
