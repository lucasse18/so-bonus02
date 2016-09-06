#include <matrix.h>
#include <gmp.h>   // GNU multiple precision library
#include <stdio.h> // putchar

#define RANDMAX 6

struct matrix {
  mpz_t **data;
  size_t size;
};

int matrix_init(matrix_t **m, size_t size) {
  (*m) = malloc(sizeof(matrix_t));
  (*m)->size = size;
  (*m)->data = malloc(size * sizeof(*((*m)->data)));
  for(size_t i = 0; i < size; i++) {
    (*m)->data[i] = malloc(size * sizeof(**((*m)->data)));
    for(size_t j = 0; j < size; j++)
      mpz_init((*m)->data[i][j]);
  }
  return 0;
}

// FIXME replicacao
int matrix_init_rand(matrix_t **m, size_t size) {
  (*m) = malloc(sizeof(matrix_t));
  (*m)->size = size;
  (*m)->data = malloc(size * sizeof(*((*m)->data)));
  for(size_t i = 0; i < size; i++) {
    (*m)->data[i] = malloc(size * sizeof(**((*m)->data)));
    for(size_t j = 0; j < size; j++)
      mpz_init_set_si((*m)->data[i][j], (long) rand()%RANDMAX);
  }
  return 0;
}

// FIXME replicacao
int matrix_cpy(const matrix_t *src, matrix_t **dst) {
  size_t size = src->size;
  (*dst) = malloc(sizeof(matrix_t));
  (*dst)->size = size;
  (*dst)->data = malloc(size * sizeof(*((*dst)->data)));
  for(size_t i = 0; i < size; i++) {
    (*dst)->data[i] = malloc(size * sizeof(**((*dst)->data)));
    for(size_t j = 0; j < size; j++)
      mpz_init_set((*dst)->data[i][j], src->data[i][j]);
  }
  return 0;
}

int matrix_mov(const matrix_t *src, matrix_t **dst) {
  size_t size = src->size;
  for(size_t i = 0; i < size; i++) {
    for(size_t j = 0; j < size; j++)
      mpz_set((*dst)->data[i][j], src->data[i][j]);
  }
  return 0;
}

int matrix_free(matrix_t **m) {
  size_t size = (*m)->size;
  for(size_t i = 0; i < size; i++) {
    for(size_t j = 0; j < size; j++)
      mpz_clear((*m)->data[i][j]);
    free((*m)->data[i]);
  }
  free((*m)->data);
  free(*m);
  return 0;
}

void matrix_mul(const matrix_t *a, const matrix_t *b, matrix_t **res) {
  size_t size = a->size;
  mpz_t sum, tmp;
  mpz_init(tmp);
  mpz_init(sum);
  for(size_t i = 0; i < size; i++) {
    for(size_t j = 0; j < size; j++) {
      for(size_t k = 0; k < size; k++) {
        // sum += a[i][k] * b[k][j]
        mpz_mul(tmp, a->data[i][k], b->data[k][j]);
        mpz_add(sum, sum, tmp);
      }
      mpz_set((*res)->data[i][j], sum);
      mpz_set_si(sum, (long) 0);
    }
  }
  mpz_clear(tmp);
  mpz_clear(sum);
}

void matrix_pow(matrix_t **m, unsigned int exp) {
  matrix_t *initial_m = NULL;
  matrix_cpy((*m), &initial_m);
  matrix_t *acc = NULL;
  matrix_init(&acc, (*m)->size);
  for(size_t i = 1; i < exp; i++) {
    matrix_mul((*m), initial_m, &acc);
    matrix_mov(acc, m);
  }
  matrix_free(&initial_m);
  matrix_free(&acc);
}

void matrix_print(const matrix_t *m) {
  size_t size = m->size;
  for(size_t i = 0; i < size; i++) {
    for(size_t j = 0; j < size; j++) {
      gmp_printf("%2Zd ", m->data[i][j]);
    }
    putchar('\n');
  }
}
