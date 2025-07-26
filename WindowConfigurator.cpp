#include "WindowConfigurator.h"
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void WindowFrame::WindowFrameConfig(fPoint2D Start, GLuint Height, GLuint Width, short unsigned int TopLeft, short unsigned int BottomLeft, short unsigned int TopRight, short unsigned int BottomRight, ViewportParams ViewPort) {
	VAO1.Bind();
    FWidth = Width;
    FHeight = Height;
    textureList[0] = BottomLeft;
    textureList[1] = BottomRight;
    textureList[2] = TopLeft;
    textureList[3] = TopLeft;
	//Invent vertices array
    GLuint indices[24] = {  //         14_________15  10________11
        //bottom left                    |\        |  |\        |
        2,0,1,//bottom triangle          |  \      |  |  \      |
        2,3,1,//top triangle             |    \    |  |    \    |
        //bottom right                   |      \  |  |      \  |
        6,4,5,//bottom triangle         12________\13 8________\9
        6,7,5,//top triangle             2_________3  6_________7
        //top right                      |\        |  |\        |
        10,8,9,//bottom triangle         |  \      |  |  \      |
        10,11,9,//top triangle           |    \    |  |    \    |          
        //top left                       |      \  |  |      \  | 
        14,12,13,//bottom triangle      0|________\1  4________\5
        14,15,13 //top triangle
    };


    //OKAY GARMIN 🗣️ ❗❗ 
    //VIDEO SPEICHERN 🔈 🔥

    //Invent texture mapping template
    GLfloat TexMapping[8]{
        0.0f,0.0f,
        0.0f,5.0f,
        5.0f,0.0f,
        5.0f,5.0f,

    };
    vertices = new GLfloat[80];
    for (int i = 0; i < 80; i++) {
        vertices[i] = 0;
    }
    //Make the coordinate system from 0 to 2 instead of -1 to 1 for ease of use (severe mental impairment)
    GLfloat horizPos;
    GLfloat vertPos;
    //Adj. horizontal
    horizPos = ConvertToZT(Start.X);
    //Adj. vertical
    vertPos = ConvertToZT(Start.Y);
    GLuint HorizPx = ViewPort.width * (horizPos / 2);
    GLuint VertiPx = ViewPort.height * (vertPos / 2);
    //Positions (pixel-wise to viewport)
    GLuint OffsetH1 = HorizPx + Width / 2;
    GLuint OffsetH2 = HorizPx + Width;
    GLuint OffsetV1 = VertiPx - Height / 2;
    GLuint OffsetV2 = VertiPx - Height;
    //Convert back to openGL -1,0,1 coordinates:
    GLfloat HSET1 = ConvertToGLCoord(OffsetH1, ViewPort, 0);
    GLfloat HSET2 = ConvertToGLCoord(OffsetH2, ViewPort, 0);
    GLfloat VSET1 = ConvertToGLCoord(OffsetV1, ViewPort, 1);
    GLfloat VSET2 = ConvertToGLCoord(OffsetV2, ViewPort, 1);
    //writing coordinates for indices 14,12,2,0
    vertices[70] = Start.X;
    vertices[71] = Start.Y;
    vertices[60] = Start.X;
    vertices[61] = VSET1;
    vertices[10] = Start.X;
    vertices[11] = VSET1;
    vertices[0] = Start.X;
    vertices[1] = VSET2;
    //writing coordinates for indices 15,13,3,1
    vertices[75] = HSET1;
    vertices[76] = Start.Y;
    vertices[65] = HSET1;
    vertices[66] = VSET1;
    vertices[15] = HSET1;
    vertices[16] = VSET1;
    vertices[5] = HSET1;
    vertices[6] = VSET2;
    //writing coordinates for indices 10,8,6,4
    vertices[50] = HSET1;
    vertices[51] = Start.Y;
    vertices[40] = HSET1;
    vertices[41] = VSET1;
    vertices[30] = HSET1;
    vertices[31] = VSET1;
    vertices[20] = HSET1;
    vertices[21] = VSET2;
    //writing coordinates for indices 11,9,7,5
    vertices[55] = HSET2;
    vertices[56] = Start.Y;
    vertices[45] = HSET2;
    vertices[46] = VSET1;
    vertices[35] = HSET2;
    vertices[36] = VSET1;
    vertices[25] = HSET2;
    vertices[26] = VSET2;

    //Populate with the template for textures:
    for (int i = 0; i < 16; i++) {
        vertices[i * 5 + 3] = TexMapping[(i % 4)*2];
        vertices[i * 5 + 4] = TexMapping[(i % 4) *2+1];
    }


    //TEMP DEBUG
    for (int i = 0; i < 80; i++) {
       if (i % 5 == 0) std::cout << '\n';
       std::cout << vertices[i]<<" ,";
   }


    // Generates Vertex Buffer Object and links it to vertices
    glGenBuffers(1, &VBO1.ID);
    VBO1.Bind();
    glBufferData(GL_ARRAY_BUFFER, 128 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    // Generates Element Buffer Object and links it to indices
    glGenBuffers(1, &EBO1.ID);
    EBO1.Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 128 * sizeof(GLfloat), indices, GL_STATIC_DRAW);

    // Links VBO attributes such as coordinates and colors to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
}
void WindowFrame::UpdatePosition(fPoint2D Start,ViewportParams ViewPort) {
    vertices = new GLfloat[80];
    for (int i = 0; i < 80; i++) {
        vertices[i] = 0;
    }
    //Make the coordinate system from 0 to 2 instead of -1 to 1 for ease of use (severe mental impairment)
    GLfloat horizPos;
    GLfloat vertPos;
    //Adj. horizontal
    horizPos = ConvertToZT(Start.X);
    //Adj. vertical
    vertPos = ConvertToZT(Start.Y);
    GLuint HorizPx = ViewPort.width * (horizPos / 2);
    GLuint VertiPx = ViewPort.height * (vertPos / 2);
    //Positions (pixel-wise to viewport)
    GLuint OffsetH1 = HorizPx + FWidth / 2;
    GLuint OffsetH2 = HorizPx + FWidth;
    GLuint OffsetV1 = VertiPx - FHeight / 2;
    GLuint OffsetV2 = VertiPx - FHeight;
    //Convert back to openGL -1,0,1 coordinates:
    GLfloat HSET1 = ConvertToGLCoord(OffsetH1, ViewPort, 0);
    GLfloat HSET2 = ConvertToGLCoord(OffsetH2, ViewPort, 0);
    GLfloat VSET1 = ConvertToGLCoord(OffsetV1, ViewPort, 1);
    GLfloat VSET2 = ConvertToGLCoord(OffsetV2, ViewPort, 1);
    //writing coordinates for indices 14,12,2,0
    vertices[70] = Start.X;
    vertices[71] = Start.Y;
    vertices[60] = Start.X;
    vertices[61] = VSET1;
    vertices[10] = Start.X;
    vertices[11] = VSET1;
    vertices[0] = Start.X;
    vertices[1] = VSET2;
    //writing coordinates for indices 15,13,3,1
    vertices[75] = HSET1;
    vertices[76] = Start.Y;
    vertices[65] = HSET1;
    vertices[66] = VSET1;
    vertices[15] = HSET1;
    vertices[16] = VSET1;
    vertices[5] = HSET1;
    vertices[6] = VSET2;
    //writing coordinates for indices 10,8,6,4
    vertices[50] = HSET1;
    vertices[51] = Start.Y;
    vertices[40] = HSET1;
    vertices[41] = VSET1;
    vertices[30] = HSET1;
    vertices[31] = VSET1;
    vertices[20] = HSET1;
    vertices[21] = VSET2;
    //writing coordinates for indices 11,9,7,5
    vertices[55] = HSET2;
    vertices[56] = Start.Y;
    vertices[45] = HSET2;
    vertices[46] = VSET1;
    vertices[35] = HSET2;
    vertices[36] = VSET1;
    vertices[25] = HSET2;
    vertices[26] = VSET2;

    //Invent texture mapping template
    GLfloat TexMapping[8]{
        0.0f,0.0f,
        0.0f,5.0f,
        5.0f,0.0f,
        5.0f,5.0f,

    };

    //Populate with the template for textures:
    for (int i = 0; i < 16; i++) {
        vertices[i * 5 + 3] = TexMapping[(i % 4) * 2];
        vertices[i * 5 + 4] = TexMapping[(i % 4) * 2 + 1];
    }

    //TEMP DEBUG
  for (int i = 0; i < 80; i++) {
      if (i % 5 == 0) std::cout << "\n#"<<i/5<<": ";
      std::cout << vertices[i]<<" ,";
   }

    ModifyVBO(VBO1, vertices, 80 * sizeof(GLfloat));
}
//void OuterWindowFrame::ConfigureWindowFrame(point Start, point Stop, std::string FrameName, short unsigned int TopLeft, short unsigned int BottomLeft, short unsigned int TopRight, short unsigned int BottomRight) {

//}
//void OuterWindowFrame::UpdatePosition(point Start, point Stop) {

//}
void WindowFrame::ConfigureToUpdatedViewport(unsigned short int Horiz, unsigned short int Vert) {

}
void OuterWindowFrame::ConfigureToUpdatedViewport(unsigned short int Horiz, unsigned short int Vert) {

}

void Element::InitializeElement(GLuint TextureCount) {
	TextureIDs = new GLuint[TextureCount];
	TextureNames = new std::string[TextureCount];
}

