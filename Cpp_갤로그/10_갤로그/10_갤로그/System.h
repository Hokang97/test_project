#pragma once
#include "DoubleBuffer.h"
#include "SceneManager.h"

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
		if (m_pSM != nullptr) delete m_pSM;
		if (m_pDB != nullptr) delete m_pDB;
		if (_instance != nullptr) delete _instance;
	}

	DoubleBuffer* GetDB()
	{
		if (m_pDB == nullptr)
			m_pDB = new DoubleBuffer;

		return m_pDB;
	}

	SceneManager* GetSM()
	{
		if (m_pSM == nullptr)
			m_pSM = new SceneManager;

		return m_pSM;
	}

private:
	SceneManager* m_pSM = nullptr;	// 씬매니저
	DoubleBuffer* m_pDB = nullptr;	// 더블버퍼
	BOOL gameExit = FALSE;
};
