#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

#define MATRIX_INIT( \
        key_t \
        ) \
\
struct matrix_##key_t { \
    unsigned int n_rows, n_cols; \
    key_t *data; \
}; \
\
struct matrix_##key_t* matrix_##key_t##_new(unsigned int n_rows, unsigned int n_cols) { \
    struct matrix_##key_t *matrix = (struct matrix_##key_t*)malloc(sizeof(struct matrix_##key_t)); \
    matrix->n_rows = n_rows; \
    matrix->n_cols = n_cols; \
    matrix->data = (key_t*)malloc(sizeof(key_t)*n_rows*n_cols); \
    return matrix; \
} \
\
void matrix_##key_t##_set_data(struct matrix_##key_t *matrix, key_t *data) { \
    matrix->data = data; \
} \
\
key_t matrix_##key_t##_cell(const struct matrix_##key_t *matrix, unsigned int row, unsigned int col) { \
    return *(matrix->data + row*matrix->n_cols + col); \
} \
\
struct matrix_##key_t* matrix_##key_t##_sum(const struct matrix_##key_t *A, const struct matrix_##key_t *B) { \
    struct matrix_##key_t *R = matrix_##key_t##_new(A->n_rows, A->n_cols); \
    unsigned int i; \
    for (i = 0; i < R->n_rows*R->n_cols; i++) R->data[i] = A->data[i] + B->data[i]; \
    return R; \
} \
\
struct matrix_##key_t* matrix_##key_t##_mult(const struct matrix_##key_t *A, const struct matrix_##key_t *B) { \
    struct matrix_##key_t *R = matrix_##key_t##_new(A->n_rows, B->n_cols); \
    unsigned int c, d, k; \
    for (c = 0; c < A->n_rows; c++) { \
        for (d = 0; d < B->n_cols; d++) { \
            R->data[c*R->n_cols + d] = 0; \
            for (k = 0; k < B->n_rows; k++) \
            R->data[c*R->n_cols + d] += A->data[c*A->n_cols + k]*B->data[k*B->n_cols + d]; \
        } \
    } \
    return R; \
} \
\
struct matrix_##key_t* matrix_##key_t##_op(const struct matrix_##key_t *A, key_t (*op)(key_t, key_t), key_t c) { \
    unsigned int i; \
    struct matrix_##key_t *R = matrix_##key_t##_new(A->n_rows, A->n_cols); \
    for (i = 0; i < A->n_rows*A->n_cols; i++) R->data[i] = op(A->data[i], c); \
    return R; \
}

#endif // MATRIX_H
