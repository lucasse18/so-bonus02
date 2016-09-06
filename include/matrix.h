#include <stdlib.h> //size_t

typedef struct matrix matrix_t;

int matrix_init(matrix_t **m, size_t size);
int matrix_init_rand(matrix_t **m, size_t size);
int matrix_free(matrix_t **m);
void matrix_mul(const matrix_t *a, const matrix_t *b, matrix_t **res);
void matrix_pow(matrix_t **m, unsigned int exp);
void matrix_print(const matrix_t *m);
