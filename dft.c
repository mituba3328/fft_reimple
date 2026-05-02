#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <complex.h>

float target_func(float x);

int main(void) {
    int sample_num = 1000;
    int max_k = 1000;
    float max_t = 1.0f;
    // float weight;
    for (int k = 0; k < max_k; k++) {
        // float real = 0.0f;
        // float imag = 0.0f;
        for (int n = 0; n < sample_num; n++) {
            float theta = -(float)n / (float)sample_num * 2.0f * M_PIf * max_t;
            float w_n = -(float)n / (float)sample_num * 2.0f * M_PIf * (float)k;
            float r = target_func(theta);
            // real += r * cosf(w_n);
            // imag += r * sinf(w_n);
            if (k == 996 || k == 997 || k == 998) {
                printf("%d, %f, %f\n", k, (double)(r * cosf(w_n)), (double)(r * sinf(w_n)));
            }
        }
        // weight = rootnf(real * real + imag * imag, 2);
        // printf("%d[hz]: %lf\n", k, (double)weight);
    }
    return 0;
}

float target_func(float x) {
    float y = sinf(3 * x);
    return y;
}
