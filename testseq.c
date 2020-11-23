#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000
#define S 7

int a[N];

int main (int argc, char * argv[]) {

    int i, k;
    int ps = N/S; // partition size é igual ao N dividido pelo número de processos
    
    // casos de divisibilidade
    int ** vp = (N % S == 0) ? 
        (int**) malloc(sizeof(int*) * S) : 
        (int**) malloc(sizeof(int*) * S+1); // vetor que contabilizará o número de processos

    printf("Partition size: %d.\n", ps);
    for (i = k = 0; i < N; i++) { // enquanto está percorrendo todo o vetor
        if(i % ps == 0) {
            printf("i: %d\n", i);
            vp[k] = (int*) malloc(sizeof(int) * ps);
            k++;
        }
        vp[i][i%ps] = a[i];
    }
    
}