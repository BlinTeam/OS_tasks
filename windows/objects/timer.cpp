#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <chrono>

using namespace std::chrono;

#define _SECOND 1000000

int main( int argc, char* argv[] )
{

  HANDLE          wTimer;
  __int64         endTime;
  LARGE_INTEGER   quitTime;

  SYSTEMTIME now;

  wTimer = CreateWaitableTimer(NULL,FALSE,NULL);

  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << '\n';
  }

  milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  srand(ms.count());
  endTime = -((rand() % 100) * _SECOND);
  quitTime.LowPart  = (DWORD) ( endTime & 0xFFFFFFFF );
  quitTime.HighPart = (LONG)  ( endTime >> 32 );

  SetWaitableTimer(wTimer,&quitTime,0,NULL,NULL,FALSE);

  GetLocalTime(&now);
  printf("Local Time %d %d %d\n",now.wHour,now.wMinute,now.wSecond);

  DWORD dw=WaitForSingleObject(wTimer,INFINITE);
  switch (dw)
  {
  case WAIT_OBJECT_0: printf("Base thread wake up\n"); break;
  case WAIT_FAILED: printf("Wait failed\n"); return 1;
  }

  printf("Waitable Timer sent signal\n");
  GetLocalTime(&now);
  printf("Local Time %d %d %d\n",now.wHour,now.wMinute,now.wSecond);

  CloseHandle( wTimer );
  return 0;
}