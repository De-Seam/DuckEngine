#include "de/engine/engine.h"
#include "test_game_instance.h"

#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        TestGameInstance* game_instance = new TestGameInstance;
        de::Engine::set_game_instance(game_instance);
    }
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    default:

        break;
    }
    return TRUE;
}
