int BubbleSortOpt(int *vetor, int tam) {
    int i, j, comparacao = 0;
    for (i = tam - 1; i >= 1; i--) {
        for (j = 0; j < i; j++) {
            comparacao++;
            int a = vetor[j];
            int b = vetor[j + 1];
            int mask = -(a > b);
            int t = (a ^ b) & mask;
            vetor[j] = a ^ t;
            vetor[j + 1] = b ^ t;
        }
    }
    return comparacao;
}