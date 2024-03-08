#include <sys/time.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void execute(char* command, int execnum);
void print_cost(struct timeval start, struct timeval end, char* command,int execnum);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <command> <times>\n", argv[0]);
        return 1;
    }

    char* command = argv[1];
    int execnum = atoi(argv[2]);
    struct timeval start;
    struct timeval end;

    // get the start time
    gettimeofday(&start, NULL);

    // call the specific command specific times
    execute(command, execnum);

    // get the end time
    gettimeofday(&end, NULL);

    // print the time cost
    print_cost(start, end, command, execnum);

    return 0;
}

void execute(char* command, int execnum)
{
    pid_t pid;
    for (int i = 0; i < execnum; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            execlp("true", "true", NULL);
            perror("execlp");
            exit(1);
        }
        else
        {
            wait(NULL);
        }
    }
}

void print_cost(struct timeval start, struct timeval end, char* command,int execnum)
{
    __time_t sec = end.tv_sec - start.tv_sec;
    __time_t usec = end.tv_usec - start.tv_usec;
    printf("execute \"%s\" %d times takes %ld seconds and %ld microseconds.\n", command, execnum, sec, usec);
}