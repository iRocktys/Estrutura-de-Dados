#include <stdio.h>
#include <stdbool.h>
#define TAMANHO 5

typedef struct{
  //Array [ objeto / inteiro]
  int array[TAMANHO];
  int topo;
  //Não necessário para pulha estática
  int quantidadeElementos;
}PilhaEstatica;

//Inicialização pilha
void iniciaPilhaEstatica(PilhaEstatica *p){
  p-> topo = 0;
  p-> quantidadeElementos = 0;
}

//Estado da pilha (Vazia ou Cheia)
bool vaziaPilhaEstatica(PilhaEstatica *p){
  //Substitui o IF/ELSE, para retorno de verdadeiro ou falso
  return(p-> topo == 0);
}
bool cheiaPilhaEstatica(PilhaEstatica *p){
  return(p-> topo == TAMANHO);
}

//Tamanho da pilha (Quantidade de elementos)
int tamanhoPilhaEstatica(PilhaEstatica *p){
  return(p-> quantidadeElementos);
}

//Inserção (empilhar)
void empilharPilhaEstatica(PilhaEstatica *p, int x){
  if(cheiaPilhaEstatica(p) == false){
    //insere novo elemento na posição apontada pelo topo
    p-> array[p->topo] = x;
    //icrementa quantidade de elementos e topo(posição)
    p-> topo++;
    p-> quantidadeElementos++;
  }else{
    printf("Error 420: Pilha cheia\n");
  }
}

//Remover (desempilhar)
int desempilharPilhaEstatica(PilhaEstatica *p){
  //Valor de controle -99.
  int ret = -99;
  if(!vaziaPilhaEstatica(p)){
    //Retira o ultimo elemento que foi colocado
    ret = p->array[p-> topo - 1];
    //Decrementa topo e a quantidade de elementos
    p-> topo--;

    p-> quantidadeElementos--;
  }else{
    printf("Error 420: Pilha vazia\n");
  }
  return(ret);
}

//Vizualizar a pilha estática
void exibirPilhaEstatica(PilhaEstatica *p){
  int i;
  printf("{");
  for(i = 0; i < p->topo; i++){
    printf("%d ", p->array[i]);
  }
  printf("}\n");
}

int main(){
  PilhaEstatica pilha;
  //Sempre passar o endereço de memória da variável para a estrutura
  iniciaPilhaEstatica(&pilha);

  //inserindo elementos na pilha
  empilharPilhaEstatica(&pilha, 10);

  //Exibe quantidade de elementos da Pilha
  printf("Tamanho = %d\n", tamanhoPilhaEstatica(&pilha));

  //Exibe a pilha PilhaEstatica
  exibirPilhaEstatica(&pilha);

  //Remove elementos
  int aux;
  aux = desempilharPilhaEstatica(&pilha);

  exibirPilhaEstatica(&pilha);
  return 0;
}
