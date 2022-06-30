#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//------------------------------------------------------
//                   Estrutura Arvore AVL
//------------------------------------------------------
typedef struct NoAVL *PtrNoAVL;

typedef struct NoAVL {
  int chave;
  PtrNoAVL direita;
  PtrNoAVL esquerda;
  //Fator de balanceamento
  int altura;
} NoAVL;

//------------------------------------------------------
//                   Estrutura fila
//------------------------------------------------------
typedef struct Nofila *PtrNofila;

typedef struct Nofila{
  int chave;
  PtrNofila proximo;
} Nofila;

typedef struct {
  PtrNofila inicio;
  PtrNofila fim;
  int tamanho;
} filaDinamica;
//------------------------------------------------------
//                   Funções fila
//------------------------------------------------------
//Função inicio da fila
void iniciaFila(filaDinamica *fila){
  fila->inicio = NULL;
  fila->fim = NULL;
  fila->tamanho = 0;
}

//Função de verificar o estado da fila
bool estaVazia(filaDinamica *fila){
  return(fila->tamanho == 0);
}

//Inserir elementos na fila
void Inserefila(filaDinamica *fila, int elemento){
  PtrNofila aux;
  aux = (PtrNofila)malloc(sizeof(Nofila));
  aux->chave = elemento;

  if (estaVazia(fila)){
    fila->inicio = aux;
    fila->fim = aux;
    aux->proximo = NULL;

  }else{
    aux->proximo = NULL;
    fila->fim->proximo = aux;
    fila->fim = aux;
  }
  fila->tamanho++;
}

// Remove elementos da fila
int Removefila(filaDinamica *fila){
  int aux = -999;
  PtrNofila temporario;

  if (!estaVazia(fila)){
    temporario = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    aux = temporario->chave;
    free(temporario);
    fila->tamanho--;
  }else{
    printf("A fila esta vazia\n");
  }
  return(aux);
}

//------------------------------------------------------
//                   Funções Arvore AVL
//------------------------------------------------------
//Inicializção da arvore
void iniciaAVL(PtrNoAVL *node) {
 *node = NULL;
}

//Verifica condição da estrutura(Vazia/cheia)
bool estaVaziaAVL(PtrNoAVL *node) {
  return((*node) == NULL);
}

//Profundidade arvore AVL
int ProfundidadeAVL(PtrNoAVL *node) {
  if ((*node) == NULL) return 0;
  else {
    int PEsquerda = ProfundidadeAVL(&(*node)->esquerda);
    int PDireita = ProfundidadeAVL(&(*node)->direita);
    if (PEsquerda > PDireita)
      return(PEsquerda+1);
    else return(PDireita+1);
  }
}

//Função para destruir AVL
void DestroiAVL(PtrNoAVL *node){
  if((*node) != NULL ) {
    DestroiAVL( &(*node)->esquerda);
    DestroiAVL( &(*node)->direita);
    free(*node);
    *node = NULL;
  }
}

// Altura da arvore AVL
int alturaAVL(PtrNoAVL node) {
  if(node == NULL) {
    return (0);
  } else {
    return ((node)->altura);
  }
}

//Atualiza a altura da arvore AVL
int atualizaAltura(PtrNoAVL esq, PtrNoAVL dir) {
  int ae = alturaAVL(esq);
  int ad = alturaAVL(dir);
  if(ae > ad) {
    return(ae + 1);
  } else {
    return(ad + 1);
  }
}

//Rotação simples da arvore AVL
void rotacaoSimplesDireita(PtrNoAVL *node) {
  PtrNoAVL u = (*node)->esquerda;
  (*node)->esquerda = u->direita;
  u->direita = (*node);

  //atualizar a altura dos nós modificados
  (*node)->altura = atualizaAltura((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAltura(u->esquerda, u->direita);

  //autualizacao da referencia
  (*node) = u;
}

//Rotação simples esquerda
void rotacaoSimplesEsquerda (PtrNoAVL *node) {
  PtrNoAVL u = (*node)->direita;
  (*node)->direita = u->esquerda;
  u->esquerda = (*node);

  //atualizar a altura dos nós modificados (node, u)
  (*node)->altura = atualizaAltura((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAltura(u->esquerda, u->direita);

  //autualizacao da referencia do node
  (*node) = u;
}

void rotacaoDuplaEsquerda (PtrNoAVL *node) {

  PtrNoAVL u, v;
  u = (*node)->direita;
  v = u->esquerda;

  (*node)->direita = v->esquerda;
  u->esquerda = v->direita;
  v->esquerda = (*node);
  v->direita = u;

  //atualizar a altura dos nós modificados (node, u, v)
  (*node)->altura = atualizaAltura((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAltura(u->esquerda, u->direita);
  v->altura = atualizaAltura(v->esquerda, v->direita);

  //autualizacao da referencia do node
  (*node) = v;
}

void rotacaoDuplaDireita (PtrNoAVL *node) {
  printf("Rotação dupla p direita, com node: %d\n", (*node)->chave);

  PtrNoAVL u, v;
  u = (*node)->esquerda;
  v = u->direita;

  (*node)->esquerda = v->direita;
  u->direita = v->esquerda;

  v->direita = (*node);
  v->esquerda = u;

  //atualizar a altura dos nós modificados
  (*node)->altura = atualizaAltura((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAltura(u->esquerda, u->direita);
  v->altura = atualizaAltura(v->esquerda, v->direita);

  //autualizacao da referencia do node
  (*node) = v;
}


// Função que aplica a rotação
void AplicarRotacoes(PtrNoAVL *node) {
  int ad = alturaAVL((*node)->direita);
  int ae = alturaAVL((*node)->esquerda);

  // Verificar se é rotacao para direita
  if(ae > ad) {
    PtrNoAVL temp = (*node)->esquerda;
    int temp_ad = alturaAVL(temp->direita);
    int temp_ae = alturaAVL(temp->esquerda);
    if(temp_ae > temp_ad) {
      rotacaoSimplesDireita(&(*node));
    } else {
      rotacaoDuplaDireita(&(*node));
    }
  }
  // Senao é rotacao para esquerda
  else {
    PtrNoAVL tmp2 = (*node)->direita;
    int tmp2_ad = alturaAVL(tmp2->direita);
    int tmp2_ae = alturaAVL(tmp2->esquerda);

    if(tmp2_ad > tmp2_ae){
      rotacaoSimplesEsquerda(&(*node));
    } else {
      rotacaoDuplaEsquerda(&(*node));
    }
  }
}

//Inserir na arvore AVL
bool inserirAVL(PtrNoAVL *node, int elemento) {

  //1. condicao final da recusao (positiva)
  if((*node) == NULL) {
    (*node) = (PtrNoAVL)malloc(sizeof(NoAVL));
    (*node)->direita = (*node)->esquerda = NULL;
    (*node)->chave = elemento;
    (*node)->altura = 1;
    return true;
  }

  //2. elemento ja existe
  if((*node)->chave == elemento) return false;

  bool auxiliar;

  // 3. Laço de chamadas recusivas
  if(elemento < (*node)->chave) {
    auxiliar = inserirAVL(&(*node)->esquerda, elemento);
  } else {
    auxiliar = inserirAVL(&(*node)->direita, elemento);
  }
  // 4. Se o auxiliar for falso, nao houve mudança na arvore
  if(!auxiliar) return (false);

  // Se houve modificacao na arvore
  // Precisamos checar o desbalanceamento
  int ae; // altura da sub-arvore da esquerda
  int ad; // altura da sub-arvore da direita

  // 5. Calculando as alturas das sub-arvores
  ae = alturaAVL((*node)->esquerda);
  ad = alturaAVL((*node)->direita);

  // 6. Verificando desbalanceamento
  if((ad - ae) == +2 || (ad - ae) == -2) {
    // desbalancemaneto
    AplicarRotacoes(&(*node));
  }

  //7. ajuste da altura do no corrente
  (*node)->altura = atualizaAltura((*node)->esquerda, (*node)->direita);
  return(true);
}

//Ponteiro que aponta para o maximo da arvore AVL
PtrNoAVL maximoAVL (PtrNoAVL *node) {
  PtrNoAVL aux;
  if((*node)->direita == NULL) {
    aux = (*node);
    (*node) = (*node)->esquerda;
    return(aux);
  }
  return(maximoAVL(&(*node)->direita));
}

//Ponteiro que aponta para o minimo da arvore AVL
PtrNoAVL minimoAVL (PtrNoAVL *node) {
  PtrNoAVL aux;
  if((*node)->esquerda == NULL) {
    aux = (*node);
    (*node) = (*node)->direita;
    return(aux);
  }
  return(minimoAVL(&(*node)->esquerda));
}

bool RemoveAVL(PtrNoAVL *node, int elemento, char op) {

  bool remv;
  int esquerda, direita;

  if((*node) == NULL) {
    printf("ERROR 420: Nao e possivel remover, elemento inexistente!!\n", elemento);
    return (false);
  }

  // Se encontrar o elemeno a ser removido, entrar no if
  if((*node)->chave == elemento) {

    PtrNoAVL temporario = (*node);

    //Se sub-arvore esquerda nula
    if((*node)->esquerda == NULL) {
      (*node) = (*node)->direita;
    }
    //Se sub-arvore direita é nula
    if((*node)->direita == NULL) {
      (*node) = (*node)->esquerda;
    }

    if (op == 'e') {
      temporario = maximoAVL(&(*node)->esquerda);
    }else{
      temporario = minimoAVL(&(*node)->direita);
    }
    (*node)->chave = temporario->chave;
    free(temporario);
    return true;
  }

  if((*node)->chave > elemento){
    remv = RemoveAVL(&(*node)->esquerda, elemento, op);
  } else {
    remv = RemoveAVL(&(*node)->direita, elemento, op);
  }

  if(remv == false) return (false);
  else {
    esquerda  = ProfundidadeAVL(&(*node)->esquerda);
    direita = ProfundidadeAVL(&(*node)->direita);

    if( abs(esquerda - direita) == 2 )
      AplicarRotacoes(&(*node));

    (*node)->altura = atualizaAltura((*node)->esquerda, (*node)->direita);
    return(true);
  }
}

//Escreve no arquivo
void Escrita(PtrNoAVL *node, int level, FILE* Saida){
  if ((*node)!=NULL && level == 0) {
    int ae = alturaAVL((*node)->esquerda);
    int ad = alturaAVL((*node)->direita);

    fprintf(Saida, " %d (%d),", (*node)->chave, ad-ae);
  }else if((*node)!=NULL){
    Escrita(&(*node)->esquerda,level-1, Saida);
    Escrita(&(*node)->direita,level-1, Saida);
  }
}

//Função para criar a saida no arquivo
void criacaoSaida(PtrNoAVL *node, FILE* Saida){
  int altura = ProfundidadeAVL(&(*node));

  for (int i = 0; i < altura; i++) {
    Escrita(&(*node), i, Saida);
    fprintf(Saida, "\n" );
  }
}

int main(int argc, const char * argv[]) {
  //D:\Faculdade\Estrutura de Dados\Pratica_4

  //Abrindo arquivos
  FILE* Entrada;
  FILE* Saida;

  //Criação de variavel da estrutura
  PtrNoAVL raiz;
  PtrNofila fila;
  char* numero;
  int n;
  char linha[100], op;

  //Nome dos arquivos abertos informados no CMD
  Entrada = fopen(argv[1], "r+");
  Saida = fopen(argv[2], "w+");

  //Verificar se os arquivos foram abertos corretamente
  if(Entrada == NULL || Saida == NULL){
    printf("Erro ao abrir arquivos!\n");
    system("pause");
  }

  //Criação do acesso a estrutura de dados
  iniciaAVL(&raiz);
  iniciaFila(&fila);


  //Função para inserir na arvore
  fgets(linha, 99, Entrada);
  numero = strtok(NULL, ",");
  while (numero != NULL){
    n = strtol(numero, NULL, 10);
    inserirAVL(&raiz, n);
    numero = strtok(NULL, ",");
  }

  //função para inserir na fila
  fgets(linha, 99, Entrada);
  numero = strtok(NULL, ",");
  while (numero != NULL){
    n = strtol(numero, NULL, 10);
    Inserefila(&fila,n);
    numero = strtok(NULL, ",");
  }

  op = fgetc(Entrada);
  op = tolower(op);

  if (op != 'e' && op != 'd') {
    fprintf(Saida, "Arquivo inválido!\n" );
  }

  fprintf(Saida, "Inicialmente: \n");

  criacaoSaida(&raiz, Saida);

  while (!estaVazia(&fila)) {
    n = Removefila(&fila);
    RemoveAVL(&raiz, n, op);
  }

  fprintf(Saida, "\nPos Operacao\n");
  criacaoSaida(&raiz, Saida);

  return 0;
}
