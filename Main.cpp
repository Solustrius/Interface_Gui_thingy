#include<filesystem>
namespace fs = std::filesystem;


//imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

#include <CompactData.h>


struct Rectangle {
	int StartX;
	int StartY;
	int StopX;
	int StopY;
};


ViewportParams ViewPort;
bool ViewPortUpdated = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Adjust the OpenGL viewport to the new window size
	glViewport(0, 0, width, height);
	ViewPort.width=width;
	ViewPort.height = height;
	if (!ViewPortUpdated) {
		ViewPortUpdated = true;
		std::cout << "Viewport changed!\n";
	}
}


int EC;


void LoadTextures() {
	// Texture loading from file

	//Resource directory paths
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/FactorioInterfaceClone/Assets/GUI/";

	std::cout << (parentDir + texPath + "gui-new.png").c_str();//debug

	// Find out how many elements and textures are in the assets/gui files
	GLuint ElementCount = 0;
	TextureLoaderInitializatorInitializer((fs::current_path().fs::path::parent_path()).string() + "/FactorioInterfaceClone/Assets/GUI/", ElementCount);
	GLuint* TexturesPerElement = new GLuint[ElementCount]; //and create a new pointer at a list of all the textures each element has
	// Initialize array with 0;
	for (int i = 0; i < ElementCount; i++) {
		TexturesPerElement[i] = 0;
	}
	// Read actually how many textures are there per element
	TextureLoaderInitializator((fs::current_path().fs::path::parent_path()).string() + "/FactorioInterfaceClone/Assets/GUI/", TexturesPerElement);
	// And finally, load the textures to the GPU, and their ID in a WindowConfigurator::Element array
	Element* ElementList = new Element[ElementCount];
	LoadTextures((fs::current_path().fs::path::parent_path()).string() + "/FactorioInterfaceClone/Assets/GUI/", (parentDir + texPath + "gui-new.png").c_str(), ElementList, TexturesPerElement, ElementCount);
	// Logic of operation //
	// The way this functions is by reading the text file, first identifying how many individual elements are
	// after that, the next function reads how many textures each element has, and adds each element's texture count to the array
	// with the information we get from here, we initialize a vector of WindowConfigurator::Element structures, for which
	// we specify for each what is the name mentioned in the look-up table, initialize an array of IDs for each texture an element has.
	// 
	EC = ElementCount;
}


bool windowWasADJ = false;


int main()
{
	//                    V U P         Compilation rev.
	std::cout << "Version 1.0.0 Revision 0.0015\n";

	//initialization is quite hard
	ViewPort.width = 800;
	ViewPort.height = 800;



	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object 
	GLFWwindow* window = glfwCreateWindow(ViewPort.width, ViewPort.height, "AgarthaView", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, ViewPort.width, ViewPort.width);
	//Call subprogram if the window size changes
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");



	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/

	LoadTextures();

	// Original code from the tutorial
	/*Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);*/

	//invent imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	// Main while loop
	int cntr=0;
	int pcntr = 0;
	// Positions
	int StX=0;
	int StY=0;
	int StpX=0;
	int StpY=0;
	int StSum=0;
	int StpSum = 0;
	char DATA[256];

	fPoint2D Start;
	Start.X = -1.0f;
	Start.Y = 1.0f;
	GLuint width = 200;
	GLuint height = 200;

	WindowFrame Test;
		Test.WindowFrameConfig(Start, width, height, 1, 2, 3, 4, ViewPort);

		EC = 9;
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.0f, 0.2f, 0.5f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);

			// Bind the VAO so OpenGL knows to use it
			Test.VAO1.Bind();
			//std::cout << '\n' << Test.VAO1.ID;
			for (int i = 0; i < 24; i += 6) {
				// Binds texture so that is appears in rendering
				glBindTexture(GL_TEXTURE_2D, Test.textureList[i / 6]);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * sizeof(GLuint)));
			}
		// ImGUI window creation
		ImGui::Begin("Texture adjustment");
		// Text that appears in the window
		ImGui::Text("Change the textures");
		// Checkbox that appears in the window
		//ImGui::Checkbox("Draw Triangle", &drawTriangle);
		// Slider that appears in the window
		ImGui::SliderInt("BottomLeft", &StX, 1, EC);
		ImGui::SliderInt("BottomRight", &StY, 1, EC);
		ImGui::SliderInt("TopLeft", &StpX, 1, EC);
		ImGui::SliderInt("TopRight", &StpY,1, EC);
		if (StX + StY != StSum || StpX + StpY != StpSum) {
			StSum = StX + StY;
			StpSum = StpX + StpY;
			Test.textureList[0] = StX;
			Test.textureList[1] = StpY;
			Test.textureList[2] = StpX;
			Test.textureList[3] = StY;
			//ModifyVAO(Test.VBO1, vertices, sizeof(vertices), 40, StX);
			//ModifyVAO(Test.VBO1, vertices, sizeof(vertices), 41, StY);

		}
		// Ends the window
		ImGui::End();
		// ImGUI window creation
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		ImGui::Begin("Cursor Position");
		snprintf(DATA, sizeof(DATA), "//  %f    %f", (x/ViewPort.width)*2-1, -((y/ViewPort.height)*2-1));
		ImGui::Text(DATA);
		ImGui::Text("pixel - wise:");
		snprintf(DATA, sizeof(DATA), "//  %f    %f", x, y);
		ImGui::Text(DATA);
		// Ends the window
		ImGui::End();

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)==GLFW_PRESS && !windowWasADJ) {
			Start.X = ((x*1.0f) / (ViewPort.width * 1.0f)) * 2 - 1;
			Start.Y = -(((y * 1.0f) / (ViewPort.height * 1.0f)) * 2 - 1);
			Test.UpdatePosition(Start,ViewPort);
			std::cout << "NPOS: " << Start.X << ' ' << Start.Y << '\n';
			//windowWasADJ = 1;
		}
		if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_1)==GLFW_RELEASE) {
			windowWasADJ = 0;
		}
		if (ViewPortUpdated == true) {
			Test.UpdatePosition(Start, ViewPort);
			ViewPortUpdated = false;
		}


		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	//VAO1.Delete();
	//VBO1.Delete();
	//EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}