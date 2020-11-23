#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

// Define o tamanho da matriz quadrada
#define N 8
int mat0[N][N], mat1[N][N], mat2[N][N];

void assignmatrix(int[N][N], int);

int main(int argc, char* argv[]) {

    int taskid, numtasks;
    int offset, rows, numworkers, dest, source, i, j, k; // processos e linhas da matriz

    assignmatrix(mat0, N);
    assignmatrix(mat1, N);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Status status;

    numworkers = numtasks - 1;

    if (taskid == 0) {
        rows = N/numworkers;
        offset = 0;

        for (dest = 1; dest <= numworkers; dest++) {

            MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&mat0[offset][0], rows*N, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&mat1, N*N, MPI_INT, dest, 1, MPI_COMM_WORLD);
            offset = offset + rows;
        }

        for (source = 1; source <= numworkers; source++) {

            MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&mat2[offset][0], rows*N, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
        }

        printf("Resultado:\n");
        for (i = 0; i < N; i++) {
            for (j=0; j < N; j++)
                printf("%d   ", mat2[i][j]);
        printf ("\n");
        }

    } else {

        MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&mat0, rows*N, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&mat1, N*N, MPI_INT, source, 1, MPI_COMM_WORLD, &status);

        /* Matrix multiplication */
        for (k = 0; k < N; k++) {
            for (i = 0; i < rows; i++) {
                mat2[i][k] = 0.0;
                for (j = 0; j < N; j++)
                    mat2[i][k] += mat0[i][j] * mat1[j][k];
            }
        }

        MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&mat2, rows*N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);

    }

    MPI_Finalize();
}

void assignmatrix(int mat[N][N], int length) { // Preenche matriz
    int i, j;
    time_t t;
    srand(time(NULL));
    for (i = 0; i < length; i++){
        for (j = 0; j < length; j++) {
            mat[i][j] = rand() % 10;
        }
      }
}