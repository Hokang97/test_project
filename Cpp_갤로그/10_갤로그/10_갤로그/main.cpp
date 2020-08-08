#include "GameDefine.h"
#include "System.h"

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



		System::getInstance()->GetDB()->FlippingBuffer();
	}

	System::getInstance()->Destroy();
	return 0;
}

void Init()
{
	// 시스템 매니저, 더블버퍼 생성 / 초기화
	System::getInstance()->GetDB()->CreateBuffer(CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT);
}