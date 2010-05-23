#ifndef TEXTURE_H
#define TEXTURE_H

#include <glut.h>
#include <stdlib.h>
#include <stdio.h>

#define GL_CLAMP_TO_EDGE 0x812F

//Window Texture 
#define WINDOW_TEXTURE_WIDTH 64
#define WINDOW_TEXTURE_HEIGHT 256
#define WINDOW_HEIGHT 8
#define WINDOW_WIDTH 8
#define WINDOW_BEZEL 2

//Sidewalk Texture
#define SIDEWALK_TEXTURE_WIDTH 128
#define SIDEWALK_TEXTURE_HEIGHT 128
#define CRACK_INTER 16

enum TextureType
{
	WINDOWS,
	SIDEWALK
};

class Texture
{
public:
	GLuint id;
	Texture();
	Texture(GLuint name, TextureType type);
private:
	GLubyte * image;
	float randR, randG, randB; // Color offsets that can be used as a sudo-filter
	void initRandomColors();
	void setGreyscale(int row, int col, int width, GLubyte color, bool filter);
	void colorWindow(int xOffset, int yOffset);
	void constructWindows();
	void pourSidewalk();
	void createGLTexture();
	GLubyte randomWindowColor();
	GLubyte randomSidewalkColor();
};

void Texture::setGreyscale(int row, int col, int width, GLubyte color, bool filter)
{
	int offset = row * width * 4 + col * 4;

	*(image + offset) = color * (filter? randR : 1.0);
	*(image + (++offset)) = color * (filter? randB : 1.0);
	*(image + (++offset)) = color * (filter? randG : 1.0);
	*(image + (++offset)) = (GLubyte) 255;
}

GLubyte Texture::randomWindowColor()
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

GLubyte Texture::randomSidewalkColor()
{
	if((rand() % 10) < 5)
		return (GLubyte) ((rand() % 100) + 20);
	else
		return (GLubyte) (255 - (rand() % 100) - 20);
}

void Texture::initRandomColors()
{
	randR = ((float)rand())/RAND_MAX;
	randG = ((float)rand())/RAND_MAX;
	randB = ((float)rand())/RAND_MAX;
}

void Texture::createGLTexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_TEXTURE_WIDTH, 
		WINDOW_TEXTURE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
		image);
}

void Texture::colorWindow(int xOffset, int yOffset)
{
	int xStart = xOffset * WINDOW_HEIGHT;
	int yStart = yOffset * WINDOW_WIDTH;
	int xPos, yPos;
	GLubyte color = randomWindowColor();
	GLubyte randMod;
	for(int row = 0; row < WINDOW_HEIGHT; row++)
	{
		for(int col = 0; col < WINDOW_WIDTH; col++)
		{
			xPos = xStart + row;
			yPos = yStart + col;
			if(row % WINDOW_HEIGHT < WINDOW_BEZEL)
			{
				setGreyscale(xPos, yPos, WINDOW_TEXTURE_WIDTH, (GLubyte) 0, true);
			}
			else if(row % WINDOW_HEIGHT >= WINDOW_HEIGHT - WINDOW_BEZEL)
			{
				setGreyscale(xPos, yPos, WINDOW_TEXTURE_WIDTH, (GLubyte) 0, true);
			}
			else
			{
				if(col % WINDOW_WIDTH < WINDOW_BEZEL)
				{
					setGreyscale(xPos, yPos, WINDOW_TEXTURE_WIDTH, (GLubyte) 0, true);
				}
				else if(col % WINDOW_WIDTH >= WINDOW_WIDTH - WINDOW_BEZEL)
				{
					setGreyscale(xPos, yPos, WINDOW_TEXTURE_WIDTH, (GLubyte) 0, true);
				}
				else
				{
					randMod = (GLubyte) ((color % col) / ((rand() % 4)+1))*color;
					setGreyscale(xPos, yPos, WINDOW_TEXTURE_WIDTH, color-randMod, true);
				}
			} 
		}
	}
}

void Texture::pourSidewalk()
{
	image = (GLubyte *)malloc(SIDEWALK_TEXTURE_WIDTH * SIDEWALK_TEXTURE_HEIGHT * 4);
	for(int row = 0; row < SIDEWALK_TEXTURE_HEIGHT; row++)
	{
		for(int col = 0; col < SIDEWALK_TEXTURE_WIDTH; col++)
		{
			if((row % CRACK_INTER) == 0 && row != 0)
			{
				setGreyscale(row, col, SIDEWALK_TEXTURE_WIDTH, (GLubyte) 10, false);
			}
			else
			{
				if((col % CRACK_INTER) == 0 && col != 0)
				{
					setGreyscale(row, col, SIDEWALK_TEXTURE_WIDTH, (GLubyte) 10, false);
				}
				else
				{
					setGreyscale(row, col, SIDEWALK_TEXTURE_WIDTH, randomSidewalkColor(), false);
				}
			} 
		}
	}
}

void Texture::constructWindows()
{
	image = (GLubyte *)malloc(WINDOW_TEXTURE_WIDTH * WINDOW_TEXTURE_HEIGHT * 4);
	
	for(int row = 0; row < WINDOW_TEXTURE_HEIGHT / WINDOW_HEIGHT; row++)
	{
		for(int col = 0; col < WINDOW_TEXTURE_WIDTH / WINDOW_WIDTH; col++)
		{
			colorWindow(row, col);
		}
	}
	
}

Texture::Texture(GLuint name, TextureType type)
{
	id = name;
	initRandomColors();
	switch(type)
	{
	case WINDOWS:
		constructWindows();
		break;
	case SIDEWALK:
		pourSidewalk();
		break;
	}
	createGLTexture();
	// image should have been malloced a fairly sizable chuck of memory in the creation process
	free(image);
}

Texture::Texture()
{
}

#endif
