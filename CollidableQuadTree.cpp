#include "CollidableQuadTree.h"

CollidableQuadTree::CollidableQuadTree(int pLevel, Rectangl bounds, int nodeIndex)
:level(pLevel), bounds(bounds), nodeIndex(nodeIndex)
{
	nodes[0] = NULL;
	nodes[1] = NULL;
	nodes[2] = NULL;
	nodes[3] = NULL;
}
void CollidableQuadTree::Clear()
{
	objects.clear();
	for(int i = 0; i < 4; i++)
	{
		nodes[i]->Clear();
		nodes[i] = NULL;
	}
}
void CollidableQuadTree::split()
{
   int subWidth = (int)(bounds.width / 2);
   int subHeight = (int)(bounds.height / 2);
   int x = bounds.x;
   int y = bounds.y;


   nodes[0] = new CollidableQuadTree(level + 1, Rectangl(x + subWidth, y, subWidth, subHeight), 4 * nodeIndex + 1);
   nodes[1] = new CollidableQuadTree(level + 1, Rectangl(x, y, subWidth, subHeight), 4 * nodeIndex + 2);
   nodes[2] = new CollidableQuadTree(level + 1, Rectangl(x, y + subHeight, subWidth, subHeight), 4 * nodeIndex + 3);
   nodes[3] = new CollidableQuadTree(level + 1, Rectangl(x + subWidth, y + subHeight, subWidth, subHeight), 4 * nodeIndex + 4);
}
int CollidableQuadTree::GetIndex(Point position) 
{
   int index = -1;
   double verticalMidpoint = bounds.x + (bounds.width / 2.);
   double horizontalMidpoint = bounds.y + (bounds.height / 2.);
 
   // Object can completely fit within the top quadrants
   bool topQuadrant = (position.z < horizontalMidpoint);
   // Object can completely fit within the bottom quadrants
   bool bottomQuadrant = (position.z > horizontalMidpoint);
 
   // Object can completely fit within the left quadrants
   if (position.x < verticalMidpoint) {
      if (topQuadrant) {
        index = 1;
      }
      else if (bottomQuadrant) {
        index = 2;
      }
    }
    // Object can completely fit within the right quadrants
    else if (position.x > verticalMidpoint) {
     if (topQuadrant) {
       index = 0;
     }
     else if (bottomQuadrant) {
       index = 3;
     }
   }
 
   return index;
}
/*
 * Insert the object into the quadtree. If the node
 * exceeds the capacity, it will split and add all
 * objects to their corresponding nodes.
 */
void CollidableQuadTree::Insert(Collidable* collidable)
{
	if (nodes[0] != NULL) 
	{
		int index = GetIndex(collidable->GetCenter());
		if (index != -1) 
		{
			nodes[index]->Insert(collidable);
			return;
		}
	}

	objects.push_back(collidable);

	if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) 
	{
		if (nodes[0] == NULL) 
		{
			split();
		}
		int i = 0;
		while (i < objects.size()) 
		{
			Collidable* toInsert = objects.at(i);
			int index = GetIndex(toInsert->GetCenter());
			if (index != -1) 
			{	
				objects.erase(objects.begin() + i);
				nodes[index]->Insert(toInsert);
			}
			else 
			{
				i++;
			}
		}
	}
}

int CollidableQuadTree::GetNodeIndex(Point position)
{
	int index = GetIndex(position);
	if (index != -1 && nodes[0] != NULL) 
		return nodes[index]->GetNodeIndex(position);
	return nodeIndex;
}
/*
 * Return all objects that could collide with the given object
 */
void CollidableQuadTree::Retrieve(std::set<Collidable*>& returnObjects, Point position)
{	
	int index = GetIndex(position);
	if (index != -1 && nodes[0] != NULL) 
    {
		nodes[index]->Retrieve(returnObjects, position);
    }
	returnObjects.insert(objects.begin(), objects.end());
}

CollidableQuadTree::~CollidableQuadTree(void)
{
}
