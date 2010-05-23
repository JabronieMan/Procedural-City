#ifndef SIDEWALK_TEXTURE_H
#define SIDEWALK_TEXTURE_H

#include <glut.h>
#include <stdlib.h>
#include <stdio.h>

#define STEXTURE_WIDTH 128
#define STEXTURE_HEIGHT 128
#define CRACK_INTER 8

static GLubyte simage[STEXTURE_HEIGHT][STEXTURE_WIDTH][4];

class SidewalkTexture
{
public:
	GLuint stexId;
	SidewalkTexture();
private:
	void setGreyscale(int row, int col, GLubyte color);
	void createGLTexture();
	GLubyte randomColor();
};

void SidewalkTexture::setGreyscale(int row, int col, GLubyte color)
{
	simage[row][col][0] = color;
	simage[row][col][1] = color;
	simage[row][col][2] = color;
	simage[row][col][3] = (GLubyte) 255;
}

GLubyte SidewalkTexture::randomColor()
{
	if((rand() % 10) < 5)
		return (GLubyte) ((rand() % 100) + 20);
	else
		return (GLubyte) (255 - (rand() % 100) - 20);
}

void SidewalkTexture::createGLTexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &stexId);
	glBindTexture(GL_TEXTURE_2D, stexId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXTURE_WIDTH, 
		TEXTURE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
		image);
}

SidewalkTexture::SidewalkTexture()
{
	stexId = (GLuint)512;
	for(int row = 0; row < STEXTURE_HEIGHT; row++)
	{
		for(int col = 0; col < STEXTURE_WIDTH; col++)
		{
			if((row % CRACK_INTER) == 0 && row != 0)
			{
				setGreyscale(row, col, (GLubyte) 10);
			}
			else
			{
				if((col % CRACK_INTER) == 0 && col != 0)
				{
					setGreyscale(row, col, (GLubyte) 10);
				}
				else
				{
					setGreyscale(row, col, randomColor());
				}
			} 
		}
	}
	createGLTexture();
}

#endif
