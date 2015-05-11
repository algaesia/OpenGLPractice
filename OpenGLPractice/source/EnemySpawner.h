#ifndef _ENEMY_SPAWNER_H
#define _ENEMY_SPAWNER_H

#include <vector>
#include "Enemy.h"
#include "Player.h"

class EnemySpawner
{
public:
	EnemySpawner(unsigned int a_ShaderProgram, Player* a_PlayerRef, int a_MaxNumEnemies = 50, const glm::vec2& a_DimensionsRange = glm::vec2(1), const glm::vec2& a_ScaleRange = glm::vec2(1));
	~EnemySpawner();

	void UpdateEnemies(float dt);
	void RenderEnemies();
	void ResetDeadEnemies();
	void ResetEnemies();
	int GetEnemiesKilled() const;
private:
	unsigned int m_ShaderProgram;

	int m_MaxNumEnemies;
	int m_EnemiesKilled;

	glm::vec2 spawnPositionRange;
	glm::vec2 scaleRange;
	glm::vec2 dimensionsRange;

	std::vector<Enemy*> m_Enemies;

	//pointer can't point to something else
	//data pointed to can't change
	Player* const m_PlayerRef;
};

#endif