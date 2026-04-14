int InsertionSort(int *vetor, int tam) {
    int aux, i, j;
    int comparacao = 0;
    for(i = 1; i < tam; i++) {
        aux = vetor[i];
        for(j = i - 1; j >= 0; j--) {
            comparacao++;
            if(aux < vetor[j]) {
                vetor[j + 1] = vetor[j];
            } else {
                break;
            }
        }
        vetor[j + 1] = aux;
    }
    return comparacao;
}