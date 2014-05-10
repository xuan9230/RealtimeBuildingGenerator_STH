#include <vector>
#include "Entity.h"

#ifndef BUILDING_H
#define BUILDING_H

using namespace std;

class RBuilding
{
private:

	// REntities used for maintaining mesh data for: Roof, Body and Ground

	REntity _Roof;
	vector<REntity> _Body;
	REntity _Ground;	

	int _GroundVerticesNum;
	int _BodyVerticesNum;

	// unique serial number for each building
	static unsigned int _snumber;

public:
	RBuilding(short int RoofType,short int BodyType,short int GroundType,
		double center_x,double center_z,double width,double depth,double height);
	~RBuilding();
	
	void bGenObj();

};


#endif