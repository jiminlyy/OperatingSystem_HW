#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    char *argv[] = {"ls", "-l", NULL};

    pid_t pid = fork();

    if (pid == 0)
    {
        execvp(argv[0], argv);
        perror("execvp failed");
        _exit(1);
    }
    else
    {
        wait(NULL);
    }

    return 0;
}