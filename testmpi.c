#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int main (int argc, char * argv[]) {
	int size, rank, length;
	char hostname[50];
	printf("Executado tantas vezes\n");
	
	

	// Inicializando ambiente MPI
	MPI_Init (&argc, &argv);

	// obter quantidade de processos paralelos
	//  MPI_Comm_World = comunicador padrão criando pelo MPI_Init
	MPI_Comm_size (MPI_COMM_WORLD, &size);

	// cada processo obtém o seu rank
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);

	// obtém o nome da máquina na qual o processo está executando
	MPI_Get_processor_name (hostname, &length);

	// gera um número aleatorio
	time_t t;
	srand(time(NULL) + rank);

	printf ("Quantidade de processos = %d | Meu ranking = %d | Maquina = %s | Random Number = %d\n", size, rank, hostname, rand() % 10);

	// Finalizando o ambiente distribuido
	MPI_Finalize ();
	return 0;
}
