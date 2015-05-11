#include "DebugLines.h"
#include "Utility.h"
#include <glm\gtc\type_ptr.hpp>

DebugLines::DebugLines()
	: m_ShaderProgram(Utility::Instance().GetUntexturedShader())
{
	GLint prevShader;
	glGetIntegerv(GL_CURRENT_PROGRAM, &prevShader);

	glUseProgram(m_ShaderProgram);

	projModelID = glGetUniformLocation(m_ShaderProgram, "Projection");
	glUniformMatrix4fv(projModelID, 1, GL_FALSE, glm::value_ptr(Utility::Instance().GetOrtho()));

	glUseProgram(prevShader);
}

DebugLines::~DebugLines()
{
	m_Lines.clear();
}

DebugLines& DebugLines::Instance()
{
	static DebugLines instance;
	return instance;
}

void DebugLines::AddLine(const glm::vec4& a_Start, const glm::vec4& a_End, const glm::vec4& a_Colour)
{
	SimpleVert start, end;
	start.position = a_Start;
	start.colour = a_Colour;

	end.position = a_End;
	end.colour = a_Colour;

	m_Lines.push_back(start);
	m_Lines.push_back(end);
}

void DebugLines::Render()
{
	if (m_Lines.empty())
	{
		return;
	}

	GLint prevShader;
	glGetIntegerv(GL_CURRENT_PROGRAM, &prevShader);
	glUseProgram(m_ShaderProgram);

	unsigned int lineVBO;
	glGenBuffers(1, &lineVBO);
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SimpleVert) * m_Lines.size(), &m_Lines[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(SimpleVert), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SimpleVert), (void*)sizeof(glm::vec4));

	glDrawArrays(GL_LINES, 0, m_Lines.size());

	glDeleteBuffers(1, &lineVBO);

	glUseProgram(prevShader);

	m_Lines.clear();
}
