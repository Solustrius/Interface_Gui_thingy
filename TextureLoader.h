#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include "Texture.h"
#include "WindowConfigurator.h"
#include<glad/glad.h>
#include<stb/stb_image.h>
#include<filesystem>
#include <WindowConfigurator.h>
namespace fs = std::filesystem;

	bool LoadTextures(std::string SourceFolderPath, std::string SourceImagePath, Element* ElementList, GLuint* TexturesPerElement, GLuint ElementCount);
	bool TextureLoaderInitializator(std::string SourceFolderLUTpath, GLuint* TexturesPerElement);
	bool TextureLoaderInitializatorInitializer(std::string SourceFolderLUTpath, GLuint& ElementCount);
#endif