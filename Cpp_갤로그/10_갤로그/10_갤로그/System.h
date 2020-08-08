#pragma once
#include "DoubleBuffer.h"

class System
{
public:
	static System* _instance;
	static System* getInstance()
	{
		if (_instance == nullptr)
			_instance = new System;

		return _instance;
	}

public:
	void SetExit(BOOL done) { gameExit = done; }
	BOOL GetExit() { return gameExit; }

	void Destroy()
	{
		if (m_pDB != nullptr) delete m_pDB;
		if (_instance != nullptr) delete _instance;
	}

	DoubleBuffer* GetDB()
	{
		if (m_pDB == nullptr)
			m_pDB = new DoubleBuffer;

		return m_pDB;
	}

private:
	DoubleBuffer* m_pDB = nullptr;
	BOOL gameExit = FALSE;
};
