#include <windows.h>
#include <cstdio>
#include <tchar.h>
#include <string>

#define _SECOND 1000000

struct Process
{
  PROCESS_INFORMATION pi;
  STARTUPINFO si;
};

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    printf("Usage: %s [cmdline]\n", argv[0]);
    return 0;
  }

  Process processes[10];

  for(size_t i = 0; i < 10; ++i)
  {
    ZeroMemory(&processes[i].si, sizeof(processes[i].si));
    processes[i].si.cb = sizeof(processes[i].si);
    ZeroMemory(&processes[i].pi, sizeof(processes[i].pi));

    std::string command = argv[1];
    command += " ";
    command += std::to_string(i);
    if(!CreateProcess(nullptr, const_cast<char *>(command.c_str()), nullptr,
                      nullptr, FALSE, 0, nullptr, nullptr, &processes[i].si, &processes[i].pi))
    {
      printf("CreateProcess failed (%d).\n", GetLastError());
      return 0;
    }
  }
  HANDLE wTimer;
  __int64 endTime;
  LARGE_INTEGER quitTime;

  SYSTEMTIME now;

  wTimer = CreateWaitableTimer(NULL, FALSE, NULL);
  endTime = -(atoi(argv[2]) * _SECOND);
  quitTime.LowPart = (DWORD) (endTime & 0xFFFFFFFF);
  quitTime.HighPart = (LONG) (endTime >> 32);

  SetWaitableTimer(wTimer, &quitTime, 0, NULL, NULL, FALSE);
  GetLocalTime(&now);

  DWORD dw = WaitForSingleObject(wTimer, INFINITE);

  CloseHandle(wTimer);
  for(auto& process: processes)
  {
    TerminateProcess(process.pi.hProcess, INFINITE);
    CloseHandle(process.pi.hProcess);
    CloseHandle(process.pi.hThread);
  }
}
