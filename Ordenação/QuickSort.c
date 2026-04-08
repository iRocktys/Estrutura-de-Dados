#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void QuickSort(int vetor[], int left, int right, int compQuick) {
    int i, j, x, y;
    i = left;
    j = right;
    x = vetor[(left + right) / 2];
    while(i <= j) {
        while(vetor[i] < x && i < right) {
            i++;
            compQuick++;
        }
        while(vetor[j] > x && j > left) {
            j--;
            compQuick++;
        }
        if(i <= j) {
            y = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = y;
            i++;
            j--;
            compQuick++;
        }
    }

    if(j > left) {
        QuickSort(vetor, left, j, compQuick);
        compQuick++;
    }

    if(i < right) {
        QuickSort(vetor, i, right, compQuick);
        compQuick++;
    }
}
