#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"


	void Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType, GLuint TexID);
	void TexturePart(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType, GLuint StartX, GLuint StartY, GLuint StopX, GLuint StopY, GLuint TexID);
#endif