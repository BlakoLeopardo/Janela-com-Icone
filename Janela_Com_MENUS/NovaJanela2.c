#include <windows.h>
#include "Resource.h"

const char g_szClassName[] = "myWindowClass";

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
        case WM_INITDIALOG:
            return TRUE;  // Indica que o diálogo foi inicializado com sucesso

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);  // Fecha o diálogo e retorna IDOK
                    return TRUE;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);  // Fecha o diálogo e retorna IDCANCEL
                    return TRUE;
            }
            break;

        default:
            return FALSE;  // Para todas as mensagens não tratadas, retorna FALSE
    }
    return FALSE;  // Se nenhuma das condições for atendida, retorna FALSE
}

// Step 4: o procedimento de janela
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case ID_HELP_ABOUT:
                // Corrigido para usar DialogBox, não MessageBox
                DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
                break;
            case ID_FILE_EXIT:
                PostMessage(hwnd, WM_CLOSE, 0, 0);  // Fecha a janela quando "Exit" é clicado
                break;
            
            case ID_STUFF_GO:
                MessageBox(hwnd, "Clique Para explodir Brasilia", "Bomba Termonuclear", MB_OK | MB_ICONINFORMATION);
                break;

            }
        break;
        case WM_LBUTTONDOWN:
        {
            char szFileName[MAX_PATH] = {0};
            HINSTANCE hInstance = GetModuleHandle(NULL);
            GetModuleFileName(NULL, szFileName, MAX_PATH);
            MessageBox(hwnd, szFileName, "Esta merda esta em:", MB_OK | MB_ICONINFORMATION);
        }
        break;
        case WM_CLOSE:
            if (MessageBox(hwnd, "Tem certeza diabo?", "Sair", MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
            {
                DestroyWindow(hwnd);
            }
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

    // Step 1: Registrando a classe Janela
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "SEIB O HOMEM MAIS AFEMINADO DE BRASILIA/DF!",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        NULL, NULL, hInstance, NULL);

    HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MYMENU));
    SetMenu(hwnd, hMenu);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: O loop da mensagem
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg); // Traduz mensagens de teclas para caracteres
        DispatchMessage(&Msg);  // Envia a mensagem para o procedimento da janela
    }
    return Msg.wParam;
}