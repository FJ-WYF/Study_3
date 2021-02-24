﻿// WindowsProject1.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "GAME.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int left = 100, top = 20, right = left + 250, bottom = top + 400;
char c1, c2;
int x = -1, y = -1;
int iScoring = 0, iFail = 0, iTime = 0;
int gameover = 0;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}
//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

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
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
void DrawBK(HDC hdc, int x1, int y1, int x2, int y2)
{
    Rectangle(hdc, x1, y1, x2, y2);
    char s1[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    TextOut(hdc, x1 + 5, y2 - 25, s1, lstrlen(s1));
    char s2[100] = "20测控——冯骏（2021.2.17）";
    TextOut(hdc, x1 + 20, y2+15, s2, lstrlen(s2));
    char s3[100] = "开启大写输入法后点击开始游戏";
    TextOut(hdc, x1 + 20, y2 + 40, s3, lstrlen(s3));
}
void ShowScoring(HDC hdc, int x, int y, int iScoring, int iFail,int iTime)
{
    char szTemp[32];
    TextOut(hdc, x, y, "当前得分: ", lstrlen("当前得分: "));
    y = y + 20;
    sprintf_s(szTemp, "%d", iScoring);
    TextOut(hdc, x, y, szTemp, lstrlen(szTemp));
    y = y + 20;
    TextOut(hdc, x, y, "当前失误: ", lstrlen("当前失误: "));
    y = y + 20;
    sprintf_s(szTemp, "%d", iFail);
    TextOut(hdc, x, y, szTemp, lstrlen(szTemp)); 
    y = y + 20;
    TextOut(hdc, x, y, "当前计时: ", lstrlen("当前计时: "));
    y = y + 20;
    sprintf_s(szTemp, "%d", iTime);
    TextOut(hdc, x, y, szTemp, lstrlen(szTemp));
}
void GameOver(HDC hdc, int x, int y)
{
    COLORREF OldColor, NewColor = RGB(rand() % 255, rand() % 255, rand() % 255);
    OldColor = SetTextColor(hdc, NewColor);
    int OldBkMode = SetBkMode(hdc, TRANSPARENT);
    ::TextOut(hdc, x, y, "GAME OVER!", lstrlen("GAME OVER!"));
    SetBkMode(hdc, OldBkMode);//字符背景透明
    SetTextColor(hdc, OldColor);
}
void Fire(HDC hdc, int x, int y1, int y2)
{
    HPEN hOldPen, hNewPen = CreatePen(PS_DASHDOTDOT, 1, RGB(255, 0, 255)); //创建新画笔
    hOldPen = (HPEN)SelectObject(hdc, hNewPen);
    MoveToEx(hdc, x, y1, NULL);
    LineTo(hdc, x, y2);
    Sleep(100);
    HPEN hNewPen2 = CreatePen(PS_SOLID, 1, RGB(255, 255, 255)); //创建新画笔
    SelectObject(hdc, hNewPen2);
    MoveToEx(hdc, x, y1, NULL);
    LineTo(hdc, x, y2);
    SelectObject(hdc, hOldPen);
    DeleteObject(hNewPen);
    DeleteObject(hNewPen2);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case ID_START:
            if (gameover == 1)
                KillTimer(hWnd, 2);
            gameover = 0;
            iScoring = 0;
            iFail = 0;
            c1 = rand() % 26 + 'A';
            x = left + 5 + (c1 - 'A') * 9;
            y = top;
            SetTimer(hWnd, 1, 10, NULL);
            SetTimer(hWnd, 3, 1000, NULL);
            break;
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
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        HBRUSH hOldBrush,hNewBrush = CreateSolidBrush(RGB(0,255,255)); 
        hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
        RECT rt;
        GetClientRect(hWnd, &rt);
        int OldBkMode = SetBkMode(hdc,TRANSPARENT);
        DrawBK(hdc, left, top, right, bottom);
        SetBkMode(hdc,OldBkMode);//字符背景透明
        ShowScoring(hdc, right + 20, top + 50, iScoring, iFail,iTime);
        if (gameover)
            GameOver(hdc, left + 80, top + 130);
        else
        {
            int OldBkMode = SetBkMode(hdc, TRANSPARENT);
            char szTemp[8];
            sprintf_s(szTemp, "%c", c1);
            ::TextOut(hdc, x, y, szTemp, lstrlen(szTemp));
            SetBkMode(hdc, OldBkMode);//字符背景透明
        }
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_CHAR:
    {
        c2 = (wParam >= 'a' && wParam <= 'z') ? wParam + 'A' - 'a' : wParam;;
        HDC hdc = GetDC(hWnd);
        Fire(hdc, left + 5 + (c2 - 'A') * 9 + 4, top, bottom);
        ReleaseDC(hWnd, hdc);
        if (c1 == c2)
        {
            c1 = rand() % 26 + 'A';
            x = left + 5 + (c1 - 'A') * 9;
            y = top;
            iScoring = iScoring + 1;
        }
        else
            iFail = iFail + 1;
    }
    break;
    case WM_TIMER:
        switch (wParam)
        {
        case 1:
            y = y + iScoring / 10 + 1;
            if (y > bottom - 40)
            {
                gameover = 1;
                KillTimer(hWnd, 1);
                SetTimer(hWnd, 2, 300, NULL);
            }
            InvalidateRect(hWnd, 0, 0);
            break;
        case 2:
            InvalidateRect(hWnd, 0, 0);
            break;
        case 3:
            if (!gameover)
                ++iTime;
            break;
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
// “关于”框的消息处理程序。
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
