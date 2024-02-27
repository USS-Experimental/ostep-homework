#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];

    // Create a pipe, pipefd[0] for read and pipefd[1] for write.
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create the first child process.
    pid_t pid1 = fork();

    if (pid1 < 0) // Check for fork error
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid1 == 0) // First child process
    {
        // Close the read side of the pipe, not used by this child.
        close(pipefd[0]);

        // Redirect the standard output to the write side of the pipe.
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); // Close the original write end after dup2

        // Execute "echo".
        execlp("echo", "echo", "Hello, World!", NULL);

        // If execlp fails:
        perror("exec");
        exit(EXIT_FAILURE);
    }
    else // Parent process
    {
        // Create the second child process.
        pid_t pid2 = fork();

        if (pid2 < 0) // Check for fork error
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid2 == 0) // Second child process
        {
            // Close the write side of the pipe, not used by this child.
            close(pipefd[1]);

            // Redirect the standard input to the read side of the pipe.
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]); // Close the original read end after dup2

            // Execute "cat".
            execlp("cat", "cat", NULL);

            // If execlp fails:
            perror("exec");
            exit(EXIT_FAILURE);
        }
        else // Still in the parent process
        {
            // Close both ends of the pipe in the parent; it doesn't use them.
            close(pipefd[0]);
            close(pipefd[1]);

            // Wait for both child processes to finish.
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }

    return 0;
}
