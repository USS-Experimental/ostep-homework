#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

int main()
{
    int rc = fork();

    if (rc < 0)
    {
        exit(1);
    }
    else if (rc == 0)
    {
        close(STDOUT_FILENO); 
        printf("child\n");
    }
    else
    {
        printf("parent\n");
    }
}