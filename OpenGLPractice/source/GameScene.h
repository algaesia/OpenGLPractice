#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include <vector>

#include "Scene.h"
#include "TextHandler.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemySpawner.h"

class GameScene : public Scene
{
public:
	GameScene(unsigned int a_ShaderProgram);
	~GameScene();

	virtual void UpdateScene(float dt);
	virtual void RenderScene();

	virtual void ResetScene();
private:
	int m_MaxNumEnemies;

	Sprite* m_BackgroundImage1;
	Sprite* m_BackgroundImage2;
	Sprite* m_WorldBackgroundImage;
	Player* m_Player;

	TextHandler m_TextHandler;
	EnemySpawner m_EnemySpawner;
};

#endif