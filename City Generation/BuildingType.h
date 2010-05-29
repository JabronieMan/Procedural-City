#ifndef _BUILDINGTYPE_H_
#define _BUILDINGTYPE_H_


//Max/Min Heights for each building
#define STANDARD_MAX_HEIGHT 30
#define STANDARD_MIN_HEIGHT 4

#define STACKED_MAX_HEIGHT 100
#define STACKED_MIN_HEIGHT 60

#define STATE_MAX_HEIGHT 200
#define STATE_MIN_HEIGHT 100

#define MODERN_MAX_HEIGHT 64
#define MODERN_MIN_HEIGHT 32

enum BuildingType
{
	STANDARD,
	STACKED,
	STATE,
	MODERN,
	SPIRE,
	FIB,
	NONE
};

#endif
