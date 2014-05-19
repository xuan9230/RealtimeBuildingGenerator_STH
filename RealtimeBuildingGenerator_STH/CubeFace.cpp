#include "CubeFace.h"

cubeFace::cubeFace()
{
}

cubeFace::cubeFace(short int originAtt)
{
	switch (originAtt)
	{
	case 1:
		break;
	case 2:
	case 3:
	case 22:
	case 23:
		_attri = 5;
		break;
	default:
		_attri = 0;
		break;
	}
}

cubeFace::~cubeFace()
{
}

short int cubeFace::getAttri()
{
	return _attri;
}

void cubeFace::iniAttri(short int iniAtt)
{
		_attri = iniAtt;
}

void cubeFace::setAttri()
{
	switch (_attri)
	{
	case 0:
		break;
	case 1:
		_attri = 0;
		break;
	default:
		break;
	}
}
