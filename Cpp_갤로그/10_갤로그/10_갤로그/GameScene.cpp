#include "GameScene.h"

void GameScene::Init(SceneManager& pSceneManager)
{
}

void GameScene::Update(float dt)
{
}

void GameScene::Render(float dt)
{
	System::getInstance()->GetDB()->WriteBuffer(0, 0, "여기는 게임씬입니다");
}

void GameScene::Destroy()
{
}

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}
