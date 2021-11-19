#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <fstream>

int main() {
	FILE* fp = fopen("text.txt", "r");

	if (fp) {
		if (fork()) {
			sleep(5);
			char buf[16]={"\0"};
			fread(buf, 10, 1, fp);
			std::cout << "\nParent read: " << buf << "\n";
			fclose(fp);
		} else {
			char buf[16] = {"\0"};
			fread(buf, 10, 1, fp);
			std::cout << "\nChild read: " << buf;
		}
	}
}

