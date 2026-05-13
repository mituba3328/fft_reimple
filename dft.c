#define _GNU_SOURCE
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>

#define Sample_N 1024

void dft(double complex* out, const double complex* in, size_t N);
void target_func(double complex *out, size_t N);

int main(void) {
    double complex samples[Sample_N];
    double complex freq_domain[Sample_N];
    target_func(samples, Sample_N);

    dft(freq_domain, samples, Sample_N);

    printf("k, F(k)\n");
    for (size_t i = 0; i < Sample_N; i++) {
        printf("%zu, %lf\n", i, cabs(freq_domain[i]));
    }
    return 0;
}

void dft(double complex* out, const double complex* in, size_t N) {
    for (size_t k = 0; k < N; k++) {
        out[k] = 0.0 + 0.0 * I;
        for (size_t n = 0; n < N; n++) {
            out[k] += in[n] * cexp(-I * 2.0 * M_PI * k * n / (double)N);
        }
    }
}

void target_func(double complex *out, size_t N) {
    for (size_t n = 0; n < N; n++) {
        out[n] = csin((2 * M_PI * n / (double)N) * 3) + csin((2 * M_PI * n / (double)N) * 6);
    }
    return;
}
