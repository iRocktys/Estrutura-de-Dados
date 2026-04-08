void SelectionSort (int *vetorOriginal, int tam, FILE *Saida) {
   int aux, i, j, min;
   int vetor[tam], comparacao=0;

   //Inicia a contagem de tempo
   clock_t start = clock();

   for(i = 0; i < tam; i++){
     vetor[i] = vetorOriginal[i];
   }

   for(i = 0; i < tam-1; i++) {
      min = i;
      for(j = i+1; j < tam; j++) {
        if(vetor[j] < vetor[min]) {
	         min = j;
           comparacao++;
         }
      }
      if (i != min) {
         aux = vetor[i];
         vetor[i] = vetor[min];
         vetor[min] = aux;
      }
   }

   //Encerramento do temporizador
   clock_t end = clock();
   int tempo = (int)((end - start)*1E3/CLOCKS_PER_SEC);

   //Escrevendo no arquivo
   fprintf(Saida, "SelectionSort: ");
   for (i = 0; i < tam; i++) {
       fprintf(Saida, "%d ", vetor[i]);
   }
   fprintf(Saida, ", %d comp, %d ms\n", comparacao, tempo);
}