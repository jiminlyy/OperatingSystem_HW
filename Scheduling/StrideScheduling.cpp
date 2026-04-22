#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Process
{
    string name;
    int tickets;
    int stride;
    int pass;
};

int main()
{
    const int K = 10000; // 공통 기준값

    vector<Process> procs = {
        {"A", 100, 0, 0},
        {"B", 50, 0, 0},
        {"C", 250, 0, 0}};

    // stride 계산
    for (auto &p : procs)
    {
        p.stride = K / p.tickets;
    }
    // A.stride=100, B.stride=200, C.stride=40

    // 8번 스케줄링
    for (int i = 0; i < 8; i++)
    {
        // pass가 가장 작은 프로세스 찾기
        int minIdx = 0;
        for (int j = 1; j < procs.size(); j++)
        {
            if (procs[j].pass < procs[minIdx].pass)
            {
                minIdx = j;
            }
        }

        cout << procs[minIdx].name << " ";
        procs[minIdx].pass += procs[minIdx].stride;
    }
    // 출력: A B C C C A C C
}