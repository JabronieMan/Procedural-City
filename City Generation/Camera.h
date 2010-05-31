#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "Vec3.h"

#define PI_OVER2 1.57
#define MIN_CAM_HEIGHT 1.5
#define MAX_CAM_HEIGHT 500

// A basic 3D based camera, tailored for OpenGL
// Manages location, orientation, and viewing frustum

struct Camera
{
	Vec3 eye;		// Position of the camera
	Vec3 center;	// Point to focus on
	Vec3 up;		// Up direction
	
	double theta;	// For horizontal camera rotation
	double phi;		// For vertical camera rotation

	double halfWidth;	// Half width of the window
	double halfHeight;	// Half height of the window
	double zNear;		// Near viewing plane
	double zFar;		// Far viewing plane

	inline Camera()
	{
		eye = Vec3(100, 100, 50);
		center = Vec3(0, 0, 0);
		up = Vec3(0, 0, 1);

		theta = 0.0; phi = 0.0;

		halfWidth = 1.778;
		halfHeight = 1.0;
		zNear = 1.0;
		zFar = 10000.0;
	}

	inline Camera(Vec3 e, Vec3 c, Vec3 u)
	{
		eye = e;
		center = c;
		up = u;

		theta = 0.0; phi = 0.0;

		halfWidth = 1.778;
		halfHeight = 1.0;
		zNear = 1.0;
		zFar = 10000.0;
	}

	inline Camera(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ)
	{
		eye = Vec3(eyeX, eyeY, eyeZ);
		center = Vec3(centerX, centerY, centerZ);
		up = Vec3(upX, upY, upZ);

		theta = 0.0; phi = 0.0;

		halfWidth = 1.778;
		halfHeight = 1.0;
		zNear = 1.0;
		zFar = 10000.0;
	}
};

// Rotate the camera horiontally
// + amt rotate clockwise
// - amt rotate counterclockwise
inline void rotateHorizontal(Camera &cam, double amt)
{
	double newTheta = cam.theta - amt;
	if(newTheta > -PI_OVER2 && newTheta < PI_OVER2)
		cam.theta = newTheta;
	else
	{
		if(newTheta <= -PI_OVER2)
			cam.theta = -PI_OVER2;
		else
			cam.theta = PI_OVER2;
	}
}

// Rotate the camera vertically
// + amt rotate up
// - amt rotate down
inline void rotateVertical(Camera &cam, double amt)
{
	cam.phi += amt;
}

// Move the camera towards the center
// Negative amount moves away
inline void moveForward(Camera &cam, double amt)
{
	Vec3 direction = (cam.center - cam.eye) * amt;
	cam.center = cam.center + direction;
	cam.eye = cam.eye + direction;
	if(cam.eye.z < MIN_CAM_HEIGHT)
	{
		cam.center.z += MIN_CAM_HEIGHT - cam.eye.z;
		cam.eye.z += MIN_CAM_HEIGHT - cam.eye.z;
	}
}

// Orients the camera rotation based on the theta and phi
inline void calculateCameraRotation(Camera &cam)
{
	double radius = 7;
	double x, y, z;
	double l = radius * cos(cam.theta);

	z = radius * sin(cam.theta);
	y = l * cos(cam.phi);
	x = l * sin(cam.phi);

	cam.center = Vec3(x, y, z) + cam.eye;
}


#endif
