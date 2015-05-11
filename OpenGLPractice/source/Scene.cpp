#include "Scene.h"
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Utility.h"

//root node is the centre of the scene,
//camera just points to a target area
Scene::Scene(unsigned int a_ShaderProgram)
	: m_SceneShaderProgramID(a_ShaderProgram),
	m_RootNode(new SceneNode())
{
	m_SceneCamera = new Camera(glm::vec3());

	m_CameraMatrix = glm::translate(glm::mat4(), m_SceneCamera->GetPosition());
	m_ViewMatrix = glm::inverse(m_CameraMatrix);
	m_ProjectionMatrix = Utility::Instance().GetOrtho();

	glUseProgram(m_SceneShaderProgramID);

	m_ProjectionViewMatrixID = glGetUniformLocation(m_SceneShaderProgramID, "ProjectionView");

	glUseProgram(0);
}

Scene::~Scene()
{
	delete m_SceneCamera;
	delete m_RootNode;
}

void Scene::UpdateScene(float dt)
{
	m_SceneCamera->Update(dt);
	m_SceneCamera->UpdateTransforms();

	m_CameraMatrix = glm::translate(glm::mat4(), m_SceneCamera->GetPosition());
	m_ViewMatrix = glm::inverse(m_CameraMatrix);

	if (m_RootNode != nullptr)
	{
		m_RootNode->UpdateTree(dt);
	}
}

SceneNode* Scene::GetRootNode() const
{
	return m_RootNode;
}

void Scene::SetCameraTarget(SceneNode* a_Target)
{
	m_SceneCamera->SetTarget(a_Target);
}

void Scene::AddChild(SceneNode* a_Child)
{
	if (a_Child != nullptr)
	{
		m_RootNode->AddChild(a_Child);
	}
}

void Scene::RemoveChild(SceneNode* a_Child)
{
	if (a_Child != nullptr)
	{
		m_RootNode->RemoveChild(a_Child);
	}
}
