#ifndef _SCENE_NODE_H
#define _SCENE_NODE_H

#include <glm\glm.hpp>
#include <vector>

class SceneNode	
{
public:
	SceneNode();
	virtual ~SceneNode();

	void SetParent(SceneNode* a_Parent);
	SceneNode* GetParent() const;

	void AddChild(SceneNode* a_Child);
	void RemoveChild(SceneNode* a_Child);

	glm::mat4 GetGlobalTransform() const;
	glm::mat4 GetLocalTransform() const;

	glm::vec3 GetPosition() const;
	glm::vec3 GetForward() const;

	glm::vec2 GetScale() const;
	glm::vec2 GetDimensions() const;

	void UpdateTree(float dt);
	void RenderTree() const;

	void UpdateTransforms();

	void SetPosition(const glm::vec3& a_Position)
	{
		m_CentrePos = a_Position;
	}
protected:
	virtual void Update(float dt);
	virtual void Render() const;

	glm::mat4 m_LocalTransform;
	glm::mat4 m_GlobalTransform;

	glm::vec3 m_CentrePos;
	glm::vec2 m_Scale;
	glm::vec2 m_Dimensions;

	float m_Rotation;
private:
	SceneNode* m_Parent;
	std::vector<SceneNode*> m_Children;
	static unsigned int nodeCount;
	unsigned int nodeID;
	int startingChildCount;
};

#endif