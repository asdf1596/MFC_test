#include "stdafx.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * @brief 애플리케이션의 진입점입니다.
 *
 * @param hInstance 현재 인스턴스 핸들입니다.
 * @param hPrevInstance 이전 인스턴스 핸들입니다. 항상 NULL입니다.
 * @param lpCmdLine 명령줄 인수입니다.
 * @param nCmdShow 윈도우 표시 옵션입니다.
 * @return int 애플리케이션 종료 코드입니다.
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS WndClass;
    HWND hwnd;
    MSG msg;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = WndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = TEXT("MouseClass");
    if (!RegisterClass(&WndClass))
        return 1;

    hwnd = CreateWindow(
        TEXT("MouseClass"),
        TEXT("MouseSDK"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    ShowWindow(hwnd, nCmdShow);
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    TCHAR str1[200] = TEXT("마우스 휠을 움직여 보세요");
    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_MOUSEWHEEL:
        MessageBox(hwnd, TEXT("마우스 휠을 움직이셨습니다."), TEXT("왼쪽 마우스 클릭!"), MB_OK);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, 100, 100, str1, lstrlen(str1));
        EndPaint(hwnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
