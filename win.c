
#include "framework.h"
#include "his.h"
// button IDs for role selection
#define ID_BTN_PATIENT 201
#define ID_BTN_DOCTOR  202
#define ID_BTN_ADMIN   203
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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY);
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
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hLeft = NULL;
    static HWND hRight = NULL;
    const int LEFT_FIXED = 220; // preferred left pane width in pixels
    switch (message)
    {
    case WM_CREATE:
    {
        // create two child static controls as left/right panes
        hLeft = CreateWindowW(L"STATIC", L"left",
            WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFTNOWORDWRAP,
            0, 0, LEFT_FIXED, 100,
            hWnd, (HMENU)101, hInst, NULL);

        hRight = CreateWindowW(L"STATIC", L"right",
            WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFTNOWORDWRAP,
            LEFT_FIXED, 0, 100, 100,
            hWnd, (HMENU)102, hInst, NULL);

        // create role selection buttons in the left pane area
        HWND hBtn1 = CreateWindowW(L"BUTTON", L"患者",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            8, 8, 80, 28,
            hLeft, (HMENU)ID_BTN_PATIENT, hInst, NULL);

        HWND hBtn2 = CreateWindowW(L"BUTTON", L"医生",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            8, 44, 80, 28,
            hLeft, (HMENU)ID_BTN_DOCTOR, hInst, NULL);

        HWND hBtn3 = CreateWindowW(L"BUTTON", L"管理",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            8, 80, 80, 28,
            hLeft, (HMENU)ID_BTN_ADMIN, hInst, NULL);

        // set default GUI font for readability
        SendMessageW(hLeft, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
        SendMessageW(hRight, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        return 0;
    }

    case WM_SIZE:
    {
        int cx = LOWORD(lParam);
        int cy = HIWORD(lParam);

        if (hLeft && hRight) {
            int leftW = LEFT_FIXED;
            // ensure left pane isn't wider than half the window or too large for small windows
            if (leftW > cx / 2) leftW = cx / 4;

            // position panes
            MoveWindow(hLeft, 0, 0, leftW, cy, TRUE);
            MoveWindow(hRight, leftW, 0, cx - leftW, cy, TRUE);
        }
        return 0;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case ID_BTN_PATIENT:
            SetWindowTextW(hRight, L"已选择：患者\n在此显示患者界面...");
            return 0;
        case ID_BTN_DOCTOR:
            SetWindowTextW(hRight, L"已选择：医生\n在此显示医生界面...");
            return 0;
        case ID_BTN_ADMIN:
            SetWindowTextW(hRight, L"已选择：管理\n在此显示管理界面...");
            return 0;
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
