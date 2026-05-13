#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include "fft.h"

void fft(double complex* out, const double complex* in, size_t N) {
    if (N == 2) {
        out[0] = in[0] + in[1];
        out[1] = in[0] - in[1];
        return;
    }
    double complex even[N / 2];
    double complex odd[N / 2];
    for (size_t i = 0; i < N / 2; i++) {
        even[i] = in[i] + in[N / 2 + i];
        odd[i] = (in[i] - in[N / 2 + i]) * cexp(-I * 2.0 * M_PI / (double)N * i);

    }
    fft(out, even, N / 2);
    fft(out + N / 2, odd, N / 2);
}

void bit_reverse(double complex *x, size_t N) {
    int i, j = 0;
    for (i = 0; i < N; i ++) {
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
