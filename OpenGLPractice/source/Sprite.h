#ifndef _SPRITE_H
#define _SPRITE_H

#include "SceneNode.h"
#include <glm\glm.hpp>

struct Vertex
{
	glm::vec4 position;
	glm::vec4 colour;
	glm::vec2 coord;
};

class Sprite : public SceneNode
{
public:
	Sprite(unsigned int a_ShaderProgram,
		   const char* a_TextureName,
		   const glm::vec3& a_CentrePos,
		   const glm::vec2& a_Scale,
		   const glm::vec2& a_Dimensions,
		   const glm::vec4& a_Colour);
	~Sprite();
	
	virtual void Render() const;
	
	bool CheckCollisions(const glm::vec3& a_CentrePos, const glm::vec2& a_Scale, const glm::vec2& a_Dimensions);
	void SetShaderProgram(unsigned int a_ShaderProgram);
protected:
	Vertex quad[4];

	unsigned int quadIBO, quadVBO, shaderProgram, modelMatID, textureID, diffuseTextureID;
	int textureWidth, textureHeight;

	//calculated in radians
	float m_RateOfRotation;
};

#endif