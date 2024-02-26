#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    int rc = fork();

    if (rc < 0)
    {
        exit(1);
    }
    else if (rc == 0)
    {
        int wc = wait(NULL);
        printf("this is child\n");
        printf("child pid:%d\n", (int)getpid());
        printf("return of wait():%d\n\n", wc);
    }
    else
    {
        int wc = wait(NULL);
        printf("this is parent\n");
        printf("parent pid:%d\n", (int)getpid());
        printf("return of wait():%d\n", wc);
    }

    return 0;
}