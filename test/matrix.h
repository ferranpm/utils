#include "../matrix.h"
#include <stdio.h>

MATRIX_INIT(float);
MATRIX_INIT(char);

float multiply(float a, float b) {
    return a*b;
}

int matrix() {
    struct matrix_float *A = matrix_float_new(2, 3);
    struct matrix_float *B = matrix_float_new(2, 3);
    struct matrix_float *C = matrix_float_new(3, 2);
    float _A[] = {
        2.3, 2.7, 1.0,
        4.2, 2.1, 4.0
    };
    float _B[] = {
        2.3, 2.7, 1.0,
        4.2, 2.1, 4.0
    };
    float _C[] = {
        3.4, 5.1,
        8.6, 7.1,
        1.2, 3.0
    };
    matrix_float_set_data(A, _A);
    matrix_float_set_data(B, _B);
    matrix_float_set_data(C, _C);

    struct matrix_float *ApB = matrix_float_sum(A, B);
    struct matrix_float *AtC = matrix_float_mult(A, C);
    struct matrix_float *At3 = matrix_float_op(A, multiply, 3);

    return
        matrix_float_cell(A, 1, 1) != 2.1f
     || matrix_float_cell(ApB, 0, 0) != 4.6f
     || matrix_float_cell(ApB, 1, 1) != 4.2f
     || matrix_float_cell(AtC, 0, 0) != 32.24f
     || matrix_float_cell(At3, 0, 2) != 3.0f
     ;
}
