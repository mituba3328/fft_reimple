#include <complex.h>
#include <stddef.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "naive_fft.h"

void naive_fft(double complex* datas, size_t length) {
    naive_bit_reverse(datas, length);

    // stage loop
    for (size_t N = 2; N <= length; N = N << 1) {
        // block loop
        #pragma omp parallel for
        for (size_t i = 0; i < (length - (N - 1)); i = i + N) {
            double complex W_N = cexp(-I * 2 * M_PI / (double)N);
            // butterfly loop
            for (size_t j = 0; j < (N >> 1); j++) {
                datas[i + j] = datas[i + j] + datas[i + j + (N >> 1)] * ((j == 0) ? 1 : W_N);
                datas[i + j + (N >> 1)] = datas[i + j] - datas[i + j + (N >> 1)] * ((j == 0) ? 1 : W_N);
                W_N = W_N * ((j == 0) ? 1 : W_N);
            }
        }
    }
}

void naive_bit_reverse(double complex *x, size_t N) {
    size_t j = 0;
    for (size_t i = 0; i < N; i ++) {
        if (i < j) {
            double complex temp = x[i];
            x[i] = x[j];
            x[j] = temp;
        }
        int m = N >> 1;
        while (m >= 1 && j >= m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
}
