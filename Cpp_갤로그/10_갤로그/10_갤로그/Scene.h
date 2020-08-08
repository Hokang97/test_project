#pragma once
#include "System.h"

class SceneManager;

class Scene
{
public:
	virtual void Init(SceneManager& pSceneManager) = 0;
	virtual void Update(float dt) = 0;
	virtual void Redner(float dt) = 0;
	virtual void Destroy() = 0;

protected:
	SceneManager* m_pSceneManager;
};
