#include "Mesh_Terrain.h"

Mesh_Terrain::Mesh_Terrain()
{
}

Mesh_Terrain::Mesh_Terrain(int rows, int cols)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	const double PI = 3.14159265358979323846264338327950288;
	pos = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	this->rows = rows;
	this->cols = cols;
	numVertices = 0;

	createMesh(rows, cols);
	createNormals();

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;

	for (int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].pos);
		texCoords.push_back(vertices[i].texCoord);
		normals.push_back(vertices[i].CalculateNormal());
		normalsPos.push_back(vertices[i].pos);
		normalsPos.push_back(
			glm::vec3(
			vertices[i].pos.x + normals[i].x,
			vertices[i].pos.y + normals[i].y,
			vertices[i].pos.z + normals[i].z
			)
		);
	}

	//for (int i = 0; i < numVertices; i++)
	//{
	//	std::cout << vertices[i].normals[i].x << vertices[i].normals[i].y << vertices[i].normals[i].z << std::endl;
	//}

	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(NUM_BUFFERS, vertexBufferObject);

	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[POSITION_INDEX]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION_INDEX);
	glVertexAttribPointer(POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[TEXCOORD_INDEX]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(TEXCOORD_INDEX);
	glVertexAttribPointer(TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[NORMAL_INDEX]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL_INDEX);
	glVertexAttribPointer(NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferObject[ELEMENT_INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	//Normal vertices
	glGenVertexArrays(1, &normalsVAO);
	glGenBuffers(1, normalsVBO);

	glBindVertexArray(normalsVAO);

	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, normalsPos.size() * sizeof(normalsPos[0]), &normalsPos[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = end - start;
	std::cout << "Generated map in: " << elapsedTime.count() << " seconds, " << numVertices << " vertices" << std::endl;
}

void Mesh_Terrain::createMesh(int rows, int cols)
{
	//glm::vec2 topLeft = glm::vec2(0.0f, 0.0f);
	//glm::vec2 topRight = glm::vec2(1.0f, 0.0f);
	//glm::vec2 bottomRight = glm::vec2(1.0f, 1.0f);
	//glm::vec2 bottomLeft = glm::vec2(0.0f, 1.0f);

	PerlinNoise pn(time(NULL));
	//bool toggle = true;
	double xOff = 0.0;
	double zOff = 0.0;
	double min = 0;
	double max = GetRand(min + 1, 25);
	double noiseValue = 0.0;
	float modifier = GetRandF(0.01f, 0.08f);

	std::cout << "Max height: " << max << " - Modifier: " << modifier << std::endl;

	for (int i = 0; i < rows; i++)
	{
		xOff = 0.0;

		for (int j = 0; j < cols; j++)
		{
			glm::vec3 vertPos = glm::vec3((-1.0f * cols / 4) + (j * 0.5f), 0, (1.0f * rows / 4) - (i * 0.5f));
			noiseValue = pn.noise(xOff, 0, zOff);
			vertPos.y = MapValue(min, max, noiseValue);
			//if (numVertices == 0) vertPos.y = 0.2f;
			createVertex(vertPos, glm::vec2(j, i));
			//if (j + 1 == 1 || j % 2 == 0)
			//{

			//	if (toggle)
			//	{
			//		CreateVertex(vertPos, glm::vec2(cols, rows));
			//	}
			//	else
			//	{
			//		CreateVertex(vertPos, glm::vec2(cols, rows));
			//	}

			//} else {

			//	if (toggle)
			//	{
			//		CreateVertex(vertPos, glm::vec2(cols, rows));
			//	}
			//	else
			//	{
			//		CreateVertex(vertPos, glm::vec2(cols, rows));
			//	}

			//}
			xOff += modifier;
		}
		zOff += modifier;

		//toggle = (toggle) ? false : true;

	}

	bool firstRow = true;

	for (int i = 0; i < numVertices; i++)
	{
		int a = i;
		int b = i + cols;
		int c = i + cols + 1;
		int d = i + 1;

		if ((i + 1) % cols == 0) continue;
		if (i >= (rows * cols) - cols) continue;

		indices.push_back(a);
		indices.push_back(d);
		indices.push_back(b);

		indices.push_back(b);
		indices.push_back(d);
		indices.push_back(c);


		////Check if the first row has ended (allow connecting above)
		//if (i != 0 && i % cols == 0)
		//{
		//	firstRow = false;
		//}

		////If this is not the first row or not on the last row, connect to vertices above
		//if ((i + 1) % (cols * rows - cols) != 0 && !firstRow)
		//{
		//	int a = i;
		//	int b = i + 1;
		//	int c = (i - cols) + 1;

		//	indices.push_back(a);
		//	indices.push_back(b);
		//	indices.push_back(c);
		//}
		//
		////If 0 or vertex is not on last row, connect to vertices below
		//if ((i + 1) % (cols * rows - cols) != 0 || i == 0)
		//{
		//	int a = i;
		//	int b = i + cols;
		//	int c = i + 1;

		//	indices.push_back(a);
		//	indices.push_back(b);
		//	indices.push_back(c);
		//}

	}

}

void Mesh_Terrain::createNormals()
{

	for (int i = 0; i != indices.size(); i += 3)
	{

		try
		{
			Vertex p1 = vertices.at(indices.at(i));
			Vertex p2 = vertices.at(indices.at(i + 1));
			Vertex p3 = vertices.at(indices.at(i + 2));

			glm::vec3 U(p2.pos - p1.pos);
			glm::vec3 V(p3.pos - p1.pos);

			glm::vec3 normal = glm::cross(U, V);

			vertices.at(indices.at(i)).AddNormal(normal);
			vertices.at(indices.at(i + 1)).AddNormal(normal);
			vertices.at(indices.at(i + 2)).AddNormal(normal);

			//glm::vec3 normal
			//(
			//	(U.y * V.z) - (U.z * V.y),
			//	(U.z * V.x) - (U.x * V.z),
			//	(U.x * V.y) - (U.y * V.x)
			//);

			//normals.push_back(normal); // inverse ?? 
			//normals.push_back(normal); 
			//normals.push_back(normal); 

			//glm::vec3 surfaceCenter = glm::vec3(
			//	(p1.pos.x + p2.pos.x + p3.pos.x) / 3,
			//	(p1.pos.y + p2.pos.y + p3.pos.y) / 3,
			//	(p1.pos.z + p2.pos.z + p3.pos.z) / 3);

			//normalPos.push_back(surfaceCenter);
		} 
		catch (const std::out_of_range& e)
		{
			std::cout << "Error: index out of range: " << i << std::endl;
		}

		//glm::vec3 one = vertices[i+2].pos - vertices[i].pos;
		//glm::vec3 two = vertices[i+1].pos - vertices[i].pos;

		//glm::vec3 normal = glm::cross(one, two);

		//normals.push_back(normal);
		//normals.push_back(normal);
		//normals.push_back(normal);
	}

}

void Mesh_Terrain::createVertex(glm::vec3 pos, glm::vec2 texCoord)
{
	vertices.push_back(Vertex(pos, texCoord));
	numVertices++;
}

Mesh_Terrain::~Mesh_Terrain()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}