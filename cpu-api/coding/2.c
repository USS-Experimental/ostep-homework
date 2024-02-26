#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main()
{
    int fd;

    fd = open("./2.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("This is the child process. File descriptor: %d\n", fd);
        write(fd, "child", 5);
    }
    else
    {
        printf("This is the parent process. File descriptor: %d\n", fd);
        write(fd, "parent", 6);
    }

    close(fd);
    
    return 0;
}