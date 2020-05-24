#pragma once

#include "Mesh.h"
#include <glm.hpp>
#include <GL/glew.h>
#include <vector>

class Mesh_Light : public Mesh
{
public:
	Mesh_Light();
	Mesh_Light(glm::vec3 pos, glm::vec3 scale);
	void CreateMesh();
	void CreateVertex(glm::vec3 pos);
	~Mesh_Light();

};