// CPPWinRTLightup.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "CPPWinRTLightup.h"
#include "WinRT/Windows.UI.Composition.h"
#include "WinRT/Windows.UI.Composition.Desktop.h"
#include <windows.ui.composition.interop.h>
#include <windows.ui.composition.desktop.h>
#include <DispatcherQueue.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int, HWND&);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

auto CreateDispatcherQueueControllerJ(DispatcherQueueOptions const& options) noexcept
{
    using Proc = HRESULT(__stdcall*)(DispatcherQueueOptions, ABI::Windows::System::IDispatcherQueueController**) noexcept;
    auto proc = reinterpret_cast<Proc>(GetProcAddress(LoadLibraryW(L"CoreMessaging"), "CreateDispatcherQueueController"));
    winrt::com_ptr<ABI::Windows::System::IDispatcherQueueController> ptr{nullptr};

    if (proc)
    {
        proc(options, ptr.put());
    }

    return ptr;
}

auto CreateDesktopWindowTarget(winrt::Windows::UI::Composition::Compositor const& compositor, HWND window)
{
    namespace abi = ABI::Windows::UI::Composition::Desktop;

    auto interop = compositor.as<abi::ICompositorDesktopInterop>();
    winrt::Windows::UI::Composition::Desktop::DesktopWindowTarget target{ nullptr };
    winrt::check_hresult(interop->CreateDesktopWindowTarget(window, true, reinterpret_cast<abi::IDesktopWindowTarget**>(winrt::put_abi(target))));
    return target;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CPPWINRTLIGHTUP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    HWND topLevel;

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow, topLevel))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CPPWINRTLIGHTUP));

    MSG msg;

    namespace composition = winrt::Windows::UI::Composition;
    composition::Desktop::DesktopWindowTarget target{nullptr};
    composition::Compositor compositor{ nullptr };
    composition::SpriteVisual visual{ nullptr };

    if (auto factory = winrt::try_get_activation_factory<composition::Compositor>()) {
        auto options = DispatcherQueueOptions{};
        options.dwSize = sizeof(DispatcherQueueOptions);
        options.threadType = DQTYPE_THREAD_CURRENT;

        if (auto ptr = CreateDispatcherQueueControllerJ(options)) {
            compositor = factory.ActivateInstance<composition::Compositor>();
            visual = compositor.CreateSpriteVisual();
            visual.Size({ 100,100 });
            visual.Offset({ 10,10,10 });
            visual.Brush(compositor.CreateColorBrush(winrt::Windows::UI::Colors::Red()));

            target = CreateDesktopWindowTarget(compositor, topLevel);
            target.Root(visual);
        }

        if (winrt::Windows::UI::Composition::ICompositor2 v2 = compositor) {
            auto shadow = v2.CreateDropShadow();
            visual.Shadow(shadow);
        }

        //TODO interface version check
    }


    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CPPWINRTLIGHTUP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CPPWINRTLIGHTUP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND& toplevel)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   toplevel = hWnd;
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
            // TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
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
