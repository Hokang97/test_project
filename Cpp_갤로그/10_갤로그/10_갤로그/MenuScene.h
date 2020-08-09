#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
public:
	virtual void Init(SceneManager& pSceneManager);
	virtual void Update(float dt);
	virtual void Render(float dt);
	virtual void Destroy();

	void DrawMenu();

private:
	WORD selectMenu = MENU_GAME_START;

public:
	MenuScene();
	~MenuScene();

};

