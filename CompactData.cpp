#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

#include"TextureLoader.h"
#include"WindowConfigurator.h"
#include <chrono>
#include <thread>

//Color template
GLfloat TemplateColor[24] = {
    1.0f, 0.0f, 0.0f, //Bottom Left
    1.0f, 1.0f, 1.0f,  //Bottom Right
    0.0f, 0.0f, 1.0f, //Top Left
    1.0f, 1.0f, 1.0f,  //Bottom Right
    0.0f, 1.0f, 0.0f, //Top Right  
};

GLfloat DisplayScale;

void FillWithTemplate(GLfloat* ColorTemplate, GLfloat* TextureTemplate, GLfloat* VerticeTable) {
    
}
void FillWithTemplate(GLfloat* TextureTemplate, GLfloat* VerticeTable) {

}
void FillWithTemplate(GLfloat* VerticeTable) {
  //  for (int i = 0; i < 9; i++) {
   //     for (int j = 3; j < 6; j++) {
    //        VerticeTable[(i * 8) + j] = TemplateColor[];
     //   }
   // }
}

GLfloat ConvertToZT(GLfloat Coordinate) {
    return 1 + Coordinate; //BRUH
}
// (0 - Horizontal, 1 - Vertical) Convert back to -1,0,1 coordinate system
GLfloat ConvertToGLCoord(GLuint Value, ViewportParams ViewPort, bool Orientation) {//Convert back to -1,0,1 WITH THIS ONE SIMPLE TRICK! 9/10 AMERICANS WONT BELIVE THIS!!!
    if(!Orientation)
    return ((Value * 1.0f) / (ViewPort.width * 1.0f)) * 2 - 1;
    else
    return 2 * ((Value * 1.0f) / (ViewPort.height * 1.0f)) - 1;
}

void ModifyVBO(VBO& vbo, GLfloat* data, GLuint DataSize)
{
    vbo.Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, DataSize, data);
    vbo.Unbind();
}