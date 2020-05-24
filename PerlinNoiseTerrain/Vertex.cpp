#include "Vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(glm::vec3 pos)
{
	this->pos = pos;
}

Vertex::Vertex(glm::vec3 pos, glm::vec2 texCoord)
{
	this->pos = pos;
	this->texCoord = texCoord;
	this->normals.clear();
}

void Vertex::AddNormal(glm::vec3 normal)
{
	this->normals.push_back(normal);
}

glm::vec3 Vertex::CalculateNormal()
{
	glm::vec3 averagedNormal;

	for (int i = 0; i < normals.size(); i++)
	{
		averagedNormal += normals[i];
	}

	averagedNormal = glm::vec3(
		averagedNormal.x / normals.size(),
		averagedNormal.y / normals.size(),
		averagedNormal.z / normals.size()
	);

	return averagedNormal;
}

Vertex::~Vertex()
{

}