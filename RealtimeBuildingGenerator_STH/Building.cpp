#include "Building.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

unsigned int RBuilding::_snumber = 0;

double bhStandard(double &bHeight,int num)
{
	double bh[30];
	bh[0]=0;
	int i;
	if(num==1)
		for(int a=1,b=2,q=1;q<10;a+=2,b+=2,q++)            //at most 10 floors
		{
			bh[a] = 2.7*q;
			bh[b] = 3.1*q;
		}
	else
		for(int a=1,b=2,q=1;q<10;a+=2,b+=2,q++)            //at most 10 floors
		{
			bh[a] = 3.0*q;
			bh[b] = 5.5*q;
		}

	for(i=1;i<21;i++)
	{
		if((bHeight>bh[i])&&(bHeight<bh[i+1]))
			break;
	}

	if(i%2==0)
	{
		if((bh[i+1]-bHeight)>(bHeight-bh[i]))
			bHeight = bh[i]-0.2;
		else
			bHeight = bh[i+1]+0.2;
	}
	
	return bHeight;
	
}

void calHeight(double &height, double &gHeight,double &rHeight,int style, double &fHeight,int &floor)
{
	srand((unsigned)time(NULL));
	double bHeight;
	double i=0.0;

	if(style > 20)				// civil  ground:2.8-3.3  roof:4.5-7.0  fHeight:2.7-3.1
	{
		gHeight = (rand()%50 + 280)/100.0;
		rHeight = (rand()%250 + 450)/100.0;	
		bHeight = height - gHeight;
		bHeight = bhStandard(bHeight,1);
		while((fHeight<2.7)||(fHeight>3.1))
		{
			i = i+1.0;
			fHeight = bHeight/i;
		}
	}
	else                        // aulic   ground:3.2-4.0  roof:6.0-9.0  fHeight:3.0-5.5
	{	
		gHeight = (rand()%80 + 320)/100.0;
		rHeight = (rand()%300 + 600)/100.0;
		bHeight = height - gHeight;
		bHeight = bhStandard(bHeight,2);
		while((fHeight<3.0)||(fHeight>5.5))
		{
			i = i+1.0;
			fHeight = bHeight/i;
		}
	}	
	floor = (int)i;
}


RBuilding::RBuilding (short int RoofType,short int BodyType,short int GroundType,
		double center_x,double center_z,double width,double depth,double height)
{
	_snumber++;
	
	// generate style value
	srand((unsigned)time(NULL));
	int style = rand()%100;

	double gHeight,rHeight,fHeight=0.0;
	int floor;
	calHeight(height,gHeight,rHeight,style,fHeight,floor);                     
	

	// set values: type,x,y,z,width,depth,height,style_value
	_Roof.setValue(RoofType, center_x, height, center_z,width, depth, rHeight,style);
	REntity newBody;
	for(int i=0;i<floor;i++)
	{
		newBody.setValue(BodyType, center_x, gHeight+0.001+i*fHeight, center_z,width, depth, fHeight,style);       // +0.01 in case of overlapping
		_Body.push_back(newBody);
	}
	_Ground.setValue(GroundType, center_x, 0.0, center_z, width, depth, gHeight,style);
	
	_GroundVerticesNum = _Ground.Render();
	for(vector<REntity>::iterator i=_Body.begin();i!=_Body.end();i++)
		_BodyVerticesNum += (*i).Render();
	_Roof.Render();

}

RBuilding::~RBuilding()
{
}

void RBuilding::bGenObj()
{
	_Ground.GenObj(_snumber,0);
	int BVN=0;
	for(vector<REntity>::iterator i=_Body.begin();i!=_Body.end();i++)
	{
		(*i).GenObj(_snumber,_GroundVerticesNum+BVN);
		BVN += (*i).verticesNum();
	}
}

