#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        // child process
        printf("Child: working...\n");
        exit(7); // 종료 코드 7
    }
    else
    {
        // parent process
        int status;
        pid_t w = wait(&status);

        if (w == -1)
        {
            perror("wait failed");
            return 1;
        }

        if (WIFEXITED(status))
        {
            printf("Child terminated normally.\n");
            printf("Exit status = %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("Child did not terminate normally.\n");
        }
    }

    return 0;
}