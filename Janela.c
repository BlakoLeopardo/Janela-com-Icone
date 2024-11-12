#include <windows.h>
#include "recurso.h"

const char g_szClassName[] = "myWindowClass";

// Declaração da função ShowAboutDialog
void ShowAboutDialog(HWND hwnd);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDD_HELP_ABOUT:
                    ShowAboutDialog(hwnd);  // Agora o compilador conhece a função
                    break;
                case ID_FILE_EXIT:
                    PostMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
                case ID_STUFF_GO:
                    MessageBox(hwnd, "Clique em \"OK\" para destruir Brasilia.", "Bomba Termonuclear!", MB_OK);
                    break;
                case ID_STUFF_SOMEWHERE:
                    MessageBox(hwnd, "Explodir os EUA!", "Menu", MB_OK | MB_ICONINFORMATION);
                    break;
            }
            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Bomba Termonuclear!",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) 
{
    switch (Message)
    {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                    break;

                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                    break;
            }
            break;

        default:
            return FALSE;
    }
    return TRUE;
}

// Função para abrir o diálogo "About"
void ShowAboutDialog(HWND hwnd)
{
    int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
    if (ret == IDOK)
    {
        MessageBox(hwnd, "Caixa de diálogo encerrada com IDOK.", "Nota!", MB_OK | MB_ICONINFORMATION);
    }
    else if (ret == IDCANCEL)
    {
        MessageBox(hwnd, "Caixa de diálogo encerrada com IDCANCEL", "Nota!", MB_OK | MB_ICONINFORMATION);
    }
    else if (ret == -1)
    {
        MessageBox(hwnd, "Caixa de diálogo falhou!", "ERRO!", MB_OK | MB_ICONERROR);
    }
}