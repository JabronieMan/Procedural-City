#ifndef TEXTURE_H
#define TEXTURE_H

#include <glut.h>
#include <stdlib.h>
#include <stdio.h>

#define GL_CLAMP_TO_EDGE 0x812F
#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 256
#define WINDOW_HEIGHT 8
#define WINDOW_WIDTH 8
#define WINDOW_BEZEL 2

static GLubyte image[TEXTURE_HEIGHT][TEXTURE_WIDTH][4];

class Texture
{
public:
	GLuint texId;

	Texture();
private:
	void setWhite(int row, int col);
	void setBlack(int row, int col);
	void setGrayscale(int row, int col, GLubyte color);
	void colorWindow(int xOffset, int yOffset);
	void createGLTexture();
	GLubyte randomColor();
};

void Texture::setGrayscale(int row, int col, GLubyte color)
{
	image[row][col][0] = color;
	image[row][col][1] = color;
	image[row][col][2] = color;
	image[row][col][3] = (GLubyte) 255;
}

void Texture::setBlack(int row, int col)
{
	setGrayscale(row, col, (GLubyte) 0);
}

void Texture::setWhite(int row, int col)
{
	setGrayscale(row, col, (GLubyte) 255);
}

GLubyte Texture::randomColor()
{
	int num = rand() % 100;
	if(num < 50)
	{
		return (GLubyte) 10;
	}
	else if (num < 60)
	{
		return (GLubyte) 80;
	}
	else if(num < 85)
	{
		return (GLubyte) 160;
	}
	else
	{
		return (GLubyte) 245;
	}
}

void Texture::createGLTexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

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

void Texture::colorWindow(int xOffset, int yOffset)
{
	int xStart = xOffset * WINDOW_HEIGHT;
	int yStart = yOffset * WINDOW_WIDTH;
	int xPos, yPos;
	GLubyte color = randomColor();
	GLubyte randMod;
	for(int row = 0; row < WINDOW_HEIGHT; row++)
	{
		for(int col = 0; col < WINDOW_WIDTH; col++)
		{
			xPos = xStart + row;
			yPos = yStart + col;
			if(row % WINDOW_HEIGHT < WINDOW_BEZEL)
			{
				setBlack(xPos, yPos);
			}
			else if(row % WINDOW_HEIGHT >= WINDOW_HEIGHT - WINDOW_BEZEL)
			{
				setBlack(xPos, yPos);
			}
			else
			{
				if(col % WINDOW_WIDTH < WINDOW_BEZEL)
				{
					setBlack(xPos, yPos);
				}
				else if(col % WINDOW_WIDTH >= WINDOW_WIDTH - WINDOW_BEZEL)
				{
					setBlack(xPos, yPos);
				}
				else
				{
					randMod = (GLubyte) ((color % col) / ((rand() % 4)+1))*color;
					setGrayscale(xPos, yPos, color-randMod);
				}
			} 
		}
	}
}

Texture::Texture()
{
	texId = (GLuint)101;
	for(int row = 0; row < TEXTURE_HEIGHT / WINDOW_HEIGHT; row++)
	{
		for(int col = 0; col < TEXTURE_WIDTH / WINDOW_WIDTH; col++)
		{
			colorWindow(row, col);
		}
	}
	createGLTexture();
}

#endif
