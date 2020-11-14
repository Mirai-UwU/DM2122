#include "Camera.h"
#include "Application.h"
Camera::Camera()
{
}


Camera::~Camera()
{
}


void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}


void Camera::Reset()
{
}

void Camera::Update(double dt)
{
	static float CAMERA_SPEED = 10.0f;
	if (Application::IsKeyPressed('W'))
		this->position.y += CAMERA_SPEED * static_cast<float>(dt);
	else if (Application::IsKeyPressed('A'))
		this->position.x += CAMERA_SPEED * static_cast<float>(dt);
	if (Application::IsKeyPressed('S'))
		this->position.y += CAMERA_SPEED * static_cast<float>(dt);
	else if (Application::IsKeyPressed('D'))
		this->position.x += CAMERA_SPEED * static_cast<float>(dt);
}