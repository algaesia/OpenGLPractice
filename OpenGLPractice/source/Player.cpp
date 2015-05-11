#include <glm\gtc\matrix_transform.hpp>
#include "Player.h"
#include "DebugLines.h"
#include "Utility.h"
#include "InputHandler.h"
#include "RandNum.h"
#include "Dimensions.h"
#include "SoundManager.h"
#include <string>

Player::Player(unsigned int a_ShaderProgram,
	const char* a_TextureName,
	const glm::vec3& a_CentrePos,
	const glm::vec2& a_Scale,
	const glm::vec2& a_Dimensions,
	const glm::vec4& a_Colour)
	: Sprite(a_ShaderProgram, a_TextureName, a_CentrePos, a_Scale, a_Dimensions, a_Colour),
	m_DecayRateVelocity(0.97f),
	m_MovementSpeed(75),
	m_MaxVelocity(10),
	m_Velocity(glm::vec3()),
	m_StartingPos(m_CentrePos),
	m_ShootTimer(0.5f),
	m_ShootReady(0.5f),
	m_Health(25),
	m_IsAlive(true)
{
	m_RateOfRotation = 0.06f;
	m_Bullets.reserve(50);
}

Player::~Player()
{
	for (unsigned int i = 0; i < m_Bullets.size(); ++i)
	{
		delete m_Bullets[i];
	}
	m_Bullets.clear();
}

void Player::Update(float dt)
{
	if (m_IsAlive)
	{
		m_ShootTimer += dt;

		if (Utility::Instance().VectorLength(m_Velocity) < 0.01f)
		{
			m_Velocity = glm::vec3();
		}

		if (!(InputHandler::Instance().CheckKeyHeld(87) ||
			InputHandler::Instance().CheckKeyHeld(83)))
		{
			if (Utility::Instance().VectorLength(m_Velocity) > 0)
			{
				m_Velocity *= m_DecayRateVelocity;
			}
		}

		//w
		if (InputHandler::Instance().CheckKeyHeld(87))
		{
			MoveUp();
		}

		//s
		if (InputHandler::Instance().CheckKeyHeld(83))
		{
			MoveDown();
		}

		//a
		if (InputHandler::Instance().CheckKeyHeld(65))
		{
			RotateLeft();
		}

		//d
		if (InputHandler::Instance().CheckKeyHeld(68))
		{
			RotateRight();
		}

		if (m_ShootTimer > m_ShootReady)
		{
			if (InputHandler::Instance().CheckKeyHeld(32))
			{
				//int randNum = (int)(RandNum::Instance().GetRandNum() * 3) + 1;
				//std::string shootName = "lasershoot" + std::to_string(randNum);
				//SoundManager::Instance().Play(shootName);

				m_ShootTimer = 0;

				glm::vec3 forward = GetForward();
				forward *= 5;
				float num = (float)(RandNum::Instance().GetRandNum() - 0.5f);

				forward += glm::vec3(num, 0, 0);

				//looks for a dead bullet
				Projectile* t = FindValidBullet();

				//if it can find one, itll use it
				//resetting position and velocity
				if (t != nullptr)
				{
					t->isAlive = true;
					t->SetPosition(m_CentrePos);
					t->SetVelocity(forward);
				}
				//otherwise a new one will be created
				else
				{
					Projectile* t = new Projectile(shaderProgram, "resources/desert.jpg", m_CentrePos, forward, glm::vec2(1), glm::vec2(25), glm::vec4(1), true);
					m_Bullets.push_back(t);
				}
			}
		}

		if (Utility::Instance().VectorLength(m_Velocity) > 0)
		{
			float mag = Utility::Instance().VectorLength(m_Velocity);

			m_Velocity = glm::normalize(m_Velocity) * glm::min(mag, m_MaxVelocity);
		}

		m_CentrePos += m_Velocity * m_MovementSpeed * dt;

		Sprite::Update(dt);
	}

	for (Projectile* i : m_Bullets)
	{
		i->Update(dt);
		i->UpdateTransforms();
	}
}

void Player::Render() const
{
	if (m_IsAlive)
	{
		Sprite::Render();
	}

	for (Projectile* i : m_Bullets)
	{
		i->Render();
	}
}

void Player::MoveUp()
{
	m_Velocity += glm::vec3(GetForward().x, GetForward().y, 0);
}

void Player::MoveDown()
{
	m_Velocity -= glm::vec3(GetForward().x, GetForward().y, 0);
}

void Player::RotateLeft()
{
	m_Rotation += m_RateOfRotation;
}

void Player::RotateRight()
{
	m_Rotation -= m_RateOfRotation;
}

//find dead bullet, make it alive
Projectile* Player::FindValidBullet()
{
	for (Projectile* i : m_Bullets)
	{
		if (!i->isAlive)
		{
			return i;
		}
	}

	return nullptr;
}

void Player::ResetPosition()
{
	m_CentrePos = m_StartingPos;
}

std::vector<Projectile*> Player::GetBullets() const
{
	return m_Bullets;
}

const int Player::GetHealth() const
{
	return m_Health;
}

void Player::DecreaseHealth(int a_Decrease)
{
	int dec = m_Health - a_Decrease;
	if (dec < 0)
	{
		dec = 0;
	}
	m_Health = dec;
}

void Player::ResetVelocity()
{
	m_Velocity = glm::vec3();
}

void Player::ResetRotation()
{
	m_Rotation = 0;
}

void Player::ResetPlayer()
{
	ResetVelocity();
	ResetRotation();
	ResetPosition();
}
