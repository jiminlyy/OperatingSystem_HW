#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0)
    {                 // child
        close(fd[1]); // 자식은 쓰기 끝 안 씀
        char buf[100];
        int n = read(fd[0], buf, sizeof(buf));
        write(1, buf, n);
        close(fd[0]);
    }
    else
    {                 // parent
        close(fd[0]); // 부모는 읽기 끝 안 씀
        char *msg = "hello pipe\n";
        write(fd[1], msg, strlen(msg));
        close(fd[1]);
        wait(NULL);
    }

    return 0;
}