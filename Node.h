#pragma once
#include "Drawable.h"
#include<vector>

#define SCALLING 1000
/* A structure which contains a Point vector with 4 elements. 
 * The points represents the coordinates of the street.
**/
struct Street{
	Point corners[4];
};
/* A class which represent an intersection. 
 * This class inherit the abstract class Drawable.
**/
class Node:public Drawable
{
	int id; /*!<int field which represent the key of the intersection */
	std::vector<int> destinations;/*!<vector of integers which contains the keys of the adjacent intersections */
	std::vector<Street> streets; /*!<vector of Streets which contains the streets between current intersection and adjacent intersections */
public:
	/* Default constructor
	**/
	Node();
	/* Constructor which initializes the fields with parameters id and center.
	 * @param id - an integer value which represent the key of the intersection
	 * @param center - a point value which represent the coordinates of the intersection
	**/
	Node(int id, Point center);
	/* A method which returns the reference to the destinations vector
	**/
	std::vector<int>& getDestinations();
	/* A method which return the coordinates of the intersection
	**/
	Point getCenter();
	/* 
	*Method used to translate a 3D node on x-axis,y-axis and z-axis.
	*@param dx translate value on x-axis
	*@param dy translate value on y-axis
	*@param dz translate value on z-axis
	**/
	void Translate(double dx, double dy, double dz);
	/* An inherit method which draw the intersection.
	 * To draw the intersection is used a circle.
	**/
	void Draw() override;
	/* A method which takes a Street parameter. This method add a street to the streets vector
	 * @param street - Street to add to the intersection
	**/
	void addStreet(Street street);
	/* A method which returns a street.
	 * @param - index int value which represent the index of the street from the vector
	**/
	Street GetStreet(int index);
};
