#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

int main()
{
  LPCSTR lpszPipeName = "\\\\.\\pipe\\Pipe1";
  HANDLE hNamedPipe = CreateNamedPipe(
    lpszPipeName,
    PIPE_ACCESS_DUPLEX,
    PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
    PIPE_UNLIMITED_INSTANCES,
    512, 512, 5000, NULL);
  if(hNamedPipe == INVALID_HANDLE_VALUE)
  {
    return -1;
  }
  std::ifstream fin("C:\\Users\\cruel\\CLionProjects\\OS\\cmake-build-debug\\input.txt");
  std::string input;
  if(ConnectNamedPipe(hNamedPipe, NULL) == false)
  {
    CloseHandle(hNamedPipe);
    fin.close();
    return -1;
  }
  DWORD cbWritten = 0;
  while(!fin.eof())
  {
    getline(fin, input);
    std::cout << input << "\n";
    Sleep(10);
    if(!WriteFile(hNamedPipe, input.c_str(), strlen(input.c_str()) + 1,
                  &cbWritten, NULL))
    {
      CloseHandle(hNamedPipe);
      fin.close();
    }
  }
}
