#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
  HANDLE pipe = CreateFile(
    "\\\\.\\pipe\\Pipe2", GENERIC_READ | GENERIC_WRITE,
    0, NULL, OPEN_EXISTING, 0, NULL);
  if(pipe == NULL)
  {
    std::cerr << "Error";
    exit(-1);
  }
  std::string output;
  char szBuf[256];
  DWORD cbRead = 0;
  std::ofstream fout;
  fout.open("C:\\Users\\cruel\\CLionProjects\\OS\\cmake-build-debug\\output.txt");
  if(!fout.is_open())
  {
    std::cout << "Error";
    return -1;
  }
  while(true)
  {
    if(ReadFile(pipe, szBuf, 256, &cbRead, NULL))
    {
      std::string outcome(szBuf);
      std::cout << outcome << " ";
      fout << outcome;
    }
  }
}
