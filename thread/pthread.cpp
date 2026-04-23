#include <pthread.h>
#include <stdio.h>

typedef struct
{
    int from, to;
    long result;
} Range;

void *sum_range(void *arg)
{
    Range *r = (Range *)arg;
    r->result = 0;
    for (int i = r->from; i <= r->to; i++)
        r->result += i;
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    Range r1 = {1, 50, 0}, r2 = {51, 100, 0};

    pthread_create(&t1, NULL, sum_range, &r1);
    pthread_create(&t2, NULL, sum_range, &r2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("total=%ld\n", r1.result + r2.result);
}