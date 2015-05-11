#include "Sprite.h"
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Utility.h"
#include "TextureManager.h"

Sprite::Sprite(unsigned int a_ShaderProgram, 
			   const char* a_TextureName, 
			   const glm::vec3& a_CentrePos,
			   const glm::vec2& a_Scale,
			   const glm::vec2& a_Dimensions,
			   const glm::vec4& a_Colour)
		: SceneNode(),
		m_RateOfRotation(0.025f)
{
	if (a_TextureName != nullptr)
	{
		TextureManager::Instance().Insert(a_TextureName, &textureID, &textureWidth, &textureHeight);
	}
	else
	{
		textureWidth = textureHeight = textureID = -1;
	}

	m_Scale = a_Scale;
	m_Dimensions = a_Dimensions;
	m_CentrePos = a_CentrePos;

	shaderProgram = a_ShaderProgram;

	quad[0].position = glm::vec4(m_Dimensions.x * 0.5f, -m_Dimensions.y * 0.5f, 0, 1);
	quad[1].position = glm::vec4(m_Dimensions.x * 0.5f, m_Dimensions.y * 0.5f, 0, 1);
	quad[2].position = glm::vec4(-m_Dimensions.x * 0.5f, m_Dimensions.y * 0.5f, 0, 1);
	quad[3].position = glm::vec4(-m_Dimensions.x * 0.5f, -m_Dimensions.y * 0.5f, 0, 1);

	quad[0].colour = a_Colour;
	quad[1].colour = a_Colour;
	quad[2].colour = a_Colour;
	quad[3].colour = a_Colour;

	quad[0].coord = glm::vec2(1, 0);
	quad[1].coord = glm::vec2(1, 1);
	quad[2].coord = glm::vec2(0, 1);
	quad[3].coord = glm::vec2(0, 0);

	quadVBO = quadIBO = 0;
	glGenBuffers(1, &quadVBO);
	glGenBuffers(1, &quadIBO);

	if (quadVBO != 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, quad, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 2));

		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
	{
		std::cout << "ERROR SETTING UP VBO" << std::endl;
		return;
	}

	if (quadIBO != 0)
	{
		unsigned int indices[6] =
		{
			0, 1, 2,
			2, 0, 3,
		};

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else
	{
		std::cout << "ERROR SETTING UP IBO" << std::endl;
		return;
	}

	glUseProgram(shaderProgram);

	modelMatID = glGetUniformLocation(shaderProgram, "Model");
	diffuseTextureID = glGetUniformLocation(shaderProgram, "diffuseTexture");

	glUseProgram(0);
}

Sprite::~Sprite()
{
	glDeleteBuffers(1, &quadIBO);
	glDeleteBuffers(1, &quadVBO);
}

void Sprite::SetShaderProgram(unsigned int a_ShaderProgram)
{
	if (glIsProgram(a_ShaderProgram))
	{
		shaderProgram = a_ShaderProgram;
	}
}

bool Sprite::CheckCollisions(const glm::vec3& a_CentrePos, const glm::vec2& a_Scale, const glm::vec2& a_Dimensions)
{
	if (m_CentrePos.x + m_Dimensions.x * m_Scale.x * 0.5f > a_CentrePos.x - a_Dimensions.x * a_Scale.x * 0.5f && m_CentrePos.x - m_Dimensions.x * m_Scale.x * 0.5f < a_CentrePos.x + a_Dimensions.x * a_Scale.x * 0.5f)
	{
		if (m_CentrePos.y + m_Dimensions.y * m_Scale.y * 0.5f > a_CentrePos.y - a_Dimensions.y * a_Scale.y * 0.5f && m_CentrePos.y - m_Dimensions.y * m_Scale.y * 0.5f < a_CentrePos.y + a_Dimensions.y * a_Scale.y * 0.5f)
		{
			return true;
		}
	}
	return false;
}

void Sprite::Render() const
{
	glUseProgram(shaderProgram);

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

	//updating any changes made to quad compared to last frame
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4, quad);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 2));

	glUniform1i(diffuseTextureID, 0);

	glUniformMatrix4fv(modelMatID, 1, GL_FALSE, glm::value_ptr(m_GlobalTransform));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);

	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, nullptr);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(0);
}
