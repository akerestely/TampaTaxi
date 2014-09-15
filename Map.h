#pragma once
#include "Node.h"
#include "map"
#include "Tools.h"
#include "glut.h"
#define STARTPOINT 5
#define ENDPOINT 5
#define CHECKPOINT 0

/* A class which represent a map. A map is represented by a list of intersections 
 * This class inherit the abstract class Drawable.
**/
class Map: public Drawable
{
	std::map<int, Node> nodes;/*!< A map which contain the coordinats of the map intersections. Each intersection has an unique id */
	void getIntersection(Node first, Node second, Point &firstPoint, Point &secondPoint);
	void translateToCenter();
	void computeStreets();
	bool ballInsideStreet(int firstNodeKey, int adjacentIndex, Point ballCenter);
	bool Map::centerInsideStreet(Street street, Point ballCenter);
	double getLength(Point A, Point B);

public:
	/* A constructor which reads the coordinates of the map, translates the coordinates to the map center
	 * and computes the coordinates of the streets
	 * @param fileName a char pointer which takes the name of the file that contains the coordinates of the map
	 * @see Tools::ReadNodesFromXML()
	**/
	Map(char* fileName);
	/* Default constructor
	**/
	Map();
	/* An inherit method which draws the map. To draw intersections are used circles and to draw the streets are used quads.
	* @see Node.Draw()
	**/
	void Draw() override;
	/* A method which takes two parameters. The first parameter is passed by reference.
	 * This method checks if a ball with center in ballCenter and radius WIDTH / 2 are on a street adjacent with a node with id nodeKey or not
	 * and it returns an enum which has two values: BallStreetPosition::Inside if the ball is on the road or BallStreetPosition::Outside 
	 * if the ball is out of the road.
	 * @param nodeKey - int value which represent the id of an intersection
	 * @param ballCenter - Point value which represent the center of the ball
	 * @see Point class
	**/
	BallStreetPosition BallCollision(int &nodeKey, Point ballCenter);
	/* A method which takes one paramter and return a node which represent an intersection which the id passed by parameter.
	 * @param key - int value which represent the id of an intersection
	**/
	Node GetPoint(int key);
};
