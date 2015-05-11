#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include "Sprite.h"
#include "Projectile.h"

//inherit from sprite, remove controls from sprite into player
class Player : public Sprite
{
public:
	Player(unsigned int a_ShaderProgram, 
		   const char* a_TextureName, 
		   const glm::vec3& a_CentrePos, 
		   const glm::vec2& a_Scale,
		   const glm::vec2& a_Dimensions,
		   const glm::vec4& a_Colour);
	~Player();

	virtual void Update(float dt);
	virtual void Render() const;

	void MoveUp();
	void MoveDown();
	void RotateLeft();
	void RotateRight();

	void ResetPlayer();

	Projectile* FindValidBullet();
	std::vector<Projectile*> GetBullets() const;

	const int GetHealth() const;

	void DecreaseHealth(int a_Decrease);
private:
	void ResetPosition();
	void ResetVelocity();
	void ResetRotation();

	bool m_IsAlive;

	int m_Health;

	float m_DecayRateVelocity;

	float m_MaxVelocity;
	float m_MovementSpeed;

	float m_ShootTimer;
	float m_ShootReady;
	
	glm::vec3 m_Velocity;
	glm::vec3 m_StartingPos;

	std::vector<Projectile*> m_Bullets;
};

#endif
