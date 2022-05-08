#include <windows.h>
#include <cstdio>
#include <iostream>
#include <ctime>

bool runFlag = true;

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	int param = *static_cast<int*>(lpParameter);

	printf("I am ThreadProc=%d Hello!\n", param);

	while (runFlag)
	{
		printf("ThreadProc=%d in while!\n", param);

		Sleep(100);
	}
	return 0;
}

int main(int argc, char* argv[])
{
  int num = atoi(argv[1]);
	int life = atoi(argv[2]);
	HANDLE*  mHandle = new HANDLE[num];
	DWORD* mArg = new DWORD[num];
  DWORD* mId = new DWORD[num];
	int i;

	printf("I am main! Hello!\n");

	clock_t now = time(0);
	clock_t budilnik = now + life;

	for (i = 0; i < num; i++)
	{
		mArg[i] = i;
		mHandle[i] = CreateThread(NULL, 0, ThreadProc, mArg + i, 0, mId + i);
	}

	while(time(0) < budilnik)
	{
		Sleep(1000);
	}
	runFlag = false;
	Sleep(5000);
	std::cout << "I'll be back";

		//while(TRUE)
		//{
		//	printf("Main in while!\n");

		//	Sleep(100);
		//}
	for (int i = 0; i < num; i++)
	{
    CloseHandle(mHandle[i]);	  
	}
	return 0;
}