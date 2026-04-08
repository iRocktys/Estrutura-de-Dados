void InsertionSort (int *vetorOriginal, int tam, FILE *Saida) {
   int aux, i, j;
   int vetor[tam], comparacao=0;

   //Inicia a contagem de tempo
   clock_t start = clock();

   //Comparacoes do InsertionSort
   for(i = 0; i < tam; i++){
     vetor[i] = vetorOriginal[i];
   }
   for(i = 1; i < tam; i++) {
      aux = vetor[i];
      for (j = i-1; j >= 0 && aux < vetor[j]; j--) {
         vetor[j + 1] = vetor[j];
         comparacao++;
      }
      vetor[j + 1] = aux;
   }

   //Encerramento do temporizador
   clock_t end = clock();
   int tempo = (int)((end - start)*1E3/CLOCKS_PER_SEC);

   //Escrevendo no arquivo
   fprintf(Saida, "InsertionSort: ");
   for (i = 0; i < tam; i++) {
       fprintf(Saida, "%d ", vetor[i]);
   }
   fprintf(Saida,", %d comp, %d ms\n", comparacao, tempo);
}