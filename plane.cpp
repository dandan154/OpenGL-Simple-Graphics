/*
	Daniel McGuinness
*/

#include "plane.h"
#include "SOIL2/SOIL2.h" //x64

using namespace std; 
using namespace glm; 

Plane::Plane() {
	shaderVert = 0;
	shaderNorm = 1;
	shaderUV = 2;
}

Plane::~Plane() {

}


/*
	.Obj Model Loader for loading in Plane Model
	Adapted from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

*/
bool Plane::loadObjFile(const char * objPath, vector<vec3> &verts, vector<vec2> &uvs, vector<vec3> &norms) {
	
	vector<GLuint> vertInd, uvInd, normInd; 
	vector<vec3> tmpVert, tmpNorm;
	vector<vec2> tmpUV; 

	FILE * objFile = fopen(objPath, "r");

	if (objFile == NULL) {
		cout << "OBJ file failed to open" << endl;
		return false; 
	}
	else {
		cout << "OBJ file opened" << endl; 
	}

	cout << "Loading OBJ model(may take a few seconds)..." << endl;
	while (1) {
		
		char lineHead[128];
		int result = fscanf(objFile, "%s", lineHead);

		if (result == EOF) {
			break;
		}


		if (strcmp(lineHead, "v") == 0) {
			vec3 vertex; 
			fscanf(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tmpVert.push_back(vertex);
		}
		else if (strcmp(lineHead, "vt") == 0){
			vec2 uv; 
			fscanf(objFile, "%f %f\n", &uv.x, &uv.y);
			tmpUV.push_back(uv);
		}
		else if (strcmp(lineHead, "vn") == 0) {
			vec3 norm;
			fscanf(objFile, "%f %f %f\n", &norm.x, &norm.y, &norm.z);
			tmpNorm.push_back(norm); 
		}
		else if (strcmp(lineHead, "f") == 0) {
			string vert1, vert2, vert3; 
			GLuint vertIndex[3], uvIndex[3], normIndex[3];
			int match = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertIndex[0], &uvIndex[0], &normIndex[0], &vertIndex[1], &uvIndex[1], &normIndex[1], &vertIndex[2], &uvIndex[2], &normIndex[2]);
			
			if (match != 9) {
				cout << "Obj File parse has failed - incorrect format" << endl; 
			}

			vertInd.push_back(vertIndex[0]);
			vertInd.push_back(vertIndex[1]);
			vertInd.push_back(vertIndex[2]);

			uvInd.push_back(uvIndex[0]);
			uvInd.push_back(uvIndex[1]);
			uvInd.push_back(uvIndex[2]);

			normInd.push_back(normIndex[0]);
			normInd.push_back(normIndex[1]);
			normInd.push_back(normIndex[2]);

		}

		for (int i = 0; i < vertInd.size(); i++) {
			vec3 vertex; 
			GLuint vertIndex = vertInd[i]; 
			vertex = tmpVert[vertIndex - 1];
			verts.push_back(vertex);
		}

		for (int i = 0; i < uvInd.size(); i++) {
			vec2 uv;
			GLuint uvIndex = uvInd[i];
			uv = tmpUV[uvIndex - 1];
			uvs.push_back(uv);
		}

		for (int i = 0; i < normInd.size(); i++) {
			vec3 norm;
			GLuint normIndex = normInd[i];
			norm = tmpNorm[normIndex - 1];
			norms.push_back(norm);
		}

	}

	cout << "OBJ model loaded" << endl;
	//fclose(objFile);
	return true;

}

/*
	Prepare Plane Obj for rendering - load Object from file and bind data to buffers
*/
void Plane::setupPlane(const char * filename)
{

	bool res = loadObjFile(filename, planeVerts, planeUVs, planeNorms); 

	glGenBuffers(1, &posBuff);
	glBindBuffer(GL_ARRAY_BUFFER, posBuff);
	glBufferData(GL_ARRAY_BUFFER, planeVerts.size() * sizeof(vec3), &planeVerts[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &uvBuff);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuff);
	glBufferData(GL_ARRAY_BUFFER, planeUVs.size() * sizeof(glm::vec2), &planeUVs[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &normBuff);
	glBindBuffer(GL_ARRAY_BUFFER, normBuff);
	glBufferData(GL_ARRAY_BUFFER, planeNorms.size() * sizeof(glm::vec3), &planeNorms[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//*/

}

/*
	Render plane using data from bound buffers
*/
void Plane::drawPlane()
{
	glBindBuffer(GL_ARRAY_BUFFER, posBuff);
	glEnableVertexAttribArray(shaderVert);
	glVertexAttribPointer(shaderVert, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, normBuff);
	glEnableVertexAttribArray(shaderNorm);
	glVertexAttribPointer(shaderNorm, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uvBuff);
	glEnableVertexAttribArray(shaderUV);
	glVertexAttribPointer(shaderUV, 2, GL_FLOAT, GL_FALSE, 0, 0);//*/

	glBindBuffer(GL_ARRAY_BUFFER, posBuff);
	glDrawArrays(GL_TRIANGLES, 0, planeVerts.size());
}
