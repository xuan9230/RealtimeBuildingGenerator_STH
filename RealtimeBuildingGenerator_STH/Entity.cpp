#include "Entity.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

// Render the geometry - calculate coordinates and faces
// return the number of the vertices

int REntity::Render()
{
	switch (_entity_type)
	{
		// 0 for nothing to render
	case 0:
		break;

		// 1 for cuboid,uniform ground
	case 1:
	{
		int subUnitSize;
		
		cubeRenderGround();

		rectangleLeftSideSubdivide(2);			// left side
		for(vector<cubeFace>::iterator i=Face.begin()+indexF[0];i!=Face.end();i++)
			unitSideSubdivide(i-Face.begin());
		setWallCorner(0,FaceDivided.size());
		subUnitSize = FaceDivided.size();

     	rectangleRightSideSubdivide(2);			// right side
		for(vector<cubeFace>::iterator i=Face.begin()+indexF[1];i!=Face.end();i++)
			unitSideSubdivide(i-Face.begin());
		setWallCorner(subUnitSize,FaceDivided.size());
		subUnitSize = FaceDivided.size();
		
		rectangleFrontSubdivide(2);			// front

		int count = Face.end()-Face.begin()-indexF[2];
		count /= 2;
		for(vector<cubeFace>::iterator i=Face.begin()+indexF[2];i!=Face.end();i++)
		{
			
			if((i-Face.begin()-indexF[2])==count)
				unitFrontSubdivide(i-Face.begin(),true);
			else
				unitFrontSubdivide(i-Face.begin(),false);
		}

		setWallCorner(subUnitSize,FaceDivided.size());
		subUnitSize = FaceDivided.size();
		
		rectangleBackSubdivide(2);         // back
		for(vector<cubeFace>::iterator i=Face.begin()+indexF[3];i!=Face.end();i++)
			unitFrontSubdivide(i-Face.begin(),false);
		setWallCorner(subUnitSize,FaceDivided.size());

		setBand(FaceDivided.size());

		unitTBSubdivide(0);                 // top
		unitTBSubdivide(1);                 // bottom
	}
		break;


		// 5 for cuboid body
	case 5:
		cubeRenderBody();
		rectangleLeftSideSubdivide(2);			// left side
		for(vector<cubeFace>::iterator i=Face.begin()+indexF[0];i!=Face.end();i++)
			unitSideSubdivide(i-Face.begin());
		rectangleRightSideSubdivide(2);			// right side
		for(vector<cubeFace>::iterator i=Face.begin()+indexF[1];i!=Face.end();i++)
			unitSideSubdivide(i-Face.begin());
		rectangleFrontSubdivide(2);			// front
		for(vector<cubeFace>::iterator i=Face.begin()+indexF[2];i!=Face.end();i++)
			unitFrontSubdivide(i-Face.begin(),false);

		rectangleBackSubdivide(2);			// back
		for(vector<cubeFace>::iterator i=Face.begin()+indexF[3];i!=Face.end();i++)
			unitFrontSubdivide(i-Face.begin(),false);
		unitTBSubdivide(0);                 // top
		unitTBSubdivide(1);                 // bottom
		break;   
		
	default:
		break;
	}

	return Vertex.size();
}

void REntity::cubeRenderGround()
{
	coordinate temp;
	cubeFace ftemp;

	// calculate values for 8 vertices

	temp.x = _center_x-_width/2;
	temp.y = _center_y;
	temp.z = _center_z-_depth/2;
	Vertex.push_back(temp);

	temp.z += _depth;
	Vertex.push_back(temp);

	temp.x += _width;
	Vertex.push_back(temp);

	temp.z -= _depth;
	Vertex.push_back(temp);

	temp.x = _center_x-_width/2;
	temp.y = _center_y+_height;
	temp.z = _center_z-_depth/2;
	Vertex.push_back(temp);

	temp.z += _depth;
	Vertex.push_back(temp);

	temp.x += _width;
	Vertex.push_back(temp);

	temp.z -= _depth;
	Vertex.push_back(temp);

	// calculate for the order of 6 cubeFaces

	ftemp.v1 = 5;
	ftemp.v2 = 6;
	ftemp.v3 = 7;
	ftemp.v4 = 8;
	ftemp.iniAttri(1);
	Face.push_back(ftemp);

	ftemp.v1 = 1;
	ftemp.v2 = 2;
	ftemp.v3 = 3;
	ftemp.v4 = 4;
	ftemp.iniAttri(1);
	Face.push_back(ftemp);

	ftemp.v1 = 5;
	ftemp.v2 = 1;
	ftemp.v3 = 2;
	ftemp.v4 = 6;
	ftemp.iniAttri(2);
	Face.push_back(ftemp);

	ftemp.v1 = 7;
	ftemp.v2 = 3;
	ftemp.v3 = 4;
	ftemp.v4 = 8;
	ftemp.iniAttri(2);
	Face.push_back(ftemp);

	ftemp.v1 = 6;
	ftemp.v2 = 2;
	ftemp.v3 = 3;
	ftemp.v4 = 7;
	ftemp.iniAttri(3);
	Face.push_back(ftemp);

	ftemp.v1 = 8;
	ftemp.v2 = 4;
	ftemp.v3 = 1;
	ftemp.v4 = 5;
	ftemp.iniAttri(4);
	Face.push_back(ftemp);

}

void REntity::cubeRenderBody()
{
	coordinate temp;
	cubeFace ftemp;

	// calculate values for 8 vertices

	temp.x = _center_x-_width/2;
	temp.y = _center_y;
	temp.z = _center_z-_depth/2;
	Vertex.push_back(temp);

	temp.z += _depth;
	Vertex.push_back(temp);

	temp.x += _width;
	Vertex.push_back(temp);

	temp.z -= _depth;
	Vertex.push_back(temp);

	temp.x = _center_x-_width/2;
	temp.y = _center_y+_height;
	temp.z = _center_z-_depth/2;
	Vertex.push_back(temp);

	temp.z += _depth;
	Vertex.push_back(temp);

	temp.x += _width;
	Vertex.push_back(temp);

	temp.z -= _depth;
	Vertex.push_back(temp);

	// calculate for the order of 6 cubeFaces

	ftemp.v1 = 5;
	ftemp.v2 = 6;
	ftemp.v3 = 7;
	ftemp.v4 = 8;
	ftemp.iniAttri(21);
	Face.push_back(ftemp);

	ftemp.v1 = 1;
	ftemp.v2 = 2;
	ftemp.v3 = 3;
	ftemp.v4 = 4;
	ftemp.iniAttri(21);
	Face.push_back(ftemp);

	ftemp.v1 = 5;
	ftemp.v2 = 1;
	ftemp.v3 = 2;
	ftemp.v4 = 6;
	ftemp.iniAttri(22);
	Face.push_back(ftemp);

	ftemp.v1 = 7;
	ftemp.v2 = 3;
	ftemp.v3 = 4;
	ftemp.v4 = 8;
	ftemp.iniAttri(22);
	Face.push_back(ftemp);

	ftemp.v1 = 6;
	ftemp.v2 = 2;
	ftemp.v3 = 3;
	ftemp.v4 = 7;
	ftemp.iniAttri(23);
	Face.push_back(ftemp);

	ftemp.v1 = 8;
	ftemp.v2 = 4;
	ftemp.v3 = 1;
	ftemp.v4 = 5;
	ftemp.iniAttri(24);
	Face.push_back(ftemp);

}

REntity::REntity()
{
}

REntity::REntity(short int entityType,double center_x,double center_y,double center_z,double width,double depth,double height)
{

	_entity_type = entityType;
	_center_x = center_x;
	_center_y = center_y;
	_center_z = center_z;
	_width = width;
	_depth = depth;
	_height = height;
	Render();

}

REntity::~REntity()
{

}


// File operate, write the values into obj file

void REntity::GenObj(unsigned int snumber,int plusNum)
{
	
	 // redistribution of faces that have finishing attributes
	vector<simpleFace> att0;
	vector<simpleFace> att6;
	vector<simpleFace> att7;
	vector<simpleFace> att8;
	vector<simpleFace> att11;
	vector<simpleFace> att14;
	vector<simpleFace> att15;
	vector<simpleFace> att16;
	simpleFace sf;

	for(vector<cubeFace>::iterator i =FaceDivided.begin();i<FaceDivided.end();i++)
	{
		sf.v1 = (*i).v1;
		sf.v2 = (*i).v2;
		sf.v3 = (*i).v3;
		sf.v4 = (*i).v4;
		
		switch ((*i).getAttri())                    
		{
		case 0:
			att0.push_back(sf);
			break;
		case 6:
			att6.push_back(sf);
			break;
		case 7:
			att7.push_back(sf);
			break;
		case 8:
			att8.push_back(sf);
			break;
		case 11:
			att11.push_back(sf);
			break;
		case 14:
			att14.push_back(sf);
			break;
		case 15:
			att15.push_back(sf);
			break;
		case 16:
			att16.push_back(sf);
			break;
		default:
			break;
		}
	}

	// write into .obj files
	char enName[99];
	ofstream outObj;

	if(_entity_type == 1)                 // for uniform cuboid ground
	{		
		sprintf(enName,"output/Building/att0.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		outObj<<"# Original RBuilding faces. Attribute: 0"<<'\n';
		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att0.begin();i<att0.end();i++)
			outObj<<"f "<<(*i).v1<<' '<<(*i).v2<<' '<<(*i).v3<<' '<<(*i).v4<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att6.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		outObj<<"# Original RBuilding faces. Attribute: 6"<<'\n';
		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att6.begin();i<att6.end();i++)
			outObj<<"f "<<(*i).v1<<' '<<(*i).v2<<' '<<(*i).v3<<' '<<(*i).v4<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att7.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		outObj<<"# Original RBuilding faces. Attribute: 7"<<'\n';
		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att7.begin();i<att7.end();i++)
			outObj<<"f "<<(*i).v1<<' '<<(*i).v2<<' '<<(*i).v3<<' '<<(*i).v4<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att8.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		outObj<<"# Original RBuilding faces. Attribute: 8"<<'\n';
		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att8.begin();i<att8.end();i++)
			outObj<<"f "<<(*i).v1<<' '<<(*i).v2<<' '<<(*i).v3<<' '<<(*i).v4<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att11.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		outObj<<"# Original RBuilding faces. Attribute: 11"<<'\n';
		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att11.begin();i<att11.end();i++)
			outObj<<"f "<<(*i).v1<<' '<<(*i).v2<<' '<<(*i).v3<<' '<<(*i).v4<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att14.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		outObj<<"# Original RBuilding faces. Attribute: 14"<<'\n';
		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att14.begin();i<att14.end();i++)
			outObj<<"f "<<(*i).v1<<' '<<(*i).v2<<' '<<(*i).v3<<' '<<(*i).v4<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att15.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		outObj<<"# Original RBuilding faces. Attribute: 15"<<'\n';
		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att15.begin();i<att15.end();i++)
			outObj<<"f "<<(*i).v1<<' '<<(*i).v2<<' '<<(*i).v3<<' '<<(*i).v4<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att16.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		outObj<<"# Original RBuilding faces. Attribute: 16"<<'\n';
		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att16.begin();i<att16.end();i++)
			outObj<<"f "<<(*i).v1<<' '<<(*i).v2<<' '<<(*i).v3<<' '<<(*i).v4<<'\n';
		outObj.close();
	}

	else if(_entity_type == 5)                 // for cuboid body
	{
		sprintf(enName,"output/Building/att0.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att0.begin();i<att0.end();i++)
			outObj<<"f "<<(*i).v1 +plusNum<<' '<<(*i).v2 +plusNum<<' '<<(*i).v3 +plusNum<<' '<<(*i).v4 +plusNum<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att6.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att6.begin();i<att6.end();i++)
			outObj<<"f "<<(*i).v1 +plusNum<<' '<<(*i).v2 +plusNum<<' '<<(*i).v3 +plusNum<<' '<<(*i).v4 +plusNum<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att7.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att7.begin();i<att7.end();i++)
			outObj<<"f "<<(*i).v1 +plusNum<<' '<<(*i).v2 +plusNum<<' '<<(*i).v3 +plusNum<<' '<<(*i).v4 +plusNum<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att8.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att8.begin();i<att8.end();i++)
			outObj<<"f "<<(*i).v1 +plusNum<<' '<<(*i).v2 +plusNum<<' '<<(*i).v3 +plusNum<<' '<<(*i).v4 +plusNum<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att11.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att11.begin();i<att11.end();i++)
			outObj<<"f "<<(*i).v1 +plusNum<<' '<<(*i).v2 +plusNum<<' '<<(*i).v3 +plusNum<<' '<<(*i).v4 +plusNum<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att14.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att14.begin();i<att14.end();i++)
			outObj<<"f "<<(*i).v1 +plusNum<<' '<<(*i).v2 +plusNum<<' '<<(*i).v3 +plusNum<<' '<<(*i).v4 +plusNum<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att15.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att15.begin();i<att15.end();i++)
			outObj<<"f "<<(*i).v1 +plusNum<<' '<<(*i).v2 +plusNum<<' '<<(*i).v3 +plusNum<<' '<<(*i).v4 +plusNum<<'\n';
		outObj.close();

		sprintf(enName,"output/Building/att16.obj",snumber);
		outObj.open(enName,ios::out|ios::app);

		for(vector<coordinate>::iterator i = Vertex.begin();i<Vertex.end();i++)
			outObj<<"v "<<(*i).x<<' '<<(*i).y<<' '<<(*i).z<<'\n';
		for(vector<simpleFace>::iterator i =att16.begin();i<att16.end();i++)
			outObj<<"f "<<(*i).v1 +plusNum<<' '<<(*i).v2 +plusNum<<' '<<(*i).v3 +plusNum<<' '<<(*i).v4 +plusNum<<'\n';
		outObj.close();
	}	


}


// private member values set by "building"

void REntity::setValue(short int entityType,double center_x,double center_y,
					   double center_z,double width,double depth,double height,int style)
{
	_entity_type = entityType;
	_center_x = center_x;
	_center_y = center_y;
	_center_z = center_z;
	_width = width;
	_depth = depth;	  
	_height = height;  
	_style = style;
	_d = 0;
}

// Rectangle subdivide: only for height of one floor.       
// If it is body that has height of several floors, then processed seperately.
// Effect: like Attri num 2 -> 5.

void REntity::rectangleLeftSideSubdivide(int face)
{
	cubeFace f = Face[face];
	int vstart = Vertex.size()+1;            // where verteices subdivided start

	if(indexF.size()!=0)                    // start position of former indices decrease
		for(vector<int>::iterator i=indexF.begin();i!=indexF.end();i++)
			(*i)--;

	indexF.push_back(Face.size()-1);

	double edged1;                 // edged1 for making uniform segments

	// use quadratic function(style) to calculate _d and d2

	coordinate temp1 = Vertex[f.v1-1];
	coordinate temp2 = Vertex[f.v2-1];
	
	// subdivide based on _d
	
	if(_d==0) _d = 0.0155*_style+2.86;

	double rDepth = Vertex[f.v4-1].z - Vertex[f.v1-1].z;	


	int segNum = rDepth/_d;

	edged1 = (rDepth - (segNum-1)*_d)/2;

	temp1.z += edged1;
	Vertex.push_back(temp1);
	temp2.z += edged1;
	Vertex.push_back(temp2);

	for(int k=0;k<segNum-1;k++)
	{
		temp1.z += _d;
		Vertex.push_back(temp1);
		temp2.z += _d;
		Vertex.push_back(temp2);
	}
	temp1.z += edged1;
	Vertex.push_back(temp1);
	temp2.z += edged1;
	Vertex.push_back(temp2);

	Face.erase(Face.begin()+face);              // erase the original face

	// create new faces
	cubeFace tmp(Face[face].getAttri());

	tmp.v1 = f.v1;
	tmp.v2 = f.v2;
	tmp.v3 = vstart+1;
	tmp.v4 = vstart;
	Face.push_back(tmp);

	for(int k=0;k<segNum;k++)
	{
		tmp.v1 = vstart+k*2;
		tmp.v2 = tmp.v1+1;
		tmp.v3 = tmp.v2+2;
		tmp.v4 = tmp.v3-1;
		Face.push_back(tmp);
	}

}

void REntity::rectangleRightSideSubdivide(int face)
{
	cubeFace f = Face[face];
	int vstart = Vertex.size()+1;            // where verteices subdivided start

	if(indexF.size()!=0)                    // start position of former indices decrease
		for(vector<int>::iterator i=indexF.begin();i!=indexF.end();i++)
			(*i)--;

	indexF.push_back(Face.size()-1);

	double edged1;                 // edged1 for making uniform segments

	// use quadratic function(style) to calculate _d and d2

	coordinate temp1 = Vertex[f.v1-1];
	coordinate temp2 = Vertex[f.v2-1];
	
	// subdivide based on _d
	
	if(_d==0) _d = 0.0155*_style+2.86;

	double rDepth = Vertex[f.v4-1].z - Vertex[f.v1-1].z;	


	int segNum = (rDepth/_d)*(-1);

	edged1 = (rDepth + (segNum-1)*_d)/2;

	temp1.z += edged1;
	Vertex.push_back(temp1);
	temp2.z += edged1;
	Vertex.push_back(temp2);

	for(int k=0;k<segNum-1;k++)
	{
		temp1.z -= _d;
		Vertex.push_back(temp1);
		temp2.z -= _d;
		Vertex.push_back(temp2);
	}
	temp1.z += edged1;
	Vertex.push_back(temp1);
	temp2.z += edged1;
	Vertex.push_back(temp2);

	Face.erase(Face.begin()+face);              // erase the original face

	// create new faces
	cubeFace tmp(Face[face].getAttri());

	tmp.v1 = f.v1;
	tmp.v2 = f.v2;
	tmp.v3 = vstart+1;
	tmp.v4 = vstart;
	Face.push_back(tmp);

	for(int k=0;k<segNum;k++)
	{
		tmp.v1 = vstart+k*2;
		tmp.v2 = tmp.v1+1;
		tmp.v3 = tmp.v2+2;
		tmp.v4 = tmp.v3-1;
		Face.push_back(tmp);
	}

}

void REntity::rectangleFrontSubdivide(int face)
{
	cubeFace f = Face[face];
	int vstart = Vertex.size()+1;            // where vertices subdivided start
	
	if(indexF.size()!=0)                    // start position of former indices decrease
		for(vector<int>::iterator i=indexF.begin();i!=indexF.end();i++)
			(*i)--;

	indexF.push_back(Face.size()-1);

	double edged1;                 // edged1 for making uniform segments

	// use linear function(style) to calculate _d and d2

	coordinate temp1 = Vertex[f.v1-1];
	coordinate temp2 = Vertex[f.v2-1];
	
	// subdivide based on _d
	
	if(_d==0) _d = 0.0155*_style+2.86;

	double rDepth = Vertex[f.v4-1].x - Vertex[f.v1-1].x;	


	int segNum = rDepth/_d;

	edged1 = (rDepth - (segNum-1)*_d)/2;

	temp1.x += edged1;
	Vertex.push_back(temp1);
	temp2.x += edged1;
	Vertex.push_back(temp2);

	for(int k=0;k<segNum-1;k++)
	{
		temp1.x += _d;
		Vertex.push_back(temp1);
		temp2.x += _d;
		Vertex.push_back(temp2);
	}
	temp1.x += edged1;
	Vertex.push_back(temp1);
	temp2.x += edged1;
	Vertex.push_back(temp2);

	Face.erase(Face.begin()+face);              // erase the original face

	// create new faces
	cubeFace tmp(Face[face].getAttri());

	tmp.v1 = f.v1;
	tmp.v2 = f.v2;
	tmp.v3 = vstart+1;
	tmp.v4 = vstart;
	Face.push_back(tmp);

	for(int k=0;k<segNum;k++)
	{
		tmp.v1 = vstart+k*2;
		tmp.v2 = tmp.v1+1;
		tmp.v3 = tmp.v2+2;
		tmp.v4 = tmp.v3-1;
		Face.push_back(tmp);
	}

}

void REntity::rectangleBackSubdivide(int face)
{
	cubeFace f = Face[face];
	int vstart = Vertex.size()+1;            // where verteices subdivided start
	
	if(indexF.size()!=0)                    // start position of former indices decrease
		for(vector<int>::iterator i=indexF.begin();i!=indexF.end();i++)
			(*i)--;

	indexF.push_back(Face.size()-1);

	double edged1;                 // edged1 for making uniform segments

	// use linear function(style) to calculate _d and d2

	coordinate temp1 = Vertex[f.v1-1];
	coordinate temp2 = Vertex[f.v2-1];
	
	// subdivide based on _d
	
	if(_d==0) _d = 0.0155*_style+2.86;

	double rDepth = Vertex[f.v1-1].x - Vertex[f.v4-1].x;	

	int segNum = rDepth/_d;

	edged1 = (rDepth - (segNum-1)*_d)/2;

	temp1.x -= edged1;
	Vertex.push_back(temp1);
	temp2.x -= edged1;
	Vertex.push_back(temp2);

	for(int k=0;k<segNum-1;k++)
	{
		temp1.x -= _d;
		Vertex.push_back(temp1);
		temp2.x -= _d;
		Vertex.push_back(temp2);
	}
	temp1.x -= edged1;
	Vertex.push_back(temp1);
	temp2.x -= edged1;
	Vertex.push_back(temp2);

	Face.erase(Face.begin()+face);              // erase the original face

	// create new faces
	cubeFace tmp(Face[face].getAttri());

	tmp.v1 = f.v1;
	tmp.v2 = f.v2;
	tmp.v3 = vstart+1;
	tmp.v4 = vstart;
	Face.push_back(tmp);

	for(int k=0;k<segNum;k++)
	{
		tmp.v1 = vstart+k*2;
		tmp.v2 = tmp.v1+1;
		tmp.v3 = tmp.v2+2;
		tmp.v4 = tmp.v3-1;
		Face.push_back(tmp);
	}

}


// unit subdivide: render window and window ornament faces

void REntity::unitFrontSubdivide(int face, bool setDoor)
{
	cubeFace ftemp = Face[face];
	int startPos = Vertex.size()+1;
	
	double uwidth,uheight;
	uwidth = (Vertex[ftemp.v4-1].x - Vertex[ftemp.v1-1].x)/3.3;
	uheight = (Vertex[ftemp.v1-1].y - Vertex[ftemp.v2-1].y)/3.4;

	coordinate p1,p2,uv1,uv2;
	uv1 = Vertex[ftemp.v1-1];
	p1 = uv1;
	p1.y -= uheight;
	p2 = p1;
	p2.y -= uheight*1.4;
	uv2 = Vertex[ftemp.v2-1];

	Vertex.push_back(p1);
	Vertex.push_back(p2);

	uv1.x += uwidth;
	Vertex.push_back(uv1);
	p1.x += uwidth;
	Vertex.push_back(p1);
	p2.x += uwidth;
	Vertex.push_back(p2);
	uv2.x += uwidth;
	Vertex.push_back(uv2);

	uv1.x += uwidth*1.3;
	Vertex.push_back(uv1);
	p1.x += uwidth*1.3;
	Vertex.push_back(p1);
	p2.x += uwidth*1.3;
	Vertex.push_back(p2);
	uv2.x += uwidth*1.3;
	Vertex.push_back(uv2);

	uv1.x += uwidth;
	Vertex.push_back(uv1);
	p1.x += uwidth;
	Vertex.push_back(p1);
	p2.x += uwidth;
	Vertex.push_back(p2);
	uv2.x += uwidth;
	Vertex.push_back(uv2);

	// create new faces, and store into FaceDivided
	
	cubeFace newf;

	newf.v1 = ftemp.v1;
	newf.v2 = startPos;
	newf.v3 = startPos+3;
	newf.v4 = startPos+2;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);
	newf.v1 = startPos;
	newf.v2 = startPos+1;
	newf.v3 = startPos+4;
	newf.v4 = startPos+3;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);
	newf.v1 = startPos+1;
	newf.v2 = ftemp.v2;
	newf.v3 = startPos+5;
	newf.v4 = startPos+4;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);

	newf.v1 = startPos+2;
	newf.v2 = startPos+3;
	newf.v3 = startPos+7;
	newf.v4 = startPos+6;
	newf.iniAttri(7);
	FaceDivided.push_back(newf);
	newf.v1 = startPos+3;
	newf.v2 = startPos+4;
	newf.v3 = startPos+8;
	newf.v4 = startPos+7;
	if(setDoor==false)
		newf.iniAttri(6);
	else
		newf.iniAttri(8);
	FaceDivided.push_back(newf);
	newf.v1 = startPos+4;
	newf.v2 = startPos+5;
	newf.v3 = startPos+9;
	newf.v4 = startPos+8;
	if(setDoor==false)
		newf.iniAttri(11);
	else
		newf.iniAttri(8);
	FaceDivided.push_back(newf);

	newf.v1 = startPos+6;
	newf.v2 = startPos+7;
	newf.v3 = startPos+11;
	newf.v4 = startPos+10;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);
	newf.v1 = startPos+7;
	newf.v2 = startPos+8;
	newf.v3 = startPos+12;
	newf.v4 = startPos+11;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);
	newf.v1 = startPos+8;
	newf.v2 = startPos+9;
	newf.v3 = startPos+13;
	newf.v4 = startPos+12;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);

}

void REntity::unitSideSubdivide(int face)
{
	cubeFace ftemp = Face[face];
	int startPos = Vertex.size()+1;
	
	double uwidth,uheight;
	uwidth = (Vertex[ftemp.v4-1].z - Vertex[ftemp.v1-1].z)/3.3;
	uheight = (Vertex[ftemp.v1-1].y - Vertex[ftemp.v2-1].y)/3.4;

	coordinate p1,p2,uv1,uv2;
	uv1 = Vertex[ftemp.v1-1];
	p1 = uv1;
	p1.y -= uheight;
	p2 = p1;
	p2.y -= uheight*1.4;
	uv2 = Vertex[ftemp.v2-1];

	Vertex.push_back(p1);
	Vertex.push_back(p2);

	uv1.z += uwidth;
	Vertex.push_back(uv1);
	p1.z += uwidth;
	Vertex.push_back(p1);
	p2.z += uwidth;
	Vertex.push_back(p2);
	uv2.z += uwidth;
	Vertex.push_back(uv2);

	uv1.z += uwidth*1.3;
	Vertex.push_back(uv1);
	p1.z += uwidth*1.3;
	Vertex.push_back(p1);
	p2.z += uwidth*1.3;
	Vertex.push_back(p2);
	uv2.z += uwidth*1.3;
	Vertex.push_back(uv2);

	uv1.z += uwidth;
	Vertex.push_back(uv1);
	p1.z += uwidth;
	Vertex.push_back(p1);
	p2.z += uwidth;
	Vertex.push_back(p2);
	uv2.z += uwidth;
	Vertex.push_back(uv2);

	// create new faces, and store into FaceDivided
	
	cubeFace newf;

	newf.v1 = ftemp.v1;
	newf.v2 = startPos;
	newf.v3 = startPos+3;
	newf.v4 = startPos+2;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);
	newf.v1 = startPos;
	newf.v2 = startPos+1;
	newf.v3 = startPos+4;
	newf.v4 = startPos+3;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);
	newf.v1 = startPos+1;
	newf.v2 = ftemp.v2;
	newf.v3 = startPos+5;
	newf.v4 = startPos+4;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);

	newf.v1 = startPos+2;
	newf.v2 = startPos+3;
	newf.v3 = startPos+7;
	newf.v4 = startPos+6;
	newf.iniAttri(7);
	FaceDivided.push_back(newf);
	newf.v1 = startPos+3;
	newf.v2 = startPos+4;
	newf.v3 = startPos+8;
	newf.v4 = startPos+7;
	newf.iniAttri(6);
	FaceDivided.push_back(newf);
	newf.v1 = startPos+4;
	newf.v2 = startPos+5;
	newf.v3 = startPos+9;
	newf.v4 = startPos+8;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);

	newf.v1 = startPos+6;
	newf.v2 = startPos+7;
	newf.v3 = startPos+11;
	newf.v4 = startPos+10;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);
	newf.v1 = startPos+7;
	newf.v2 = startPos+8;
	newf.v3 = startPos+12;
	newf.v4 = startPos+11;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);
	newf.v1 = startPos+8;
	newf.v2 = startPos+9;
	newf.v3 = startPos+13;
	newf.v4 = startPos+12;
	newf.iniAttri(11);
	FaceDivided.push_back(newf);

}

void REntity::unitTBSubdivide(int face)
{
	cubeFace ftb = Face[face];
	ftb.iniAttri(0);
	FaceDivided.push_back(ftb);
}


// set wall corner: assign attributes to wall corner

void REntity::setWallCorner(int WCSeq,int unitNum)
{
	if(_style > 20)
	{
		FaceDivided[WCSeq].iniAttri(15);
		FaceDivided[WCSeq+1].iniAttri(15);
		FaceDivided[WCSeq+2].iniAttri(15);
		FaceDivided[unitNum-3].iniAttri(15);
		FaceDivided[unitNum-2].iniAttri(15);
		FaceDivided[unitNum-1].iniAttri(15);
	}
	else
	{
		FaceDivided[WCSeq].iniAttri(16);
		FaceDivided[WCSeq+1].iniAttri(16);
		FaceDivided[WCSeq+2].iniAttri(16);
		FaceDivided[unitNum-3].iniAttri(16);
		FaceDivided[unitNum-2].iniAttri(16);
		FaceDivided[unitNum-1].iniAttri(16);
	}
}

// set ground band: assign attributes to bands

void REntity::setBand(int BSeq)
{
	vector<cubeFace>::iterator i=FaceDivided.begin();
	short int cornerAttri;
	for(int x=2;x<FaceDivided.size();x+=3)
	{
		cornerAttri = (*(i+x)).getAttri();
		if(cornerAttri!=15 && cornerAttri!=16 && cornerAttri!=8)                     // avoid overlapping with corner and door
			(*(i+x)).iniAttri(14);
	}
}

// return the number of the vertices in this REntity

int REntity::verticesNum()
{
	return Vertex.size();
}