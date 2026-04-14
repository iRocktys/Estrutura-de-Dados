int BubbleSort(int *vetor, int tam) {
    int aux, i, j;
    int comparacao = 0;
    for(i = tam - 1; i >= 1; i--) {
        for(j = 0; j < i; j++) {
            comparacao++;
            if(vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
    return comparacao;
}