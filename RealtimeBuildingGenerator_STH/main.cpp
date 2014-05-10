#include "Building.h"
#include "Entity.h"


int main()
{
	// demo: roof=10, body=5, ground=1
	RBuilding ddd(10,5,1,0.0,0.0,12.000,8.000,15.000);
	ddd.bGenObj();

	system("pause");
	return 0;
}