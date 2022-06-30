#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

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

void BubbleSort (int *vetorOriginal, int tam, FILE *Saida) {
   int aux, i, j;
   int vetor[tam], comparacao=0;

   //Inicia a contagem de tempo
   clock_t start = clock();

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
   //Encerramento do temporizador
   clock_t end = clock();
   int tempo = (int)((end - start)*1000000000/CLOCKS_PER_SEC);

   //Escrevendo no arquivo
   fprintf(Saida, "BubbleSort: ");
   for (i = 0; i < tam; i++) {
       fprintf(Saida, "%d ", vetor[i]);
   }
   fprintf(Saida, ", %d comp, %d ms\n", comparacao, tempo);
}

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

//Auxiliar do MergeSort somente para impressão bonitinha
void auxMergeSort(int vetorOriginal[], int comeco, int fim, int tam, FILE *Saida){
  int vetor[tam], i, compMerge;

  //Inicia a contagem de tempo
  clock_t start = clock();

  for(i = 0; i < tam; i++){
    vetor[i] = vetorOriginal[i];
  }

  MergeSort(vetor, comeco, fim, 0);

  //Encerramento do temporizador
  clock_t end = clock();
  int tempo = (int)((end - start)*1E3/CLOCKS_PER_SEC);

  //Escrevendo no arquivo
  fprintf(Saida, "MergeSort: ");
  for (i = 0; i < tam; i++) {
      fprintf(Saida, "%d ", vetor[i]);
  }
  fprintf(Saida, ", %d comp, %d ms\n", compMerge, tempo);
}

void QuickSort(int vetor[], int left, int right, int compQuick) {
    int i, j, x, y;
    i = left;
    j = right;
    x = vetor[(left + right) / 2];
    while(i <= j) {
        while(vetor[i] < x && i < right) {
            i++;
            compQuick++;
        }
        while(vetor[j] > x && j > left) {
            j--;
            compQuick++;
        }
        if(i <= j) {
            y = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = y;
            i++;
            j--;
            compQuick++;
        }
    }

    if(j > left) {
        QuickSort(vetor, left, j, compQuick);
        compQuick++;
    }

    if(i < right) {
        QuickSort(vetor, i, right, compQuick);
        compQuick++;
    }
}

//Auxiliar do QuickSort somente para impressão bonitinha
void auxQuickSort(int vetorOriginal[], int left, int right, int tam, FILE *Saida){
  int vetor[tam], i, compQuick;

  //Inicia a contagem de tempo
  clock_t start = clock();

  for(i = 0; i < tam; i++){
    vetor[i] = vetorOriginal[i];
  }

  //Chamando a função QuickSort
  QuickSort(vetor, left, right-1, 0);

  //Encerramento do temporizador
  clock_t end = clock();
  int tempo = (int)((end - start)*1E9/CLOCKS_PER_SEC);

  //Escrevendo no arquivo
  fprintf(Saida, "QuickSort: ");
  for (i = 0; i < tam; i++) {
      fprintf(Saida, "%d ", vetor[i]);
  }
  fprintf(Saida, ", %d comp, %d ms\n", compQuick, tempo);
}

//Função principal
int main (int argc, const char *argv[]) {
  //Abrindo arquivos
  FILE* Entrada;
  FILE* Saida;

  //Nome dos arquivos abertos informados no CMD
  Entrada = fopen(argv[1], "r+");
  Saida = fopen(argv[2], "w+");

  //Verificar se os arquivos foram abertos corretamente
  if(Entrada == NULL || Saida == NULL){
    printf("Error 4:20 - Falha ao abrir arquivo!\n");
    system("pause");
  }else{
    printf("Arquivo com sucesso neh pai, seloko\n");
  }

  //Variaveis para leitura
  int tam;
  char op;
  fscanf(Entrada, "%d %c", &tam, &op);

  //Vetor a ser ordenado
  int vetorCrescente[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int vetorDecrescente[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int vetorAleatorio[10] = {10, 2, -1, 4, 8, 19, 25, 3, 15, 11};

  //switch para fazer a operacao informada pelo usuario
  switch (op) {
    case 'c':
      BubbleSort(vetorCrescente, tam, Saida);
      InsertionSort(vetorCrescente, tam, Saida);
      SelectionSort(vetorCrescente, tam, Saida);
      auxQuickSort(vetorCrescente, 0, tam, tam, Saida);
      auxMergeSort(vetorCrescente, 0, tam, tam, Saida);
    break;

    case 'd':
      BubbleSort(vetorDecrescente, tam, Saida);
      InsertionSort(vetorDecrescente, tam, Saida);
      SelectionSort(vetorDecrescente, tam, Saida);
      auxQuickSort(vetorDecrescente, 0, tam, tam, Saida);
      auxMergeSort(vetorDecrescente, 0, tam, tam, Saida);
    break;

    case 'r':
      BubbleSort(vetorAleatorio, tam, Saida);
      InsertionSort(vetorAleatorio, tam, Saida);
      SelectionSort(vetorAleatorio, tam, Saida);
      auxQuickSort(vetorAleatorio, 0, 10, tam, Saida);
      auxMergeSort(vetorAleatorio, 0, 10, tam, Saida);
    break;

    default: printf("Error 4:20 - Opcao invalida\n");

    fclose(Entrada);
  }
}
