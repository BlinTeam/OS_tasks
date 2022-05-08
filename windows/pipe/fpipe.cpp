#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

int main(int argc, char* argv[])
{
  std::string output;
  char szBuf[256];
  DWORD cbRead = 0;
  DWORD cbWritten = 0;
  HANDLE newPipe = CreateNamedPipe(
    "\\\\.\\pipe\\Pipe2",
    PIPE_ACCESS_DUPLEX,
    PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
    PIPE_UNLIMITED_INSTANCES,
    512, 512, 5000, NULL);
  if(ConnectNamedPipe(newPipe, NULL) == false)
  {
    std::cerr << "Error";
    CloseHandle(newPipe);
    return -1;
  }
  HANDLE pipe = CreateFile(
    "\\\\.\\pipe\\Pipe1", GENERIC_READ | GENERIC_WRITE,
    0, NULL, OPEN_EXISTING, 0, NULL);
  if(pipe == NULL)
  {
    exit(-1);
  }
  while(true)
  {
    if(ReadFile(pipe, szBuf, 256, &cbRead, NULL))
    {
      std::cout << szBuf << "\n";
      Sleep(10);
      int i = 0;
      while (szBuf[i])
      {
        szBuf[i] = toupper(szBuf[i]);
        i++;
      }
      std::cout << szBuf << "\n";
      if(!WriteFile(newPipe, szBuf, 256,
                    &cbWritten, NULL))
      {
        CloseHandle(newPipe);
      }
    }
  }
}
