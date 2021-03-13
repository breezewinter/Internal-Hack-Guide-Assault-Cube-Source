#include "functions.h"

bool healthSwitch = false;

int WINAPI MainThread(HMODULE hModule)
{
    DWORD moduleBase = (DWORD)GetModuleHandle("ac_client.exe");
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    printf("Injected!\n[F1] Unlimited health\n[END] Exit!\n");
    while (true)
    {
        // Switch
        if (GetAsyncKeyState(VK_F1) & 1)
        {
            healthSwitch = !healthSwitch;
            if (healthSwitch)
            {
                printf("Unlimited health on!\n");
            }
            else
            {
                printf("Unlimited health off!\n");
            }
        }
        if (healthSwitch)
        {
            ptr localPlayer = *(ptr*)(moduleBase + 0x10F4F4);
            *(int*)(localPlayer + 0xF8) = 1337;
        }
        else
        {
            ptr localPlayer = *(ptr*)(moduleBase + 0x10F4F4);
            if (true & 1)
            {
                *(int*)(localPlayer + 0xF8) = 100;
            }
        }
        if (GetAsyncKeyState(VK_END))
        {
            FreeLibraryAndExitThread(hModule, NULL);
            return 0;
        }
    }


}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL);
        break;
    }
    return TRUE;
}