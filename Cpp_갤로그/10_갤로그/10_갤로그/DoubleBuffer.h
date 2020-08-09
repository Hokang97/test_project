#pragma once
#include<conio.h>
#include<Windows.h>
#include "GameDefine.h"

class DoubleBuffer
{
public:
	HANDLE GetBuffer();

	void CreateBuffer(const int &width, const int &height); // 버퍼 생성
	void WriteBuffer(int x, int y, const char *string);			// 버퍼 쓰기
	void FlippingBuffer();	// 버퍼 전환
	void ClearBuffer();		// 버퍼 비우기
	void DestroyBuffer();	// 버퍼 해제

	bool CloseHandle(HANDLE& handle);

private:
	int m_BufferIndex;
	HANDLE m_hBuffer[2];


public:
	DoubleBuffer();
	~DoubleBuffer();
	
};

