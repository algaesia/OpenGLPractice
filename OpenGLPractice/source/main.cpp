#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "Dimensions.h"
#include "GameTimer.h"
#include "Utility.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "PostRectangle.h"
#include "InputHandler.h"

//reference to pointer yields modifiable value that is used like a normal pointer
bool init(GLFWwindow*& a_Window, const char* a_WindowTitle, int a_WindowWidth = 1280, int a_WindowHeight = 720)
{
	if (!glfwInit())
	{
		printf("FAILED TO INIT GLFW");
		return false;
	}

	Dimensions::Instance().SetWindowDimensions(a_WindowWidth, a_WindowHeight);
	a_Window = glfwCreateWindow((int)Dimensions::Instance().GetWindowDimensions().x, (int)Dimensions::Instance().GetWindowDimensions().y, a_WindowTitle, nullptr, nullptr);

	if (!a_Window)
	{
		printf("FAILED TO CREATE WINDOW INSTANCE");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(a_Window);

	if (glewInit() != GLEW_OK)
	{
		printf("FAILED TO INIT GLEW");
		glfwTerminate();
		return false;
	}

	return true;
}

int main()
{
	GLFWwindow* window = nullptr;

	if (!init(window, "Test Project"))
	{
		system("pause");
		return INIT_FAILED;
	}

	double simulationTime = 0;

	unsigned int normalShaderProgram = Utility::Instance().GetTexturedShader();

	TextureManager::Instance().LoadTextures();

	SceneManager::Instance().CreateScenes(normalShaderProgram);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.25f, 0.5f, 0.25f, 1);

	PostRectangle test = PostRectangle();

	//SoundManager::Instance().Play("background1");

	while (!glfwWindowShouldClose(window))
	{
		GameTimer::Instance().StartTimer();

		glClear(GL_COLOR_BUFFER_BIT);

		double realTime = GameTimer::Instance().GetTotalTime();

		//updating
		while (simulationTime < realTime)
		{
			simulationTime += 1 / 60.0;

			float dt = (float)GameTimer::Instance().GetElapsedTime();

			//SoundManager::Instance().Update();
			SceneManager::Instance().UpdateCurrentScene(dt);
		}

		test.BindFramebuffer();

		SceneManager::Instance().RenderCurrentScene();

		test.UnbindFramebuffer();
		test.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		GameTimer::Instance().EndTimer();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
