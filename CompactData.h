#ifndef COMPACTDATA_CLASS_H
#define COMPACTDATA_CLASS_H
struct fPoint2D {
	GLfloat X;
	GLfloat Y;
};
struct iPoint2D {
	GLuint X;
	GLuint Y;
};
struct fPoint3D {
	GLfloat X;
	GLfloat Y;
	GLfloat Z;
};
struct iPoint3D {
	GLuint X;
	GLuint Y;
	GLuint Z;
};
struct ViewportParams {
	GLuint width;
	GLuint height;
};
void FillWithTemplate(GLfloat* ColorTemplate, GLfloat* TextureTemplate, GLfloat* VerticeTable); //Fill vertice table with a color and texture template, specified when calling
void FillWithTemplate(GLfloat* TextureTemplate, GLfloat* VerticeTable); //Fill vertice table with a texture template, specified when calling
void FillWithTemplate(GLfloat* VerticeTable); //Fill vertice table with generic templates

GLfloat ConvertToZT(GLfloat Coordinate);//Convert -1,0,1 OpenGL coordinate system for ease of manipulation to 0-2
GLfloat ConvertToGLCoord(GLuint Value, ViewportParams ViewPort, bool Orientation);// (0 - Horizontal, 1 - Vertical) Convert back to -1,0,1 coordinate system 

void ModifyVBO(VBO& vbo, GLfloat* data, GLuint DataSize);
#endif