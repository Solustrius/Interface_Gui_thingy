#include <TextureLoader.h>
#include <Texture.h>
#include <WindowConfigurator.h>
#include<glad/glad.h>
#include<stb/stb_image.h>
#include<filesystem>
#include<fstream>
#include<string.h>
#include<stdlib.h>

//Legit load the textures trust me brother
bool LoadTextures(std::string SourceFolderPath, std::string SourceImagePath, Element* ElementList, GLuint* TexturesPerElement, GLuint ElementCount) {
	std::cout << "Attempting to load textures...\n";
	std::cout << "Loading from: " + SourceFolderPath + "textureLUT.UOD" + "\n";
	std::ifstream fin(SourceFolderPath+"textureLUT.UOD");
		if (!fin){
			std::cout << "Failed to load look-up table.\n";
			return 0;
	}
	std::string TextureName = "";
	std::string data="";
	std::string TexName = "";
	GLuint LocalTextureID = 0;//ID of each texture stored in an element relative to that element
	GLuint GraphMemIndex = -1;
	GLuint TexIDindex=0;//position of the texture index in the element vectors
	GLuint TexID = 0;//ID of each texture stored in an element relative to everything stored in the GPU
	//Coordinates
	GLuint StartX=0;
	GLuint StartY=0;
	GLuint StopX=0;
	GLuint StopY=0;
	while (std::getline(fin, data)) {
		data = data + '\0';
		if (data[0] == '(') {
			GraphMemIndex++;
			TexIDindex = 0;
			LocalTextureID = 0;
			TexName = "";
			for (unsigned int i = 1; data[i] != ')'; i++) {
				TexName += data[i];
			}
			ElementList[GraphMemIndex].InitializeElement(TexturesPerElement[GraphMemIndex]);
			std::cout << "Initializing element for write with size " << TexturesPerElement[GraphMemIndex] << '\n';
			std::cout << "Looking at: " + TexName+"\n";
		}
		if (data[0] == '[') {
			TextureName = "";
			for (unsigned int i = 1; data[i] != ']'; i++) {
				TextureName += data[i];
			}
			ElementList[GraphMemIndex].ElementName = TexName;
			std::cout << "Identified: " + TextureName+"\n";
		}
		bool HasComma = false;
		for (int j = 0; data[j] && !HasComma; j++) {
			if (data[j] == ',')
				HasComma = true;
		}
		if (HasComma) {
		for (unsigned int i = 0; data[i]; i++) {//browse the line
			//Reset the coordinates if a new coordinate number is found
			if (isdigit(data[i])) {
				StartX = 0;
				StartY = 0;
				StopX = 0;
				StopY = 0;
			}
			//Read the numbers
			do{
				StartX = StartX * 10 + (int)data[i] - (int)'0';
				i++;
			} while (isdigit(data[i]));
			i++;
			do{
				StartY = StartY * 10 + (int)data[i] - (int)'0';
				i++;
			}while (isdigit(data[i]));
			i++;
			 do{
				StopX = StopX * 10 + (int)data[i] - (int)'0';
				i++;
			 } while (isdigit(data[i]));
			i++;
			do{
				StopY = StopY * 10 + (int)data[i] - (int)'0';
				i++;
			} while (isdigit(data[i]));
			//Access the element vectors and create a new texture based on the coordinates extracted, then associate it to the element variables
			std::cout << "Texture coords: " << StartX << " " << StartY << " " << StopX << " " << StopY << "\n";
				ElementList[GraphMemIndex].TextureIDs[TexIDindex] = TexID;
				ElementList[GraphMemIndex].TextureNames[LocalTextureID] = TextureName;
				TexturePart((SourceFolderPath+"/gui-new.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE,StartX,StartY,StopX,StopY,TexID);
				//((parentDir + texPath + "gui-new.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, 0, 4, 16, 8, 0);
				TexID++;
				TexIDindex++;
				LocalTextureID++;
				std::cout << "Texture load OK, ID:"<<TexID<<"\n";
			}
		ElementList[GraphMemIndex].TextureCount = TexturesPerElement[GraphMemIndex];
		}
	}
	std::cout << "Textures loaded to memory.\n";

	return 1;
}
//Find out how many textures each element has
bool TextureLoaderInitializatorInitializer(std::string SourceFolderLUTpath, GLuint& ElementCount) {
	std::ifstream fin(SourceFolderLUTpath + "textureLUT.UOD");
	std::cout << "Attempting to load texture information...\n";
	if (!fin) {
		std::cout << "Failed to load look-up table\n";
		return 0;
	}
	std::string data = "";
	while (std::getline(fin, data)) {
		for (int i = 0; data[i]; i++) {
			if (data[i] == '(')
				ElementCount++;
		}
	}
	std::cout << "Loaded\n";
	return 1;
}
//Find out how many elements are there
bool TextureLoaderInitializator(std::string SourceFolderLUTpath, GLuint* TexturesPerElement) {
	GLuint ElementCount = 0;
	std::cout << "Loading from: " + SourceFolderLUTpath + "textureLUT.UOD" + "\n";
	std::ifstream fin(SourceFolderLUTpath + "textureLUT.UOD");
	if (!fin) {
		std::cout << "Failed to load look-up table\n";
		return 0;
	}
	std::string data = "";
	bool firstInit = false;
	while (std::getline(fin, data)) {
		for (int i = 0; data[i]; i++) {
			if (data[i] == '(') {
				if (firstInit) {
					std::cout << "For element #" << ElementCount << " found " << TexturesPerElement[ElementCount - 1] << " Textures.\n";
				}
				else {
					firstInit = true;
				}
				ElementCount++;
				TexturesPerElement[ElementCount] = 0;
			}
			if (data[i] == '[')
				TexturesPerElement[ElementCount-1]++;
		}
	}
	std::cout << "For element #" << ElementCount << " found " << TexturesPerElement[ElementCount-1] << " Textures.\n";
	std::cout << "Found " << ElementCount << " elements\n";
	return 1;
}