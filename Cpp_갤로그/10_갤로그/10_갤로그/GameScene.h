#pragma once
#include "Scene.h"
#include "Character.h"
#include "Enemy.h"
class GameScene : public Scene
{
public:
	virtual void Init(SceneManager& pSceneManager);
	virtual void Update(float dt);
	virtual void Render(float dt);
	virtual void Destroy();

	void DrawMap();
	void DrawUI();


private:
	Character m_Character;
	vector<Enemy> mEnemy;

	INT mEnemyMakeTime = 0;


public:
	GameScene();
	~GameScene();

};

