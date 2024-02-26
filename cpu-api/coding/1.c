#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int x = 100;
    int rc = fork();

    if (rc < 0)
    {
        exit(1);
    }
    else if (rc == 0)
    {
        x = 114;
        printf("child(pid:%d): %d\n", (int)getpid(), x);
    }
    else
    {
        x = 514;
        printf("parent(pid:%d): %d\n", (int)getpid(), x);
    }

    return 0;
}