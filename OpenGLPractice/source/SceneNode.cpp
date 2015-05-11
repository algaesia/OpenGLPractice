#include "SceneNode.h"
#include <glm\gtc\matrix_transform.hpp>

unsigned int SceneNode::nodeCount = 0;

SceneNode::SceneNode()
	: m_CentrePos(glm::vec3()),
	m_Scale(glm::vec2(1)),
	m_Dimensions(glm::vec2(100, 100)),
	m_Rotation(0.0f),
	nodeID(nodeCount),
	m_Parent(nullptr), //did not new parent - no deletion here
	m_GlobalTransform(glm::mat4()),
	m_LocalTransform(glm::mat4()),
	startingChildCount(100)
{
	nodeCount++;
	m_Children.reserve(startingChildCount);
}

SceneNode::~SceneNode()
{
	for (unsigned int i = 0; i < m_Children.size(); ++i)
	{
		delete m_Children[i];
	}
	m_Children.clear();
}

void SceneNode::Update(float dt) 
{
	m_LocalTransform = glm::translate(glm::mat4(), glm::vec3(m_CentrePos.x, m_CentrePos.y, m_CentrePos.z)) *
					   glm::rotate(glm::mat4(), m_Rotation, glm::vec3(0, 0, 1)) *
					   glm::scale(glm::mat4(), glm::vec3(m_Scale.x, m_Scale.y, 1));
}

glm::vec2 SceneNode::GetDimensions() const
{
	return m_Dimensions;
}

glm::vec3 SceneNode::GetForward() const
{
	glm::vec4 t = glm::rotate(glm::mat4(), m_Rotation, glm::vec3(0, 0, 1))[1];
	return glm::vec3(t.x, t.y, 0);
}

glm::vec2 SceneNode::GetScale() const
{
	return m_Scale;
}

void SceneNode::Render() const { }

void SceneNode::SetParent(SceneNode* a_Parent)
{
	if (m_Parent != nullptr)
	{
		m_Parent->RemoveChild(this);
	}
	m_Parent = a_Parent;
}

SceneNode* SceneNode::GetParent() const
{
	return m_Parent;
}

//need to new the scenenode in the function
//instead of newing outside and passing
//pointer in, ownership needs to belong
//to the scenenode itself
void SceneNode::AddChild(SceneNode* a_Child)
{
	if (a_Child != nullptr)
	{
		if (a_Child->m_Parent == nullptr)
		{
			a_Child->m_Parent = this;
		}

		m_Children.push_back(a_Child);
	}
}

void SceneNode::RemoveChild(SceneNode* a_Child)
{
	if (a_Child != nullptr)
	{
		for (unsigned int i = 0; i < m_Children.size(); ++i)
		{
			if (*(m_Children.begin() + i) == a_Child)
			{
				m_Children.erase(m_Children.begin() + i);
				break;
			}
		}
	}
}

void SceneNode::UpdateTree(float dt)
{
	Update(dt);

	for (SceneNode* t : m_Children)
	{
		t->UpdateTree(dt);
	}

	UpdateTransforms();
}

void SceneNode::RenderTree() const
{
	//draw children, then draw parent
	for (SceneNode* t : m_Children)
	{
		t->RenderTree();
	}

	Render();
}

void SceneNode::UpdateTransforms()
{
	if (m_Parent != nullptr)
	{
		m_GlobalTransform = m_Parent->GetGlobalTransform() * m_LocalTransform;
	}
	else
	{
		m_GlobalTransform = m_LocalTransform;
	}
}

glm::mat4 SceneNode::GetGlobalTransform() const
{
	return m_GlobalTransform;
}

glm::mat4 SceneNode::GetLocalTransform() const
{
	return m_LocalTransform;
}

glm::vec3 SceneNode::GetPosition() const
{
	return glm::vec3(m_GlobalTransform[3].x, m_GlobalTransform[3].y, m_GlobalTransform[3].z);
}
