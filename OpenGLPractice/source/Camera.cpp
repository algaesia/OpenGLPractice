#include "Camera.h"
#include "Utility.h"
#include "Dimensions.h"
#include <GLFW\glfw3.h>
#include <glm\gtx\compatibility.hpp>

//stop camera from going offscreen

Camera::Camera(const glm::vec3& a_CentrePos)
	: SceneNode(),
	m_IsActive(true),
	m_MovementSpeed(10),
	m_TargetToFollow(nullptr)
{
	m_CentrePos = a_CentrePos;
}

void Camera::Update(float dt)
{
	if (m_IsActive)
	{
		glm::vec3 current = m_CentrePos;
		glm::vec3 target = glm::vec3(m_TargetToFollow->GetPosition().x - Dimensions::Instance().GetWindowDimensions().x * 0.5f,
			m_TargetToFollow->GetPosition().y - Dimensions::Instance().GetWindowDimensions().y * 0.5f,
			m_TargetToFollow->GetPosition().z);

		m_CentrePos = glm::lerp(current, target, 0.5f);
	}

	SceneNode::Update(dt);
}

void Camera::SetTarget(SceneNode* a_TargetToFollow)
{
	m_TargetToFollow = a_TargetToFollow;
}

void Camera::CameraShake()
{
	
}
