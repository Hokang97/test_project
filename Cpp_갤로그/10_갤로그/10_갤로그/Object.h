#pragma once
#include "System.h"

class Object
{
public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Redner(float dt) = 0;
	virtual void Destroy() = 0;

protected:
	int posX = 0;
	int posY = 0;

public:
	void SetPosX(int value) { posX = value; }
	void SetPosY(int value) { posY = value; }

	int GetPosX() { return posX; }
	int GetPosY() { return posY; }
};
