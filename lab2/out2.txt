#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

int main() {
	if(fork()) {
		sleep(5);
		char path[255];
		if(getcwd(path, sizeof(path))) {
			std::cout <<  "Parent is in " << path << "\n";
		} else {
			std::cout << "\nError with printing parent's working directory";
		}
	} else {
	    if(chdir("./test") == 0) {
		    char path[256];
		    if (getcwd(path, sizeof(path))) {
			    std::cout << "Child is in " << path << "\n";
            } else {
			    std::cout << "\nError with printing child directory";
		    }
	    } else {
		    std::cout << "\nError with changing directory";
	    }
    }
}	
