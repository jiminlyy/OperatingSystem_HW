#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    printf("parent: start\n");

    pid_t pid = fork();

    if (pid == 0)
    {
        printf("child: before exec\n");
        execlp("ls", "ls", "-l", NULL);
        perror("exec failed");
        _exit(1);
    }
    else
    {
        wait(NULL);
        printf("parent: child=%d\n", pid);
    }

    return 0;
}