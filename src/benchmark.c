#define _GNU_SOURCE
#include <stddef.h>
#include <threads.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <time.h>

#include "dft.h"
#include "fft.h"

double get_time(void);
void target_func(double complex *out, size_t N);

int main(void) {
    int start_n = 1;
    int end_n = 18;

    printf("N,DFT_Time(s),FFT_Time(s)\n");
    
    for (size_t i = start_n; i <= end_n; i++) {
        size_t N = pow(2, i);

        double complex samples[N];
        double complex out_dft[N];
        double complex out_fft[N];

        target_func(samples, N);

        // dft
        double time_dft; 
        double start_dft = get_time();
        dft(out_dft, samples, N);
        double end_dft = get_time();
        time_dft = end_dft - start_dft;

        // fft
        double start_fft = get_time();
        fft(out_fft, samples, N);
        bit_reverse(out_fft, N);
        double end_fft = get_time();
        double time_fft = end_fft - start_fft;

        printf("%zu, %f, %f\n", N, time_dft, time_fft);
    }
    return 0;
}

double get_time(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

void target_func(double complex *out, size_t N) {
    for (size_t i = 0; i < N; i++) {
        out[i] = csin((2 * M_PI * i / (double)i) * 3) + csin((2 * M_PI * i / (double)N) * 6);
    }
}
