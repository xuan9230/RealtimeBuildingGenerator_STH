#include <vector>
#include "CubeFace.h"

#ifndef ENTITY_H
#define ENTITY_H

using namespace std;

struct coordinate
{
	double x;
	double y;
	double z;
};

struct simpleFace
{
	int v1;
	int v2;
	int v3;
	int v4;
};


class REntity 
{
private:

	vector<coordinate> Vertex;
	vector<coordinate> UV;
	vector<cubeFace> Face;
	vector<cubeFace> FaceDivided;      // final faces after division, with attributes
	vector<int> indexF;				   // store index for start faces. [0]-left side, [1]-right, [2]-front, [3]-back

	short int _entity_type;

	double _center_x;
	double _center_y;
	double _center_z;
	double _width;
	double _depth;
	double _height;

	double _d;                     // constant d: the size when subdividing rectangle and units. based on _style

	int _style;

	void cubeRenderGround();
	void cubeRenderBody();
	void rectangleLeftSideSubdivide(int face);
	void rectangleRightSideSubdivide(int face);
	void rectangleFrontSubdivide(int face);
	void rectangleBackSubdivide(int face);
	void unitSideSubdivide(int face);
	void unitFrontSubdivide(int face,bool setDoor);
	void unitTBSubdivide(int face);
	void setWallCorner(int WCSeq,int unitNum);
	void setBand(int BSeq);

public:
	REntity(short int entityType,double center_x,double center_y,double center_z,double width,double depth,double height);
	REntity();
	~REntity();

	int Render();
	void GenObj(unsigned int snumber,int plsuNum,int floors);
	int verticesNum();
	void setValue(short int entityType,double center_x,double center_y,double center_z,double width,double depth,double height,int style);
	
	
};



#endif