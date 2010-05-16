

#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "BuildingType.h"
#include "MyUtil.h"

class Building
{
private:
	Mat4x4 trans;
	GLint id;
	int levels;
	int width, depth; // Of the base to work with
	void generate();
	void generateStandard();

public: 
	BuildingType type;
	void draw() const;
	void increaseHeight();
	void decreaseHeight();

	inline Building(BuildingType t, int width, int depth, Mat4x4 position, GLint ident);
};

void Building::generateStandard()
{
	GLUquadric *qobj = gluNewQuadric();
	gluQuadricNormals( qobj, GL_TRUE );
	glNewList( id, GL_COMPILE );
	glEnable( GL_NORMALIZE );

	glEndList();
	gluDeleteQuadric( qobj );
}

void Building::generate()
{
	switch(type)
	{
	case STANDARD:
		generateStandard();
		break;
	}
}

inline Building::Building(BuildingType t, int w, int d, Mat4x4 position, GLint ident)
{
	type = t;
	width = w;
	depth = d;
	trans = position;
	id = ident;

}

#endif
