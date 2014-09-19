#pragma once
#include <vector>   /*!< Used to store GLfloat values for vertices, normals, indices and texture coordinates. */
#include "glut.h"   /*!< OpenGL Utility Toolkit. */
#include "Point.h"   /*!< Used to manipulate point 2D objects. */
#include "math.h"   /*!< Used for cos and sin math functions. */
#include "Object3d.h"
#include "Drawable.h"   /*!< Base abstract class. */

#define POWER 0.5   /*!<The double value used to increase the y coordinate of the ball when it jumps. */
#define GRAVITY 0.05   /*!<The double value used to repeatedly decrease the y coordinate of the ball after the jump(when is falling). */

/**
* Class used to design and control a ball. The ball has a texture, it can rotate to right and to left, forward and backward and it can jump. 
*/
class Ball : public Object3d, public Drawable
{
private:
	std::vector<GLfloat> vertices;  /*!< A private variable which stores the sphere vertices. */
    std::vector<GLfloat> normals;  /*!< A private variable which stores the sphere normals. */
    std::vector<GLfloat> texcoords;  /*!< A private variable which stores the sphere texture coordinates. */
    std::vector<GLushort> indices;  /*!< A private variable which stores the sphere indices. */
	static const int rings=50;  /*!<A private static variable which represents the number of the rings of the drawn sphere. */
	static const int sectors=100;  /*!<A private static variable which represents the number of the sectors of the drawn sphere. */
	bool boolX, boolZ;  /*!< Private boolean values used for rotations on X-axis and Y-axis. */
	bool canJump;   /*!< A private variable which represents a boolean value used in the jumping process of the ball. */
	double energy;   /*!<A private variable which represents a double value used to repeatedly increase the y coordinate when the ball is jumping..*/
	double alphaX, alphaZ;   /*!< Private values which represents the double values of the angles used in the rotation process of the ball. */
	int texnr;   /*!< A private value which represents the coresponding index of the used texture. */
public:
	/**
	* The class empty destructor.
	*/
	~Ball(void);

	/**
	* The class constructor used to:
		* initialize the radius and the center point of the drawn ball. 
		* set the boolean values boolX and boolZ to false and the boolean value of the canJump to true.
		* calculate using math formulas to calculate the vertices, the normals, the indices and the texture coordinates for the sphere.
	* @param radius - the double value for the drawn sphere radius.
	* @param center - the center point of the drawn sphere.
	*/ 
	Ball(float radius, Point center);

	/**
	* This method sets the index of the texture used to drawn the ball.
	*/
	void SetTexNr(int nr);

	/**
	* This method is used to draw a sphere and it contains:
		* openGl settings to draw the sphere: glMatrixMode
		* the process to bind the selected texture to the ball(sphere) 
		* the translation of the ball in the center point
		* the ball's rotations on X-axis and Y-axis
		* draws the vertices, normals and indices of the sphere
	*/
	void Draw();

	/**
	* This method increases(right) or decreases(left) the value of the angle used on rotation of the ball on the X-axis
	and sets the boolean value of boolX to false and boolZ to true used to know the right order of the rotations.
	*/
	void MoveX(double dx);

	/**
	* This method increases(forward) or decreases(backward) the value of the angle used on rotation of the ball on the Z-axis
	and sets the boolean value of boolX to true and boolZ to false used to know the right order of the rotations.
	*/
	void MoveZ(double dz);

	/**
	* This method increases or decreases the value on the Y-axis so the visual effect on redrawing will be the jump action.
	* @param isJump - boolean value used in main to control the jump action after pressing spacebar.
	* @see Main.keyboardPressed 
	* @see Main.timer
	*/
	void Jump(bool &isJump);
};
