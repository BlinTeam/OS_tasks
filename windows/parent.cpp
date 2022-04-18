#include <cstring>
#include <windows.h>
#include <cstdio>
#include <fstream>

char Name[50];
char path[200];
char str[200];

HANDLE hEvent;

SECURITY_ATTRIBUTES SecurityAttributes;

PROCESS_INFORMATION ProcessInf;

STARTUPINFO StartInfo;

int main(int argc, char* argv[])
{
  strcpy_s(Name,"Parent");

  SecurityAttributes.bInheritHandle=TRUE;
  SecurityAttributes.lpSecurityDescriptor=NULL;
  SecurityAttributes.nLength=sizeof(SecurityAttributes);

  strcpy_s(path,R"(c:\Users\cruel\CLionProjects\OS\cmake-build-debug)");
  strcat_s(path,"\\");
  strcat_s(path,"child.exe");
  strcat_s(path," ");

  hEvent = CreateEvent(&SecurityAttributes,FALSE,TRUE,NULL);

  _itoa_s(reinterpret_cast<int&>(hEvent),str,10);
  strcat_s(path,str);

  memset(&StartInfo,0,sizeof(StartInfo));
  StartInfo.cb=sizeof(StartInfo);

  if(!CreateProcess(NULL,path,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,
                    &StartInfo,&ProcessInf))
  {
    printf("Could not create child process!\n");
    CloseHandle(hEvent);
    return 0;
  }

  BOOL bExit = FALSE;
  DWORD dw;

  std::fstream out("out.txt");

  while(!bExit)
  {
    strcpy_s(str,"a");

    WaitForSingleObject(hEvent,INFINITE);

    printf("Hello! My name is %s\n",Name);

    gets(str);
    printf("User input %s\n", str);
    for (size_t i = 0; i < 10; ++i)
    {
      out << (rand() % 100)  << " ";
    }
    out << str << "\n";

    while(strcmp(str, "next") && strcmp(str, "exit"))
    {
      gets(str);
      printf("User input %s\n", str);
      for (size_t i = 0; i < 10; ++i)
      {
        out << (rand() % 100)  << " ";
      }
      out << str << "\n";
    }

    if(!strcmp(str, "exit"))
    {
      bExit = TRUE;
    }

    printf("Thread %ls release control\n", Name);
    SetEvent(hEvent);

  }
  printf("good buy!\n");
  return 0;
}