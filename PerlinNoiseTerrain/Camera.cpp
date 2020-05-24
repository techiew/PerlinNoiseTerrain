#include "camera.h"

Camera::Camera() 
{ 
}

Camera::Camera(int resX, int resY, float zNear, float zFar)
{	
	cameraPos = glm::vec3(0, 20, 50);
	this->resX = resX;
	this->resY = resY;
	cameraFOV = 1.57f;
	aspectRatio = (float)resX / (float)resY;
	this->zNear = zNear;
	this->zFar = zFar;
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	mouseSpeed = 0.005f;

	forward = glm::vec3(0, 0, -1);
	up = glm::vec3(0, 1, 0);
	right = glm::vec3(1, 0, 0);

	projection = glm::perspective(cameraFOV, aspectRatio, zNear, zFar);
	view = glm::lookAt(cameraPos, cameraPos + forward, up);
}

void Camera::Update()
{
	view = glm::lookAt(cameraPos, cameraPos + forward, up);
}

void Camera::Move(glm::vec3 cameraPos) 
{
	this->cameraPos = cameraPos;
}

void Camera::Rotate(Sint32 x, Sint32 y) 
{
	verticalAngle += mouseSpeed * (int)y;
	horizontalAngle += mouseSpeed * (int)x;

	if (verticalAngle >= 1.50f)
	{
		verticalAngle = 1.50f;
	}
	else if (verticalAngle <= -1.50f)
	{
		verticalAngle = -1.50f;
	}

	forward = glm::vec3
	(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	right = glm::vec3
	(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	up = glm::cross(right, forward);
}

void Camera::SetResolution(int resX, int resY)
{
	this->resX = resX;
	this->resY = resY;
	aspectRatio = (float)resX / (float)resY;
	projection = glm::perspective(cameraFOV, aspectRatio, zNear, zFar);
}

Camera::~Camera()
{
}
