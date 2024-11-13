#include <windows.h>
#include "Resource.h"

const char g_szClassName[] = "myWindowClass";

// Step 4: o procedimento de janela
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
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
        /* As referências para indicar que passar em NULL nos retornará "um identificador para o arquivo usado para criar o processo de chamada", 
           que é exatamente o que precisamos, o que acabamos de mencionar.
        */
        HINSTANCE hInstance = GetModuleHandle(NULL);
        /* Agora, para o segundo parâmetro {HINSTANCE hInstance = GetModuleHandle(NULL);} vemos que ele é " um ponteiro para um buffer que recebe
           o caminho e o nome do arquivo do módulo especificado" e o tipo de dados é (ou se suas referências são antigas).
        */
        GetModuleFileName(NULL, szFileName, MAX_PATH);
        /* MAX_PATH é uma macro útil incluída por meio de que é definida para o comprimento máximo de um buffer necessário
           para armazenar um nome de arquivo no Win32.
           Também passamos para que ele saiba o tamanho do buffer. <windows.h>MAX_PATHGetModuleFileName()
        */
        /* O terceiro parâmetro de GetModuleFileName deve ser o tamanho do buffer szFileName, não uma string. 
           Esse erro causa um comportamento inesperado.
        */
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

    //Step 1: Registrando a classe Janela
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

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: O loop da mensagem 
    /* O que é um loop de mensagem:
       
    1. A chamada do loop de mensagens, que procura na sua fila de mensagens. 
       Se a fila de mensagens estiver vazia, seu programa basicamente para e espera por (Bloqueia). GetMessage()
    
    2. Quando ocorre um evento que faz com que uma mensagem seja adicionada à fila (por exemplo, o sistema registra um clique do mouse) 
       retorna um valor positivo indicando que há uma mensagem para ser processado e que preencheu os membros da estrutura que passamos. 
       Ele retorna se atingir, e um valor negativo se ocorreu um erro. GetMessages()MSG0WM_QUIT
    
    3. Pegamos a mensagem (na variável) e passamos, isso faz um pouco de processamento adicional, 
       traduzindo mensagens de chave virtual em mensagens de caracteres.
       Esta etapa é realmente opcional, mas certas coisas não funcionarão se não estiver lá. MsgTranslateMessage()

    4. Feito isso, passamos a mensagem para . O que faz é tomar a mensagem, verifica para qual janela ela se destina e, em seguida, 
       procura a janela Procedimento para a janela.]
       Em seguida, ele chama esse procedimento, enviando como parâmetros o identificador da janela, a mensagem e. DispatchMessage()wParamlParam
    
    5. No procedimento da janela, você verifica a mensagem e seus parâmetros e faz o que quiser com eles! Se você não estiver lidando com a mensagem específica, quase sempre chamará o que executará as ações padrão para você 
       (o que geralmente significa que não faz nada). DefWindowProc()

    6. Depois de terminar de processar a mensagem, o procedimento do Windows retorna, retorna e voltamos ao início do loop. DispatchMessage()
    */
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
    /* 
    7. Este é um conceito muito importante para programas do Windows. Seu procedimento de janela não é magicamente chamado pelo sistema,
       na verdade você o chama indiretamente. Se você quiser, você pode usar no identificador da janela para o qual a mensagem é destinada para procurar 
       o procedimento da janela e chamá-lo diretamente! DispatchMessage()GetWindowLong()
    */
        TranslateMessage(&Msg); // 7. WNDPROC fWndProc = (WNDPROC)GetWindowLong(Msg.hwnd, GWL_WNDPROC);
        DispatchMessage(&Msg); // 7. fWndProc(Msg.hwnd, Msg.message, Msg.wParam, Msg.lParam);
    }
    return Msg.wParam;
}

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
        case WM_INITDIALOG:
            return TRUE;  // Retorna TRUE para indicar que a inicialização do diálogo foi bem-sucedida

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);  // Fecha o diálogo e retorna IDOK
                    return TRUE;  // Indica que o comando foi tratado

                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);  // Fecha o diálogo e retorna IDCANCEL
                    return TRUE;  // Indica que o comando foi tratado
            }
            break;

        default:
            return FALSE;  // Para todas as mensagens não tratadas, retorna FALSE
    }

    return FALSE;  // Se nenhuma das condições for atendida, retorna FALSE
}

// Codigo copiado do link - http://www.winprog.org/tutorial/simple_window.html :)

/*  Explicação do código - 
    cbSize - O tamanho da estrutura.
    style - Class Styles (), não deve ser confundido com Window Styles ().
    Isso geralmente pode ser definido como. CS_*WS_*0
    lpfnWndProc - Ponteiro para o procedimento de janela para essa classe de janela.
    cbClsExtra - Amount of extra data allocated for this class in memory. Usually . 0
    cbWndExtra - Quantidade de dados extras alocados na memória por janela desse tipo. Normalmente. 0
    hInstance - Identificador para a instância do aplicativo (que obtivemos no primeiro parâmetro de ). WinMain()
    hIcon - Ícone grande (geralmente 32x32) mostrado quando o usuário pressiona Alt+Tab.
    hCursor - Cursor que será exibido sobre nossa janela.
    hbrBackground - Pincel de fundo para definir a cor da nossa janela.
    lpszMenuName - Nome de um recurso de menu a ser usado para as janelas com essa classe.
    lpszClassName - Nome com o qual identificar a classe.
    hIconSm - Ícone pequeno (geralmente 16x16) para mostrar na barra de tarefas e no canto superior esquerdo da janela.
    */