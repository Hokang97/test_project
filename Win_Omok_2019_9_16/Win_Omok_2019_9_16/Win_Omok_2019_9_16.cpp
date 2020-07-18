// Win_Omok_2019_9_16.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Win_Omok_2019_9_16.h"
#include <vector>

using namespace std;

#define MAX_LOADSTRING 100

class Stone
{
public:
	BYTE m_Type;  //0 ~ 255 용도 : 0이면 빈자리  1이면 흑돌이 놓여 있다는 뜻  2이면 백돌이 놓여 있다는 뜻

	int  m_XX;
	int  m_YY;
};

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND  g_hWnd = NULL;
Stone g_GridType[19][19];

bool g_isBlack = true;     //true 흑들 플레이 턴,  false 백돌 플레이 턴(현재 누구 턴인지? 를 나타내는 변수)
int  sx = 0;
int  sy = 0;

vector<Stone> g_STList;

int g_BlackWin = 0;
int g_WhiteWin = 0;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void Clear();
void Judgment(HWND hWnd); //판정

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINOMOK2019916, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINOMOK2019916));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINOMOK2019916));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(70, 140, 255)); //(HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINOMOK2019916);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
				100, 80, 836, 879, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


HPEN LinePen = NULL;
HBRUSH BackBS = NULL; //바둑판용 노란색 브러쉬
HBRUSH BlackBS = NULL;	//검은색 브러쉬
HBRUSH WhiteBS = NULL;	//하얀색 브러쉬
HFONT  hMyFont = NULL;	
 
//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		{
			//--- 초기화
			for (int yy = 0; yy < 19; yy++)
			{
				for (int xx = 0; xx < 19; xx++)
				{
					g_GridType[xx][yy].m_Type = 0;
					g_GridType[xx][yy].m_XX = 50 + (xx * 40);
					g_GridType[xx][yy].m_YY = 50 + (yy * 40);
				}
			}
			//--- 초기화

			LinePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

			BackBS = CreateSolidBrush(RGB(220, 179, 92));

			BlackBS = CreateSolidBrush(RGB(0, 0, 0));
			WhiteBS = CreateSolidBrush(RGB(255, 255, 255));

			hMyFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
								  VARIABLE_PITCH | FF_ROMAN, _T("굴림"));
		}
		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

	case WM_LBUTTONDOWN:	//마우스 왼쪽 버튼이 눌려졌을 때 발생하는 메시지
		{
			sx = LOWORD(lParam);  //마우스 좌표
			sy = HIWORD(lParam);

			if ( (30 < sx && sx < 30 + 19 * 40)
				 && (30 < sy && sy < 30 + 19 * 40) )
			{
				int a_Cxx = (int)((sx - 30) / 40);
				int a_Cyy = (int)((sy - 30) / 40);

				if (g_GridType[a_Cxx][a_Cyy].m_Type <= 0) //빈자리일 때만
				{
					g_GridType[a_Cxx][a_Cyy].m_Type = g_isBlack ? 1 : 2;

					g_isBlack = !g_isBlack;
				}//if (g_GridType[a_Cxx][a_Cyy].m_Type <= 0)
			}//if ( (30 < sx && sx < 30 + 19 * 40) ...

			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;

	case WM_LBUTTONUP:
		Judgment(hWnd);
		break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			RECT a_rc;
			GetClientRect(hWnd, &a_rc);
			//a_rc.right  == 가로 크기 820
			//a_rc.bottom == 세로크기  820
			//TCHAR a_tstr[256];
			//wsprintf(a_tstr, _T("가로크기 : %d,  세로크기 : %d"), a_rc.right, a_rc.bottom);
			//MessageBox(hWnd, a_tstr, _T("테스트"), MB_OK);

			HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, BackBS);
			Rectangle(hdc,  50 - 15, 
							50 - 15,
							50 + (18 * 40) + 15,
							50 + (18 * 40) + 15);

			//----- 오목판 선 그리기
			HPEN OldPen = (HPEN)SelectObject(hdc, LinePen); //<-- 선두께 2, 색깔은 검은색
			int a_Cxx = 50;
			for (int a_xx = 0; a_xx < 19; a_xx++)
			{
				a_Cxx = 50 + (a_xx * 40);
				MoveToEx(hdc, a_Cxx, 50, NULL);
				LineTo(hdc, a_Cxx, 50 + (18 * 40));
			}

			int a_Cyy = 50;
			for (int a_yy = 0; a_yy < 19; a_yy++)
			{
				a_Cyy = 50 + (a_yy * 40);
				MoveToEx(hdc, 50, a_Cyy, NULL);
				LineTo(hdc, 50 + (18 * 40), a_Cyy);
			}
			//----- 오목판 선 그리기

			//----- 돌 그리기
			for (int yy = 0; yy < 19; yy++)
			{
				for (int xx = 0; xx < 19; xx++)
				{
					if (g_GridType[xx][yy].m_Type <= 0)
						continue;

					if(g_GridType[xx][yy].m_Type == 1)
						SelectObject(hdc, BlackBS); //흑돌
					else if(g_GridType[xx][yy].m_Type == 2)
						SelectObject(hdc, WhiteBS); //백돌

					Ellipse(hdc, g_GridType[xx][yy].m_XX - 18,
								 g_GridType[xx][yy].m_YY - 18,
								 g_GridType[xx][yy].m_XX + 18,
								 g_GridType[xx][yy].m_YY + 18);
				}//for (int xx = 0; xx < 19; xx++)
			}//for (int yy = 0; yy < 19; yy++)
			//----- 돌 그리기
	
			//----- 글씨 쓰기
			HFONT OldFont = (HFONT)SelectObject(hdc, hMyFont);
			SetBkMode(hdc, TRANSPARENT);  //<-- 글씨 배경 빼기...

			if (g_isBlack == true)
			{
				SetTextColor(hdc, RGB(0, 0, 0));  //<-- 글씨색 바꾸기...
				TextOut(hdc, 50, 2, _T("흑돌 차례입니다."), _tcslen(_T("흑돌 차례입니다.")));
			}
			else
			{
				SetTextColor(hdc, RGB(255, 255, 255)); //<-- 글씨색 바꾸기...
				TextOut(hdc, 50, 2, _T("백돌 차례입니다."), _tcslen(_T("백돌 차례입니다.")));
			}

			SetTextColor(hdc, RGB(255, 255, 0)); //<-- 글씨색 바꾸기...
			TCHAR a_TempStr[128];
			_stprintf_s(a_TempStr, _T("흑돌 (%d : %d) 백돌"), g_BlackWin, g_WhiteWin);
			TextOut(hdc, 330, 2, a_TempStr, _tcslen(a_TempStr));
			//----- 글씨 쓰기
 
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		{
			if (hMyFont != NULL)
			{
				DeleteObject(hMyFont);
				hMyFont = NULL;
			}

			if (LinePen != NULL)
			{
				DeleteObject(LinePen);
				LinePen = NULL;
			}

			if (BackBS != NULL)
			{
				DeleteObject(BackBS);
				BackBS = NULL;
			}

			if (BlackBS != NULL)
			{
				DeleteObject(BlackBS);
				BlackBS = NULL;
			}

			if (WhiteBS != NULL)
			{
				DeleteObject(WhiteBS);
				WhiteBS = NULL;
			}

			PostQuitMessage(0);
		}
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void Clear()
{
	for (int ii = 0; ii < 19; ii++)
	{
		for (int aa = 0; aa < 19; aa++)
		{
			g_GridType[ii][aa].m_Type = 0;
		}
	}
	InvalidateRect(g_hWnd, NULL, TRUE);
}

void Judgment(HWND hWnd) //판정
{
	for (int aa = 0; aa < 19; aa++)
	{
		for (int ii = 0; ii < 19; ii++)
		{
			if ((ii + 1 < 19) && (ii + 2 < 19) && (ii + 3 < 19) && (ii + 4 < 19))
				if ((g_GridType[ii][aa].m_Type == 1) &&
					(g_GridType[ii + 1][aa].m_Type == 1) &&
					(g_GridType[ii + 2][aa].m_Type == 1) &&
					(g_GridType[ii + 3][aa].m_Type == 1) &&
					(g_GridType[ii + 4][aa].m_Type == 1))
				{
					g_BlackWin++;
					TCHAR winner[15];
					_stprintf_s(winner, _T("흑돌이 승리하였습니다."));
					MessageBoxW(hWnd, winner, _T("승리"), MB_OK);
					Clear();
				}

			if ((aa + 1 < 19) && (aa + 2 < 19) && (aa + 3 < 19) && (aa + 4 < 19))
				if ((g_GridType[ii][aa].m_Type == 1) &&
					(g_GridType[ii][aa + 1].m_Type == 1) &&
					(g_GridType[ii][aa + 2].m_Type == 1) &&
					(g_GridType[ii][aa + 3].m_Type == 1) &&
					(g_GridType[ii][aa + 4].m_Type == 1))
				{
					g_BlackWin++;
					TCHAR winner[15];
					_stprintf_s(winner, _T("흑돌이 승리하였습니다."));
					MessageBoxW(hWnd, winner, _T("승리"), MB_OK);
					Clear();
				}

			if ((ii + 1 < 19) && (ii + 2 < 19) && (ii + 3 < 19) && (ii + 4 < 19))
				if ((aa + 1 < 19) && (aa + 2 < 19) && (aa + 3 < 19) && (aa + 4 < 19))
					if ((g_GridType[ii][aa].m_Type == 1) &&
						(g_GridType[ii + 1][aa + 1].m_Type == 1) &&
						(g_GridType[ii + 2][aa + 2].m_Type == 1) &&
						(g_GridType[ii + 3][aa + 3].m_Type == 1) &&
						(g_GridType[ii + 4][aa + 4].m_Type == 1))
					{
						g_BlackWin++;
						TCHAR winner[15];
						_stprintf_s(winner, _T("흑돌이 승리하였습니다."));
						MessageBoxW(hWnd, winner, _T("승리"), MB_OK);
						Clear();
					}

			if ((0 <= ii - 1) && (0 <= ii - 2) && (0 <= ii - 3) && (0 <= ii - 4))
				if ((aa + 1 < 19) && (aa + 2 < 19) && (aa + 3 < 19) && (aa + 4 < 19))
					if ((g_GridType[ii][aa].m_Type == 1) &&
						(g_GridType[ii - 1][aa + 1].m_Type == 1) &&
						(g_GridType[ii - 2][aa + 2].m_Type == 1) &&
						(g_GridType[ii - 3][aa + 3].m_Type == 1) &&
						(g_GridType[ii - 4][aa + 4].m_Type == 1))
					{
						g_BlackWin++;
						TCHAR winner[15];
						_stprintf_s(winner, _T("흑돌이 승리하였습니다."));
						MessageBoxW(hWnd, winner, _T("승리"), MB_OK);
						Clear();
					}

			if ((ii + 1 < 19) && (ii + 2 < 19) && (ii + 3 < 19) && (ii + 4 < 19))
				if ((g_GridType[ii][aa].m_Type == 2) &&
					(g_GridType[ii + 1][aa].m_Type == 2) &&
					(g_GridType[ii + 2][aa].m_Type == 2) &&
					(g_GridType[ii + 3][aa].m_Type == 2) &&
					(g_GridType[ii + 4][aa].m_Type == 2))
				{
					g_WhiteWin++;
					TCHAR winner[15];
					_stprintf_s(winner, _T("백돌이 승리하였습니다."));
					MessageBoxW(hWnd, winner, _T("승리"), MB_OK);
					Clear();
				}

			if ((aa + 1 < 19) && (aa + 2 < 19) && (aa + 3 < 19) && (aa + 4 < 19))
				if ((g_GridType[ii][aa].m_Type == 2) &&
					(g_GridType[ii][aa + 1].m_Type == 2) &&
					(g_GridType[ii][aa + 2].m_Type == 2) &&
					(g_GridType[ii][aa + 3].m_Type == 2) &&
					(g_GridType[ii][aa + 4].m_Type == 2))
				{
					g_WhiteWin++;
					TCHAR winner[15];
					_stprintf_s(winner, _T("백돌이 승리하였습니다."));
					MessageBoxW(hWnd, winner, _T("승리"), MB_OK);
					Clear();
				}

			if ((ii + 1 < 19) && (ii + 2 < 19) && (ii + 3 < 19) && (ii + 4 < 19))
				if ((aa + 1 < 19) && (aa + 2 < 19) && (aa + 3 < 19) && (aa + 4 < 19))
					if ((g_GridType[ii][aa].m_Type == 2) &&
						(g_GridType[ii + 1][aa + 1].m_Type == 2) &&
						(g_GridType[ii + 2][aa + 2].m_Type == 2) &&
						(g_GridType[ii + 3][aa + 3].m_Type == 2) &&
						(g_GridType[ii + 4][aa + 4].m_Type == 2))
					{
						g_WhiteWin++;
						TCHAR winner[15];
						_stprintf_s(winner, _T("백돌이 승리하였습니다."));
						MessageBoxW(hWnd, winner, _T("승리"), MB_OK);
						Clear();
					}

			if ((0 <= ii - 1) && (0 <= ii - 2) && (0 <= ii - 3) && (0 <= ii - 4))
				if ((aa + 1 < 19) && (aa + 2 < 19) && (aa + 3 < 19) && (aa + 4 < 19))
					if ((g_GridType[ii][aa].m_Type == 2) &&
						(g_GridType[ii - 1][aa + 1].m_Type == 2) &&
						(g_GridType[ii - 2][aa + 2].m_Type == 2) &&
						(g_GridType[ii - 3][aa + 3].m_Type == 2) &&
						(g_GridType[ii - 4][aa + 4].m_Type == 2))
					{
						g_WhiteWin++;
						TCHAR winner[15];
						_stprintf_s(winner, _T("백돌이 승리하였습니다."));
						MessageBoxW(hWnd, winner, _T("승리"), MB_OK);
						Clear();
					}
		}
	}
}
