#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "Sprite.h"

class Projectile : public Sprite
{
public:
	Projectile(unsigned int a_ShaderProgram, const char* a_TextureName, const glm::vec3& a_CentrePos, const glm::vec3& a_Velocity, const glm::vec2& a_Scale, const glm::vec2& a_Dimensions, const glm::vec4& a_Colour, bool a_IsAlive = false);

	virtual void Update(float dt);
	virtual void Render() const;

	bool isAlive;

	void SetPosition(glm::vec3 a_Position)
	{
		m_CentrePos = a_Position;
		m_StartingPos = a_Position;
	}

	void SetVelocity(glm::vec3 a_Velocity)
	{
		m_Velocity = a_Velocity;
	}
private:
	float m_MovementSpeed;
	float m_MaxTravelDistance;

	glm::vec3 m_Velocity;
	glm::vec3 m_StartingPos;
};

#endif