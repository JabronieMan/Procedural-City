#ifndef SKYBOX_H
#define SKYBOX_H

#define STARS_TEXTURE	10000000
#define SIDE_TEXTURE	20000000
#define BOTTOM_TEXTURE	30000000
#define SKY_BOX_ID		10000001
#define SKYBOX_SIDES 1024

#include "Texture.h"
#include "Vec3.h"

class Skybox
{
public:
	Skybox(Vec3 min, Vec3 max);
	Skybox();
	void draw();
private:
	Vec3 min, max;
	Texture stars;
	Texture side;
	Texture bottom;

	void constructBox();
};

void Skybox::draw()
{
	glCallList(SKY_BOX_ID);
}

void Skybox::constructBox()
{
	GLUquadric *qobj = gluNewQuadric();
	gluQuadricNormals( qobj, GL_TRUE );
	glNewList( SKY_BOX_ID, GL_COMPILE );
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, stars.id);

	// Roof
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);	glVertex3f(min.x, min.y, max.z);
	glTexCoord2f(1.0, 0.0);	glVertex3f(max.x, min.y, max.z);
	glTexCoord2f(1.0, 1.0);	glVertex3f(max.x, max.y, max.z);
	glTexCoord2f(0.0, 1.0);	glVertex3f(min.x, max.y, max.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, side.id);

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);	glVertex3f(max.x, min.y, min.z);
	glTexCoord2f(1.0, 1.0);	glVertex3f(max.x, min.y, max.z);
	glTexCoord2f(0.0, 1.0);	glVertex3f(min.x, min.y, max.z);
	glTexCoord2f(0.0, 0.0);	glVertex3f(min.x, min.y, min.z);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);	glVertex3f(max.x, max.y, max.z);
	glTexCoord2f(1.0, 0.0);	glVertex3f(max.x, max.y, min.z);
	glTexCoord2f(0.0, 0.0);	glVertex3f(min.x, max.y, min.z);
	glTexCoord2f(0.0, 1.0);	glVertex3f(min.x, max.y, max.z);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);	glVertex3f(max.x, min.y, min.z);
	glTexCoord2f(1.0, 0.0);	glVertex3f(max.x, max.y, min.z);
	glTexCoord2f(1.0, 1.0);	glVertex3f(max.x, max.y, max.z);
	glTexCoord2f(0.0, 1.0);	glVertex3f(max.x, min.y, max.z);
	glEnd();
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);	glVertex3f(min.x, max.y, min.z);
	glTexCoord2f(1.0, 0.0);	glVertex3f(min.x, min.y, min.z);
	glTexCoord2f(1.0, 1.0);	glVertex3f(min.x, min.y, max.z);
	glTexCoord2f(0.0, 1.0);	glVertex3f(min.x, max.y, max.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, bottom.id);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);	glVertex3f(min.x, min.y, min.z);
	glTexCoord2f(0.0, 1.0);	glVertex3f(min.x, max.y, min.z);
	glTexCoord2f(1.0, 1.0);	glVertex3f(max.x, max.y, min.z);
	glTexCoord2f(1.0, 0.0);	glVertex3f(max.x, min.y, min.z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEndList();
	gluDeleteQuadric( qobj );
}

Skybox::Skybox(Vec3 mn, Vec3 mx)
{
	min = mn;
	max = mx;
	stars = Texture(STARS_TEXTURE, SKY_BOX_TOP, SKYBOX_SIDES, SKYBOX_SIDES);
	side = Texture(SIDE_TEXTURE, SKY_BOX_SIDE, SKYBOX_SIDES, SKYBOX_SIDES);
	bottom = Texture(BOTTOM_TEXTURE, SKY_BOX_BOTTOM, 2, 2);
	constructBox();
}

Skybox::Skybox()
{
}

#endif //SKYBOX_H
