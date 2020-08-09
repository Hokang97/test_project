#include "MenuScene.h"

void MenuScene::Init(SceneManager& pSceneManager)
{
}

void MenuScene::Update(float dt)
{
}
int line = 0;
void MenuScene::Render(float dt)
{
	line++;
	line %= 10;
	System::getInstance()->GetDB()->WriteBuffer(0, line, "여기는 메뉴씬입니다");
}

void MenuScene::Destroy()
{
}

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}
