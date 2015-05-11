#include "MainMenuScene.h"
#include "Sprite.h"
#include "TextHandler.h"

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\type_ptr.hpp>

#include "SceneManager.h"
#include "InputHandler.h"

MainMenuScene::MainMenuScene(unsigned int a_ShaderProgram)
	: Scene(a_ShaderProgram),
	m_TextHandler(TextHandler(a_ShaderProgram, glm::vec3(0), glm::vec4(1, 0, 0, 1))),
	backgroundImage(new Sprite(a_ShaderProgram, "resources/LightHouse.jpg", glm::vec3(), glm::vec2(1), glm::vec2(1280, 720), glm::vec4(1)))
{
	AddChild(backgroundImage);
}

MainMenuScene::~MainMenuScene()
{
	delete backgroundImage;
}

void MainMenuScene::UpdateScene(float dt)
{
	SetCameraTarget(backgroundImage);

	if (InputHandler::Instance().CheckKeyDown(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
	}

	if (InputHandler::Instance().CheckKeyDown(GLFW_KEY_ENTER))
	{
		SceneManager::Instance().ChangeScene(1);
	}

	Scene::UpdateScene(dt);
}

void MainMenuScene::RenderScene()
{
	glUseProgram(m_SceneShaderProgramID);

	glUniformMatrix4fv(m_ProjectionViewMatrixID, 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix * m_ViewMatrix));

	glUseProgram(0);

	if (m_RootNode != nullptr)
	{
		m_RootNode->RenderTree();
	}

	m_TextHandler.DrawString("main");
}
