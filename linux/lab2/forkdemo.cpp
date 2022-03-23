#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

#include <fstream>
#include <sys/wait.h>

int main()
{
    int i;

    std::ofstream out("out.txt");

    if (fork()) {    /* I must be the parent  */
        for (i = 0; i < 1000; i++) {
            out << "\t\tPARENT " << i << "\n";
        }
      	sleep(7);
    } else {      /* I must be the child   */
        for (i = 0; i < 1000; i++) {
            out << "CHILD "<< i << "\n";
	    }
        sleep(7);
    }
}

