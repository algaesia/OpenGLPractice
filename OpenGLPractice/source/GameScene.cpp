#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\type_ptr.hpp>

#include "GameScene.h"
#include "RandNum.h"
#include "Dimensions.h"
#include <string>

#include "InputHandler.h"
#include "SceneManager.h"

GameScene::GameScene(unsigned int a_ShaderProgram)
	: Scene(a_ShaderProgram),
	m_TextHandler(TextHandler(a_ShaderProgram, glm::vec3(), glm::vec4(1,0,0,1))),
	m_WorldBackgroundImage(new Sprite(a_ShaderProgram,
									  "resources/blankSquare.png", 
									  glm::vec3(), 
									  glm::vec2(1), 
									  glm::vec2(Dimensions::Instance().GetWorldDimensions().x * 2, Dimensions::Instance().GetWorldDimensions().y * 2), 
									  glm::vec4(0, 0, 0, 1))),
	m_BackgroundImage1(new Sprite(a_ShaderProgram, 
								 "resources/Tulips.jpg", 
								 glm::vec3(0, 400, 0),
								 glm::vec2(1),
								 glm::vec2(800, 1440),
								 glm::vec4(1))),
	m_BackgroundImage2(new Sprite(a_ShaderProgram, 
								 "resources/Tulips.jpg", 
								 glm::vec3(0, -400, 0),
								 glm::vec2(1),
								 glm::vec2(800, 1440),
								 glm::vec4(1))),
	m_Player(new Player(a_ShaderProgram, "resources/Koala.jpg", glm::vec3(), glm::vec2(1), glm::vec2(60), glm::vec4(1, 1, 0, 1))),
	m_MaxNumEnemies(50),
	m_EnemySpawner(a_ShaderProgram, m_Player, 25, glm::vec2(100)) //enemy spawn is not new'd so does not need to be deleted
{
	//responsibility of deletion moves to scene node
	//as they are now children of the scene
	//destructor for root node cleans up children too
	AddChild(m_WorldBackgroundImage);
	AddChild(m_BackgroundImage1);
	AddChild(m_BackgroundImage2);
	AddChild(m_Player);
}

GameScene::~GameScene()
{
	delete m_Player;
	delete m_BackgroundImage1;
	delete m_BackgroundImage2;
	delete m_WorldBackgroundImage;
}

void GameScene::UpdateScene(float dt)
{
	SetCameraTarget(m_Player);

	//reset pos based on position of background image
	if (!m_Player->CheckCollisions(m_BackgroundImage1->GetPosition(), m_BackgroundImage1->GetScale(), m_BackgroundImage1->GetDimensions()) && 
		!m_Player->CheckCollisions(m_BackgroundImage2->GetPosition(), m_BackgroundImage2->GetScale(), m_BackgroundImage2->GetDimensions()))
	{
		m_Player->ResetPlayer();
	}

	m_EnemySpawner.UpdateEnemies(dt);

	if (InputHandler::Instance().CheckKeyDown(GLFW_KEY_ESCAPE))
	{
		//back to first scene
		SceneManager::Instance().ChangeScene(0);
	}

	printf("PLAYER POS X: %f Y: %f\n", m_Player->GetPosition().x, m_Player->GetPosition().y);

	Scene::UpdateScene(dt);
}

void GameScene::RenderScene()
{
	glUseProgram(m_SceneShaderProgramID);

	glUniformMatrix4fv(m_ProjectionViewMatrixID, 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix * m_ViewMatrix));

	glUseProgram(0);

	if (m_RootNode != nullptr)
	{
		m_RootNode->RenderTree();
	}

	m_EnemySpawner.RenderEnemies();

	m_TextHandler.SetPosition(glm::vec3(-800, 0, 0));
	m_TextHandler.DrawString("GAME SCENE");

	m_TextHandler.SetPosition(glm::vec3(-800, -100, 0));
	std::string scoreString = "CURRENT SCORE: " + std::to_string(m_EnemySpawner.GetEnemiesKilled());
	m_TextHandler.DrawString(scoreString.c_str());
}

void GameScene::ResetScene()
{
	m_Player->ResetPlayer();
	m_EnemySpawner.ResetEnemies();
}
