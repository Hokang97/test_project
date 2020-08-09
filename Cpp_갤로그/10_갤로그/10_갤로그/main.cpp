#include "System.h"
#include "SceneDefine.h"
System* System::_instance = nullptr;
void Init();

int main()
{
	// Tlsaoslwj
	Init();

	// 게임 루프문
	while (!System::getInstance()->GetExit())
	{
		System::getInstance()->GetDB()->ClearBuffer();

		// Update, Render
		System::getInstance()->GetSM()->Render(DELTATIME);
		System::getInstance()->GetSM()->Update(DELTATIME);

		System::getInstance()->GetDB()->FlippingBuffer();
	}

	System::getInstance()->Destroy();
	return 0;
}

void Init()
{
	// 시스템 매니저, 더블버퍼 생성 / 초기화
	System::getInstance()->GetDB()->CreateBuffer(CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT);

	// 씬매니저 생성/초기화
	System::getInstance()->GetSM()->RegisterScene("MenuScene", new MenuScene);
	System::getInstance()->GetSM()->RegisterScene("GameScene", new GameScene);

	//씬 등록
	System::getInstance()->GetSM()->reserveChangeScene("MenuScene");
}