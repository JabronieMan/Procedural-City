#ifndef TEXTURE_H
#define TEXTURE_H

#include <glut.h>
#include <stdlib.h>
#include <stdio.h>

#define TEXTURE_DIM 512
#define WINDOW_HEIGHT 8
#define WINDOW_WIDTH 8

static GLubyte image[TEXTURE_DIM][TEXTURE_DIM][4];

class Texture
{
public:
	GLuint texId;

	Texture();
private:
	void setWhite(int row, int col);
	void setBlack(int row, int col);
	void createGLTexture();
};

void Texture::setBlack(int row, int col)
{
	image[row][col][0] = (GLubyte) 0;
	image[row][col][1] = (GLubyte) 0;
	image[row][col][2] = (GLubyte) 0;
	image[row][col][3] = (GLubyte) 255;
}

void Texture::setWhite(int row, int col)
{
	image[row][col][0] = (GLubyte) 255;
	image[row][col][1] = (GLubyte) 255;
	image[row][col][2] = (GLubyte) 255;
	image[row][col][3] = (GLubyte) 255;
}

void Texture::createGLTexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
		GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
		GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXTURE_DIM, 
		TEXTURE_DIM, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
		image);
}

Texture::Texture()
{
	texId = (GLuint)101;

	for(int row = 0; row < TEXTURE_DIM; row++)
	{
		for(int col = 0; col < TEXTURE_DIM; col++)
		{
			if(row % WINDOW_HEIGHT <= 1)
			{
				setBlack(row, col);
			}
			else if(row % WINDOW_HEIGHT >= 6)
			{
				setBlack(row, col);
			}
			else
			{
				if(col % WINDOW_WIDTH <= 1)
				{
					setBlack(row, col);
				}
				else if(col % WINDOW_WIDTH >= 6)
				{
					setBlack(row, col);
				}
				else
				{
					setWhite(row, col);
				}
			}
		}
	}

	createGLTexture();
}

#endif
