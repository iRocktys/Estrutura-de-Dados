int SelectionSortOpt(int *vetor, int tam) {
    int i, j, min_idx, comparacao = 0;
    for (i = 0; i < tam - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < tam; j++) {
            comparacao++;
            int cond = vetor[j] < vetor[min_idx];
            min_idx = (cond * j) + ((1 - cond) * min_idx);
        }
        int temp = vetor[i];
        vetor[i] = vetor[min_idx];
        vetor[min_idx] = temp;
    }
    return comparacao;
}