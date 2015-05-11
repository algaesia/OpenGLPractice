#include "SceneManager.h"
#include "MainMenuScene.h"
#include "GameScene.h"

SceneManager::SceneManager()
	: m_CurrentScene(0), m_PreviousScene(0)
{
	m_Scenes.reserve(5);
}

SceneManager::~SceneManager()
{
	for (unsigned int i = 0; i < m_Scenes.size(); ++i)
	{
		delete m_Scenes[i];
	}
	m_Scenes.clear();
}

SceneManager& SceneManager::Instance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::AddScene(Scene* a_Scene)
{
	m_Scenes.push_back(a_Scene);
}

void SceneManager::CreateScenes(unsigned int a_ShaderProgram)
{
	m_Scenes.push_back(new MainMenuScene(a_ShaderProgram));
	m_Scenes.push_back(new GameScene(a_ShaderProgram));
}

void SceneManager::RemoveScene(Scene* a_Scene)
{
	std::vector<Scene*>::iterator sceneIter;
	for (sceneIter = m_Scenes.begin(); sceneIter != m_Scenes.end();)
	{
		if ((*sceneIter) == a_Scene)
		{
			delete (*sceneIter);
			m_Scenes.erase(sceneIter);
			return;
		}
		else
		{
			++sceneIter;
		}
	}
}

void SceneManager::UpdateCurrentScene(float dt)
{
	if (m_Scenes.size() > 0)
	{
		m_Scenes[m_CurrentScene]->UpdateScene(dt);
	}
}

void SceneManager::RenderCurrentScene()
{
	if (m_Scenes.size() > 0)
	{
		m_Scenes[m_CurrentScene]->RenderScene();
	}
}

void SceneManager::ChangeScene(int a_SceneNum)
{
	if (m_Scenes.size() > 0 && a_SceneNum >= 0 && (unsigned int)a_SceneNum < m_Scenes.size())
	{
		m_CurrentScene = a_SceneNum;
		m_Scenes[m_CurrentScene]->ResetScene();
	}
	else
	{
		printf("SCENE NUMBER OUTSIDE OF LIMITS 0 & SIZE OF ARRAY - 1");
	}
}

void SceneManager::IncrementScene()
{
	++m_CurrentScene;

	if ((unsigned int)m_CurrentScene > m_Scenes.size() - 1)
	{
		m_CurrentScene = 0;
	}
}
