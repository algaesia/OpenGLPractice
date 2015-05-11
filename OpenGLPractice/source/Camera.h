#ifndef _CAMERA_H
#define _CAMERA_H

#include "SceneNode.h"
#include <glm\glm.hpp>

class Camera : public SceneNode
{
public:
	Camera(const glm::vec3& a_CentrePos);
	
	virtual void Update(float dt);
	void SetTarget(SceneNode* a_TargetToFollow);
	void CameraShake();
private:
	SceneNode* m_TargetToFollow;

	float m_MovementSpeed;
	bool m_IsActive;
};

#endif