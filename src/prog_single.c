/* programa para calcular R=M^10 * N^10, sendo R, M e N matrizes m_size x m_size
 * valor maximo possivel para cada elemento: sum 1..m_size ((RAND_MAX^10)^2)
 * para manter o valor maximo em um valor representavel por 128bits é assumido
 * m_size <= 5000 e definido RAND_MAX = 50
*/

#include <stdio.h>
#include "matrix.h"

int main(int argc, char *argv[]) {
  size_t m_size;
  if(argc < 2)
    m_size = 3;
  else
    m_size = (size_t) atoi(argv[1]);

  //FIXME como alocar vetor de um tipo incompleto?
  matrix_t *R=NULL, *M=NULL, *N=NULL;
  matrix_init(&R, m_size);
  matrix_init_rand(&M, m_size);
  matrix_init_rand(&N, m_size);

  printf("\nMatriz M:\n");
  matrix_print(M);
  printf("\nMatriz N:\n");
  matrix_print(N);

  matrix_pow(&M, 10);
  printf("\nMatriz M^10:\n");
  matrix_print(M);

  matrix_pow(&N, 10);
  printf("\nMatriz N^10:\n");
  matrix_print(N);

  //R = M^10 * N^10
  matrix_mul(M, N, &R);
  printf("\nMatriz R:\n");
  matrix_print(R);

  matrix_free(&R);
  matrix_free(&M);
  matrix_free(&N);
}
