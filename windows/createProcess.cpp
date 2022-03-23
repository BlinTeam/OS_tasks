#include <comutil.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

STARTUPINFO startInfo;
PROCESS_INFORMATION processInfo;

int main(int argc, char* argv[])
{
	std::string str = "C:\\WINDOWS\\SYSTEM32\\NOTEPAD.EXE ";
	std::string arg = argv[1];

	str += arg;

	std::wstring stemp = std::wstring(str.begin(), str.end());
	LPCWSTR sw = stemp.c_str();

	LPCWSTR lpCommandLine[3] = {
	  sw,
		L"C:\\WINDOWS\\sYSTEM32\\CALC.EXE",
	  L"C:\\WINDOWS\\SYSTEM32\\CHARMAP.EXE"
	};
	ZeroMemory(&startInfo, sizeof(STARTUPINFO));
	startInfo.cb = sizeof(startInfo);

	WCHAR proc_name[256];

	for (auto& i : lpCommandLine)
  {
		wcscpy_s(proc_name, wcslen(i) + 1, i);
		printf("!!!%ls %d\n", i, wcslen(i));

		if (!CreateProcess(NULL, proc_name, NULL, NULL, FALSE,
			HIGH_PRIORITY_CLASS | CREATE_NEW_CONSOLE, NULL, NULL,
			&startInfo, &processInfo))
		{
			fprintf(stderr, "CreateProcess failed on error %d\n", GetLastError());
			ExitProcess(1);
		}
	}

	printf("ProcessHandle=%d\n", (int)processInfo.hProcess);
	printf("ThreadHandle=%d\n", (int)processInfo.hThread);

	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
	return 0;
}