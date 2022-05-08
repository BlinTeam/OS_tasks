#include <cstdio>
#include <windows.h>
#include <iostream>

int main(int argc, char* argv[])
{
  HANDLE hPipe, hInputFile;
  char buffer[1024], fileBUF[1024];
  DWORD dwRead, dwWrite;

  while(true)
  {
    hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Pipe"),
                            PIPE_ACCESS_DUPLEX,
                            PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
                            1, 1024, 1024, NMPWAIT_USE_DEFAULT_WAIT, NULL);

    if(hPipe == INVALID_HANDLE_VALUE)
    {
      std::cout << "Error: " << GetLastError();
    }

    printf("Waiting for clients!\n");
    ConnectNamedPipe(hPipe, NULL);
    printf("New client connected!\n");

    ReadFile(hPipe, buffer, 1024, &dwRead, NULL);

    if(!strcmp(buffer, "disconnect"))
    {
      DisconnectNamedPipe(hPipe);
      CloseHandle(hPipe);
      printf("Client disconnected!\n");
      continue;
    }

    printf("File to open: %s\n", buffer);

    hInputFile = CreateFile(buffer,
                            GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

    if(GetLastError() == 2)
    {
      char error[50] = "Error while opening! Such file doesn't exist!\n";
      WriteFile(hPipe,
                error,
                strlen(error),
                &dwWrite,
                NULL);
    }
    else
    {
      printf("Reading from file...\n");
      if(!ReadFile(hInputFile, fileBUF, 1024, &dwRead, NULL))
      {
        printf("Can't read from file\n");
        ExitProcess(0);
      }

      Sleep(5000);

      if(!WriteFile(hPipe, fileBUF, dwRead, &dwWrite, NULL))
      {
        printf("Can't write to pipe\n");
        ExitProcess(0);
      }
      printf("File readed!\n");
    }
    CloseHandle(hInputFile);
    CloseHandle(hPipe);
  }
}