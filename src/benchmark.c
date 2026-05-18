#include <string.h>
#define _GNU_SOURCE
#define USE_NAIVE_IMPLE
#include <stddef.h>
#include <threads.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <time.h>

#include "naive_imple/naive_dft.h"
#include "naive_imple/naive_fft.h"

double get_time(void);
void target_func(double complex *out, size_t N);

int main(void) {
    int start_n = 1;
    int end_n = 28;

    printf("N, FFT_Time(s)\n");
    
    for (size_t i = start_n; i <= end_n; i++) {
        size_t N = pow(2, i);

        double complex *datas = malloc(sizeof(double complex) * N);

        target_func(datas, N);

        // fft
        double start_fft = get_time();

        # if defined (USE_NAIVE_IMPLE)
        naive_fft(datas, N);
        # elif defined (USE_AVX_512_IMPLE)
        # endif

        double end_fft = get_time();
        double time_fft = end_fft - start_fft;

        printf("N: %zu, time: %lf\n", N, time_fft);
        free(datas);
    }
    return 0;
}

double get_time(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

// f(x)) = sin(3x) + cos(6x)
void target_func(double complex *out, size_t N) {
    for (size_t i = 0; i < N; i++) {
        out[i] = csin((2 * M_PI * i / (double)i) * 3) + ccos((2 * M_PI * i / (double)N) * 6);
    }
}
