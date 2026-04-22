#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        close(1); // stdout 비우기
        open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        execlp("ls", "ls", NULL);
        _exit(1);
    }
    else
    {
        wait(NULL);
    }
}