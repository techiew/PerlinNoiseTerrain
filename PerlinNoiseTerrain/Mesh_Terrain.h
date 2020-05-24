#pragma once

#include "Mesh.h"
#include <chrono>
#include "PerlinNoise.h"
#include <math.h>
#include <iostream>

class Mesh_Terrain : public Mesh
{

public:
	int rows, cols;

	Mesh_Terrain();
	Mesh_Terrain(int rows, int cols);
	void createMesh(int rows, int cols);
	void createNormals();
	void createVertex(glm::vec3 pos, glm::vec2 texCoord);
	~Mesh_Terrain();

};

