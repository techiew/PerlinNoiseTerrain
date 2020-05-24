#pragma once

#include <glm.hpp>
#include <GL/glew.h>
#include <vector>
#include "vertex.h"

using namespace std;

class Mesh
{

protected:
	enum
	{
		POSITION_INDEX,
		TEXCOORD_INDEX,
		NORMAL_INDEX,
		ELEMENT_INDEX,

		NUM_BUFFERS
	};

	glm::vec3 pos;
	glm::vec3 rotation;
	glm::vec3 scale;

	GLuint vertexArrayObject;
	GLuint vertexBufferObject[NUM_BUFFERS];
	GLuint normalsVAO;
	GLuint normalsVBO[1];

	int numVertices;
	vector<Vertex> vertices;
	vector<unsigned short> indices;
	vector<glm::vec3> normals;
	vector<glm::vec3> normalsPos;

	void createMesh();
	void createVertex();
	void createNormals();
	
public:
	glm::vec3 getPos() { return pos; }
	glm::vec3 getRotation() { return rotation; }
	glm::vec3 getScale() { return scale; }
	void setPos(glm::vec3 newPos) { pos = newPos; }

	GLuint getVAO() { return vertexArrayObject; }
	GLuint* getVBO() { return vertexBufferObject; }
	GLuint getNormalsVAO() { return normalsVAO; }
	GLuint* getNormalsVBO() { return normalsVBO; }
	vector<glm::vec3> getNormalsPos() { return normalsPos; }

	int getNumVertices() { return numVertices; }
	vector<Vertex> getVertices() { return vertices; }
	vector<unsigned short> getIndices() { return indices; }
	vector<glm::vec3> getNormals() { return normals; }

};

inline float MapValue(float minimum, float maximum, float value)
{
	return minimum + (maximum - minimum) * ((value - 0) / (1 - 0));
}

inline float GetRandF(float fMin, float fMax)
{
	return (fMax - fMin) * ((((float)rand()) / (float)RAND_MAX)) + fMin;
}

inline int GetRand(int min, int max)
{
	return min + (rand() % static_cast<int>(max - min + 1));
}