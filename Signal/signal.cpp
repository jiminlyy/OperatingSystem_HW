#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig)
{
    printf("Caught signal %d\n", sig);
}

int main(void)
{
    signal(SIGINT, handler); // 핸들러 등록
    printf("PID=%d, waiting...\n", getpid());
    while (1)
    {
        sleep(1);
    }
    return 0;
}