#include "Building.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

unsigned int RBuilding::_snumber = 0;

void calHeight(double &gHeight,double &rHeight,int style)
{
	srand((unsigned)time(NULL));

	if(style > 50)				// civil  ground:2.8-3.3  roof:4.5-7.0
	{
		gHeight = (rand()%50 + 280)/100.0;
		rHeight = (rand()%250 + 450)/100.0;
	}
	else                        // aulic   ground:3.2-5.0  roof:6.0-15.0
	{	
		gHeight = (rand()%180 + 320)/100.0;
		rHeight = (rand()%900 + 600)/100.0;
	}	
}


RBuilding::RBuilding (short int RoofType,short int BodyType,short int GroundType,
		double center_x,double center_z,double width,double depth,double height)
{
	_snumber++;
	
	// generate style value
	srand((unsigned)time(NULL));
	int style = rand()%100;

	double gHeight,rHeight;
	calHeight(gHeight,rHeight,style);

	// set values: type,x,y,z,width,depth,height,style_value
	_Roof.setValue(RoofType, center_x, height, center_z,width, depth, rHeight,style);
	_Body.setValue(BodyType, center_x, gHeight+0.001, center_z,width, depth, height-gHeight,style);              // +0.01 in case of overlapping
	_Ground.setValue(GroundType, center_x, 0.0, center_z, width, depth, gHeight,style);
	
	_GroundVerticesNum = _Ground.Render();
	_BodyVerticesNum = _Body.Render();
	_Roof.Render();

}

RBuilding::~RBuilding()
{
}

void RBuilding::bGenObj()
{
	_Ground.GenObj(_snumber,0);
	_Body.GenObj(_snumber,_GroundVerticesNum);	
}

