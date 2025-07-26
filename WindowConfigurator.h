#ifndef WINDOWCONF_CLASS_H
#define WINDOWCONF_CLASS_H

#include<glad/glad.h>
#include<Texture.h>
#include<filesystem>
namespace fs = std::filesystem;
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "CompactData.h"
#include<string.h>

//For defining a frame where the inside components are located
class WindowFrame {
public:
	std::string FrameName;
	VAO VAO1;
	VBO VBO1;
	EBO EBO1;
	GLuint textureList[4] = { 0 };
	GLuint FWidth;
	GLuint FHeight;
	GLfloat* vertices;
	short unsigned int cornerTextures[4];//TopLeft, BottomLeft, TopRight, BottomRight
	void WindowFrameConfig(fPoint2D Start, GLuint Height, GLuint Width, short unsigned int TopLeft, short unsigned int BottomLeft, short unsigned int TopRight, short unsigned int BottomRight, ViewportParams ViewPort);
	void UpdatePosition(fPoint2D Start,ViewportParams ViewPort);
	void ConfigureToUpdatedViewport(unsigned short int Horiz, unsigned short int Vert);
};
class OuterWindowFrame {
	VAO VAO1;
	VBO VBO1;
	EBO EBO1;
	GLfloat* vertices;
	fPoint2D TopCorner;
	fPoint2D BottomCorner;
	//Element TextureSource;
	short unsigned int cornerTextures[4];//TopLeft, BottomLeft, TopRight, BottomRight
	//void ConfigureWindowFrame(point Start, point Stop, std::string FrameName, short unsigned int TopLeft, short unsigned int BottomLeft, short unsigned int TopRight, short unsigned int BottomRight);
	//void UpdatePosition(point Start, point Stop);
	void ConfigureToUpdatedViewport(unsigned short int Horiz, unsigned short int Vert);
};

class Element {
public:
	std::string ElementName;
	GLuint* TextureIDs;
	std::string* TextureNames;
	GLuint TextureCount;
	void InitializeElement(GLuint TextureCount);
};




#endif