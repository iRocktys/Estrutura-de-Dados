#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Struct principal do arquivo entrada
typedef struct{
    char codigo[4];
    char nome[31];
    char sexo[2];
    char idade[4];
    char especialidade[31];
    char telefone[15];
}Professores;

//Struct principal do arquivo operacao
typedef struct{
    char instrucao[2];
    char codigo_op[4];
    char nome_op[31];
    char sexo_op[2];
    char idade_op[4];
    char especialidade_op[31];
    char telefone_op[15];
}Operacao;

//Funcao para contar linha de arquivos
int contar_linha(FILE *arquivo){
  char letra;
  int contador=0;
  letra = getc(arquivo);
  do{
      letra = fgetc(arquivo);
      if(letra == '\n'){
          contador++;
      }
  }while(letra != EOF);
  return contador;
}

void RegistrosTamanhoFixo(FILE *Saida, Professores *p, int tamanho_entrada, int size, int top) {
  int j = 0, tamanho = 0, tcod = 3, tnome = 30, tsexo = 1, tidade = 3, tespe = 30, ttel = 14, i;
  fprintf(Saida, "size=%d top=%d\n", size, top);
  while(j < tamanho_entrada){
   tamanho = strlen(p[j].codigo);               // CodID
   fprintf(Saida, "%s", p[j].codigo);
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
 }

}  // escreverRegistrosTamanhoFixo

int main(int argc, const char * argv[]){
    //Declaração de variáveis
    char *l, palavra[100], letra;
    int tamanho_entrada, tamanho_operacao, i = 0, saida=1;
    int size, top;

    //verifica argumentos
    if(argc != 5) {
      printf("ERROR 4:20 - Argumentos invalidos\n");
      exit(1);
    }

    //Criação do argumento para struct de entrada
    Professores *p;

    //Criação do argumento para struct de operacao
    Operacao *op;

    //abertura de arquivo
    FILE* arqEntrada = fopen(argv[1] , "r");
    FILE* arqOperacao = fopen(argv[2] , "r");
    FILE* arqTemporario = fopen(argv[3] , "w");
    FILE* arqSaida = fopen(argv[4], "w");

    //verifica se o arquivo foi aberto corretamente
    if(arqEntrada == NULL || arqOperacao == NULL || arqTemporario == NULL || arqSaida == NULL){
        printf("ERROR 4:20 - OPERACAO INVALIDA\n");
        system("pause");
    }else{
      printf("Arquivo com sucesso neh pai, seloko\n");
    }//else

    //Analise de erro caso arquivo entrada vazio
     letra = getc(arqEntrada);
     if(letra == EOF){
        fprintf(arqSaida, "ERROR 4:20 - ARQUIVO VAZIO\n");
        fclose(arqEntrada);
        fclose(arqOperacao);
        fclose(arqTemporario);
        fclose(arqSaida);
        exit(1);
    }//if

    //volta ao inicio do arquivo entrada
    fseek(arqEntrada, 0, SEEK_SET);

    //Contar linha arquivo entrada
    tamanho_entrada = contar_linha(arqEntrada);

    //vonta ao inicio do arquivo entrada
    fseek(arqEntrada, 0, SEEK_SET);

    //alocação de memoria para professores
    p = (Professores*) malloc (sizeof(Professores)*(tamanho_entrada+5));

    //Coletar os caracteres iniciais <size> e <top>
    fscanf(arqEntrada, "size=%d top=%d\n", &size, &top);


    //Leitura para colocar na Struct PROFESSOR
while(fgets(palavra,99,arqEntrada)!=NULL){

      l = strtok(palavra, "|");
      strcpy(p[i].codigo, l);
    //  printf("%s\n", p[i].codigo);

      l= strtok(NULL, "|");
      strcpy(p[i].nome, l);
      //printf("%s\n", p[i].nome);

      l= strtok(NULL, "|");
      strcpy(p[i].sexo, l);
    //  printf("%s\n", p[i].sexo);

      l= strtok(NULL, "|");
      strcpy(p[i].idade, l);
      //printf("%s\n", p[i].idade);

      l= strtok(NULL, "|");
      strcpy(p[i].especialidade, l);
    //  printf("%s\n", p[i].especialidade);

      l= strtok(NULL, "|");
      strcpy(p[i].telefone, l);
    //  printf("%s\n", p[i].telefone);

      i++;
  }

    //RegistrosTamanhoFixo(arqSaida, p);

    //alocação de memoria para operacao
    op = (Operacao*) malloc (sizeof(Operacao)*(tamanho_operacao-1));

    //Contar linha arquivo operacao
    tamanho_operacao = contar_linha(arqOperacao);
    i=0;

    //volta ao inicio do arquivo OPERACAO
    fseek(arqOperacao, 0, SEEK_SET);

    //Auxiliares
    char aux[2] = "i";
    int ret;

    //Coleta de dados para struct OPERACAO
      while(i <= tamanho_operacao){
        fgets(palavra, 100, arqOperacao);

        l = strtok(palavra, " ");
        strcpy(op[i].instrucao, l);

        //Utilizado para comparar as String
        ret = strcmp(op[i].instrucao, aux);

        if(ret == 0){
          l = strtok(NULL, ",");
          strcpy(op[i].codigo_op, l);
          //printf("%s\n", op[i].codigo_op);

          l= strtok(NULL, ",");
          strcpy(op[i].nome_op, l);
          //printf("%s\n", op[i].nome_op);

          l= strtok(NULL, ",");
          strcpy(op[i].sexo_op, l);
          //printf("%s\n", op[i].sexo_op);

          l= strtok(NULL, ",");
          strcpy(op[i].especialidade_op, l);
          //printf("%s\n", op[i].especialidade_op);

          l= strtok(NULL, ",");
          strcpy(op[i].telefone_op, l);
          //printf("%s\n", op[i].telefone_op);
        }else{
          l = strtok(NULL, "\n");
          strcpy(op[i].codigo_op, l);
        }
      i++;
    }//while

    //Comparar
    int aux2, cont=0, vetor_inserir[10];
    for(int i=0; i < tamanho_entrada; i++){
      for(int j=0; j< tamanho_operacao; j++){
        aux2 = strcmp(p[j].codigo, op[i].codigo_op);
        if(aux2 == 0){
          vetor_inserir[cont] = j;
          cont++;
        }
      }
    }

    //fazer uns baguio
    char comp[2]="d";
    int aux1, j=0, endereco, end=0;

    endereco = tamanho_entrada - 1;

    //Resetando algumas coisas
    i=0;
    j=0;



    //While que faz comparações
    while(i <= tamanho_entrada){
      ret = strcmp(op[i].instrucao, aux);
      if(ret == 0){
        if(i >= 1){
          //Compara a instrução anterior para ver se foi removido algo
          aux1 = strcmp(op[i-1].instrucao, comp);
          //printf("%s\n", op[i-1].instrucao);
          if(aux1 == 0){
            //se foi removido algo inserir (como e onde)?
            strcpy(p[vetor_inserir[j]].codigo, op[i].codigo_op);
            strcpy(p[vetor_inserir[j]].nome, op[i].nome_op);
            strcpy(p[vetor_inserir[j]].sexo, op[i].sexo_op);
            strcpy(p[vetor_inserir[j]].especialidade, op[i].especialidade_op);
            strcpy(p[vetor_inserir[j]].telefone, op[i].telefone_op);
            j++;
          }else{
            strcpy(p[endereco].codigo, op[i].codigo_op);
            strcpy(p[endereco].nome, op[i].nome_op);
            strcpy(p[endereco].sexo, op[i].sexo_op);
            strcpy(p[endereco].especialidade, op[i].especialidade_op);
            strcpy(p[endereco].telefone, op[i].telefone_op);
            endereco++;
          }
        }else{
          strcpy(p[endereco].codigo, op[i].codigo_op);
          strcpy(p[endereco].nome, op[i].nome_op);
          strcpy(p[endereco].sexo, op[i].sexo_op);
          strcpy(p[endereco].especialidade, op[i].especialidade_op);
          strcpy(p[endereco].telefone, op[i].telefone_op);
          endereco++;
        }
      }else{
        //Parte destinada para remocao

      }
      i++;
    }
    /*
    for (i = 0; i <= 6; i++) {
      //printf("seloko\n" );
      printf("%s\n", p[i].codigo);
      printf("%s\n", p[i].nome);
      printf("%s\n", p[i].sexo);
      printf("%s\n", p[i].especialidade);
      printf("%s\n", p[i].telefone);
      printf("\n");
    }*/

    RegistrosTamanhoFixo(arqSaida, p, endereco, size, top);

    fclose(arqEntrada);
    fclose(arqSaida);
    fclose(arqTemporario);
    fclose(arqOperacao);
    return 0;
}
