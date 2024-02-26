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
        int wc = waitpid(rc, NULL, WNOHANG);
        printf("this is child\n");     
        printf("child pid:%d\n", (int)getpid());
        printf("child's return of waitpid():%d\n", wc);
    }
    else
    {
        int wc = waitpid(rc, NULL, 0);
        printf("this is parent\n");
        printf("parent pid:%d\n", (int)getpid());
        printf("parent's return of waitpid():%d\n", wc);
    }

    return 0;
}