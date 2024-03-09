#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

void print_cost(struct timeval start, struct timeval end, int times);

int main(int argc, char *argv[])
{
    // Ensure correct usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <message> <times>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    __pid_t cpid;
    int pipe1fd[2], pipe2fd[2]; // File descriptors for pipes 
    char buf[1024]; // Buffer for reading messages
    char *meg = argv[1]; // Message to be sent
    int times = atoi(argv[2]); // The number of exchanges
    struct timeval start, end; // Sturct for time calculation
   
   // Create two pipes
    if (pipe(pipe1fd) == -1 || pipe(pipe2fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    // Create a child process
    cpid = fork();
    if (cpid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) // Child process
    {
        close(pipe1fd[1]); // Close the write-end of pipe1
        close(pipe2fd[0]); // Clost the read-end of pipe2

        for (size_t i = 0; i < times; i++)
        {
            // Wait for message from parent in pipe1
            read(pipe1fd[0], buf, sizeof(buf));

            // Sent the message backe to parent with pipe2
            write(pipe2fd[1], buf, strlen(buf) + 1);
        }

        // Close all pipes
        close(pipe1fd[0]);
        close(pipe2fd[1]);

        exit(EXIT_SUCCESS);
    }
    else // Parent process
    {
        close(pipe1fd[0]); // Close the read-end of pipe1
        close(pipe2fd[1]); // Close the write-end of pipe2

        // Start timing
        gettimeofday(&start, NULL);

        for (size_t i = 0; i < times; i++)
        {
            write(pipe1fd[1], meg, strlen(meg) + 1);

            read(pipe2fd[0], buf, sizeof(buf));
        }

        // End timing
        gettimeofday(&end, NULL);

        // Calculate and print the time cost
        print_cost(start, end, times);

        // Close all pipes
        close(pipe1fd[1]);
        close(pipe2fd[1]);

        exit(EXIT_SUCCESS);
    }
}

/**
 * Prints the total time cost and the approximate time per context switch.
 * 
 * @param start A struct timeval representing the start time.
 * @param end A struct timeval representing the end time.
 * @param times The number of message exchanges that occurred.
*/
void print_cost(struct timeval start, struct timeval end, int times)
{
    struct timeval cost;
    cost.tv_sec = end.tv_sec - start.tv_sec;
    cost.tv_usec = ((cost.tv_sec * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("Total time for %d messages: %ld microseconds\n", times, cost.tv_usec);
    printf("Approximate time per context switch: %ld microseconds\n", cost.tv_usec / (times * 2));
}