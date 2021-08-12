#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

/**
*   QUESTÃO 7
*   SISTEMAS DISTRIBUIDOS - A2
*   2020.2 NOITE 
*   DANIEL NEVES CAMARGO
*   20161107403
**/

#define N 1000
int array[N] = {0};

int getbiggest( int[N], int, int );
void randassign( int[N], int, int );
void printcontent( int arr[N], int );

int main ( int argc, char * argv[] ) {

    // Def variaveis
    int id, size;
    
    randassign( array, N, 100 );
    //printcontent(array, N);
    
    MPI_Init( &argc, &argv ); // Inicio
	MPI_Comm_rank( MPI_COMM_WORLD, &id );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Status st;

    int partition_length = ( (N / sizeof(int)) / (size-1) );
    
    // Last Worker
    if ( id != 0 && id == (size-1) ) {
        int result = getbiggest( array, ((partition_length * id) - size), (N / sizeof(int)) );
        MPI_Send( &result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD );
    }

    // Worker N
    if ( id > 0 && id < (size-1) ) {
        int result = getbiggest( array, ((partition_length * id) - size), ((partition_length * id) -1) );
        MPI_Send( &result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD );
    }

    // Master
    if ( id == 0 && id != (size-1) ) {
        int result[size], i;

        for(i = 1; i < size; i++) {
            MPI_Recv( &result[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &st );
        }
        printf("\nResult: %d\n", result[0] = getbiggest(result, 1, (size - 1)) );
    }

    // Unique Process
    if ( id == 0 && id == (size-1) ) {
        int result = getbiggest( array, 0, (N/sizeof(int)) );
        printf( "\nResult: %d\n", result );
    }

    MPI_Finalize();
    return 0;
}

// Returns o maior valor armazenado em um vetor
// os parâmetros fi e li são o primeiro e último index verificado
int getbiggest ( int arr[N], int fi, int li ) {
    int i,  biggest = 0;
    for ( i = fi; i <= li; i++ ) {
        if(arr[i] > biggest)
            biggest = arr[i];
    }
    return biggest;
}

void randassign( int arr[N], int length, int max_value ) {
    time_t t;
    srand(time(NULL));
    int i;
    for ( i = 0; i < length; i++ )
        arr[i] = rand() % max_value;
}

void printcontent(int arr[N], int length) {
    int i;
    for ( i = 0; i < length-1; i++ )
        printf( "%d:\t%d\n", i, arr[i] );
}