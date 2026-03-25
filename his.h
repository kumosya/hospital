#pragma once

#include "resource.h"

#define MAX_LOADSTRING 100

// 全局变量:
extern HINSTANCE hInst;                                // 当前实例
extern WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
extern WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
