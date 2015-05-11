#include "EnemySpawner.h"
#include "RandNum.h"
#include "Dimensions.h"
#include "SoundManager.h"
#include <string>

EnemySpawner::EnemySpawner(unsigned int a_ShaderProgram, Player* a_PlayerRef, int a_MaxNumEnemies, const glm::vec2& a_DimensionsRange, const glm::vec2& a_ScaleRange)
	: m_MaxNumEnemies(a_MaxNumEnemies),
	spawnPositionRange(Dimensions::Instance().GetWorldDimensions()),
	dimensionsRange(a_DimensionsRange),
	scaleRange(a_ScaleRange),
	m_PlayerRef(a_PlayerRef),
	m_EnemiesKilled(0)
{
	m_ShaderProgram = a_ShaderProgram;
	for (int i = 0; i < m_MaxNumEnemies; ++i)
	{
		Enemy* t = new Enemy(m_ShaderProgram, //shader
							 "resources/Tulips.jpg", //texture file name
							 glm::vec3(RandNum::Instance().GetRandNum() * spawnPositionRange.x - (spawnPositionRange.x * 0.5f), //position
							 		   RandNum::Instance().GetRandNum() * spawnPositionRange.y - (spawnPositionRange.y * 0.5f), 0),
							 glm::vec2(RandNum::Instance().GetRandNum() * scaleRange.x + (scaleRange.x * 0.5f), //scale
									   RandNum::Instance().GetRandNum() * scaleRange.y + (scaleRange.y * 0.5f)), 
							 glm::vec2(RandNum::Instance().GetRandNum() * dimensionsRange.x + (dimensionsRange.x * 0.5f), //dimensions
									   RandNum::Instance().GetRandNum() * dimensionsRange.y + (dimensionsRange.y * 0.5f)),
							 glm::vec4(RandNum::Instance().GetRandNum(), //colour
							 		   RandNum::Instance().GetRandNum(),
							 		   RandNum::Instance().GetRandNum(),
							 		   1)
							 );
		m_Enemies.push_back(t);
	}
}

EnemySpawner::~EnemySpawner()
{
	for (unsigned int i = 0; i < m_Enemies.size(); ++i)
	{
		delete m_Enemies[i];
	}
	m_Enemies.clear();
}

void EnemySpawner::UpdateEnemies(float dt)
{
	ResetDeadEnemies();

	for (Enemy* i : m_Enemies)
	{
		if (i->CheckCollisions(m_PlayerRef->GetPosition(), m_PlayerRef->GetScale(), m_PlayerRef->GetDimensions()))
		{
			//int randNum = (int)(RandNum::Instance().GetRandNum() * 3) + 1;
			//std::string explosionName = "explosion" + std::to_string(randNum);
			//SoundManager::Instance().Play(explosionName);
			i->isAlive = false;

			//move it off screen
			i->SetPosition(glm::vec3(Dimensions::Instance().GetWorldDimensions().x + 100.0f, Dimensions::Instance().GetWorldDimensions().y + 100.0f, 0));
			m_PlayerRef->DecreaseHealth(i->GetAttackPower());
			m_EnemiesKilled++;
		}

		i->Update(dt);
		i->UpdateTransforms();
	}

	for (Enemy* i : m_Enemies)
	{
		for (Projectile* j : m_PlayerRef->GetBullets())
		{
			if (i->CheckCollisions(j->GetPosition(), j->GetScale(), j->GetDimensions()))
			{
				j->isAlive = false;
				i->isAlive = false;

				//int randNum = (int)(RandNum::Instance().GetRandNum() * 3) + 1;
				//std::string explosionName = "explosion" + std::to_string(randNum);
				//SoundManager::Instance().Play(explosionName);

				//move it off screen
				i->SetPosition(glm::vec3(Dimensions::Instance().GetWorldDimensions().x + 100.0f, Dimensions::Instance().GetWorldDimensions().y + 100.0f, 0));
				j->SetPosition(glm::vec3(Dimensions::Instance().GetWorldDimensions().x + 100.0f, Dimensions::Instance().GetWorldDimensions().y + 100.0f, 0));
				m_EnemiesKilled++;
			}
		}
	}
}

void EnemySpawner::RenderEnemies()
{
	for (Enemy* i : m_Enemies)
	{
		i->Render();
	}
}

void EnemySpawner::ResetDeadEnemies()
{
	for (Enemy* i : m_Enemies)
	{
		if (!i->isAlive)
		{
			i->isAlive = true;
			i->SetPosition(glm::vec3(RandNum::Instance().GetRandNum() * spawnPositionRange.x - (spawnPositionRange.x * 0.5f), //position
				RandNum::Instance().GetRandNum() * spawnPositionRange.y - (spawnPositionRange.y * 0.5f), 0));
			i->SetScale(glm::vec2(RandNum::Instance().GetRandNum() * scaleRange.x + (scaleRange.x * 0.5f), //scale
				RandNum::Instance().GetRandNum() * scaleRange.x + (scaleRange.y * 0.5f)));
		}
	}
}

void EnemySpawner::ResetEnemies()
{
	m_EnemiesKilled = 0;
	for (Enemy* i : m_Enemies)
	{
		i->isAlive = true;
		i->SetPosition(glm::vec3(RandNum::Instance().GetRandNum() * spawnPositionRange.x - (spawnPositionRange.x * 0.5f), //position
			RandNum::Instance().GetRandNum() * spawnPositionRange.y - (spawnPositionRange.y * 0.5f), 0));
		i->SetScale(glm::vec2(RandNum::Instance().GetRandNum() * scaleRange.x + (scaleRange.x * 0.5f), //scale
			RandNum::Instance().GetRandNum() * scaleRange.x + (scaleRange.y * 0.5f)));
	}
}

int EnemySpawner::GetEnemiesKilled() const
{
	return m_EnemiesKilled;
}
