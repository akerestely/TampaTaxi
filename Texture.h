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
	GLuint ballTex[5]; /*!<Public variable which represents a GLuint array with 5 textures used to design the ball. */
	GLuint cardTex[2]; /*!<Public variable which represents a GLuint array with 2 textures used to design the pass card (Route 66 logo) and the support made from 3 spheres with wood texture. */
	GLuint skyCube[6];  /*!<Public variable which represents a GLuint array with 6 textures used to design the sky and the ground. */
	GLuint roadTex;  /*!<Public variable which represents a GLuint value containing a texture used to design the road. */
	GLuint textures[10]; /*!<Public variable which represents a GLuint array with 10 textures used to design the buildings drawn on the map. */
	GLuint doorTex; /*!<Public variable which represents a GLuint value containing a texture used to design the doors at the end point of the game. */
	GLuint winTex; /*!<Public variable which represents a GLuint value containing a texture used to design the rectangle with the message "you win" behind the doors at the end point of the game. */
	GLuint hudText;
	GLuint hudNumbers;
};
