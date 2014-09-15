#pragma once
#include "glut.h"  /*!< OpenGL Utility Toolkit. */
#include "Point.h"  /*!< Used to manipulate point 2D objects. */
#include "Drawable.h"  /*!< Base abstract class. */

/**
* Class used to draw and design 2 static doors and 2 moving doors with textures; when the moving doors begin to open is drawn a rectangle with a texture with the message: "you win" and the game ends.
*/
class Win : public Drawable
{
	double dx; /*!<Private variable which represents the double value used to translate the moving doors. */
	bool win; /*!< Private variable which represents the boolean value set true if the pass card was taken and false if not. */
public:
	/**
	* The class constructor which initialize the center of the object, sets the boolean value of win to false and initialize the variable dx with 0.
	*/
	Win(Point center);
	/**
	* The empty destructor of the class
	*/
	~Win(void);
	/**
	* Empty constructor used in main.
	*/
	Win(){}
	
	/**
	* This method sets the boolean value of the variable win to true or false. 
	* @see Main.timer
	*/
	void SetWin(bool win);
	
	/**
	* This method is used to 
		* draw the backward rectangle with texture: "You win" drawn only when the doors begin to open
		* draw 2 static doors (left and right) 
		* draw 2 moving doors (left and right) between the 2 static doors which opens to see the backward rectangle
	*/
	void Draw();
};
