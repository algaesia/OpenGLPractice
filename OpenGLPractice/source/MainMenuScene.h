#ifndef _MAIN_MENU_SCENE_H
#define _MAIN_MENU_SCENE_H

#include "Scene.h"
#include "TextHandler.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene(unsigned int a_ShaderProgram);
	~MainMenuScene();

	virtual void UpdateScene(float dt);
	virtual void RenderScene();
	virtual void ResetScene(){}
private:
	Sprite* backgroundImage;
	TextHandler m_TextHandler;
};

#endif