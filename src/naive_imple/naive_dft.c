#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include "naive_dft.h"

void naive_dft(double complex* out, const double complex* in, size_t N) {
    for (size_t k = 0; k < N; k++) {
        out[k] = 0.0 + 0.0 * I;
        for (size_t n = 0; n < N; n++) {
            out[k] += in[n] * cexp(-I * 2.0 * M_PI * k * n / (double)N);
        }
    }
}
