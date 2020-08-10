#include "Bullet.h"

void Bullet::Init()
{
}

void Bullet::Update(float dt)
{
	if (m_Remove) return;
	if (posX >= 30) Destroy();

	posX++;
}

void Bullet::Render(float dt)
{
	if (m_Remove) return;
	if (posX < 30 && !colEnemy)
	{
		System::getInstance()->GetDB()->WriteBuffer(posX * 2, posY, "¡Ü");
	}
}

void Bullet::Destroy()
{
	m_Remove = TRUE;
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}
