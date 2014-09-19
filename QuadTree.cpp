#include "QuadTree.h"

QuadTree::QuadTree(int pLevel, Rectangl bounds)
:level(pLevel),bounds(bounds),objectsCount(0)
{
	nodes[0] = NULL;
	nodes[1] = NULL;
	nodes[2] = NULL;
	nodes[3] = NULL;
}
void QuadTree::Clear()
{
	nodesObj.clear();
	for(int i = 0; i < 4; i++)
	{
		nodes[i]->Clear();
		nodes[i] = NULL;
	}
}
void QuadTree::split()
{
   int subWidth = (int)(bounds.width / 2);
   int subHeight = (int)(bounds.height / 2);
   int x = bounds.x;
   int y = bounds.y;


   nodes[0] = new QuadTree(level+1, Rectangl(x + subWidth, y, subWidth, subHeight));
   nodes[1] = new QuadTree(level+1, Rectangl(x, y, subWidth, subHeight));
   nodes[2] = new QuadTree(level+1, Rectangl(x, y + subHeight, subWidth, subHeight));
   nodes[3] = new QuadTree(level+1, Rectangl(x + subWidth, y + subHeight, subWidth, subHeight));
}
int QuadTree::GetIndex(Point position) 
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
void QuadTree::Insert(Node* node)
{
	if (nodes[0] != NULL) 
	{
		int index = GetIndex(node->GetCenter());
		if (index != -1) 
		{
			nodes[index]->Insert(node);
			return;
		}
	}

	nodesObj.push_back(node);
	objectsCount++;

	if (objectsCount > MAX_OBJECTS && level < MAX_LEVELS) 
	{
		if (nodes[0] == NULL) 
		{
			split();
		}

		int i = 0;
		while (i < nodesObj.size()) 
		{
			int index = GetIndex(nodesObj.at(i)->GetCenter());
			if (index != -1) 
			{
				Node* toInsert = nodesObj.at(i);
				nodesObj.erase(nodesObj.begin() + i);
				objectsCount--;
				nodes[index]->Insert(toInsert);
			}
			else 
			{
				i++;
			}
		}
	}
}
void QuadTree::Insert(Building* building)
{
	if (nodes[0] != NULL) 
	{
		int index = GetIndex(building->buildingPoints[0]);
		for(int i = 1; i < building->buildingPoints.size(); i++)
			if(GetIndex(building->buildingPoints[i]) != index)
			{
				index = -1;
				break;
			}
		if (index != -1) 
		{
			nodes[index]->Insert(building);
			return;
		}
	}

	buildingsObj.push_back(building);
	objectsCount++;
	if (objectsCount > MAX_OBJECTS && level < MAX_LEVELS) 
	{
		if (nodes[0] == NULL) 
		{
			split();
		}

		int i = 0;
		while (i < buildingsObj.size()) 
		{
			Building *toInsert = buildingsObj.at(i);
			int index = GetIndex(toInsert->buildingPoints[0]);
			for(int i = 1; i < toInsert->buildingPoints.size(); i++)
				if(GetIndex(toInsert->buildingPoints[i]) != index)
				{
					index = -1;
					break;
				}
			if (index != -1) 
			{
				buildingsObj.erase(buildingsObj.begin() + i);
				objectsCount--;
				nodes[index]->Insert(toInsert);
			}
			else 
			{
				i++;
			}
		}
	}
}

/*
 * Return all objects that could collide with the given object
 */
void QuadTree::Retrieve(Point position, std::vector<Node*>& returnObjects)
{
	int index = GetIndex(position);
	if (index != -1 && nodes[0] != NULL) 
    {
		nodes[index]->Retrieve(position, returnObjects);
    }
	returnObjects.insert(returnObjects.end(), nodesObj.begin(), nodesObj.end());
}
void QuadTree::Retrieve(Point position, std::vector<Building*>& returnObjects)
{
	int index = GetIndex(position);
	if (index != -1 && nodes[0] != NULL) 
    {
		nodes[index]->Retrieve(position, returnObjects);
    }
	returnObjects.insert(returnObjects.end(), buildingsObj.begin(), buildingsObj.end());
}

//int QuadTree::GetLevel(Point position)
//{
//	int index = GetIndex(position);
//	if (index != -1 && nodes[0] != NULL) 
//    {
//		nodes[index]->GetLevel(position);
//    }
//	return level;
//}

QuadTree::~QuadTree(void)
{
}
