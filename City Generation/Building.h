

#ifndef _BUILDING_H_
#define _BUILDING_H_

#define WINDOW_OFFSET 1000000
#define SIDEWALK_OFFSET 2000000

#define STANDARD_MAX_HEIGHT 30
#define STANDARD_MIN_HEIGHT 4
#define STACKED_MAX_HEIGHT 100
#define STACKED_MIN_HEIGHT 60
#define MODERN_MAX_HEIGHT 64
#define MODERN_MIN_HEIGHT 32

#include <math.h>
#include <vector>
#include "BuildingType.h"
#include "Texture.h"
#include "MyUtil.h"

class Building
{
private:
	Texture windows;
	Texture sidewalk;
	Mat4x4 trans;
	GLint id;
	int levels;
	int width, depth; // Of the base to work with
	void generate();
	void drawBox(const Vec3& min, const Vec3& max);
	void drawBoxTextured(const Vec3& min, const Vec3& max, double maxW, double maxD, double maxHeight);
	void drawSidewalk();
	void drawHelipad(double height);
	void generateStandard();
	void generateStacked();
	void generateState();
	void generateModern();
	void generateBlocks();
	void generateWindows(int width, int height);
	void generateSidewalk();

public: 
	BuildingType type;
	void draw() const;
	void increaseHeight();
	void decreaseHeight();

	inline Building(BuildingType t, int width, int depth, Mat4x4 position, GLuint ident);
};

void Building::draw() const
{
	glPushMatrix();
	glMultMatrix(trans);
	glCallList(id);
	glPopMatrix();
}

void Building::drawBox(const Vec3& min, const Vec3& max)
{
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUAD_STRIP);
	glVertex(min);
	glVertex3f(min.x, min.y, max.z);
	glVertex3f(max.x, min.y, min.z);
	glVertex3f(max.x, min.y, max.z);
	glVertex3f(max.x, max.y, min.z);
	glVertex(max);
	glVertex3f(min.x, max.y, min.z);
	glVertex3f(min.x, max.y, max.z);
	glVertex(min);
	glVertex3f(min.x, min.y, max.z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex(min);
	glVertex3f(max.x, min.y, min.z);
	glVertex3f(max.x, max.y, min.z);
	glVertex3f(min.x, max.y, min.z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(min.x, min.y, max.z);
	glVertex3f(min.x, max.y, max.z);
	glVertex(max);
	glVertex3f(max.x, min.y, max.z);
	glEnd();
	glEnable(GL_TEXTURE_2D);

}

void Building::drawBoxTextured(const Vec3& min, const Vec3& max, double maxW, double maxD, double maxHeight)
{
	double w = max.x - min.x;
	double d = max.y - min.y;
	double height = (max.z - min.z) / levels;

	double textureRatio = (w >= d? w/maxW : w/maxD);

	glBegin(GL_POLYGON);
	glTexCoord2f(textureRatio, 0.0);	glVertex3f(max.x, min.y, min.z);
	glTexCoord2f(0.0, 0.0);				glVertex3f(min.x, min.y, min.z);
	glTexCoord2f(0.0, height);			glVertex3f(min.x, min.y, max.z);
	glTexCoord2f(textureRatio, height);	glVertex3f(max.x, min.y, max.z);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(textureRatio, height);	glVertex3f(max.x, max.y, max.z);
	glTexCoord2f(0.0, height);			glVertex3f(min.x, max.y, max.z);
	glTexCoord2f(0.0, 0.0);				glVertex3f(min.x, max.y, min.z);
	glTexCoord2f(textureRatio, 0.0);	glVertex3f(max.x, max.y, min.z);
	glEnd();

	textureRatio = (d >= w? d/maxD : d/maxW);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);				glVertex3f(max.x, min.y, min.z);
	glTexCoord2f(0.0, height);			glVertex3f(max.x, min.y, max.z);
	glTexCoord2f(textureRatio, height);	glVertex3f(max.x, max.y, max.z);
	glTexCoord2f(textureRatio, 0.0);	glVertex3f(max.x, max.y, min.z);
	glEnd();
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);				glVertex3f(min.x, max.y, min.z);
	glTexCoord2f(0.0, height);			glVertex3f(min.x, max.y, max.z);
	glTexCoord2f(textureRatio, height);	glVertex3f(min.x, min.y, max.z);
	glTexCoord2f(textureRatio, 0.0);	glVertex3f(min.x, min.y, min.z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	// Roof
	glBegin(GL_POLYGON);
	glVertex3f(max.x, min.y, max.z);
	glVertex3f(min.x, min.y, max.z);
	glVertex3f(min.x, max.y, max.z);
	glVertex3f(max.x, max.y, max.z);
	glEnd();
	glEnable(GL_TEXTURE_2D);

}

void Building::drawSidewalk()
{
	double w,d;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sidewalk.id);
	w = (width / 2.0) + 0.2;
	d = (depth / 2.0) + 0.2;

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);		glVertex3f(w, d, 0.2);
	glTexCoord2f(1.0, 0.0);		glVertex3f(w, -d, 0.2);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-w, -d, 0.2);
	glTexCoord2f(0.0, 1.0);		glVertex3f(-w, d, 0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-w, d, 0.0);
	glTexCoord2f(1.0, 0.0);		glVertex3f(w, d, 0.0);
	glTexCoord2f(1.0, 0.2/w);	glVertex3f(w, d, 0.2);
	glTexCoord2f(0.0, 0.2/w);	glVertex3f(-w, d, 0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-w, -d, 0.0);
	glTexCoord2f(0.0, 0.2/w);	glVertex3f(-w, -d, 0.2);
	glTexCoord2f(1.0, 0.2/w);	glVertex3f(w, -d, 0.2);
	glTexCoord2f(1.0, 0.0);		glVertex3f(w, -d, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-w, -d, 0.0);
	glTexCoord2f(0.0, 1.0);		glVertex3f(-w, d, 0.0);
	glTexCoord2f(0.2/d, 1.0);	glVertex3f(-w, d, 0.2);
	glTexCoord2f(0.2/d, 0.0);	glVertex3f(-w, -d, 0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);		glVertex3f(w, -d, 0.0);
	glTexCoord2f(0.2/d, 0.0);	glVertex3f(w, -d, 0.2);
	glTexCoord2f(0.2/d, 1.0);	glVertex3f(w, d, 0.2);
	glTexCoord2f(0.0, 1.0);		glVertex3f(w, d, 0.0);
	glEnd();
}

void Building::drawHelipad(double height)
{
	height = height + 0.01; // A little offset to put it above the roof (no Z fighting).
	glMaterial( GL_AMBIENT  , Color(0.9,0.1,0.1) );
	glMaterial( GL_DIFFUSE  , Color(0.9,0.1,0.1) );

	// The circle around
	glBegin(GL_QUAD_STRIP);
	for(int angle = 360; angle >= 0; angle -= 10)
	{
		glVertex3f(-sinf((float)angle * DEGREES_TO_RADIANS)*2, cosf((float)angle * DEGREES_TO_RADIANS)*2, height);
		glVertex3f(-sinf((float)angle * DEGREES_TO_RADIANS)*2.20, cosf((float)angle * DEGREES_TO_RADIANS)*2.20, height);
	}
	glEnd();

	glMaterial( GL_AMBIENT  , Color(0.9,0.9,0.9) );
	glMaterial( GL_DIFFUSE  , Color(0.9,0.9,0.9) );

	// The 'H'
	glBegin(GL_QUADS);
	glVertex3f(-1, -1, height);
	glVertex3f(-1, 1, height);
	glVertex3f(-0.5, 1, height);
	glVertex3f(-0.5, -1, height);

	glVertex3f(-0.5, -0.25, height);
	glVertex3f(-0.5, 0.25, height);
	glVertex3f(0.5, 0.25, height);
	glVertex3f(0.5, -0.25, height);

	glVertex3f(0.5, -1, height);
	glVertex3f(0.5, 1, height);
	glVertex3f(1, 1, height);
	glVertex3f(1, -1, height);
	glEnd();

	glMaterial( GL_AMBIENT  , Color(0.02,0.02,0.02) );
	glMaterial( GL_DIFFUSE  , Color(0.1,0.1,0.1) );
}

void Building::generateStandard()
{
	double w = (width / 2) - ((rand() % (width / 2)) + 1) / 2;
	double d = (depth / 2) - ((rand() % (depth / 2)) + 1) / 2;
	generateWindows(w >= d ? w*2 : d*2, levels);

	GLUquadric *qobj = gluNewQuadric();
	gluQuadricNormals( qobj, GL_TRUE );
	glNewList( id, GL_COMPILE );
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, windows.id);

	Vec3 min = Vec3(-w, -d, 0);
	Vec3 max = Vec3(w, d, levels);
	double maxW = w*2;
	double maxD = d*2;

	drawBoxTextured(min, max, maxW, maxD, levels);

	drawSidewalk();

	glDisable(GL_TEXTURE_2D);

	glEndList();
	gluDeleteQuadric( qobj );
}

void Building::generateStacked()
{
	double w = (width / 2) - ((rand() % 3));
	double d = (depth / 2) - ((rand() % 3));

	//These tiers are to calculate the height of the various sections
	int base = ((rand() % 25) + 50);
	float tier1 = levels * (base / 100.0);
	if((int)tier1 % 2 != 0)
		tier1++;

	base = 100 - base;
	float tier2Off = levels * ((base / 2)/100.0);
	float tier2 = tier1 + tier2Off;
	float tier3 = tier2 + tier2Off;

	generateWindows(w >= d ? w*2 : d*2, tier1);

	GLUquadric *qobj = gluNewQuadric();
	gluQuadricNormals( qobj, GL_TRUE );
	glNewList( id, GL_COMPILE );
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, windows.id);

	Vec3 min = Vec3(-w, -d, 0);
	Vec3 max = Vec3(w, d, tier1);
	double maxW = w*2;
	double maxD = d*2;

	drawBoxTextured(min, max, maxW, maxD, tier1);

	drawBox(Vec3(-w-0.3, -d-0.3, tier1-0.5), Vec3(w+0.3, d+0.3, tier1+0.5));

	glEnable(GL_TEXTURE_2D);

	w -= 1;
	d -= 1;

	min = Vec3(-w, -d, tier1);
	max = Vec3(w, d, tier2);

	drawBoxTextured(min, max, maxW, maxD, tier1);

	drawBox(Vec3(-w-0.3, -d-0.3, tier2-0.5), Vec3(w+0.3, d+0.3, tier2+0.5));

	glEnable(GL_TEXTURE_2D);

	w -= 1;
	d -= 1;
	min = Vec3(-w, -d, tier2);
	max = Vec3(w, d, tier3);

	drawBoxTextured(min, max, maxW, maxD, tier1);

	drawBox(Vec3(-w-0.3, -d-0.3, tier3-0.5), Vec3(w+0.3, d+0.3, tier3+0.5));

	drawSidewalk();

	glDisable(GL_TEXTURE_2D);

	if(tier3 > MIN_HELIPAD_HEIGHT && ((rand() % 100) > 85))
	{
		drawHelipad(tier3+0.5);
	}

	glEndList();
	gluDeleteQuadric( qobj );
}

void Building::generateState()
{
	double modSquare = ((rand() % (width / 4)) + 1) / 2;
	double w = (width / 4) + modSquare;
	double d = (depth / 4) + modSquare;
	generateWindows(w >= d ? w*2 : d*2, levels);

	GLUquadric *qobj = gluNewQuadric();
	gluQuadricNormals( qobj, GL_TRUE );
	glNewList( id, GL_COMPILE );
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, windows.id);

	drawBoxTextured(Vec3(-w, -d, 0), Vec3(w, d, levels), w*2, d*2, levels);

	drawSidewalk();

	glDisable(GL_TEXTURE_2D);

	if(levels > MIN_HELIPAD_HEIGHT && ((rand() % 100) > 95))
	{
		drawHelipad(levels);
	}

	glEndList();
	gluDeleteQuadric( qobj );
}

void Building::generateModern()
{
	double w = (width / 2) - rand()%4;
	double d = (depth / 2) - rand()%4;
	generateWindows(8, levels);

	GLUquadric *qobj = gluNewQuadric();
	gluQuadricNormals( qobj, GL_TRUE );
	glNewList( id, GL_COMPILE );
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, windows.id);

	Vec3 lowOld = Vec3(0, 0, 0.0);
	Vec3 highOld = Vec3(0, 0, levels);
	float x, y;

	ModernFaces faces = randomModernFaces();
	int angleAdjust = 360 / faces;
	double textX = (THIRTY_SIX / faces) * 0.25;
	double minX = 0, maxX = textX;

	bool flip = true, skipped = false;
	Vec3 newLow;
	std::vector<int> skips;
	for(int angle = 360; angle >= 0; angle -= angleAdjust)
	{
		x = -sinf((float)angle * DEGREES_TO_RADIANS) * w;
		y = cosf((float)angle * DEGREES_TO_RADIANS) * d;
		if(!(lowOld.x == 0 && lowOld.y == 0))
		{
			if(skipped)
			{
				minX = 0.0;
				maxX = 1.0;
				skipped = false;
			}
			
			glBegin(GL_POLYGON);
			if(flip)
			{
				glTexCoord2f(maxX, 1.0);		glVertex3f(x, y, levels);
				glTexCoord2f(minX, 1.0);		glVertex(highOld);
				glTexCoord2f(minX, 0.0);		glVertex(lowOld);
				glTexCoord2f(maxX, 0.0);		glVertex3f(x, y, 0.0);
			}
			else
			{
				glTexCoord2f(maxX, 0.0);		glVertex3f(x, y, levels);
				glTexCoord2f(minX, 0.0);		glVertex(highOld);
				glTexCoord2f(minX, 1.0);		glVertex(lowOld);
				glTexCoord2f(maxX, 1.0);		glVertex3f(x, y, 0.0);
			}
			glEnd();

			flip = !flip;
			if(textX < 1.0)
			{
				double start = rand() % (int)((1.0 - textX) * 4);
				minX = start * 0.25;
				maxX = minX + textX;
			}
		}
		lowOld.x = x;
		lowOld.y = y;
		highOld.x = x;
		highOld.y = y;

		if(angle > SKIP_RANGE)
		{
			if(rand() % 100 > SKIP_PROB)
			{
				skips.push_back(angle);
				angle -= SKIP_RANGE;
				skipped = true;
			}
		}
	}

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, levels);
	size_t skipdex = 0;
	for(int angle = 360; angle >= 0; angle -= angleAdjust)
	{
		x = -sinf((float)angle * DEGREES_TO_RADIANS) * w;
		y = cosf((float)angle * DEGREES_TO_RADIANS) * d;
		glVertex3f(x, y, levels);

		if(skips.size() > skipdex)
		{
			if(angle == skips[skipdex])
			{
				angle -= SKIP_RANGE;
				skipdex++;
			}
		}
	}
	glEnd();

	drawSidewalk();
	glDisable(GL_TEXTURE_2D);
	glEndList();
	gluDeleteQuadric( qobj );
}

void Building::generateBlocks()
{
	double w = (width / 4) + ((rand() % 5)-2);
	double d = (depth / 4) + ((rand() % 5)-2);
	Vec2 center(((rand() % 5)-2), ((rand() % 5)-2));

	generateWindows(w >= d ? w*2 : d*2, levels);

	GLUquadric *qobj = gluNewQuadric();
	gluQuadricNormals( qobj, GL_TRUE );
	glNewList( id, GL_COMPILE );
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, windows.id);

	int height = levels;
	Vec3 min = Vec3(center.x - w, center.y - d, 0.0);
	Vec3 max = Vec3(center.x + w, center.y + d, height);
	double maxW = w*2;
	double maxD = d*2;
	drawBoxTextured(min, max, maxW, maxD, levels);
	
	for(int i = 0; i < 3; i++)
	{
		w = (width / 4) + ((rand() % 5)-2);
		d = (depth / 4) + ((rand() % 5)-2);
		if(w > maxW/2)
		{
			w -= maxW/2 * (rand()/(float)RAND_MAX);
		}
		if(d > maxD/2)
		{
			d -= maxD/2 * (rand()/(float)RAND_MAX);
		}
		height = rand() % (levels - 5);
		center = Vec2(((rand() % 7)-3), ((rand() % 7)-3));
		min = Vec3(center.x - w - (rand()/((float)RAND_MAX*16)), center.y - d - (rand()/((float)RAND_MAX*16)), 0.0);
		max = Vec3(center.x + w - (rand()/((float)RAND_MAX*16)), center.y + d - (rand()/((float)RAND_MAX*16)), height);
		drawBoxTextured(min, max, maxW, maxD, levels);
	}

	drawSidewalk();
	glDisable(GL_TEXTURE_2D);
	glEndList();
	gluDeleteQuadric( qobj );
}

void Building::generateWindows(int width, int height)
{
	windows = Texture(id + WINDOW_OFFSET, WINDOWS, (width / 2) * WINDOW_WIDTH, (height / 2) * WINDOW_HEIGHT);
}

void Building::generateSidewalk()
{
	sidewalk = Texture(id + SIDEWALK_OFFSET, SIDEWALK, 64, 64);
}

void Building::generate()
{
	generateSidewalk();
	switch(type)
	{
	case STANDARD:
		levels = rand() % (STANDARD_MAX_HEIGHT - STANDARD_MIN_HEIGHT) + STANDARD_MIN_HEIGHT;
		generateStandard();
		break;
	case STACKED:
		levels = rand() % (STACKED_MAX_HEIGHT - STACKED_MIN_HEIGHT) + STACKED_MIN_HEIGHT;
		generateStacked();
		break;
	case STATE:
		levels = rand() % (STATE_MAX_HEIGHT - STATE_MIN_HEIGHT) + STATE_MIN_HEIGHT;
		generateState();
		break;
	case MODERN:
		levels = rand() % (MODERN_MAX_HEIGHT - MODERN_MIN_HEIGHT) + MODERN_MIN_HEIGHT;
		generateModern();
		break;
	case BLOCKS:
		levels = rand() % (BLOCKS_MAX_HEIGHT - BLOCKS_MIN_HEIGHT) + BLOCKS_MIN_HEIGHT;
		generateBlocks();
		break;
	}
}

inline Building::Building(BuildingType t, int w, int d, Mat4x4 position, GLuint ident)
{
	type = t;
	width = w;
	depth = d;
	trans = position;
	id = ident;

	generate();
}

#endif
