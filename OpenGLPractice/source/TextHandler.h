#ifndef _TEXT_HANDLER_H
#define _TEXT_HANDLER_H

struct Character
{
	int x, y, width, height, value;
};

#include <vector>
#include <tinyXML2\tinyxml2.h>
using namespace tinyxml2;

#include "Sprite.h"

//parses xml data that points
//to sections of the font bmp
//locating specific letters
//part of that image is then
//drawn onto a quad and displayed
//onscreen
//Based off Rebecca Fernandez's Text class
//https://github.com/BecFernandez/OpenGLPractice/blob/master/MorePractice/MorePractice/Text.cpp
class TextHandler : public Sprite
{
public:
	TextHandler(unsigned int a_ShaderProgram, const glm::vec3& a_Position = glm::vec3(), const glm::vec4& a_Colour = glm::vec4(1));
	~TextHandler();

	void DrawString(const char* a_StringToDraw);
	void SetPosition(const glm::vec3& a_Position)
	{
		m_CentrePos = a_Position;
	}
private:
	std::vector<Character> m_Characters;
	XMLError XMLCheckResult(XMLError a_Result)
	{
		if (a_Result != XML_SUCCESS) 
		{
			printf("Error: %i\n", a_Result); 
		}
		return a_Result;
	}
	int charsCount;
};

#endif