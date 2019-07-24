/*
	Daniel McGuinness
*/

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

class WindowManager {
private:
	GLFWwindow* win;
	const char* title; 
	int width;
	int height;
	void(*renderer)(); 
	void(*keyCallBack)(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	WindowManager(int width, int height, const char* title);
	~WindowManager();

	void mainLoop();
	void setRenderer(void (*f)());
	void setKeyCallback(void(*f)(GLFWwindow* window, int key, int scancode, int action, int mods));

	GLuint buildShaders(const char*  vertexShaderPath, const char* fragmentShaderPath);

};
#endif