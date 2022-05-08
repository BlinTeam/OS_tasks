#include <stdio.h>
#include <windows.h>
int main(int argc, char* argv[])
{
  // Открыть исходный файл
  LPSTR path = R"(C:\Users\cruel\CLionProjects\OS\cmake-build-debug\test.txt)";
  HANDLE hfile = CreateFile(path, GENERIC_WRITE | GENERIC_READ, 0, NULL
    , OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  DWORD dwfilesize = GetFileSize(hfile, NULL);
  if (hfile == INVALID_HANDLE_VALUE)
  {
    printf("Cann't create file! %d\n", GetLastError());
    exit(0);
  }
  HANDLE hfilemap = CreateFileMapping(hfile, 0,               /*not inherited*/
                                      PAGE_READWRITE,     /*write copy*/
                                      0,                  /*high-order size*/
                                      0,                  /*low-order size*/
                                      0);
  if (hfilemap == NULL)
  {
    printf("Cann't create file mapping! %d\n", GetLastError());
    exit(0);
  }
  // Получить размер файла dwfilesize

  PVOID pvfile = MapViewOfFile(hfilemap, FILE_MAP_ALL_ACCESS, 0, 0, dwfilesize);

  PSTR pchANSI = (PSTR)pvfile;
  for (int i = 0; i < dwfilesize; i++)
  {
    printf("ch=%c\n", pchANSI[i]);
    pchANSI[i] = 't';
  }

  UnmapViewOfFile(pvfile);
  CloseHandle(hfilemap);
  CloseHandle(hfile);

  return(0);
}