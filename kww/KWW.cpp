// KWW.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "KWW.h"

#define MAX_LOADSTRING 100
#define SIZEOFCLIENT 1200
#define LINE 18
#define EMPTY 0
#define BLACK 1
#define WHITE 2

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
RECT pos;
POINT CrossPoint[19][19];
POINT blocksize;
int CheckPoint[19][19];
int a = 50;
int flag;

void GameWin(HWND hWnd, int x)
{
    if (x == BLACK)
        MessageBox(hWnd, _T("흑돌 승"), _T(""), MB_OK);
    else if (x == WHITE)
        MessageBox(hWnd, _T("백돌 승"), _T(""), MB_OK);

    PostQuitMessage(0);
}

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_KWW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KWW));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KWW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KWW);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
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

        GetClientRect(hWnd, &pos);

        blocksize.x = (((pos.right - a) - (pos.left + a)) / LINE);
        blocksize.y = (((pos.bottom - a) - (pos.top + a)) / LINE);

        RECT wpos;
        wpos.top = 100;
        wpos.left = 100;
        wpos.right = wpos.left + SIZEOFCLIENT;
        wpos.bottom = wpos.top + SIZEOFCLIENT;
        MoveWindow(hWnd, wpos.left, wpos.top, wpos.right, wpos.bottom, true);

        for (int i = 0; i <= LINE; i++)
        {
            for (int j = 0; j <= LINE; j++)
            {
                CheckPoint[i][j] = EMPTY;
                CrossPoint[i][j].x = (pos.left + a) + i * blocksize.x;
                CrossPoint[i][j].y = (pos.top + a) + j * blocksize.y;
            }
        }

        flag = BLACK;

    }
    break;
    case WM_GETMINMAXINFO:
    {
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = SIZEOFCLIENT;
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = SIZEOFCLIENT;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = SIZEOFCLIENT;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = SIZEOFCLIENT;
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
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        for (int i = 0; i < LINE; i++)
        {
            for (int j = 0; j < LINE; j++)
            {
                Rectangle(hdc, CrossPoint[i][j].x, CrossPoint[i][j].y, CrossPoint[i][j].x + blocksize.x, CrossPoint[i][j].y + blocksize.y);
            }
        }

        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        int cxpos LOWORD(lParam);
        int cypos HIWORD(lParam);
        bool finish = FALSE;
        int i = 0;
        int j = 0;
        int tempx = 0;
        int tempy = 0;
        int count = 1;


        COLORREF White = RGB(255, 255, 255);
        COLORREF Black = RGB(0, 0, 0);

        for (i = 0; i <= LINE; i++)
        {
            for (j = 0; j <= LINE; j++)
            {
                if (cxpos >= (CrossPoint[i][j].x - blocksize.x / 2) && cxpos <= CrossPoint[i][j].x + blocksize.x / 2)
                {
                    if (cypos >= (CrossPoint[i][j].y - blocksize.y / 2) && cypos <= CrossPoint[i][j].y + blocksize.y / 2)
                    {
                        cxpos = CrossPoint[i][j].x;
                        cypos = CrossPoint[i][j].y;

                        if (CheckPoint[i][j] != EMPTY)
                        {
                            MessageBox(hWnd, _T("이미 돌이 놓여져 있습니다."), _T(""), MB_OK);
                            break;
                        }
                        else
                        {
                            HDC hdc = GetDC(hWnd);
                            HBRUSH hBrush = NULL;
                            HBRUSH hOldBrush = NULL;
                            if (flag == BLACK) // 검은돌 그리기
                            {
                                flag = WHITE;
                                CheckPoint[i][j] = BLACK;
                                hBrush = CreateSolidBrush(Black);
                                hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                            }
                            else if (flag == WHITE) // 하얀돌 그리기                          
                            {
                                flag = BLACK;
                                CheckPoint[i][j] = WHITE;
                                hBrush = CreateSolidBrush(White);
                                hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                            }
                            Ellipse(hdc, cxpos - blocksize.x / 2, cypos - blocksize.y / 2, cxpos + blocksize.x / 2, cypos + blocksize.y / 2);
                            SelectObject(hdc, hOldBrush);
                            ReleaseDC(hWnd, hdc);
                            DeleteObject(hBrush);
                            finish = TRUE;
                            break;
                        }
                    }
                }

            }
            if (finish)
                break;
        }
        tempx = i;
        tempy = j;
        if (CheckPoint[i][j] == BLACK)
        {
            count = 1;
            while (CheckPoint[tempx - 1][tempy - 1] == BLACK) // 좌상우하 대각선 검사
            {
                tempx--;
                tempy--;
            }
            while (CheckPoint[tempx + 1][tempy + 1] == BLACK)
            {
                tempx++;
                tempy++;
                count++;
            }
            while (CheckPoint[tempx + 1][tempy - 1] == BLACK) // 우상좌하 대각선 검사
            {
                tempx++;
                tempy--;
            }
            while (CheckPoint[tempx - 1][tempy + 1] == BLACK)
            {
                tempx--;
                tempy++;
                count++;
            }
            while (CheckPoint[i][tempy - 1] == BLACK) // 세로줄 검사
                tempy--;
            while (CheckPoint[i][tempy + 1] == BLACK)
            {
                tempy++;
                count++;
            }

            while (CheckPoint[tempx - 1][j] == BLACK) //가로줄 검사
                tempx--;
            while (CheckPoint[tempx + 1][j] == BLACK)
            {
                tempx++;
                count++;
            }



            if (count == 5)
                GameWin(hWnd, BLACK);
        }
        else if (CheckPoint[i][j] == WHITE)
        {
            count = 1;
            while (CheckPoint[tempx - 1][tempy - 1] == WHITE) // 좌상우하 대각선 검사
            {
                tempx--;
                tempy--;
            }
            while (CheckPoint[tempx + 1][tempy + 1] == WHITE)
            {
                tempx++;
                tempy++;
                count++;
            }
            while (CheckPoint[tempx + 1][tempy - 1] == WHITE) // 우상좌하 대각선 검사
            {
                tempx++;
                tempy--;
            }
            while (CheckPoint[tempx - 1][tempy + 1] == WHITE)
            {
                tempx--;
                tempy++;
                count++;
            }
            while (CheckPoint[i][tempy - 1] == WHITE) // 세로줄 검사
                tempy--;
            while (CheckPoint[i][tempy + 1] == WHITE)
            {
                tempy++;
                count++;
            }

            while (CheckPoint[tempx - 1][j] == WHITE) //가로줄 검사
                tempx--;
            while (CheckPoint[tempx + 1][j] == WHITE)
            {
                tempx++;
                count++;
            }

            if (count == 5)
                GameWin(hWnd, WHITE);
        }





    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
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
