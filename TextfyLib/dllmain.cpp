// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"
#include <iostream>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::cout << "Proces DLL_PROCESS_ATTACH API" << std::endl;
        break;
    case DLL_THREAD_ATTACH:
        std::cout << "Proces DLL_THREAD_ATTACH API" << std::endl;
        break;
    case DLL_THREAD_DETACH:
        std::cout << "Proces DLL_THREAD_DETACH API" << std::endl;
        break;
    case DLL_PROCESS_DETACH:
        std::cout << "Proces DLL_PROCESS_DETACH API" << std::endl;
        break;
    }
    return TRUE;
}