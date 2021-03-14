#include "functions.h"

bool healthSwitch = false;
DWORD localPlayer = *(DWORD*)(moduleBase + 0x10F4F4);
DWORD WINAPI MainThread(HMODULE hModule)
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
            if (healthSwitch == true)
            {
                printf("Unlimited health on!\n");
                
            }
            else
            {
                printf("Unlimited health off!\n");
            }
        
        }  
       
        if (healthSwitch == true)
        {
            //Write our health value to 1337
            *(int*)(localPlayer + 0xF8) = 1337;
        }
     
        if (GetAsyncKeyState(VK_END) & 1)
        {
            FreeLibraryAndExitThread(hModule, NULL);
            fclose(f);
            
        }
    }

    return 0;
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
