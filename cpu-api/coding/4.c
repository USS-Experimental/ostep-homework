#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
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
        char *args[3];
        args[0] = strdup("ls");
        args[1] = strdup("/home/liyuting/");
        args[2] = NULL;
        
        char *env[0];
        env[0] = NULL;

        /* Execute path with all arguments. */
        execl("/bin/ls", "ls", "/home/liyuting/", NULL);

        /* Execute file with all arguments. */
        execlp("ls", "ls", "/home/liyuting/", NULL);

        /* Execute path with ith all arguments and new environment. */
        execle("/bin/ls", "ls", "/home/liyuting/", NULL, env);

        /* execute path with arguments ARGV. */
        execv("/bin/ls", args);

        /* Execute file with arguments ARGV. */
        execvp(args[0], args);

        /* Execute path with argument ARGV and new environment. */
        execve("/bin/ls", args, env);
    }
    else
    {
        int wc = wait(NULL);
        assert(wc >= 0);
    }

    return 0;
}