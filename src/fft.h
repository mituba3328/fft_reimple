#include <stddef.h>
#include <complex.h>

void fft(double complex* out, const double complex* in, size_t N);
void bit_reverse(double complex *x, size_t N);
