#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <GL/glew.h>

enum CameraMovement {
	FORWARD,
    BACKWARD,
	LEFT,
	RIGHT
};

// default camera values
const float YAW					= -90.0f;
const float PITCH					= 0.0f;
const float SPEED				= 2.5f;
const float SENSITIVITY		= 0.1f;
const float ZOOM				= 45.0f;

class Camera
{
public:
	//camera attributes
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;
	//euler angels
	float m_Yaw;
	float m_Pitch;
	//camera options
	float m_MovementSpeed;
	float m_MouseSensitivity;
	float m_Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldup = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
		

	Camera(float posX, float posY, float posZ, float worldupX, float worldupY, float worldupZ, float yaw, float pitch);

	glm::mat4 GetViewMatrix();

	void ProcessKeyboard(CameraMovement direction, float deltaTime);

	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	void ProcessMouseScroll(float yoffset);

private:
	void UpDateCameraVectors();

};