#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "Vec3.h"

// A basic 3D based camera, tailored for OpenGL

struct Camera
{
	Vec3 eye;		// Position of the camera
	Vec3 center;	// Point to focus on
	Vec3 up;		// Up direction

	inline Vec3()
	{
		eye = Vec3(0, 5, 5);
		center = Vec3(0, 0, 0);
		up = Vec3(0, 0, 1);
	}

	inline Vec3(Vec3 e, Vec3 c, Vec3 u)
	{
		eye = e;
		center = c;
		up = u;
	}

	inline Vec3(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ)
	{
		eye = Vec3(eyeX, eyeY, eyeZ);
		center = Vec3(centerX, centerY, centerZ);
		up = Vec3(upX, upY, upZ);
	}
}


#endif
