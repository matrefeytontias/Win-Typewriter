// gcc -shared dll.c -lwinmm -o typewriter.dll

#pragma comment(lib, "winmm.lib")

#include <stdio.h>
#include <Windows.h>

MCI_OPEN_PARMS mPar = { 0 };
int nbCharacters = 100;
volatile int *counter;
volatile int *stopFlag;

#define DLLEXPORT __declspec(dllexport)

void openDiskTray()
{
    // Open disk tray device
    mPar.lpstrDeviceType = (LPCSTR)MCI_DEVTYPE_CD_AUDIO;
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID, (long unsigned int)&mPar);
    // Open actual disk tray
    mciSendCommand(mPar.wDeviceID, MCI_SET, MCI_SET_DOOR_OPEN, 0);
}

void DLLEXPORT setParams(volatile int *stop, volatile int *c, int count)
{
    stopFlag = stop;
    counter = c;
    nbCharacters = count;
}

LRESULT CALLBACK DLLEXPORT keyboardHook(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    if(nCode >= 0)
    {
        if(wParam == WM_KEYDOWN && ((KBDLLHOOKSTRUCT*)lParam)->vkCode == VK_ESCAPE)
            *stopFlag = 1;
        if(++*counter == nbCharacters)
        {
            openDiskTray();
            *counter = 0;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
