#ifndef TEXTURE_H
#define TEXTURE_H

#include <glut.h>
#include <stdlib.h>
#include <stdio.h>

#define GL_CLAMP_TO_EDGE 0x812F

//Window Texture 
#define WINDOW_HEIGHT 8
#define WINDOW_WIDTH 8
#define WINDOW_BEZEL 2

//Sidewalk Texture
#define CRACK_INTER 8

//Features
#define MIPMAP 0

enum TextureType
{
	WINDOWS,
	SIDEWALK,
	SKY_BOX_TOP,
	SKY_BOX_SIDE
};

class Texture
{
public:
	GLuint id;
	Texture();
	Texture(GLuint name, TextureType type, unsigned int w, unsigned int h);
private:
	unsigned int width, height;
	unsigned int unlit, dimlit, welllit;
	GLubyte * image;
	float randR, randG, randB; // Color offsets that can be used as a sudo-filter
	void initRandomColors();
	void setGreyscale(int row, int col, int width, GLubyte color, bool filter);
	void setColor(int row, int col, int width, GLubyte r, GLubyte g, GLubyte b);
	void colorWindow(int xOffset, int yOffset);
	void setBrightnessIntervals();
	void constructWindows();
	void createSkyGradient();
	void createSkyStars();
	void pourSidewalk();
	void createGLTexture();
	GLubyte randomWindowColor();
	GLubyte randomSidewalkColor();
};

void Texture::setColor(int row, int col, int width, GLubyte r, GLubyte g, GLubyte b)
{
	int offset = row * width * 4 + col * 4;

	*(image + offset) = r;
	*(image + (++offset)) = g;
	*(image + (++offset)) = b;
	*(image + (++offset)) = (GLubyte) 255;
}

void Texture::setGreyscale(int row, int col, int width, GLubyte color, bool filter)
{
	setColor(row, col, width,
		color + (filter? color * randR : 0.0),
		color + (filter? color * randB : 0.0),
		color + (filter? color * randG : 0.0));
}

GLubyte Texture::randomWindowColor()
{
	unsigned int num = rand() % 100;
	if(num < unlit)
	{
		return (GLubyte) 10;
	}
	else if (num < dimlit)
	{
		return (GLubyte) 80;
	}
	else if(num < welllit)
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
	return (GLubyte) (255 - (rand() % 100) - 20);
}

void Texture::initRandomColors()
{
	randR = ((float)rand())/RAND_MAX;
	randG = ((float)rand())/RAND_MAX;
	randB = ((float)rand())/RAND_MAX;
	randR /= 10;
	randG /= 10;
	randB /= 10;
}

void Texture::createGLTexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if(MIPMAP)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height,
						GL_RGBA, GL_UNSIGNED_BYTE, image);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, 
			height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	}
}

void Texture::colorWindow(int xOffset, int yOffset)
{
	int xStart = xOffset * WINDOW_HEIGHT;
	int yStart = yOffset * WINDOW_WIDTH;
	int xPos, yPos;
	GLubyte color = randomWindowColor();
	//GLubyte randMod;
	for(int row = 0; row < WINDOW_HEIGHT; row++)
	{
		for(int col = 0; col < WINDOW_WIDTH; col++)
		{
			xPos = xStart + row;
			yPos = yStart + col;
			if(row % WINDOW_HEIGHT < WINDOW_BEZEL)
			{
				setGreyscale(xPos, yPos, width, (GLubyte) 0, false);
			}
			else if(row % WINDOW_HEIGHT >= WINDOW_HEIGHT - WINDOW_BEZEL)
			{
				setGreyscale(xPos, yPos, width, (GLubyte) 0, false);
			}
			else
			{
				if(col % WINDOW_WIDTH < WINDOW_BEZEL)
				{
					setGreyscale(xPos, yPos, width, (GLubyte) 0, false);
				}
				else if(col % WINDOW_WIDTH >= WINDOW_WIDTH - WINDOW_BEZEL)
				{
					setGreyscale(xPos, yPos, width, (GLubyte) 0, false);
				}
				else
				{
					//randMod = (GLubyte) ((color % col) / ((rand() % 4)+1))*color;
					setGreyscale(xPos, yPos, width, color, false);
				}
			} 
		}
	}
}

void Texture::pourSidewalk()
{
	image = (GLubyte *)malloc(width * height * 4);
	for(unsigned int row = 0; row < height; row++)
	{
		for(unsigned int col = 0; col < width; col++)
		{
			if((row % CRACK_INTER) == 0 && row != 0)
			{
				setGreyscale(row, col, width, (GLubyte) 10, false);
			}
			else
			{
				if((col % CRACK_INTER) == 0 && col != 0)
				{
					setGreyscale(row, col, width, (GLubyte) 10, false);
				}
				else
				{
					setGreyscale(row, col, width, randomSidewalkColor(), false);
				}
			} 
		}
	}
}

void Texture::createSkyGradient()
{
	image = (GLubyte *)malloc(width * height * 4);
	for(unsigned int row = 0; row < height; row++)
	{
		for(unsigned int col = 0; col < width; col++)
		{
			setColor(row, col, width, 0, 3, 18);
		}
	}
}

void Texture::createSkyStars()
{
	image = (GLubyte *)malloc(width * height * 4);
	for(unsigned int row = 0; row < height; row++)
	{
		for(unsigned int col = 0; col < width; col++)
		{
			if((rand() % 1000) > 997)
			{
				setColor(row, col, width, 200, 200, 200);
			}
			else
			{
				setColor(row, col, width, 0, 3, 18);
			}
		}
	}

}

void Texture::setBrightnessIntervals()
{
	unlit = (rand() % 40) + (rand() % 10);
	dimlit = (rand() % 40) + (rand() % 10) + unlit;
	welllit = (rand() % 40) + (rand() % 10) + dimlit;
}

void Texture::constructWindows()
{
	image = (GLubyte *)malloc(width * height * 4);
	setBrightnessIntervals();
	for(unsigned int row = 0; row < height / WINDOW_HEIGHT; row++)
	{
		for(unsigned int col = 0; col < width / WINDOW_WIDTH; col++)
		{
			colorWindow(row, col);
		}
	}
	
}

Texture::Texture(GLuint name, TextureType type, unsigned int w, unsigned int h)
{
	id = name;
	width = w;
	height = h;
	initRandomColors();
	switch(type)
	{
	case WINDOWS:
		constructWindows();
		break;
	case SIDEWALK:
		pourSidewalk();
		break;
	case SKY_BOX_TOP:
		createSkyStars();
		break;
	case SKY_BOX_SIDE:
		createSkyGradient();
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
