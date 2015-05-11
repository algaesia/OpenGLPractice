#ifndef _DEBUG_H
#define _DEBUG_H

#include <glm\glm.hpp>
#include <vector>

struct SimpleVert
{
	glm::vec4 position;
	glm::vec4 colour;
};

class DebugLines
{
public:
	static DebugLines& Instance();

	void AddLine(const glm::vec4& a_Start, const glm::vec4& a_End, const glm::vec4& a_Colour = glm::vec4(1));
	void Render();
private:
	DebugLines();
	~DebugLines();

	DebugLines(const DebugLines&) = delete;
	void operator=(const DebugLines&) = delete;

	std::vector<SimpleVert> m_Lines;
	unsigned int m_ShaderProgram, projModelID;
};

#endif