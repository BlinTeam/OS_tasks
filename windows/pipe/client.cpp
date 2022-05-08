#include <windows.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  HANDLE hPipe;
  DWORD dwWrite, dwRead;
  char lpBuffer[50]{};
  char fileBuffer[1024]{};

  while (true) {
    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Pipe"),
                       GENERIC_READ | GENERIC_WRITE,
                       0,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);
    if (hPipe != INVALID_HANDLE_VALUE)
    {
      printf("Enter file to open: ");
      scanf("%s", lpBuffer);

      WriteFile(hPipe,
                lpBuffer,
                strlen(lpBuffer) + 1,   // = length of string + terminating '\0' !!!
                &dwWrite,
                NULL);

      if (!strcmp(lpBuffer, "disconnect"))
      {
        CloseHandle(hPipe);
        return 0;
      }

      Sleep(10000);

      if (!ReadFile(hPipe, fileBuffer, 1024, &dwRead, NULL))
      {
        printf("Can't read from file\n");
        ExitProcess(0);
      }

      printf("\nFile Text:\n%s\n\n", fileBuffer);

      CloseHandle(hPipe);
    }
  }
}