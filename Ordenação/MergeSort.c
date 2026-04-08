void merge(int vetor[], int comeco, int meio, int fim, int compMerge) {
    int com1 = comeco, com2 = meio+1, i = 0, tam = fim-comeco+1;
    int *vetAux;

    vetAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim) {
        if(vetor[com1] < vetor[com2]) {
            vetAux[i] = vetor[com1];
            com1++;
            compMerge++;
        } else {
            vetAux[i] = vetor[com2];
            com2++;
            compMerge++;
        }
        i++;
    }
    
    while(com1 <= meio) {
        vetAux[i] = vetor[com1];
        i++;
        com1++;
        compMerge++;
    }

    while(com2 <= fim) {
        vetAux[i] = vetor[com2];
        i++;
        com2++;
        compMerge++;
    }

    for(i = comeco; i <= fim; i++) {
        vetor[i] = vetAux[i-comeco];
        compMerge++;
    }
    
    free(vetAux);
}

void MergeSort(int vetor[], int comeco, int fim, int compMerge) {
    if (comeco < fim) {
        int meio = (fim+comeco)/2;
        MergeSort(vetor, comeco, meio, compMerge);
        MergeSort(vetor, meio+1, fim, compMerge);
        merge(vetor, comeco, meio, fim, compMerge);
        compMerge++;
    }
}