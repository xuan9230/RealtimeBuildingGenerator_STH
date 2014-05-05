#include "Building.h"
#include "Entity.h"


int main()
{
	// demo: roof=10, body=5, ground=1
	RBuilding ddd(10,5,1,0.0,0.0,12.0,8.000,10.000);
	ddd.bGenObj();

	system("pause");
	return 0;
}