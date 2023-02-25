#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct timespec start, end;

// this is the code given in the question
float dp(long N, float *pA, float *pB)
{
    float R = 0.0;
    int j;
    for (j = 0; j < N; j++)
    {
        R += pA[j] * pB[j];
    }
    // printf("value of R:%f", R);
    return R;
}

int main(int argc, char *argv[])
{

    long N = strtol(argv[1], NULL, 10);

    long iterations = strtol(argv[2], NULL, 10);

    printf("vector size: %ld measurements: %ld\n", N, iterations);

    float pa[N];
    float pb[N];

    for (int i = 0; i < N; i++)
    {
        pa[i] = 1.0;
        pb[i] = 1.0;
    }

    float second_half = 0;
    float R = 0.0;
    for (int i = 0; i < iterations; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);

        R = dp(N, pa, pb);

        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_nsec = (((double)end.tv_sec * 1000000000 + (double)end.tv_nsec) - ((double)start.tv_sec * 1000000000 + (double)start.tv_nsec));

        

        if (i >= iterations / 2)
        {
            second_half += time_nsec;
        }
    }
    printf("R:%f\n",R);
    float mean_exe_time = second_half / (iterations / 2);

    float throughput = (2 * N) / (mean_exe_time); // gives answer in GFLOPs per second

    float bandwidth = (2 * N * 4) / (mean_exe_time); // gives answer in GB per second

    printf("N: %ld  <T>: %f sec  B:%.2f GB/sec   F: %.2f GFLOP/sec\n", N, mean_exe_time/1000000000, bandwidth, throughput);

    return 0;
}