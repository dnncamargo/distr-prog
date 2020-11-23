#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

void assign(int[], int);
void print(int[], int);

#define N 100
int array[N];

int main(int argc, char* argv[]) {
    int id, size, n_workers, partition_length;
    MPI_Init(&argc, &argv); // Inicio do bloco de execucao paralela
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status st;
    
    assign(array, N);
    printf("Array created and assigned successfully in proc: %d\n", id); //print(array, N);

    n_workers = size-1;
    partition_length = N/n_workers;

    if (id == 0) {

        int i;
        int * buffer = (int*) malloc (sizeof(int) * n_workers);
        for (i = 1; i < size; i++) {
            //MPI_Recv(buffer, n_workers, MPI_INT, i, 0, MPI_COMM_WORLD, &st);
        }
        //print(buffer, n_workers);

    } else {
        int t, max_value, init, end;
        
        init = partition_length * (id-1);
        end = (id == n_workers) ? N : (partition_length) * (id) -1;
        max_value = array[init];
        
        for(t = init; init <= end; t++) {
            if(array[t] >= max_value)
                max_value = array[t];
        }
        printf("The maximum value of proccess %d is: %d\n", id, max_value);
        //MPI_Send(&max_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }


    MPI_Finalize();

}

void assign(int arr[], int length) {
    time_t t;
    srand(time(NULL));
    int i;
    for (i = 0; i < length; i++)
        arr[i] = rand() % 1000;
}

void print(int arr[], int length) {
    int i;
    for (i = 0; i < length-1; i++)
        printf("%d - ", arr[i]);
    printf("%d\n", arr[length-1]);
}