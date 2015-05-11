#include "TextHandler.h"
#include <sstream>
#include <fstream>

TextHandler::TextHandler(unsigned int a_ShaderProgram, const glm::vec3& a_Position, const glm::vec4& a_Colour)
	: Sprite(a_ShaderProgram, "resources/calibri_light_0.png", a_Position, glm::vec2(1), glm::vec2(50), a_Colour)
{
	m_Characters.reserve(256);

	for (unsigned int i = 0; i < m_Characters.capacity(); ++i)
	{
		m_Characters.push_back(Character());
	}

	XMLDocument bmpDoc;
	XMLError loadResult = bmpDoc.LoadFile("resources/calibri_light.fnt");
	XMLCheckResult(loadResult);

	//structure of xml document is different.
	//root node has no children
	//next root node - "font" - has the data
	//we want, all data required are children of this node
	XMLNode* fontNode = bmpDoc.FirstChild()->NextSibling();
	if (fontNode == nullptr)
	{
		printf("XML FILE READ ERROR\n");
		return;
	}

	//total number of characters in XML file
	charsCount = fontNode->FirstChildElement("chars")->FirstAttribute()->IntValue();

	XMLNode* firstChild = fontNode->FirstChildElement("chars")->FirstChild();
	XMLElement* t = firstChild->ToElement();

	do
	{
		Character temp;

		//id represents the ASCII value
		temp.value = atoi(t->Attribute("id"));
		temp.x = atoi(t->Attribute("x"));
		temp.y = atoi(t->Attribute("y"));
		temp.width = atoi(t->Attribute("width"));
		temp.height = atoi(t->Attribute("height"));

		m_Characters[temp.value] = temp;

		//move onto the next one
		t = t->NextSibling()->ToElement();
	} while (t->NextSibling() != nullptr);
}

TextHandler::~TextHandler()
{
	m_Characters.clear();
}

void TextHandler::DrawString(const char* a_StringToDraw)
{
	glm::vec3 currentCentre = m_CentrePos;
	float currentX = 0;

	//points to beginning of char array
	const char* currentLetter = a_StringToDraw;

	//keep going until null terminator is hit
	while (*currentLetter != '\0')
	{
		//can be used as index into characters vector
		int arrayIndex = (int)(*currentLetter);

		//index into characters vector to find data required
		Character t = m_Characters[arrayIndex];		

		//move centre pos along, so that images arent drawn on top of each other
		m_CentrePos.x = currentCentre.x + currentX + m_Dimensions.x * m_Scale.x + t.width * 0.5f;

		//need to account for XML coords has top left as origin
		quad[0].coord = glm::vec2((float)(t.x + t.width) / (float)textureWidth, 1 - (float)(t.y + t.height) / (float)textureHeight);
		quad[1].coord = glm::vec2((float)(t.x + t.width) / (float)textureWidth, 1 - (float)t.y / (float)textureHeight);
		quad[2].coord = glm::vec2((float)t.x / (float)textureWidth, 1 - (float)t.y / (float)textureHeight);
		quad[3].coord = glm::vec2((float)t.x / (float)textureWidth, 1 - (float)(t.y + t.height) / (float)textureHeight);

		//update the transforms then render the single image
		Sprite::Update(0); //set local transform
		Sprite::UpdateTransforms(); //set global based on parent
		Sprite::Render(); //draw image

		//adding spaces in the string done with respect to the
		//scale provided initially
		currentX += (float)(t.width * m_Dimensions.x * 0.075f);
		
		//progress pointer
		currentLetter++;
	}

	m_CentrePos = currentCentre;
}
