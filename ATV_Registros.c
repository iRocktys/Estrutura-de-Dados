#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX 6

// Struct de organização
typedef struct Professor {
   char codID[4];
   char nome[30];
   char sexo[2];
   char idade[4];
   char especialidade[30];
   char telefone [15];
} Professor;  // Professor

Professor Prof[MAX];


//Parte de tamanho fixo
void escreverRegistrosTamanhoFixo(FILE *Saida, Professor *p, FILE *Persistencia) {
  int i=0;
  while (i <= 5) {
    fprintf(Persistencia,"{%s,%s,%s,%s,%s,%s}\n", p[i].codID,p[i].nome,p[i].sexo,p[i].idade,p[i].especialidade,p[i].telefone);
    i++;
  }  // while
}  // lerRegistrosTamanhoFixo


void lerRegistrosTamanhoFixo(FILE *Saida, Professor *p) {
  int j = 0, tamanho = 0, tcod = 3, tnome = 30, tsexo = 1, tidade = 3, tespe = 30, ttel = 14, i;

 do {
   tamanho = strlen(p[j].codID);               // CodID
   fprintf(Saida, "%s", p[j].codID);
   for(i = 0; i < tcod - tamanho; i++) {
     fprintf(Saida, " ");
   }  // for
   fprintf(Saida, "|");

   tamanho = strlen(p[j].nome);                  // Nome
   fprintf(Saida, "%s", p[j].nome);
   for(i = 0; i < tnome - tamanho; i++) {
     fprintf(Saida, " ");
   }  // for
   fprintf(Saida, "|");

   tamanho = strlen(p[j].sexo);                // Sexo
   fprintf(Saida, "%s", p[j].sexo);
   for(i = 0; i < tsexo - tamanho; i++) {
     fprintf(Saida, " ");
   }  // for
   fprintf(Saida, "|");

   tamanho = strlen(p[j].idade);               // Idade
   fprintf(Saida, "%s", p[j].idade);
   for(i = 1; i < tidade - tamanho; i++) {
     fprintf(Saida, " ");
   }  // for
   fprintf(Saida, "|");

   tamanho = strlen(p[j].especialidade);              // Especialidade
   fprintf(Saida, "%s", p[j].especialidade);
   for(i = 0; i < tespe - tamanho; i++) {
     fprintf(Saida, " ");
   }  // for
   if(j == 3) {
     fprintf(Saida, " ");
   }  // if
   fprintf(Saida, "|");

   tamanho = strlen(p[j].telefone);                  // Telefone
   fprintf(Saida, "%s", p[j].telefone);
   for(i = 0; i < ttel - tamanho; i++) {
     fprintf(Saida, " ");
   }  // for
   fprintf(Saida, "|\n");

   j++;
 } while(j <= 5);

}  // escreverRegistrosTamanhoFixo


///Parte com indicador de tamanho
void escreverRegistrosIndicadoresTamanho(FILE *Saida, Professor *p) {
  int i, cont_bit = 6;
  for(i = 0; i <= 5; i++){
    cont_bit = cont_bit + strlen(p[i].codID);
    cont_bit = cont_bit + strlen(p[i].nome);
    cont_bit = cont_bit + strlen(p[i].sexo);
    cont_bit = cont_bit + strlen(p[i].idade);
    cont_bit = cont_bit + strlen(p[i].especialidade);
    cont_bit = cont_bit + strlen(p[i].telefone);
    // Escrevendo no arquivo
    fprintf(Saida, "%d ", cont_bit);
    fprintf(Saida, "%s|%s|%s|%s|%s|%s|", p[i].codID,p[i].nome,p[i].sexo,p[i].idade,p[i].especialidade,p[i].telefone);
    cont_bit = 6;
  }
}  // escreverRegistrosIndicadoresTamanho
void lerRegistrosIndicadoresTamanho(FILE *Saida, Professor *p, FILE *Persistencia) {
  int i=0;
  while (i <= 5) {
    fprintf(Persistencia,"{%s,%s,%s,%s,%s,%s}\n", p[i].codID,p[i].nome,p[i].sexo,p[i].idade,p[i].especialidade,p[i].telefone);
    i++;
  }  // while
}  // lerRegistrosIndicadoresTamanho


//Parte delimitador de tamanho
void lerRegistrosDelimitadores(FILE *Saida, Professor *p, FILE *Persistencia) {
  int i = 0;
  while (i <= 5) {
    fprintf(Persistencia,"{%s,%s,%s,%s,%s,%s}\n", p[i].codID,p[i].nome,p[i].sexo,p[i].idade,p[i].especialidade,p[i].telefone);
    i++;
  }  // while
}  // lerRegistrosDelimitadores

void escreverRegistrosDelimitadores(FILE *Saida, Professor *p) {
  int i, cont_bit = 6;
  for(i = 0; i <= 5; i++){
    // Escrevendo no arquivo
    fprintf(Saida, "%s|%s|%s|%s|%s|%s|", p[i].codID,p[i].nome,p[i].sexo,p[i].idade,p[i].especialidade,p[i].telefone);
    fprintf(Saida, "#");
    cont_bit = 6;
  }
}  // escreverRegistrosDelimitadores


//Função principal
int main (int argc, const char *argv[]) {
  //Abrindo arquivos
  FILE* Entrada;
  FILE* Saida;
  FILE* Persistencia;

  //Nome dos arquivos abertos informados no CMD
  Entrada = fopen("input1.txt", "r+");
  Saida = fopen("output1.txt", "w+");
  Persistencia = fopen("read1.txt", "w+");

  int i = 0, numProf = 0, cont = 0;
  char ultima_linha, op, Linha[100];
  char *result;

  //Verificar se os arquivos foram abertos corretamente
  if(Entrada == NULL || Saida == NULL || Persistencia == NULL) {
    printf("ERROR 4:20 - OPERACAO INVALIDA\n");
    system("pause");
  } else {
    printf("Arquivo com sucesso neh pai, seloko\n");
  }  // else if

while (i <= 5) {
  fgets(Linha, 100, Entrada);

  result = strtok(Linha, "{,");
  strcpy(Prof[i].codID, result);

  result = strtok('\0', ",}");
  strcpy(Prof[i].nome, result);

  result = strtok('\0', ",}");
  strcpy(Prof[i].sexo, result);

  result = strtok('\0', ",}");
  strcpy(Prof[i].idade, result);

  result = strtok('\0', ",}");
  strcpy(Prof[i].especialidade, result);

  result = strtok('\0', ",}");
  strcpy(Prof[i].telefone, result);

  i++;
}  // while


// le o arquivo pra pegar ultima linha
  while(!feof(Entrada)) {
    fscanf(Entrada,"%c", &ultima_linha);
    fflush(stdin);
    if (ultima_linha != '\n') {
      op = ultima_linha;
    }
  }  // while

// Caso de erro de operação
  if(op != '1' && op != '2' && op != '3') {
    printf("ERROR 4:20 - OPERACAO INVALIDA \n");
    fprintf(Saida,"ERROR 4:20 - OPERACAO INVALIDA \n");
    exit(1);

  }  //if

  switch (op) {
    case '1':

      escreverRegistrosTamanhoFixo(Saida, Prof, Persistencia);
      lerRegistrosTamanhoFixo(Saida, Prof);
    break;

    case '2':
      escreverRegistrosIndicadoresTamanho(Saida, Prof);
      lerRegistrosIndicadoresTamanho(Saida, Prof, Persistencia);
    break;

    case '3':
      escreverRegistrosDelimitadores(Saida, Prof );
      lerRegistrosDelimitadores(Saida, Prof, Persistencia);
    break;

    default: printf("ERROR: OPCAO INVALIDA\n");

    fclose(Entrada);
    fclose(Saida);
    fclose(Persistencia);
  }  // switch

  return 0;
}  // main
