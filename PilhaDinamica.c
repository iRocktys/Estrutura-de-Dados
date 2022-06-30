#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//NoPilha -> ptrNoPilha
typedef struct NoPilha *ptrNoPilha;
//NoPilha
typedef struct NoPilha{
  int x;
  ptrNoPilha proximo;
}Nopilha;

typedef struct {
  ptrNoPilha topo;
  int qtdeElementos;
}PilhaDinamica;

//Iniciar pilha Dinâmica
void iniciaPilhaDinamica(PilhaDinamica *p){
  p->topo = NULL;
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
  aux->proximo = p->topo;
  p->topo = aux;
  p->qtdeElementos++;
}

//Remover Pilha Dinamica
int desempilhaPilhaDinamica(PilhaDinamica *p){
  int ret = -99;
  if(!vaziaPilhaDinamica(p)){
    ptrNoPilha aux;
    aux = p->topo;
    ret = aux->x;
    p->topo = p->topo->proximo;
    free(aux);
    p-> qtdeElementos--;
  }else{
    printf("Nao foi possivel Remover\n");
  }

  return(ret);
}
//imprimir pilha dinamica
void imprimirPilhaDinamica(PilhaDinamica *p){
  printf("Pilha = {");
  ptrNoPilha temp;
  for(temp = p-> topo; temp != NULL; temp = temp->proximo){
    printf("%d ", temp->x);
  }
  printf("}\n");
}

int main(){
  PilhaDinamica pilha;
  iniciaPilhaDinamica(&pilha);

  for(int i=0; i<5; i++){
    empilharPilhaDinamica(&pilha, i+1);
    imprimirPilhaDinamica(&pilha);
  }
  for(int i=0; i<5; i++){
    desempilhaPilhaDinamica(&pilha);
    imprimirPilhaDinamica(&pilha);
  }

  if(!vaziaPilhaDinamica(&pilha)){
    printf("Nao esta Vazia!\n");
  }

  printf("Tamanho = %d \n", tamanhoPilhaDinamica(&pilha));
  return 0;
}
