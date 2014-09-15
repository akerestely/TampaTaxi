#pragma once
#include "glut.h"  /*!< OpenGL Utility Toolkit. */
#include "Point.h"  /*!< Used to manipulate point 2D objects. */
#include "Drawable.h"  /*!< Base abstract class. */

/**
* Class used to draw and design a pass card on a support made by 3 spheres. The pass card is represented by a rectangle with the logo of Route66 as a texture.
*/
class Card : public Drawable
{
	double angle; /*!< A private variable which represents the angle in degrees used to rotate the card on each redraw. */
	bool isMiniCard; /*!< A private variable which represents the boolean value used in the Draw function */
	/**
	* This method is used to drawn the big pass card represented by a rectangle with a texture with the logo of Route 66 
	and 3 spheres with a wooden texture which represents the support of the card . 
	The Rotatef opengl functions are used for each object at each redraw to see the visual effect of spinning continuously.
	This card is placed on the map and the ball has to find it and take it to win the game.
	*/
	void DrawBigCard();

	/**
	* This method draws a mini pass (a scaled big card) card in the up - right corner of the screen after the ball has found the big card.
	*/
	void DrawMiniCard();
public:
   /**
	* The class constructor used to:
		* initialize the value of the angle with 0 degrees.
		* initialize the value of the boolean variable isMiniCard with the value given by the parameter isMiniCard
	* @param center - the center point of the drawn object.
	* @param isMiniCard - the boolean value used in the Draw function to draw a big card when is false or a small card when is true
	*/
	Card(Point center,bool isMiniCard);

	/** 
	* The empty class constructor used in main.
	*/ 
	Card(){}

	/** 
	* The empty class destructor.
	*/
	~Card(void);

	/**
	* This method draws a big card if the variable isMiniCard is false or a mini card otherwise.
	*/
	void Draw();

};
