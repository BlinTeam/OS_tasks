#include <cstdio>
#include <cstring>
#include <windows.h>

HANDLE readPipe, writePipe;
SECURITY_ATTRIBUTES pipeSA;
STARTUPINFO scrStartInfo, sinkStartInfo, filterStartInfo;
PROCESS_INFORMATION scrProcessInfo, sinkProcessInfo, filterProcessInfo;

HANDLE hStdIn, hStdout;

//char saveStdout[20];
char path[200];

int main(int argc, char* argv[])
{
  pipeSA.nLength = sizeof(SECURITY_ATTRIBUTES);
  pipeSA.lpSecurityDescriptor = NULL;
  pipeSA.bInheritHandle = TRUE;

  if(!CreatePipe(&readPipe, &writePipe, &pipeSA, 0))
  {
    printf("Cann't create PIPE\n");
    ExitProcess(1);
  }

  printf("readPipe %d writePipe %d\n", readPipe, writePipe);

  // Create process to write the pipe
  // Make handles inheritable

  printf("Main: creating source process\n");

  memset(&scrStartInfo, 0, sizeof(STARTUPINFO));
  scrStartInfo.cb = sizeof(STARTUPINFO);
  scrStartInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
  scrStartInfo.hStdOutput = writePipe;
  scrStartInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
  scrStartInfo.dwFlags = STARTF_USESTDHANDLES;

  strcpy_s(path, strlen(R"(c:\Users\cruel\CLionProjects\OS\cmake-build-debug\wpipe.exe)") + 1,
           R"(c:\Users\cruel\CLionProjects\OS\cmake-build-debug\wpipe.exe)");

  if(!CreateProcess(NULL, path, NULL, NULL, TRUE, CREATE_NEW_CONSOLE,
                    NULL, NULL, &scrStartInfo, &scrProcessInfo))
  {
    printf("Cannot create source process\n");
    ExitProcess(1);
  }

  Sleep(1000);

  // Create process to read the pipe
  // Make handles inheritable

  printf("Main: creating filter process\n");

  memset(&filterStartInfo, 0, sizeof(STARTUPINFO));
  filterStartInfo.cb = sizeof(STARTUPINFO);
  filterStartInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
  filterStartInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  filterStartInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
  filterStartInfo.dwFlags = STARTF_USESTDHANDLES;

  strcpy_s(path, strlen(R"(c:\Users\cruel\CLionProjects\OS\cmake-build-debug\fpipe.exe)") + 1,
           R"(c:\Users\cruel\CLionProjects\OS\cmake-build-debug\fpipe.exe)");

  if(!CreateProcess(NULL, path, NULL, NULL, TRUE, CREATE_NEW_CONSOLE,
                    NULL, NULL, &filterStartInfo, &filterProcessInfo))
  {
    printf("Cannot create filter process\n");
    ExitProcess(1);
  }


  printf("Main: creating sink process\n");

  memset(&sinkStartInfo, 0, sizeof(STARTUPINFO));
  sinkStartInfo.cb = sizeof(STARTUPINFO);
  sinkStartInfo.hStdInput = readPipe;
  sinkStartInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  sinkStartInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
  sinkStartInfo.dwFlags = STARTF_USESTDHANDLES;

  strcpy_s(path, strlen(R"(c:\Users\cruel\CLionProjects\OS\cmake-build-debug\rpipe.exe)") + 1,
           R"(c:\Users\cruel\CLionProjects\OS\cmake-build-debug\rpipe.exe)");

  if(!CreateProcess(NULL, path, NULL, NULL, TRUE, CREATE_NEW_CONSOLE,
                    NULL, NULL, &sinkStartInfo, &sinkProcessInfo))
  {
    printf("Cannot create sink process\n");
    ExitProcess(1);
  }
  CloseHandle(readPipe);
  CloseHandle(writePipe);
}