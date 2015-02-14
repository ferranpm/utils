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

    matrix_float_set_cell(A, 0, 0, 2.3);
    matrix_float_set_cell(A, 0, 1, 2.7);
    matrix_float_set_cell(A, 0, 2, 1.0);
    matrix_float_set_cell(A, 1, 0, 4.2);
    matrix_float_set_cell(A, 1, 1, 2.1);
    matrix_float_set_cell(A, 1, 2, 4.0);

    matrix_float_set_cell(B, 0, 0, 2.3);
    matrix_float_set_cell(B, 0, 1, 2.7);
    matrix_float_set_cell(B, 0, 2, 1.0);
    matrix_float_set_cell(B, 1, 0, 4.2);
    matrix_float_set_cell(B, 1, 1, 2.1);
    matrix_float_set_cell(B, 1, 2, 4.0);

    matrix_float_set_cell(C, 0, 0, 3.4);
    matrix_float_set_cell(C, 0, 1, 5.1);
    matrix_float_set_cell(C, 1, 0, 8.6);
    matrix_float_set_cell(C, 1, 1, 7.1);
    matrix_float_set_cell(C, 2, 0, 1.2);
    matrix_float_set_cell(C, 2, 1, 3.0);

    struct matrix_float *ApB = matrix_float_sum(A, B);
    struct matrix_float *AtC = matrix_float_mult(A, C);
    struct matrix_float *At3 = matrix_float_op(A, multiply, 3);

    int ret =
        matrix_float_cell(A, 1, 1) != 2.1f
     || matrix_float_cell(ApB, 0, 0) != 4.6f
     || matrix_float_cell(ApB, 1, 1) != 4.2f
     || matrix_float_cell(AtC, 0, 0) != 32.24f
     || matrix_float_cell(At3, 0, 2) != 3.0f
     ;

    matrix_float_delete(A);
    matrix_float_delete(B);
    matrix_float_delete(C);
    matrix_float_delete(ApB);
    matrix_float_delete(AtC);
    matrix_float_delete(At3);

    return ret;
}
