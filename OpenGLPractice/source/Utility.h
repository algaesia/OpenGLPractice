#ifndef _UTILITY_H
#define _UTILITY_H

#include <GLEW\glew.h>
#include <glm\glm.hpp>

enum Errors
{
	GLEW_FAILED = -3,
	WINDOW_FAILED,
	GLFW_FAILED,
	INIT_FAILED = 1,
};

class Utility
{
public:
	static Utility& Instance();
	
	glm::mat4 GetOrtho();

	float VectorLength(const glm::vec3& a_Vector3);

	GLuint GetTexturedShader();
	GLuint GetUntexturedShader();
	GLuint GetPostBasicShader();
	GLuint GetPostWavyShader();
	GLuint GetLightingShader();

	GLuint CreateProgramFromShaderText(const char* a_VertexShader, const char* a_FragmentShader);

	~Utility();
private:
	GLuint CreateShader(GLenum a_ShaderType, const char* a_ShaderFileName);
	GLuint CreateShaderFromText(GLenum a_ShaderType, const char* a_ShaderText);

	GLuint CreateProgram(const char* a_VertexFileName, const char* a_FragFileName);

	Utility();

	Utility(Utility const&) = delete;
	void operator=(Utility const&) = delete;

	const char* const postProcBasicVertShader;
	const char* const postProcBasicFragShader;

	const char* const postProcWavyVertShader;
	const char* const postProcWavyFragShader;

	const char* const texturedVertexShader;
	const char* const texturedFragmentShader;

	const char* const untexturedVertexShader;
	const char* const untexturedFragmentShader;

	const char* const lightingVertShader;
	const char* const lightingFragShader;

	unsigned int texturedShaderProgram;
	unsigned int untexturedShaderProgram;
	unsigned int postProcBasicShaderProgram;
	unsigned int postProcWavyShaderProgram;
	unsigned int lightingShaderProgram;
};

#endif