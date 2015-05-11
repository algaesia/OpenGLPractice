#ifndef _SCENE_H
#define _SCENE_H

#include "SceneNode.h"
#include <glm\glm.hpp>
#include "Camera.h"

class Scene
{
public:
	Scene(unsigned int a_ShaderProgram);
	~Scene();

	virtual void UpdateScene(float dt);
	virtual void RenderScene() = 0;

	virtual void ResetScene() = 0;

	void AddChild(SceneNode* a_Child);
	void RemoveChild(SceneNode* a_Child);
	void SetCameraTarget(SceneNode* a_Target);

	SceneNode* GetRootNode() const;
protected:
	SceneNode* m_RootNode;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_CameraMatrix;

	unsigned int m_SceneShaderProgramID,
				 m_ProjectionViewMatrixID;

	Camera* m_SceneCamera;
};

#endif