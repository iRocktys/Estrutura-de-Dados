void QuickSort(int *vetor, int left, int right, int *compQuick) {
    int i = left, j = right;
    int x = vetor[(left + right) / 2];
    int y;

    while(i <= j) {
        while(vetor[i] < x && i < right) {
            (*compQuick)++;
            i++;
        }
        (*compQuick)++; // Falha da condição do loop

        while(vetor[j] > x && j > left) {
            (*compQuick)++;
            j--;
        }
        (*compQuick)++; // Falha da condição do loop

        if(i <= j) {
            y = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = y;
            i++;
            j--;
        }
    }
    if(j > left) {
        QuickSort(vetor, left, j, compQuick);
    }
    if(i < right) {
        QuickSort(vetor, i, right, compQuick);
    }
}