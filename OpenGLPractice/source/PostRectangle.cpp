#include "PostRectangle.h"
#include <iostream>
#include "Dimensions.h"
#include <glm\gtc\type_ptr.hpp>
#include "GameTimer.h"

PostRectangle::PostRectangle()
	: quadVBO(0),
	  quadIBO(0),
	  quadRBO(0),
	  quadFBT(0),
	  quadFBO(0),
	  shaderProgram(0)
{
	float quadVertices[] =
	{
		-1, -1, 0, 1,
		-1, 1, 0, 1,
		1, 1, 0, 1,
		1, -1, 0, 1
	};

	unsigned int quadIndices[] =
	{
		0, 1, 2,
		2, 0, 3,
	};

	glGenBuffers(1, &quadVBO);
	if (quadVBO != 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, quadVertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
	{
		printf("ERROR CREATING VERTEX BUFFER OBJECT\n");
	}

	glGenBuffers(1, &quadIBO);
	if (quadIBO != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, quadIndices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else
	{
		printf("ERROR CREATING INDEX BUFFER OBJECT\n");
	}

	glGenRenderbuffers(1, &quadRBO);
	if (quadRBO != 0)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, quadRBO);

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (GLsizei)(Dimensions::Instance().GetWindowDimensions().x), (GLsizei)(Dimensions::Instance().GetWindowDimensions().y));

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
	else
	{
		printf("ERROR CREATING RENDER BUFFER OBJECT\n");
	}

	glGenTextures(1, &quadFBT);
	if (quadFBT != 0)
	{
		glBindTexture(GL_TEXTURE_2D, quadFBT);

		//generate texture same dimensions as window
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, (GLsizei)(Dimensions::Instance().GetWindowDimensions().x), (GLsizei)(Dimensions::Instance().GetWindowDimensions().y), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

		//any values of s,t that go over 1, is clamped to the value seen at 1
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		printf("ERROR CREATING FRAME BUFFER TEXTURE\n");
	}

	glGenFramebuffers(1, &quadFBO);
	if (quadFBO != 0)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, quadFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, quadFBT, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, quadRBO);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			printf("ERROR COMPLETING FRAME BUFFER CREATION\n");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else
	{
		printf("ERROR CREATING FRAME BUFFER OBJECT\n");
	}

	shaderProgram = Utility::Instance().GetPostBasicShader();

	glUseProgram(shaderProgram);

	//non-changing values, pass once only
	glUniform1i(glGetUniformLocation(shaderProgram, "diffuseTexture"), 0);
	glUniform2i(glGetUniformLocation(shaderProgram, "dimensions"), Dimensions::Instance().GetWindowDimensions().x, Dimensions::Instance().GetWindowDimensions().y);
	offsetID = glGetUniformLocation(shaderProgram, "offset");

	glUseProgram(0);
}

PostRectangle::~PostRectangle()
{
	glDeleteBuffers(1, &quadVBO);
	glDeleteBuffers(1, &quadIBO);
	glDeleteBuffers(1, &quadFBO);
	glDeleteRenderbuffers(1, &quadRBO);
	glDeleteTextures(1, &quadFBT);
}

void PostRectangle::BindFramebuffer()
{
	//x,y specifies the left corner
	glViewport(0, 0, Dimensions::Instance().GetWindowDimensions().x, Dimensions::Instance().GetWindowDimensions().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, quadFBO);
}

void PostRectangle::UnbindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, Dimensions::Instance().GetWindowDimensions().x, Dimensions::Instance().GetWindowDimensions().y);
}

void PostRectangle::Render() const
{
	glUseProgram(shaderProgram);

	glUniform1f(offsetID, GameTimer::Instance().GetTotalTime());

	//bind required buffers and texture
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, quadFBT);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);

	//draw elements
	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, nullptr);

	//unbind used buffers and textures
	glDisableVertexAttribArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(0);
}
