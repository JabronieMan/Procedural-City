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
#define SKIP_RANGE 90
#define SKIP_PROB 85

#define BLOCKS_MAX_HEIGHT 80
#define BLOCKS_MIN_HEIGHT 50

enum BuildingType
{
	STANDARD,
	STACKED,
	STATE,
	MODERN,
	BLOCKS,
	SPIRE,
	FIB,
	NONE
};

enum ModernFaces
{
	EIGHT = 8,
	TWELVE = 12,
	TWENTY_FOUR = 24,
	THIRTY_SIX = 36
};

ModernFaces randomModernFaces()
{
	int choice = rand() % 4;

	switch(choice)
	{
	case 0:
		return TWELVE;
	case 1:
		return TWENTY_FOUR;
	case 2:
		return THIRTY_SIX;
	case 3:
		return EIGHT;
	}
	return EIGHT;
}

#endif
