#include "Character.h"

void Character::Init()
{
	posX = 3;
	posY = 2;
}

void Character::Update(float dt)
{
	if (GetAsyncKeyState(VK_UP))
	{
		if (posY > 2) posY--;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		if (posY < 12) posY++;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (posX > 2) posX--;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (posX < 25) posX++;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		Bullet temp;
		temp.SetPosX(posX + 5);
		temp.SetPosY(posY + 2);
		m_bullet.push_back(temp);
	}

	for (auto itor = m_bullet.begin(); itor != m_bullet.end();)
	{
		if (itor->m_Remove)
			itor = m_bullet.erase(itor);
		else
		{
			itor->Update(dt);
			itor++;
		}
	}
}

void Character::Render(float dt)
{
	SetConsoleTextAttribute(System::getInstance()->GetDB()->GetBuffer(), WHITE);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			System::getInstance()->GetDB()->WriteBuffer((posX + i) * 2, (posY + j), (mChar[j][i]) ? "бс" : "");
		}
	}

	for (auto itor = m_bullet.begin(); itor != m_bullet.end(); ++itor)
	{
		itor->Render(dt);
	}
}

void Character::Destroy()
{
	for (auto itor = m_bullet.begin(); itor != m_bullet.end(); ++itor)
		itor->Destroy();
}

vector<Bullet>& Character::GetBullet()
{
	return m_bullet;
}

Character::Character()
{
}

Character::~Character()
{
}
