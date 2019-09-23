// WindowsProject1.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WindowsProject1.h"
#include "Header.h"
#include<typeinfo>
#include<cstring>
#include <windows.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING] = L"Chess";                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

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
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

struct Click {
	bool is_clicked;
	int x;
	int y;
	Click() {
		is_clicked = false;
	}
};

void PaintBoard(HDC&hdc, Chess&obj, HWND&hWnd, RECT&rect, Click&ch) {
	RECT board[8][8];
	HBRUSH Brush;
	for (short i = 0; i < 8; i++) {
		for (short j = 0; j < 8; j++) {
			board[i][j].left = rect.right/3 + 30 * i;
			board[i][j].top = rect.bottom/3 + 30 * j;
			board[i][j].right = board[i][j].left + 30;
			board[i][j].bottom = board[i][j].top + 30;
			if (ch.is_clicked && (ch.x - rect.right / 3) / 30 == i && (ch.y - rect.bottom / 3) / 30 == j) {
				Brush = CreateSolidBrush(RGB(120, 120, 120));
				SelectObject(hdc, Brush);
				FillRect(hdc, &board[i][j], Brush);
				DeleteObject(Brush);
			}
			else if ((i + j) % 2) {
				Brush = CreateSolidBrush(RGB(77, 25, 25));
				SelectObject(hdc, Brush);
				FillRect(hdc, &board[i][j], Brush);
				DeleteObject(Brush);
			}
			else {
				Brush = CreateSolidBrush(RGB(196, 128, 94));
				SelectObject(hdc, Brush);
				FillRect(hdc, &board[i][j], Brush);
				DeleteObject(Brush);
			}
		}
	}
	SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_BASELINE);
	for (short i = 0; i < 8; i++) {
		for (short j = 0; j < 8; j++) {
			if (obj.board[i][j]) {
				if (obj.board[i][j]->side) SetTextColor(hdc, RGB(255, 255, 255));
				else SetTextColor(hdc, RGB(0, 0, 0));
				if (typeid(*obj.board[i][j]) == typeid(Pawn)) TextOut(hdc, board[i][j].left + 12, board[7 - i][7 - j].top + 19, L"1", 2);
				if (typeid(*obj.board[i][j]) == typeid(Knight)) TextOut(hdc, board[i][j].left + 12, board[7 - i][7 - j].top + 19, L"2", 2);
				if (typeid(*obj.board[i][j]) == typeid(Bishop)) TextOut(hdc, board[i][j].left + 12, board[7 - i][7 - j].top + 19, L"3", 2);
				if (typeid(*obj.board[i][j]) == typeid(Rook)) TextOut(hdc, board[i][j].left + 12, board[7 - i][7 - j].top + 19, L"4", 2);
				if (typeid(*obj.board[i][j]) == typeid(Queen)) TextOut(hdc, board[i][j].left + 12, board[7 - i][7 - j].top + 19, L"5", 2);
				if (typeid(*obj.board[i][j]) == typeid(King)) TextOut(hdc, board[i][j].left + 12, board[7 - i][7 - j].top + 19, L"0", 2);
			}
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Click ch;
	static Chess obj;
	RECT rect;
	GetClientRect(hWnd, &rect);
	switch (message)
	{
	case WM_LBUTTONDOWN: {
		int x, y;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if (ch.is_clicked) {
			int Err = obj.DoMove((ch.x - rect.right / 3) / 30, 7 - (ch.y - rect.bottom / 3) / 30, (x - rect.right / 3) / 30, 7 - (y - rect.bottom / 3) / 30);
			if (!Err) {
				InvalidateRect(hWnd, NULL, true);
			}
			if (Err == 10) {
				MessageBox(hWnd, L"White side won!", L"Game over", MB_OK);
			}
			if (Err == -10) {
				MessageBox(hWnd, L"Black side won!", L"Game over", MB_OK);
			}
			if(Err == 1) MessageBox(hWnd, L"Choose chess!", L"Error", MB_OK);
			if (Err == 2) MessageBox(hWnd, L"Choose chess of your side!", L"Error", MB_OK);
			if (Err == 5) goto skip;
			if (Err == 4) MessageBox(hWnd, L"You can not beat your own chess!", L"Error", MB_OK);
			if (Err == 8) MessageBox(hWnd, L"Impossible move!", L"Error", MB_OK);
			skip:
			ch.is_clicked = false;
			InvalidateRect(hWnd, NULL, true);
			break;
		}
		ch.x = x;
		ch.y = y;
		ch.is_clicked = true;
		InvalidateRect(hWnd, NULL, true);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
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
		PaintBoard(hdc, obj, hWnd, rect, ch);
		EndPaint(hWnd, &ps);
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

// Обработчик сообщений для окна "О программе".
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
