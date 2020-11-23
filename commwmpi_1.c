#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

// Neste exemplo, o processo de rank zero irá receber o valor do ranking dos demais processos.
int main(int argc, char* argv[]) {

	int id, size, value = 1000;

	MPI_Init(&argc, &argv); // Inicio do bloco de execucao paralela
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status st;

		if (id == 0) {
		// MASTER
		int i;
		for (i = 1; i < size; i++) {
		/*
		 * PARAMS:
		 *  -Dado Enviado
		 *  -Quantidade de dados
		 *  -Tipo do dado
		 *  -Processo destino
		 *  -Tag da mensagem
		 *  -Comunicador global
		 */


		MPI_Recv(&value, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &st);
		printf("MASTER recebeu o valor %d de WORKER %d\n", value, i);
		}

	} else {
		// WORKERS
		/*
		 * PARAMS:
		 *  -Dado recebido
		 *  -Quantidade de dados
		 *  -Tipo do dado
		 *  -Processo de origem
		 *  -Tag da mensagem
		 *  -Comunicador global
		 *  -Status
		 */

		MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		printf("WORKER %d enviou o valor %d para MASTER\n", id, value);
	}

	MPI_Finalize(); // Fim do bloco de execucao paralela
}
