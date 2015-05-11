#include "Utility.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include "Dimensions.h"

using std::ifstream;
using std::string;

Utility::Utility()
	: texturedShaderProgram(0),
	untexturedShaderProgram(0),
	postProcBasicShaderProgram(0),
	postProcWavyShaderProgram(0),
	lightingShaderProgram(0),
	postProcBasicVertShader(
	"#version 400\n\
	layout(location = 0) in vec4 position;\n\
	out vec2 vUV;\n\
	void main()\n\
	{ \n\
	  	vUV = position.xy * 0.5f + 0.5f; \n\
		gl_Position = position;\
	}"),
	postProcBasicFragShader(
	"#version 400\n\
	in vec2 vUV;\n\
	out vec4 outputColour;\n\
	uniform sampler2D diffuseTexture;\n\
	uniform vec2 dimensions;\n\
	uniform float offset;\n\
	float pi = 3.14159f;\n\
	vec2 pixelSize = 1 / dimensions;\n\
	void main()\n\
	{\n\
	  	vec4 centrePixel = texture2D(diffuseTexture, vUV);\n\
		outputColour = centrePixel;\n\
	}"),
	postProcWavyVertShader(
	"#version 400\n\
	layout(location = 0) in vec4 position;\n\
	out vec2 vUV;\n\
	void main()\n\
	{ \n\
	  	vUV = position.xy * 0.5f + 0.5f; \n\
		gl_Position = position;\
	}"),
	postProcWavyFragShader(
	"#version 400\n\
	in vec2 vUV;\n\
	out vec4 outputColour;\n\
	uniform sampler2D diffuseTexture;\n\
	uniform vec2 dimensions;\n\
	uniform float offset;\n\
	float pi = 3.14159f;\n\
	vec2 pixelSize = 1 / dimensions;\n\
	void main()\n\
	{\n\
		vec2 texCoord = vUV;\n\
		texCoord.x += sin(texCoord.y * 1.5f * pi + offset) / 100.0f;\n\
	  	vec4 centrePixel = texture2D(diffuseTexture, texCoord);\n\
		centrePixel += vec4(sin(texCoord.y * pi + offset) * 0.1f, cos(texCoord.y * 40 * pi + offset) / 250.0f, tan(texCoord.x * 10 * pi + offset) / 300.0f, 1);\n\
		outputColour = centrePixel;\n\
	}"),
	texturedVertexShader(
	"#version 400\n\
	layout(location = 0) in vec4 position;\n\
	layout(location = 1) in vec4 colour;\n\
	layout(location = 2) in vec2 coord;\n\
	smooth out vec4 vertColour;\n\
	smooth out vec2 texCoord;\n\
	uniform mat4 ProjectionView;\n\
	uniform mat4 Model;\n\
	void main()\n\
	{\n\
		texCoord = coord;\n\
		vertColour = colour;\n\
		gl_Position = ProjectionView * Model * position;\n\
	}"),
	texturedFragmentShader(
	"#version 400\n\
	smooth in vec4 vertColour;\n\
	smooth in vec2 texCoord;\n\
	out vec4 outputColour;\n\
	uniform sampler2D diffuseTexture;\n\
	void main()\n\
	{\n\
		outputColour = texture(diffuseTexture, texCoord).rgba * vertColour;\n\
	}"),
	untexturedVertexShader(
	"#version 400\n\
	layout(location = 0) in vec4 position;\n\
	layout(location = 1) in vec4 colour;\n\
	smooth out vec4 vertColour;\n\
	smooth out vec2 texCoord;\n\
	uniform mat4 Projection;\n\
	void main()\n\
	{\n\
		vertColour = colour;\n\
		gl_Position = Projection * position;\n\
	}"),
	untexturedFragmentShader(
	"#version 400\n\
	smooth in vec4 vertColour;\n\
	out vec4 outputColour;\n\
	void main()\n\
	{\n\
		outputColour = vertColour;\n\
	}"),
	lightingVertShader(
	"#version 400\n\
	layout (location = 0) in vec4 vertPos;\n\
	layout (location = 1) in vec4 vertNorm;\n\
	out vec3 lightIntensity;\n\
	uniform vec4 lightPos;\n\
	uniform vec3 diffReflectivity;\n\
	uniform vec3 lightSourceIntensity;\n\
	uniform mat4 Projection\n\
	uniform mat4 View;\n\
	uniform mat4 Model;\n\
	uniform mat3 NormalMat;\n\
	void main()\n\
	{\n\
		vec3 tNorm = normalize(NormalMat * vertNorm);\n\
		vec4 eyeCoords = Model * View * vec4(vertPos, 1.0);\n\
		vec3 s = normalize(vec3(lightPos - eyeCoords));\n\
		lightIntensity = lightSourceIntensity * diffReflectivity * max(dot(s, tNorm), 0.0);\n\
		gl_Position = Projection * View * Model * vertPos;\n\
	}"),
	lightingFragShader(
	"#version 400\n\
	in vec3 lightIntensity;\n\
	layout (location = 0) vec4 outputColour;\n\
	void main()\n\
	{\n\
		outputColour = vec4(lightIntensity, 1.0);\n\
	}")
{
	
}

Utility::~Utility()
{
	glDeleteProgram(texturedShaderProgram);
	glDeleteProgram(untexturedShaderProgram);
	glDeleteProgram(postProcBasicShaderProgram);
	glDeleteProgram(postProcWavyShaderProgram);
}

GLuint Utility::GetTexturedShader()
{
	if (texturedShaderProgram == 0)
	{
		texturedShaderProgram = CreateProgramFromShaderText(texturedVertexShader, texturedFragmentShader);
	}
	return texturedShaderProgram;
}

GLuint Utility::GetUntexturedShader()
{
	if (untexturedShaderProgram == 0)
	{
		untexturedShaderProgram = CreateProgramFromShaderText(untexturedVertexShader, untexturedFragmentShader);
	}
	return untexturedShaderProgram;
}

GLuint Utility::GetPostBasicShader()
{
	if (postProcBasicShaderProgram == 0)
	{
		postProcBasicShaderProgram = CreateProgramFromShaderText(postProcBasicVertShader, postProcBasicFragShader);
	}
	return postProcBasicShaderProgram;
}

GLuint Utility::GetPostWavyShader()
{
	if (postProcWavyShaderProgram == 0)
	{
		postProcWavyShaderProgram = CreateProgramFromShaderText(postProcWavyVertShader, postProcWavyFragShader);
	}
	return postProcWavyShaderProgram;
}

GLuint Utility::GetLightingShader()
{
	if (lightingShaderProgram == 0)
	{
		lightingShaderProgram = CreateProgramFromShaderText(lightingVertShader, lightingFragShader);
	}
	return lightingShaderProgram;
}

Utility& Utility::Instance()
{
	static Utility instance;
	return instance;
}

glm::mat4 Utility::GetOrtho()
{
	return glm::ortho(0.0f,
		Dimensions::Instance().GetWindowDimensions().x,
		0.0f,
		Dimensions::Instance().GetWindowDimensions().y);
}

GLuint Utility::CreateShaderFromText(GLenum a_ShaderType, const char* a_ShaderText)
{
	GLuint uiShader = glCreateShader(a_ShaderType);
	glShaderSource(uiShader, 1, &a_ShaderText, nullptr);
	glCompileShader(uiShader);

	GLint status;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, nullptr, strInfoLog);

		const char* strShaderType = nullptr;
		switch (a_ShaderType)
		{
		case GL_VERTEX_SHADER:
			strShaderType = "vertex";
			break;
		case GL_FRAGMENT_SHADER:
			strShaderType = "fragment";
			break;
		}
		fprintf(stderr, "COMPILATION FAILURE IN %s SHADER: \n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}
	return uiShader;
}

GLuint Utility::CreateShader(GLenum a_ShaderType, const char* a_ShaderFileName)
{
	string strShaderCode;
	ifstream shaderStream(a_ShaderFileName);
	if (shaderStream.is_open())
	{
		string line = "";
		while (std::getline(shaderStream, line))
		{
			strShaderCode += "\n" + line;
		}
		shaderStream.close();
	}

	char const* shaderSrcPtr = strShaderCode.c_str();
	GLuint uiShader = glCreateShader(a_ShaderType);
	glShaderSource(uiShader, 1, &shaderSrcPtr, nullptr);
	glCompileShader(uiShader);

	GLint status;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, nullptr, strInfoLog);

		const char* strShaderType = nullptr;
		switch (a_ShaderType)
		{
		case GL_VERTEX_SHADER:
			strShaderType = "vertex";
			break;
		case GL_FRAGMENT_SHADER:
			strShaderType = "fragment";
			break;
		}
		fprintf(stderr, "COMPILATION FAILURE IN %s SHADER: \n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}
	return uiShader;
}

GLuint Utility::CreateProgramFromShaderText(const char* a_VertexShader, const char* a_FragmentShader)
{
	std::vector<GLuint> shaderList;
	shaderList.push_back(CreateShaderFromText(GL_VERTEX_SHADER, a_VertexShader));
	shaderList.push_back(CreateShaderFromText(GL_FRAGMENT_SHADER, a_FragmentShader));

	GLuint uiProgram = glCreateProgram();

	for (auto& shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glAttachShader(uiProgram, *shader);
	}

	glLinkProgram(uiProgram);

	GLint status;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, nullptr, strInfoLog);
		fprintf(stderr, "LINKER FAILRE: %s\n", strInfoLog);

		delete[] strInfoLog;
	}

	for (auto& shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
}

GLuint Utility::CreateProgram(const char* a_VertexFileName, const char* a_FragFileName)
{
	std::vector<GLuint> shaderList;
	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_VertexFileName));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_FragFileName));

	GLuint uiProgram = glCreateProgram();

	for (auto& shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glAttachShader(uiProgram, *shader);
	}

	glLinkProgram(uiProgram);

	GLint status;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, nullptr, strInfoLog);
		fprintf(stderr, "LINKER FAILRE: %s\n", strInfoLog);

		delete[] strInfoLog;
	}

	for (auto& shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
}

float Utility::VectorLength(const glm::vec3& a_Vector3)
{
	return glm::sqrt(a_Vector3.x * a_Vector3.x +
		a_Vector3.y * a_Vector3.y +
		a_Vector3.z * a_Vector3.z);
}

