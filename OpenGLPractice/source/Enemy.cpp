#include "Enemy.h"
#include "Utility.h"
#include "RandNum.h"
#include "Dimensions.h"

Enemy::Enemy(unsigned int a_ShaderProgram,
	const char* a_TextureName,
	const glm::vec3& a_CentrePos,
	const glm::vec2& a_Scale,
	const glm::vec2& a_Dimensions,
	const glm::vec4& a_Colour)
	: Sprite(a_ShaderProgram, a_TextureName, a_CentrePos, a_Scale, a_Dimensions, a_Colour),
	m_MaxVelocity(10),
	m_Velocity(glm::vec3()),
	m_MovementSpeed(100),
	actionTimer(1),
	changeAction(1),
	m_MaxDistFromStart(2500),
	m_StartingPos(a_CentrePos),
	isAlive(true),
	m_AttackPower(1)
{
	m_RateOfRotation = 0.5f;
}

void Enemy::Update(float dt)
{
	if (isAlive)
	{
		//if (m_CentrePos.x + m_Dimensions.x * m_Scale.x * 0.5f > Dimensions::Instance().GetWorldDimensions().x * 0.5f ||
		//	m_CentrePos.y + m_Dimensions.y * m_Scale.y * 0.5f > Dimensions::Instance().GetWorldDimensions().y * 0.5f ||
		//	m_CentrePos.x - m_Dimensions.x * m_Scale.x * 0.5f < -Dimensions::Instance().GetWorldDimensions().x * 0.5f ||
		//	m_CentrePos.y - m_Dimensions.y * m_Scale.y * 0.5f < -Dimensions::Instance().GetWorldDimensions().y * 0.5f)
		//{
		//	ResetPosition();
		//}

		actionTimer += dt;

		if (Utility::Instance().VectorLength(m_Velocity) < 0.01f)
		{
			m_Velocity = glm::vec3();
		}

		if (Utility::Instance().VectorLength(m_Velocity) > 0)
		{
			float mag = Utility::Instance().VectorLength(m_Velocity);

			m_Velocity = glm::normalize(m_Velocity) * glm::min(mag, m_MaxVelocity);
		}

		m_CentrePos += m_Velocity * m_MovementSpeed * dt;

		if (actionTimer > changeAction)
		{
			actionTimer = 0;

			float randNum = (float)RandNum::Instance().GetRandNum();
			int action = (int)(randNum * 4);

			switch (action)
			{
			case 0:
				MoveUp();
				break;
			case 1:
				MoveDown();
				break;
			case 2:
				RotateLeft();
				break;
			case 3:
				RotateRight();
				break;
			}
		}

		Sprite::Update(dt);
	}
}

void Enemy::Render() const
{
	if (isAlive)
	{
		Sprite::Render();
	}
}

void Enemy::MoveUp()
{
	m_Velocity += glm::vec3(GetForward().x, GetForward().y, 0);
}

void Enemy::MoveDown()
{
	m_Velocity -= glm::vec3(GetForward().x, GetForward().y, 0);
}

void Enemy::RotateLeft()
{
	m_Rotation += m_RateOfRotation;
}

void Enemy::RotateRight()
{
	m_Rotation -= m_RateOfRotation;
}

void Enemy::ResetPosition()
{
	m_CentrePos = m_StartingPos;
}

void Enemy::SetScale(const glm::vec2& a_Scale)
{
	m_Scale = a_Scale;
}

int Enemy::GetAttackPower() const
{
	return m_AttackPower;
}
