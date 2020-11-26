#include "Camera2.h"
#include "Application.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera2::Camera2()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera2::~Camera2()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera2::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera2::Update(double dt)
{
	static const float CAMERA_SPEED = 10.f;
	if (Application::IsKeyPressed('W'))
		this->position.y += CAMERA_SPEED * static_cast<float>(dt); //move camera up
	if (Application::IsKeyPressed('A'))
		this->position.x -= CAMERA_SPEED * static_cast<float>(dt); //move camera left
	if (Application::IsKeyPressed('S'))
		this->position.y -= CAMERA_SPEED * static_cast<float>(dt); //move camera down
	if (Application::IsKeyPressed('D'))
		this->position.x += CAMERA_SPEED * static_cast<float>(dt); //move camera right
}