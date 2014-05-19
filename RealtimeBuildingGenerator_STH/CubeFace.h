#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

class cubeFace                             
{
private:
	short int _attri;

public:
	unsigned int v1;                         // four integers, as index of Vertices
	unsigned int v2;
	unsigned int v3;
	unsigned int v4;
	short int getAttri();
	cubeFace();
	cubeFace(short int originAtt);
	~cubeFace();
	void iniAttri(short int iniAtt);
	void setAttri();
};
#endif