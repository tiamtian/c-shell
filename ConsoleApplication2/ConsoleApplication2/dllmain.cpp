// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{	
		HWND hwnd = GetActiveWindow();
		MessageBox(hwnd, L"DLL已进入目标进程。", L"信息", MB_ICONINFORMATION);
	}
	}
	return TRUE;
}

