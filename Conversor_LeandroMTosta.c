#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define TAMANHO 100

//Criação Pilha estatica
typedef struct{
  //Array [ objeto / inteiro]
  int array[TAMANHO];
  int topoEstatica;
  int bin[8];
}PilhaEstatica;

//Inicialização pilha estatica
void iniciaPilhaEstatica(PilhaEstatica *p){
  p-> topoEstatica = 0;
}

//Estado da pilha estatica (Vazia ou Cheia)
bool vaziaPilhaEstatica(PilhaEstatica *p){
  return(p-> topoEstatica == 0);
}
bool cheiaPilhaEstatica(PilhaEstatica *p){
  return(p-> topoEstatica == TAMANHO);
}

//Inserção (empilhar) Estatica
void empilharPilhaEstatica(PilhaEstatica *p, int x){
  if(cheiaPilhaEstatica(p) == false){
    //insere novo elemento na posição apontada pelo topo
    p-> array[p->topoEstatica] = x;
    //icrementa quantidade de elementos e topo(posição)
    p-> topoEstatica++;
  }else{
    printf("Error 420: Pilha cheia\n");
  }
}

//Remover (desempilhar) Estatica
int desempilharPilhaEstatica(PilhaEstatica *p){
  int ret = -99;
  if(!vaziaPilhaEstatica(p)){
    ret = p->array[p-> topoEstatica - 1];
    p-> topoEstatica--;
  }else{
    printf("Error 420: Pilha vazia\n");
  }
  return(ret);
}

//Vizualizar a pilha estática
void exibirPilhaEstatica(PilhaEstatica *p){
  int i;
  printf("Pilha = {");
  for(i = 0; i < p->topoEstatica; i++){
    printf("%d ", p->array[i]);
  }
  printf("}\n");
}



//Criação pilha Dinamica
//NoPilha -> ptrNoPilha
typedef struct NoPilha *ptrNoPilha;
//NoPilha
typedef struct NoPilha{
  int x;
  ptrNoPilha proximo;
}Nopilha;

typedef struct {
  ptrNoPilha topoDinamica;
  int qtdeElementos;
  int bin[8];
}PilhaDinamica;

//Iniciar pilha Dinâmica
void iniciaPilhaDinamica(PilhaDinamica *p){
  p->topoDinamica = NULL;
  p->qtdeElementos = 0;
}
//Tamanho da pilha Dinamica
int tamanhoPilhaDinamica(PilhaDinamica *p){
  return(p->qtdeElementos);
}

//Ver estado da Pilha Dinamica
bool vaziaPilhaDinamica(PilhaDinamica *p){
  return(p-> qtdeElementos == 0);
}

//inserir Elementos
void empilharPilhaDinamica(PilhaDinamica *p, int x){
  ptrNoPilha aux;
  aux = (ptrNoPilha)malloc(sizeof(int));
  aux-> x = x;
  aux->proximo = p->topoDinamica;
  p->topoDinamica = aux;
  p->qtdeElementos++;
}

//Remover Pilha Dinamica
int desempilhaPilhaDinamica(PilhaDinamica *p){
  int ret = -99;
  if(!vaziaPilhaDinamica(p)){
    ptrNoPilha aux;
    aux = p->topoDinamica;
    ret = aux->x;
    p->topoDinamica = p->topoDinamica->proximo;
    free(aux);
    p-> qtdeElementos--;
  }else{
    printf("Nao foi possivel Remover\n");
  }
  return(ret);
}
//imprimir pilha dinamica
void exibirPilhaDinamica(PilhaDinamica *p){
  printf("Pilha = {");
  ptrNoPilha temp;
  for(temp = p-> topoDinamica; temp != NULL; temp = temp->proximo){
    printf("%d ", temp->x);
  }
  printf("}\n");
}

void converterPilhaDinamica(PilhaDinamica *p){
  //Auxiliares para conversao
  int aux;

  int ret = -99;
  ptrNoPilha temp;

  //for(temp = p-> topoDinamica; temp != NULL; temp = temp->proximo){
  temp = p-> topoDinamica;
  ret =  temp->x;
  //For para conversao para binario
  for (int i = 7; i >= 0; i--) {
     if (ret % 2 == 0 ) {
        p->bin[i] = 0;
        ret = ret / 2;
     } else {
        p->bin[i] = 1;
        ret = ret / 2;
     }
  }
}

void converterPilhaEstatica(PilhaEstatica *p){
  //Auxiliares para conversao
  int i, aux, bin[8];
  int ret = -99;

  if(!vaziaPilhaEstatica(p)){
    ret = p->array[p-> topoEstatica-1];
    //For para conversao para binario
    for (i = 7; i >= 0; i--) {
       if (ret % 2 == 0 ) {
          p->bin[i] = 0;
          ret = ret / 2;
       } else {
          p->bin[i] = 1;
          ret = ret / 2;
       }
    }
  }
}
//Função principal
int main(int argc, const char *argv[]){
  //Variaveis usadas na funcao principal
  int aux;
  float numeros;
  char tipoPilha;
  PilhaEstatica pilhaE;
  PilhaDinamica  pilhaD;
  //Abrindo arquivos
  FILE* Entrada;
  FILE* Saida;
  //Nome dos arquivos abertos informados no CMD
  Entrada = fopen(argv[1], "r+");
  Saida = fopen(argv[2], "w+");

  //Verificar se os arquivos foram abertos corretamente
  if(Entrada == NULL || Saida == NULL){
    printf("Erro ao abrir arquivos!\n");
    system("pause");
  }
  //Descobr qual pilha sera usada
  fscanf(Entrada,"%c", &tipoPilha);

  //Caso erro na seleção do tipo de pilha
if(tipoPilha == 'd' || tipoPilha == 'D' || tipoPilha == 'e' || tipoPilha == 'E'){
  //Caso a escolha da pilha estatica
    if((tipoPilha == 'e' || tipoPilha == 'E') && tipoPilha != EOF){
      iniciaPilhaEstatica(&pilhaE);
      printf("Opcao - Pilha Estatica\n" );
      //Insere os valores na pilha estatica
      while((fscanf(Entrada,"%f", &numeros)) != EOF && numeros == (int)numeros){
            //Coloca numeros na pilha e faz a conversao para binario
            empilharPilhaEstatica(&pilhaE, numeros);
            converterPilhaEstatica(&pilhaE);
            //Grava o valor binario no arquivo de saida
            for (int aux = 0; aux < 8; aux++){
              fprintf(Saida,"%d", pilhaE.bin[aux]);
            }
            fprintf(Saida,"\n");
      }
      //Verificar a existencia de ter somente numeros inteiros
      if(numeros != (int)numeros){
        printf("Error 420: Numero nao inteiro encontrado!!\n");
        fprintf(Saida,"Error 420: Numero nao inteiro encontrado!!");
      }else{
        //Caso ocorrer tudo certo, exibe mensagem de confirmacaoe a pilha formada
        exibirPilhaEstatica(&pilhaE);
        printf("Arquivo convertido com sucesso!\n");
      }
  }
  //casa a escolha da pilha dinamica
  if(tipoPilha == 'd' || tipoPilha == 'D'){
    iniciaPilhaDinamica(&pilhaD);
    printf("Opcao - Pilha Dinamica\n");
    //Insere os valores na pilha Dinamica
    while((fscanf(Entrada,"%f", &numeros)) != EOF ){
        //Coloca numeros na pilha e faz a conversao para binario
        empilharPilhaDinamica(&pilhaD, numeros);
        converterPilhaDinamica(&pilhaD);
        //Grava o valor binario no arquivo de saida
        for (int aux = 0; aux < 8; aux++){
          fprintf(Saida,"%d", pilhaD.bin[aux]);
        }
        fprintf(Saida,"\n");
      }
      //Verificar a existencia de ter somente numeros inteiros
      if(numeros != (int)numeros){
        printf("Error 420: Numero nao inteiro encontrado!!\n");
        fprintf(Saida,"Error 420: Numero nao inteiro encontrado!!");
      }else{
        //Caso ocorrer tudo certo, exibe mensagem de confirmacao e a pilha informada
        exibirPilhaDinamica(&pilhaD);
        printf("Arquivo convertido com sucesso!\n");
      }
    }
  }else{
    //Se entrar algum caractere inadequado, exibir mensagens
    printf("Error: Tipo de pilha invalido!\n");
    fprintf(Saida,"Error: Tipo de pilha invalido!\n");
}

  return 0;
}
