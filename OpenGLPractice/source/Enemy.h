#ifndef _ENEMY_H
#define _ENEMY_H

#include "Sprite.h"

class Enemy : public Sprite
{
public:
	Enemy(unsigned int a_ShaderProgram,
		const char* a_TextureName,
		const glm::vec3& a_CentrePos,
		const glm::vec2& a_Scale,
		const glm::vec2& a_Dimensions,
		const glm::vec4& a_Colour);

	virtual void Update(float dt);
	virtual void Render() const;

	void MoveUp();
	void MoveDown();
	void RotateLeft();
	void RotateRight();

	void ResetPosition();

	void SetScale(const glm::vec2& a_Scale);

	bool isAlive;

	int GetAttackPower() const;
private:
	int m_AttackPower;

	float m_MaxVelocity;
	float m_MovementSpeed;
	float m_MaxDistFromStart;

	float actionTimer;
	float changeAction;

	glm::vec3 m_Velocity;
	glm::vec3 m_StartingPos;
};

#endif