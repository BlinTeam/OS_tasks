#include <cstring>
#include <windows.h>
#include <cstdio>
#include <fstream>

char Name[50];
char str[200];

HANDLE hEvent;


int main(int argc, char* argv[])
{
  if(argc!=2)
  {
    printf("Invalid parameter!\n");
    return 0;
  }

  hEvent = (HANDLE) atoi(argv[1]);
  strcpy_s(Name,"child");


  BOOL bExit = FALSE;
  DWORD dw;

  while(!bExit)
  {
    strcpy_s(str,"a");

    WaitForSingleObject(hEvent,INFINITE);

    printf("Hello! My name is %s\n",Name);

    std::fstream out("out.txt");
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