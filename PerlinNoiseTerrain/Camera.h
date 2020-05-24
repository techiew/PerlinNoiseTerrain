#pragma once

#include <glm.hpp>
#include <gtx\transform.hpp>
#include <SDL.h>

class Camera
{
public:
	glm::vec3 cameraPos;
	int resX, resY;
	float cameraFOV;
	float aspectRatio;
	float zNear;
	float zFar;
	float horizontalAngle;
	float verticalAngle;
	float mouseSpeed;

	glm::mat4 projection;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 view;

	Camera();
	Camera(int resX, int resY, float zNear, float zFar);
	void Update();
	void Move(glm::vec3 cameraPos);
	void Rotate(Sint32 x, Sint32 y);
	void SetResolution(int resX, int resY);
	~Camera();
};

