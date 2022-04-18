#include <conio.h>
#include <cstring>
#include <cstdio>
#include <windows.h>
#include <string>
#include <fstream>

HANDLE hEvent;

WCHAR proc_name[50];
WCHAR str[50];

int main(int argc, char* argv[])
{
  if(argc >= 2)
  {
    std::string name = argv[1];
    std::wstring w_name = std::wstring(name.begin(), name.end());
    wcscpy_s(proc_name, strlen(argv[1]) + 1, w_name.c_str());
  }
  else
  {
    wcscpy_s(proc_name, wcslen(L"Default Proc_name") + 1, L"Default Proc_name");
  }

  hEvent = CreateEvent(NULL, FALSE, TRUE, reinterpret_cast<LPCSTR>(L"exclusive_speech_event"));
  if(GetLastError() == ERROR_ALREADY_EXISTS)
  {
    printf("Event was opened\n");
  }
  else
  {
    printf("Event was created\n");
  }

  BOOL bExit = FALSE;
  DWORD dw;

  while(!bExit)
  {
    wcscpy_s(str, wcslen(L"a") + 1, L"a");

    dw = WaitForSingleObject(hEvent, INFINITE);
    switch(dw)
    {
    case WAIT_OBJECT_0:
      printf("Thread %ls catch Event\n", proc_name);
      break;
    case WAIT_FAILED:
      printf("Wait failed\n");
      break;
    }

    printf("Hello! My name is %ls\n", proc_name);

    std::fstream out("out.txt");

    _getws_s(str, 10);
    printf("User input %ls\n", str);

    for (size_t i = 0; i < 10; ++i)
    {
      out << (rand() % 100)  << " ";
    }

    while(wcscmp(str, L"next") && wcscmp(str, L"exit"))
    {
      _getws_s(str, 10);
      printf("User input %ls\n", str);
      for (size_t i = 0; i < 10; ++i)
      {
        out << (rand() % 100)  << " ";
      }
    }

    if(!wcscmp(str, L"exit"))
    {
      bExit = TRUE;
    }

    printf("Thread %ls release control\n", proc_name);
    SetEvent(hEvent);

  }
  printf("good buy!\n");
  return 0;
}
