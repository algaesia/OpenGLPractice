#include "Projectile.h"
#include "Utility.h"

Projectile::Projectile(unsigned int a_ShaderProgram, const char* a_TextureName, const glm::vec3& a_CentrePos, const glm::vec3& a_Velocity, const glm::vec2& a_Scale, const glm::vec2& a_Dimensions, const glm::vec4& a_Colour, bool a_IsAlive)
	: Sprite(a_ShaderProgram, a_TextureName, a_CentrePos, a_Scale, a_Dimensions, a_Colour),
	m_Velocity(a_Velocity),
	m_StartingPos(a_CentrePos),
	m_MovementSpeed(1500),
	m_MaxTravelDistance(500),
	isAlive(a_IsAlive)
{

}

void Projectile::Update(float dt)
{
	if (isAlive)
	{
		glm::vec3 startToCurrent = m_StartingPos - m_CentrePos;
		float dist = Utility::Instance().VectorLength(startToCurrent);

		if (dist > m_MaxTravelDistance)
		{
			isAlive = false;
		}

		if (Utility::Instance().VectorLength(m_Velocity) > 0)
		{
			m_Velocity = glm::normalize(m_Velocity);
		}

		m_CentrePos += m_MovementSpeed * m_Velocity * dt;

		Sprite::Update(dt);
	}
}

void Projectile::Render() const
{
	if (isAlive)
	{
		Sprite::Render();
	}
}
