#include <stdio.h>
#include <stdlib.h>

// Multiplicação de matrizes
// Implementar um programa de algoritmo distribuido usando MPI


int** creatematrix(int);
void assignmatrix(int**, int);
int generaterand();
void printmatrix(int**, int, char *);

int main(int argc, char* argv[]) {
  int i, j, k, length;

  // Recebe o parâmetro do tamanho da matriz quadrada
  if (argc > 1 ) {
    length = atoi(argv[1]);
  } else return 0;

  // Matriz 0
  int ** mat0 = creatematrix(length);
  assignmatrix(mat0, length);

  // Matriz 1
  int ** mat1 = creatematrix(length);
  assignmatrix(mat1, length);

  printmatrix(mat0, length, "0"); // Imprime a matriz 0 na tela
  printmatrix(mat1, length, "1"); // Imprime a matriz 1 na tela

  // Matriz Resultado
  int ** mat2 = creatematrix(length);
  for (i = 0; i < length; i++) {
    for (j = 0; j < length; j++ ) {
      mat2[i][j] = 0;
      for (k = 0; k < length; k++)
      mat2[i][j] += mat0[i][k] * mat1[k][j];
    }
  }
  printf("Resultado da multiplicacao\n");
  printmatrix(mat2, length, "Resultado"); // Imprime a matriz resultado na tela
}


int** creatematrix(int length) { // Aloca a matriz na memoria
  int i, j;
  int** mat = (int**) malloc (sizeof(int*) * length);

  for (i = 0; i < length; i++) {
    mat[i] = (int*) malloc (sizeof(float) * length);
  }
  if(mat != NULL) {
      printf("Matriz criada: %ld bytes\n", sizeof(int)*length*length);
      return mat;
    } else {
      printf("Ocorreu um erro\n");
      return NULL;
    }
}

void assignmatrix(int ** mat, int length) { // Preenche matriz
      int i, j;
      for (i = 0; i < length; i++){
        for (j = 0; j < length; j++) {
          mat[i][j] = generaterand();
        }
      }
}

void printmatrix (int** mat, int length, char* identification) {
  int i, j;
  printf("\n\nMatriz %s:\n", identification);
  for (i = 0; i < length; i++){
    for (j = 0; j < length; j++) {
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
}

int generaterand() {
  return rand() % 10;
}
