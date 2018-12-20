// gcc main.cpp -lstdc++ -o typewriter

#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <string>
#include <Windows.h>
#include <mmsystem.h>

typedef void (*DLLfunc1)(volatile int*, volatile int*, int);
typedef LRESULT (CALLBACK *DLLfunc2)(_In_ int, _In_ WPARAM, _In_ LPARAM);

volatile int stop = 0, counter = 0;

int counter2 = 0;

int main(int argc, char *argv[])
{
    HINSTANCE hDLL;
    DLLfunc1 setParams; DLLfunc2 keyboardHook;
    
    hDLL = LoadLibrary("typewriter");
    if(hDLL != NULL)
    {
        setParams = (DLLfunc1)GetProcAddress(hDLL, "setParams");
        keyboardHook = (DLLfunc2)GetProcAddress(hDLL, "keyboardHook");
        
        if(setParams && keyboardHook)
        {
            setParams(&stop, &counter, argc > 1 ? std::stoi(argv[1]) : 100);
            HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHook, hDLL, 0);
            if(!hook)
            {
                std::cout << "Hooking didn't work :(" << std::endl;
                goto exitLabel;
            }
            
            while(!stop)
            {
                MSG msg;
                while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE | PM_QS_SENDMESSAGE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
            
            UnhookWindowsHookEx(hook);
        }
        else
            std::cout << "Couldn't find functions : " << (void*)setParams << ", " << (void*)keyboardHook << std::endl;
exitLabel:
        FreeLibrary(hDLL);
    }
    else
        std::cout << "nah man" << std::endl;
    
    return 0;
}
