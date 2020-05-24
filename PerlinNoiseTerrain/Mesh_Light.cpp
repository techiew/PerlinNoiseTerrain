#include "Mesh_Light.h"

Mesh_Light::Mesh_Light()
{
}

Mesh_Light::Mesh_Light(glm::vec3 pos, glm::vec3 scale)
{
	this->pos = pos;
	this->scale = scale;

	numVertices = 0;

	CreateMesh();

	std::vector<glm::vec3> positions;

	for (int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].pos);
	}

	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(2, vertexBufferObject);

	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[0]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferObject[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh_Light::CreateMesh()
{
	glm::vec3 p1 = pos + glm::vec3(-2.0f, -2.0f, 2.0f);
	glm::vec3 p2 = pos + glm::vec3(2.0f, -2.0f, 2.0f);
	glm::vec3 p3 = pos + glm::vec3(-2.0f, -2.0f, -2.0f);
	glm::vec3 p4 = pos + glm::vec3(2.0f, -2.0f, -2.0f);

	glm::vec3 p5 = pos + glm::vec3(-2.0f, 2.0f, 2.0f);
	glm::vec3 p6 = pos + glm::vec3(2.0f, 2.0f, 2.0f);
	glm::vec3 p7 = pos + glm::vec3(-2.0f, 2.0f, -2.0f);
	glm::vec3 p8 = pos + glm::vec3(2.0f, 2.0f, -2.0f);

	CreateVertex(p1);
	CreateVertex(p2);
	CreateVertex(p3);
	CreateVertex(p4);
	CreateVertex(p5);
	CreateVertex(p6);
	CreateVertex(p7);
	CreateVertex(p8);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(1);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(1);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(4);

	indices.push_back(1);
	indices.push_back(5);
	indices.push_back(4);

	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(5);

	indices.push_back(3);
	indices.push_back(7);
	indices.push_back(5);

	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(7);

	indices.push_back(2);
	indices.push_back(6);
	indices.push_back(7);

	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(6);

	indices.push_back(0);
	indices.push_back(4);
	indices.push_back(6);

	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(5);

	indices.push_back(6);
	indices.push_back(7);
	indices.push_back(5);

}

void Mesh_Light::CreateVertex(glm::vec3 pos)
{
	vertices.push_back(Vertex(pos));
	numVertices++;
}

Mesh_Light::~Mesh_Light()
{

}
