#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#include <vector>
#include "Scene.h"

class SceneManager
{
public:
	~SceneManager();

	static SceneManager& Instance();

	void CreateScenes(unsigned int a_ShaderProgram);

	void UpdateCurrentScene(float dt);
	void RenderCurrentScene();

	void ChangeScene(int a_SceneNum);
	void IncrementScene();
private:
	SceneManager();
	
	SceneManager(const SceneManager&) = delete;
	void operator=(const SceneManager&) = delete;

	void AddScene(Scene* a_Scene);
	void RemoveScene(Scene* a_Scene);

	std::vector<Scene*> m_Scenes;

	int m_CurrentScene;
	int m_PreviousScene;
};

#endif