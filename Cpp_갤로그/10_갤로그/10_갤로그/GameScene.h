#pragma once
#include "Scene.h"
class GameScene : public Scene
{
public:
	virtual void Init(SceneManager& pSceneManager);
	virtual void Update(float dt);
	virtual void Render(float dt);
	virtual void Destroy();


public:
	GameScene();
	~GameScene();

};

