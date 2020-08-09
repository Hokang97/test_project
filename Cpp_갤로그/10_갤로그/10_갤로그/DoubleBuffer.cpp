#include "DoubleBuffer.h"

DoubleBuffer::DoubleBuffer()
{
	m_BufferIndex = 0;
}

DoubleBuffer::~DoubleBuffer()
{
}


HANDLE DoubleBuffer::GetBuffer()
{
	return m_hBuffer[m_BufferIndex];
}

void DoubleBuffer::CreateBuffer(const int &width, const int &height)
{
	CONSOLE_CURSOR_INFO cci;	// 콘솔창 커서 정보
	COORD size = { width, height };	// 버퍼 크기를 저장하는 구조체
	SMALL_RECT rect;			// 창 크기를 저장하는 구조체
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = width - 1;
	rect.Bottom = height -1;

	// 0번 버퍼 생성
	m_hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(m_hBuffer[0], size);
	SetConsoleWindowInfo(m_hBuffer[0], TRUE, &rect);


	// 1번 버퍼 생성
	m_hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(m_hBuffer[1], size);
	SetConsoleWindowInfo(m_hBuffer[1], TRUE, &rect);

	cci.dwSize = 1;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(m_hBuffer[0], &cci);	//깜빡이는 커서 사라짐
	SetConsoleCursorInfo(m_hBuffer[1], &cci);   //깜빡이는 커서 사라짐
}

void DoubleBuffer::WriteBuffer(int x, int y, const char * string)
{
	DWORD dw;
	COORD CursorPosition = { x,y };

	// 버퍼내에서 좌표 이동
	SetConsoleCursorPosition(m_hBuffer[m_BufferIndex], CursorPosition);
	WriteFile(m_hBuffer[m_BufferIndex], string, strlen(string), &dw, NULL);
}

void DoubleBuffer::FlippingBuffer()
{
	Sleep(30);

	// 버퍼 활성화
	SetConsoleActiveScreenBuffer(m_hBuffer[m_BufferIndex]);
	m_BufferIndex = !m_BufferIndex;
}

void DoubleBuffer::ClearBuffer()
{
	COORD coord = { 0, 0 };
	DWORD dw;

	FillConsoleOutputCharacter(m_hBuffer[m_BufferIndex], ' ', CONSOLE_MAX_WIDTH * CONSOLE_MAX_HEIGHT, coord, &dw);
}

void DoubleBuffer::DestroyBuffer()
{
	CloseHandle(m_hBuffer[0]);
	CloseHandle(m_hBuffer[1]);
}

bool DoubleBuffer::CloseHandle(HANDLE& handle)
{
	if (INVALID_HANDLE_VALUE != handle)
	{
		__try
		{
			return (0 != ::CloseHandle(handle));
		}

		__finally
		{
			handle = INVALID_HANDLE_VALUE;
		}
	}
	return false;
}

