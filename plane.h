/*
	Daniel McGuinness
*/


#pragma once
#include "windowmanager.h"
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>

class Plane {

public: 
	GLuint posBuff;
	GLuint normBuff;
	GLuint uvBuff;

	GLuint shaderVert;
	GLuint shaderUV; 
	GLuint shaderNorm;

	std::vector<glm::vec3> planeVerts;
	std::vector<glm::vec3> planeNorms;
	std::vector<glm::vec2> planeUVs;
	
	Plane(); 
	~Plane(); 

	bool loadObjFile(const char * objPath, std::vector<glm::vec3> &verts, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &norms);
	void setupPlane(const char * filename);
	void drawPlane(); 
};