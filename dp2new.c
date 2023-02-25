#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct timespec start, end;

// this is the code given in the question
float dpunroll(long N, float *pA, float *pB)
{
    float R = 0.0;
    int j;
    for (j = 0; j < N; j += 4)
        R += pA[j] * pB[j] + pA[j + 1] * pB[j + 1] + pA[j + 2] * pB[j + 2] + pA[j + 3] * pB[j + 3];
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

    float total_time = 0;
    float second_half = 0;
    float R = 0.0;
    for (int i = 0; i < iterations; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);

        R = dpunroll(N, pa, pb);

        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_nsec = (((double)end.tv_sec * 1000000 + (double)end.tv_nsec) - ((double)start.tv_sec * 1000000 + (double)start.tv_nsec));

        total_time += time_nsec;
        if (i >= iterations / 2)
        {
            second_half += time_nsec;
        }
        printf("R:%f\n", R);
    }

    printf("R:%f\n", R);
    float mean_exe_time = second_half / (iterations / 2);

    float throughput = (8 * N / 4) / (mean_exe_time);

    float bandwidth = (8 * N) / (mean_exe_time);

    printf("N: %ld  <T>: %f nano sec  B:%.2f GB/sec   F: %.2f GFLOP/sec\n", N, mean_exe_time, bandwidth, throughput);

    return 0;
}