#include "Tools.h"
#include "fstream"

int Tools::ReadNodesFromXML(char *fileName, std::map<long,Node*>& nodes,std::map<long,Way*>& ways)
{
	
	char *buffer = new char[200];
	char *name = new char[100];
	char *tag = "</way>";
	long id, ref; 
	double longit, latit;
	strcpy(name, "unknown");
	bool isOneWay=false;
	std::vector<Node*> keys;
	FILE *fo = fopen(fileName, "r");
	if (fo == NULL)
		return 0;
	try
	{
		fgets(buffer, 200, fo);
		fgets(buffer,200,fo);

		fgets(buffer, 200, fo);
		while(strstr(buffer, "node"))
		{		
			strcpy(buffer, strstr(buffer, "='"));
			sscanf(buffer, "%*c%*c%ld", &id);
			strcpy(buffer, strstr(buffer+2, "='"));
			sscanf(buffer, "%*c%*c%lf", &latit);
			strcpy(buffer, strstr(buffer+2, "='"));
			sscanf(buffer, "%*c%*c%lf", &longit);

			nodes[(-id)]=new Node(Point(latit,0,longit), -id);
			fgets(buffer, 200, fo);
		}

		while(strstr(buffer,"way"))
		{
			strcpy(buffer, strstr(buffer, "='"));
			sscanf(buffer, "%*c%*c%d", &id);
			fgets(buffer,200,fo);
			while(!strstr(buffer,tag))
			{
				if(strstr(buffer,"<nd"))
				{
					strcpy(buffer,strstr(buffer,"='"));
					sscanf(buffer, "%*c%*c%ld",&ref);
					keys.push_back(nodes[(-ref)]);
					nodes[(-ref)]->AddWay(-id);
				}
				else
				{
					if(strstr(buffer,"'name'"))
					{
						strcpy(buffer,strstr(buffer,"v='"));
						strcpy(buffer,buffer+3);
						buffer[strlen(buffer)-4]=0;
						if(buffer[strlen(buffer)-1]=='\'')
							buffer[strlen(buffer)-1]=0;
						strcpy(name,buffer);
					}
					else
						if(strstr(buffer,"'oneway'"))
						{
							strcpy(buffer,strstr(buffer,"v='"));
							if(buffer[3]=='y')
								isOneWay=true;
							else
								isOneWay=false;
						}
				}
				fgets(buffer, 200, fo);
			}
			ways[-id]=new Way(name,keys,isOneWay);
			keys.clear();	
			strcpy(name,"unknown");
			isOneWay=false;
			fgets(buffer, 200, fo);
		}
	}
	catch(...)
	{
		return 0;
	}

	delete []buffer;
	delete []name;
	fclose(fo);
	return 1;
}

int Tools::ReadBuildingsFromXML(char *fileName, std::vector<Building*> &buildings)
{
	std::map<long,Point> points;
	char *buffer = new char[200];
	char *tag = "</way>";
	long id, ref; 
	double longit, latit;
	std::vector<Point> ways;
	FILE *fo = fopen(fileName, "r");
	if (fo == NULL)
		return 0;
	try
	{
		fgets(buffer, 200, fo);
		fgets(buffer,200,fo);

		fgets(buffer, 200, fo);
		while(strstr(buffer, "node"))
		{		
			strcpy(buffer, strstr(buffer, "='"));
			sscanf(buffer, "%*c%*c%ld", &id);
			strcpy(buffer, strstr(buffer+2, "='"));
			sscanf(buffer, "%*c%*c%lf", &latit);
			strcpy(buffer, strstr(buffer+2, "='"));
			sscanf(buffer, "%*c%*c%lf", &longit);

			points[(-id)]=Point(latit,0,longit);
			fgets(buffer, 200, fo);
		}

		while(strstr(buffer,"way"))
		{
			strcpy(buffer, strstr(buffer, "='"));
			sscanf(buffer, "%*c%*c%ld", &id);
			fgets(buffer,200,fo);
			while(!strstr(buffer,tag))
			{
				if(strstr(buffer,"<nd"))
				{
					strcpy(buffer,strstr(buffer,"='"));
					sscanf(buffer, "%*c%*c%ld",&ref);
					ways.push_back(points[-ref]);
				}

				fgets(buffer, 200, fo);
			}
			buildings.push_back(new Building(ways,buildings.size()));
			ways.clear();	
			fgets(buffer, 200, fo);
		}
	}
	catch(...)
	{
		return 0;
	}

	delete []buffer;
	fclose(fo);
	return 1;
}
int Tools::Sign(double x)
{
	return x<0?-1:1;
}
bool Tools::PointInsideRectangle(Point point, Point rTopRight, Point rBottomRight, Point rBottomLeft, Point rTopLeft)
{
	 SF3dVector AM(rTopRight, point), AB(rTopRight, rBottomRight), AD(rTopRight, rTopLeft);
	 if (((0 <=(AM*AB)) && ((AM*AB) <= (AB*AB))) &&
		((0 <= (AM*AD)) && ((AM*AD) <= (AD*AD))))
	 {
		 return true;
	 }
	 return false;
}
bool Tools::PointInsideCircle(Point point, Point cCenter, double cRadius)
{
	return (point.x - cCenter.x) * (point.x - cCenter.x) + (point.z - cCenter.z) * (point.z - cCenter.z) <= cRadius * cRadius;
}
long Tools::LongRand()
{
	static long next = 0;
	next = next * 1103515245 + 12345;
	return ((next / 65536) % 32768);
}

void Tools::WriteHadoopStreetsFiles(std::vector<char*> wayNames)
{
	static int streetsFilesCount = 0;
	char name[70];
	sprintf(name, "%s%d%s","hadoopFiles/", streetsFilesCount, ".txt");
	std::ofstream fout(name,std::ios::app);

	for(std::vector<char*>::iterator it = wayNames.begin(); it != wayNames.end(); ++it)
		fout<<(*it)<<"\n";

	fout.close();
	streetsFilesCount++;
}
void Tools::WriteIntersectionsFiles(std::vector<long> inters)
{
	static int intersFilesCount = 0;
	char name[70];
	sprintf(name, "%s%d%s","hadoopIntersFiles/", intersFilesCount, ".txt");
	std::ofstream fout(name,std::ios::app);

	for(std::vector<long>::iterator it = inters.begin(); it != inters.end(); ++it)
		fout<<(*it)<<"\n";

	fout.close();
	intersFilesCount++;
}
void Tools::UpdateIntersections(long id)
{
	static std::vector<long> intersections;

	intersections.push_back(id);

	if (intersections.size() > 5)
	{
		WriteIntersectionsFiles(intersections);
	}
}