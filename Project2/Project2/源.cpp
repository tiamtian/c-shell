#include <windows.h>
#include <iostream>
#include <processthreadsapi.h>
#include <tlhelp32.h>

using namespace std;

DWORD qureyProcessId(string name) {

	DWORD pid = 0;
	PROCESSENTRY32 stcp;
	stcp.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &stcp))
	{
		while (Process32Next(snapshot, &stcp) == TRUE)
		{
			if (stcp.szExeFile == name) {
				pid = stcp.th32ProcessID;
			}
		}
	}
	CloseHandle(snapshot);
	return pid;
}

void LoadDll(DWORD pid, char* pathname)
{
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);

	DWORD dwlength = strlen(pathname) + 1;

	LPSTR FileRemote = (LPSTR)VirtualAllocEx(hprocess, NULL, dwlength, MEM_COMMIT, PAGE_READWRITE);
	
	WriteProcessMemory(hprocess, (LPVOID)FileRemote, (LPVOID)pathname, dwlength, NULL);

	HMODULE hkernel = GetModuleHandle("Kernel32.dll");

	DWORD loadaddr = (DWORD)GetProcAddress(hkernel, "LoadLibraryA");

	DWORD threadID;

	HANDLE t = CreateRemoteThread(hprocess, NULL, 0, (LPTHREAD_START_ROUTINE)loadaddr, (LPVOID)FileRemote, 0, &threadID);

	CloseHandle(t);
}

int main()
{	
	DWORD pid = qureyProcessId("devenv.exe");
	cout << pid << endl;
	LoadDll(pid, "D:\\ConsoleApplication2.dll");
	printf("按下回车终止！\n");
	getchar();
	return 0;
}