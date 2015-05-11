#include "InputHandler.h"
#include <GLFW\glfw3.h>

InputHandler::InputHandler()
{
	for (int i = 0; i < 300; ++i)
	{
		//all keys start off as released
		IsKeyDown[i] = IsKeyHeld[i] = false;
	}
}

InputHandler& InputHandler::Instance()
{
	static InputHandler instance;
	return instance;
}

bool InputHandler::CheckKeyDown(int a_KeyCode)
{
	//first instance of press, not held previous frame - both true
	if (glfwGetKey(glfwGetCurrentContext(), a_KeyCode) == GLFW_PRESS && !IsKeyHeld[a_KeyCode])
	{
		//true for first frame only
		IsKeyDown[a_KeyCode] = true;

		//true as long as key is pressed
		IsKeyHeld[a_KeyCode] = true;
	}
	//next frame, so set key down to false, while key held remains true
	else if (glfwGetKey(glfwGetCurrentContext(), a_KeyCode) == GLFW_PRESS && IsKeyHeld[a_KeyCode])
	{
		IsKeyDown[a_KeyCode] = false;
	}
	//key is not pressed
	else
	{
		IsKeyDown[a_KeyCode] = false;
		IsKeyHeld[a_KeyCode] = false;
	}

	return IsKeyDown[a_KeyCode];
}

bool InputHandler::CheckKeyHeld(int a_KeyCode)
{
	//first instance of press, not held previous frame - both true
	if (glfwGetKey(glfwGetCurrentContext(), a_KeyCode) == GLFW_PRESS && !IsKeyHeld[a_KeyCode])
	{
		//true for first frame only
		IsKeyDown[a_KeyCode] = true;

		//true as long as key is pressed
		IsKeyHeld[a_KeyCode] = true;
	}
	//next frame, so set key down to false, while key held remains true
	else if (glfwGetKey(glfwGetCurrentContext(), a_KeyCode) == GLFW_PRESS && IsKeyHeld[a_KeyCode])
	{
		IsKeyDown[a_KeyCode] = false;
	}
	//key is not pressed
	else
	{
		IsKeyDown[a_KeyCode] = false;
		IsKeyHeld[a_KeyCode] = false;
	}

	return IsKeyHeld[a_KeyCode];
}

