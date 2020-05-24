#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <glm.hpp>
#include <gtx/transform.hpp>

class Shader
{
public:

	// Shaders
	enum
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,

		NUM_SHADERS
	};

	// Uniforms
	enum
	{
		U_MODEL,
		U_VIEW,
		U_PROJECTION,
		U_CAMERAPOS,
		U_LIGHTPOS,
		U_ISWIREFRAME,
		U_SHOWLIGHT,

		NUM_UNIFORMS
	};

	// Attributes
	enum
	{
		A_POSITION,
		A_TEXCOORD,
		A_NORMAL,

		NUM_ATTRIBUTES
	};

	GLuint shaderProgram;
	GLuint shaders[NUM_SHADERS];
	GLuint uniforms[NUM_UNIFORMS];

	bool isWireframe;
	bool showLight;
	
	Shader();
	Shader(const std::string fileName);
	void Bind();
	void Update(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale, glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPos, glm::vec3 lightPos);
	void ShowWireframe(bool enabled);
	void ShowLight(bool enabled);
	static GLuint CreateShader(const std::string& text, GLenum shaderType);
	std::string LoadShader(const std::string& fileName);
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	~Shader();
};

