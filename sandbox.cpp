/*
	Daniel McGuinness
*/

/*Include Libraries*/
#include "GL/glew.h"	//x64
#include "GLFW/glfw3.h" //x64 VS2015 edition
#include <glm/glm.hpp> //0.9.9.2
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "SOIL2/SOIL2.h" //x64

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stack>
#include <vector>

#include "windowmanager.h"
#include "plane.h"
#include "sandbox.h"

using namespace glm;
using namespace std; 

GLuint positionBufferObj; 
GLuint pVertexBuffer, pUVBuffer; 
GLuint program; 
GLuint vao; 

//Shader uniforms
GLuint modelViewID, projID; 
GLuint textureID; 
GLuint lightModeID, texModeID;
GLuint lightMode = 0;
GLuint texMode = 0; 


//sampler2D texture; 

//Window Variables
GLfloat winWidth = 1024; 
GLfloat winHeight = 768;


//Camera Variables
vec3 camPos = vec3(10, 10, 0);
vec3 camDir = vec3(0, 0, 0);
vec3 camUp = vec3(0, 1, 0);
GLfloat fov = 90.0f;
GLfloat clipNear = 0.1f;
GLfloat clipFar = 100.0f;

//User Inputs
GLfloat xMove = 0.0f; 
GLfloat yMove = 0.0f;
GLfloat zMove = 0.0f;

GLfloat yRotate = 90.0f;

GLfloat xInc = 0.05f; 
GLfloat yInc = 0.05f; 
GLfloat zInc = 0.05f; 
GLfloat yRotInc = 0.9f; 


Plane plane;

vector<vec3> planeVerts, planeNorms;
vector<vec2> planeUVs;

void drawObjects() {

	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1ui(lightModeID, lightMode);
	glUniform1ui(texModeID, texMode);

	//Projection Matrix
	mat4 proj = perspective(radians(fov), (winWidth / winHeight), clipNear, clipFar);
	glUniformMatrix4fv(projID, 1, GL_FALSE, &(proj[0][0]));

	//View Matrix
	mat4 view = lookAt(camPos, camDir, camUp);

	//Model-View Matrix Stack
	stack<mat4> mvStack;
	mvStack.push(mat4(1.0f));
	mvStack.top() = translate(mvStack.top(), vec3(xMove, yMove, zMove));
	mvStack.push(mvStack.top());
	{
		mvStack.top() = rotate(mvStack.top(), -radians(yRotate), vec3(0, 1, 0));
		mvStack.top() = view * mvStack.top();

		glUniformMatrix4fv(modelViewID, 1, GL_FALSE, &mvStack.top()[0][0]);
		plane.drawPlane();

	}
	mvStack.pop(); 

	vec3 planeTwoLoc = vec3(30, 0, 0);

	/*Create second aeroplane to circle the central plane*/
	mvStack.push(mvStack.top());
	{
		mvStack.top() = scale(mvStack.top(), vec3(0.5f, 0.5f, 0.5f)); 
		mvStack.top() = rotate(mvStack.top(), radians(yRotate), vec3(0, 1, 0));
		mvStack.top() = translate(mvStack.top(), planeTwoLoc);
		mvStack.top() = rotate(mvStack.top(), radians(90.0f), vec3(0, 1, 0));
		mvStack.top() = view * mvStack.top();

		glUniformMatrix4fv(modelViewID, 1, GL_FALSE, &mvStack.top()[0][0]);
		plane.drawPlane();
	}
	mvStack.pop(); 

	/*Create a third aeroplane to rotate around the second plane*/
	mvStack.push(mvStack.top());
	{
		mvStack.top() = scale(mvStack.top(), vec3(0.5f, 0.5f, 0.5f));
		mvStack.top() = rotate(mvStack.top(), radians(yRotate), vec3(0, 1, 0));
		mvStack.top() = translate(mvStack.top(), planeTwoLoc);
		mvStack.top() = rotate(mvStack.top(), radians(yRotate), vec3(0, 1, 0));
		mvStack.top() = translate(mvStack.top(), vec3(15, 0, 0));
		mvStack.top() = rotate(mvStack.top(), radians(90.0f), vec3(0, 1, 0));
		mvStack.top() = view * mvStack.top();

		glUniformMatrix4fv(modelViewID, 1, GL_FALSE, &mvStack.top()[0][0]);
		plane.drawPlane();
	}
	mvStack.pop();
	

	//Update Transformation Variables
	yRotate += yRotInc; 
}

/*
	Initialization function - sets up VAO and plane objects, textures.
*/
void init() {

	//Setup VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Uniform variable setup
	modelViewID = glGetUniformLocation(program, "modelview");
	projID = glGetUniformLocation(program, "projection");
	lightModeID = glGetUniformLocation(program, "lightMode");
	texModeID = glGetUniformLocation(program, "texMode");

	//Setup Plane Objects
	plane = Plane(); 

	plane.setupPlane("..\\common\\sam2.obj");

	//Load texture for plane
	textureID = SOIL_load_OGL_texture("..\\common\\texture.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);//*/

}

/*
	Print instruction keyboard controls to console
*/
void instruct() {

	cout << "\n" << endl; 
	cout << "Camera Controls" << endl; 
	cout << "===============" << endl; 
	cout << "WS - Forwards and Backwards" << endl; 
	cout << "AD - Left and Right" << endl; 
	cout << "RF - Up and Down\n" << endl;

	cout << "Model Controls" << endl; 
	cout << "=========================" << endl;
	cout << "[ ] - Rotate plane model on Y-axis" << endl; 
	cout << "L - switch between lighting modes (Ambient/Ambient + Diffuse/Ambient + Specular)" << endl; 
	cout << "T - toggle texturing of the plane" << endl; 
}

/*
	Main display loop, ran every frame - updates transformations and uniforms
*/
void display() {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(program);

	drawObjects(); 

	glDisableVertexAttribArray(0);
	glUseProgram(0);
}


static void keyCallback(GLFWwindow* window, int key, int s, int action, int mods) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//Movement keys
	if (key == 'S') { xMove = xMove - xInc; }
	if (key == 'W') { xMove = xMove + xInc; }
	if (key == 'R') { yMove = yMove + yInc; }
	if (key == 'F') { yMove = yMove - yInc; }
	if (key == 'A') { zMove = zMove - zInc; }
	if (key == 'D') { zMove = zMove + zInc; }

	//Model keys
	if (key == '[') { yRotInc = yRotInc + 0.05f; }
	if (key == ']') { yRotInc = yRotInc - 0.05f; }

	//Toggle lighting type
	if (key == 'L' && action != GLFW_PRESS)
	{
		lightMode++;
		if (lightMode > 2) {
			lightMode = 0;
		}
	}

	if (key == 'T' && action != GLFW_PRESS) {
		if (texMode == 0) {
			texMode = 1; 
		}
		else {
			texMode = 0; 
		}
	}

}

int main() {

	if (!glfwInit()) {
		glfwTerminate();
	}

	//create window and make current context
	WindowManager m = WindowManager(winWidth, winHeight, "Sandbox");
	
	glewExperimental = GL_TRUE;
	glewInit();

	program = m.buildShaders("..\\shaders\\simple.vert", "..\\shaders\\simple.frag");

	init();

	instruct(); 

	m.setRenderer(display);
	m.setKeyCallback(keyCallback);

	m.mainLoop(); 

	return 0; 
}
