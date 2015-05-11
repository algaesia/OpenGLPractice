#ifndef _POST_RECTANGLE_H
#define _POST_RECTANGLE_H

#include <GLEW\glew.h>
#include "Utility.h"

class PostRectangle
{
public:
	PostRectangle();
	~PostRectangle();

	void BindFramebuffer();
	void UnbindFramebuffer();

	void Render() const;
private:
	unsigned int quadVBO, quadIBO, quadRBO, quadFBT, quadFBO, shaderProgram, offsetID;
};

#endif