#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <thread>
#include <vector>
#include <sys/mman.h>
#include <stdlib.h>
#include <cstring>
#include <chrono>
#include <atomic>

using namespace std;

long iterations = 15;
long accessCount = 10ULL << 20;
int threadCount = 5;

atomic<int> readyCount;
atomic<int> totalTime;


double randWriteImpl(long size)
{
    void* mem; 
    mem = (void*)malloc(size);
    memset(mem, 0, size);

    readyCount++;
    while(readyCount != threadCount);
    int time = 0;

    for (long i = 0; i < iterations; i++) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        for (long n = 0; n < accessCount; n++) {
            long randnum = rand() % size;
            ((char*)(mem))[randnum] = 'a';
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        time += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();     
    }


    free(mem);
    totalTime += time;
    return time / iterations;
}

double randWrite(long size)
{
    readyCount = 0;
    totalTime = 0;

    vector<std::thread> threads;

    for(int i = 0; i < threadCount; i++) {
        threads.emplace_back(randWriteImpl, size);
    }

    for (auto& th : threads) {
        th.join();
    }

    return totalTime / threadCount / iterations;
}


int main(int argc, char const *argv[])
{
    long  SizeGb = 1ULL << 30;
    long SizeMb = 1ULL << 20;
    long SizeKb = 1ULL << 10;
    printf("Buffer(KB), Latency(ms)\n");
    printf("%d, %.3f\n", 1, randWrite(SizeKb*1));
    printf("%d, %.3f\n", 2, randWrite(SizeKb*2));
    printf("%d, %.3f\n", 4, randWrite(SizeKb*4));
    printf("%d, %.3f\n", 8, randWrite(SizeKb*8));
    printf("%d, %.3f\n", 16, randWrite(SizeKb*16));
    printf("%d, %.3f\n", 32, randWrite(SizeKb*32));
    printf("%d, %.3f\n", 64, randWrite(SizeKb*64));
    printf("%d, %.3f\n", 128, randWrite(SizeKb*128));
    printf("%d, %.3f\n", 256, randWrite(SizeKb*256));
    printf("%d, %.3f\n", 2000, randWrite(SizeMb*2));
    printf("%d, %.3f\n", 4000, randWrite(SizeMb*4));
    printf("%d, %.3f\n", 8000, randWrite(SizeMb*8));
    printf("%d, %.3f\n", 16000, randWrite(SizeMb*16));
    printf("%d, %.3f\n", 32000, randWrite(SizeMb*32));
    printf("%d, %.3f\n", 64000, randWrite(SizeMb*64));
    printf("%d, %.3f\n", 128000, randWrite(SizeMb*128));
    printf("%d, %.3f\n", 256000, randWrite(SizeMb*256));
    printf("%d, %.3f\n", 512000, randWrite(SizeMb*512));
    printf("%d, %.3f\n", 768000, randWrite(SizeMb*768));
    printf("%d, %.3f\n", 1000000, randWrite(SizeGb*1));

    // std::this_thread::sleep_for(std::chrono::seconds(1000));
    return 0;
}
//g++ test.cc -o test -pthread -O3
// to run ./test