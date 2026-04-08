void BubbleSort (int *vetorOriginal, int tam) {
   int aux, i, j;
   int vetor[tam], comparacao=0;

   for(i = 0; i < tam; i++){
     vetor[i] = vetorOriginal[i];
   }

   for(i = tam-1; i >= 1; i--) {
      for(j = 0; j < i; j++) {
         if(vetor[j] > vetor[j + 1]) {
	          aux = vetor[j];
            vetor[j] = vetor[j + 1];
            vetor[j + 1] = aux;
            comparacao++;
         }
      }
   }
}