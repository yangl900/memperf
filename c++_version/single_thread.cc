#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <thread>
#include <vector>
#include <sys/mman.h>
#include <stdlib.h>
#include <cstring>
#include <chrono>

using namespace std;

long iterations = 15;
long accessCount = 10ULL << 20;


double randWrite(long size)
{
    void* mem; 
    mem = (void*)malloc(size);
    memset(mem, 0, size);

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
    return time / iterations;
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