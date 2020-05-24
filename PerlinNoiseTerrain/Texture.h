#pragma once

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <SOIL.h>

class Texture {
public:
	GLuint textures[1];

	Texture();
	void Bind(int index);
	void LoadTexture(std::string filepath, GLenum texIndex);
	~Texture();
};