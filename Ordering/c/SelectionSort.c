int SelectionSort(int *vetor, int tam) {
    int aux, i, j, min;
    int comparacao = 0;
    for(i = 0; i < tam - 1; i++) {
        min = i;
        for(j = i + 1; j < tam; j++) {
            comparacao++;
            if(vetor[j] < vetor[min]) {
                min = j;
            }
        }
        if (i != min) {
            aux = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = aux;
        }
    }
    return comparacao;
}