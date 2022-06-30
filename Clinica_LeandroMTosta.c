#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct cadastro{
  char informacao[50];
}cadastro;
//Criação da Lista Dinâmica duplamente encadeada
typedef struct NoLista* PtrNoLista;

typedef struct NoLista{
  int codigo;
  PtrNoLista proximo;
  PtrNoLista anterior;
} NoLista;

typedef struct {
  PtrNoLista inicio;
  int tamanho;
} ListaDinamica;

//Inicia lista Dinâminca
void iniciaListaDinamica(ListaDinamica *lista) {
  lista->inicio = NULL;
  lista->tamanho = 0;
}

//Verifica se a lista está vazia
bool estaVaziaListaDinamica(ListaDinamica *lista) {
  return(lista->inicio == NULL);
}

//Tamanho da lista
int tamanhoListaDinamica(ListaDinamica *lista) {
  return(lista->tamanho);
}

//imprimir elementos da lista
void imprimirListaDinamicaCrescente(ListaDinamica *lista) {
  printf("Lista Crescente = {");
  PtrNoLista percorre;
  for(percorre = lista->inicio; percorre != NULL; percorre = percorre->proximo) {
    printf("%d ", percorre->codigo);
  }
  printf("}\n");
}

//Imprime elementos em ordem decrescente
void imprimirListaDinamicaDecrescente(ListaDinamica *lista) {
  if(estaVaziaListaDinamica(lista)) {
    printf("Lista Decrescente = { }");
  } else {

    PtrNoLista percorre;
    for(percorre = lista->inicio; percorre->proximo != NULL; percorre = percorre->proximo);

    printf("Lista Decrescente = {");
    PtrNoLista aux;
    aux = percorre;

    while(aux != NULL){
      printf("%d ", aux->codigo);
      aux = aux->anterior;
    }
    printf("}\n");
  }
}

//Pesquisar lista Dinamica
bool pesquisaListaDinamica(ListaDinamica *lista, int consulta) {
  //Se a lista estiver vazia retorna falso
  if(estaVaziaListaDinamica(lista)){
    return false;
  }
  //Percorre toda lista para verificar a existencia do objeto
  PtrNoLista percorre = lista->inicio;
  while(percorre != NULL && consulta > percorre->codigo) {
    percorre = percorre->proximo;
  }
  if(percorre == NULL || percorre->codigo > consulta) {
    return false;
  }
  //Retorna verdadeiro se o objeto existir dentro da lista
  return true;
}

//Inserção de Elementos
void inserirListaDinamica(ListaDinamica *lista, int elemento) {
  //Criar o ponteiro
  PtrNoLista novo;
  //Aloca memoria para Novo
  novo = (PtrNoLista)malloc(sizeof(NoLista));
  //copia o valor do elemento para chave do Novo no
  novo->codigo = elemento;
  // Condição para 1 inserção: Lista esta Vazia , ou se o elemento que a gente quer inserir é menor do que o primeiro
  if(estaVaziaListaDinamica(lista) || elemento < lista->inicio->codigo) {
    //proximo do novo aponta para nulo (inicio)
    novo->proximo = lista->inicio;
    //Inicio aponta para o novo no
    lista->inicio = novo;
  }else{
    PtrNoLista aux;
    // Percorrer e encontrar o ponto de insercao
    aux = lista->inicio;
    while((aux->proximo!= NULL) && (elemento > aux->proximo->codigo)) {
      aux = aux->proximo;
    }
    //proximo Novo aponta proximo Aux
    novo->proximo = aux->proximo;
    //proximo do Aux aponta para Novo
    aux->proximo = novo;
  }
  //Incrementa o contador
  lista->tamanho = lista->tamanho++;
}


int main(int argc, const char *argv[]){
  //Abrindo arquivos
  FILE* Entrada;
  FILE* Saida;
  cadastro usuario;
  char aux;
  int codigo, i=1, opcao[3];

  //Nome dos arquivos abertos informados no CMD
  Entrada = fopen(argv[1], "r+");
  Saida = fopen(argv[2], "w+");

  //Verificar se os arquivos foram abertos corretamente
  if(Entrada == NULL || Saida == NULL){
    printf("Erro ao abrir arquivos!\n");
    system("pause");
  }

  //Criação da lista
  ListaDinamica Lista;
  //Inicia a lista duplamente encadeada

  iniciaListaDinamica(&Lista);
  //Metodo para pegar os codigos dos usuarios
  while(fscanf(Entrada, "%c", &aux) != EOF){
    if(aux == '{'){
      fscanf(Entrada,"%d ", &codigo);
      fflush(stdin);
      inserirListaDinamica(&Lista, codigo);
    }
  }

  Entrada = fopen(argv[1], "r+");

  while (!feof(Entrada)) {
      fgets(usuario.informacao, 100, Entrada);
      fprintf(Saida,"%s", usuario.informacao);
      if(strlen(usuario.informacao) < 5 ){
        //converte string em inteiro
        opcao[i] = atoi(usuario.informacao);
        i++;
      }
  }
  //Condicao de impressao
    //imprimir em orde crescente
    if(opcao[1] == 1){
      imprimirListaDinamicaCrescente(&Lista);
    }
    //imprimir em ordem decrescente
    else if(opcao[1] == 2){

      imprimirListaDinamicaDecrescente(&Lista);
    }
    //Consultar
    else if(opcao[1] == 3){
      if(pesquisaListaDinamica(&Lista, opcao[2])){
        fprintf(Saida, "Usuario cadastrado!!\n");
      }else{
        fprintf(Saida, "Usuario nao encontrado!!\n");

      }
    }
    //Se não houver nenhuma das opcoes exibe mensagem de erro
    else{
      fprintf(Saida, "Opcao invalida");
    }


  //Verifica se a lista está vazia
  if(estaVaziaListaDinamica(&Lista)){
    printf("Lista esta vazia\n");
  }
  return 0;
}
