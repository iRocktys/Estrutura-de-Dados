#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Criação da estrutura da AVL
typedef struct NoAVL *PtrNoAVL;

typedef struct NoAVL {
  int chave;
  PtrNoAVL direita;
  PtrNoAVL esquerda;
  //Fator de balanceamento
  int altura;
} NoAVL;


//Inicializção da arvore
void iniciaAVL(PtrNoAVL *node) {
 *node = NULL;
}

//Verifica condição da estrutura(Vazia/cheia)
bool estaVaziaAVL(PtrNoAVL *node) {
  return((*node) == NULL);
}

//Imprime em ordem
void emOrdem(PtrNoAVL *node) {
  if((*node) == NULL) return;
  emOrdem(&(*node)->esquerda);
  printf("%d ", (*node)->chave);
  emOrdem(&(*node)->direita);
}

//Imprime em pre-ordem
void preOrdem(PtrNoAVL *node) {
  if((*node) == NULL) return;
  printf("%d ", (*node)->chave);
  preOrdem(&(*node)->esquerda);
  preOrdem(&(*node)->direita);
}

// Altura da arvore AVL
int alturaArvoreAVL(PtrNoAVL node) {
  if(node == NULL) {
    return (0);
  } else {
    return ((node)->altura);
  }
}

//Atualiza a altura da arvore AVL
int atualizaAltura(PtrNoAVL esq, PtrNoAVL dir) {
  int ae = alturaArvoreAVL(esq);
  int ad = alturaArvoreAVL(dir);
  if(ae > ad) {
    return(ae + 1);
  } else {
    return(ad + 1);
  }
}


//Rotação simples da arvore AVL
void rotacaoSimplesDireita(PtrNoAVL *node) {
  printf("Rotação simples p direita, com node: %d\n", (*node)->chave);
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
  printf("Rotação simples p esquerda, com node: %d\n", (*node)->chave);
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
  printf("Rotação dupla p esquerda, com node: %d\n", (*node)->chave);

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

  int ad = alturaArvoreAVL((*node)->direita);
  int ae = alturaArvoreAVL((*node)->esquerda);

  // Verificar se é rotacao para direita
  if(ae > ad) {
    PtrNoAVL temp = (*node)->esquerda;
    int temp_ad = alturaArvoreAVL(temp->direita);
    int temp_ae = alturaArvoreAVL(temp->esquerda);
    if(temp_ae > temp_ad) {
      rotacaoSimplesDireita(&(*node));
    } else {
      rotacaoDuplaDireita(&(*node));
    }
  }
  // Senao é rotacao para esquerda
  else {
    PtrNoAVL tmp2 = (*node)->direita;
    int tmp2_ad = alturaArvoreAVL(tmp2->direita);
    int tmp2_ae = alturaArvoreAVL(tmp2->esquerda);

    if(tmp2_ad > tmp2_ae){
      rotacaoSimplesEsquerda(&(*node));
    } else {
      rotacaoDuplaEsquerda(&(*node));
    }
  }
}


//Inserir na arvore AVL
bool InserirAVL(PtrNoAVL *node, int x) {

  //1. condicao final da recusao (positiva)
  if((*node) == NULL) {
    (*node) = (PtrNoAVL)malloc(sizeof(NoAVL));
    (*node)->direita = (*node)->esquerda = NULL;
    (*node)->chave = x;
    (*node)->altura = 1;
    return true;
  }

  //2. elemento ja existe
  if((*node)->chave == x) return false;

  bool auxiliar;

  // 3. Laço de chamadas recusivas
  if(x < (*node)->chave) {
    auxiliar = InserirAVL(&(*node)->esquerda, x);
  } else {
    auxiliar = InserirAVL(&(*node)->direita, x);
  }
  // 4. Se o auxiliar for falso, nao houve mudança na arvore
  if(!auxiliar) return (false);

  // Se houve modificacao na arvore
  // Precisamos checar o desbalanceamento
  int ae; // altura da sub-arvore da esquerda
  int ad; // altura da sub-arvore da direita

  // 5. Calculando as alturas das sub-arvores
  ae = alturaArvoreAVL((*node)->esquerda);
  ad = alturaArvoreAVL((*node)->direita);

  // 6. Verificando desbalanceamento
  if((ad - ae) == +2 || (ad - ae) == -2) {
    // desbalancemaneto
    AplicarRotacoes(&(*node));
  }

  //7. ajuste da altura do no corrente
  (*node)->altura = atualizaAltura((*node)->esquerda, (*node)->direita);
  return(true);
}


int main(int argc, const char * argv[]) {
  //Criação do acesso a estrutura de dados
  PtrNoAVL raiz;
  iniciaAVL(&raiz);
  InserirAVL(&raiz, 90);
  InserirAVL(&raiz, 15);
  InserirAVL(&raiz, 21);
  InserirAVL(&raiz, 100);
  //InserirAVL(&raiz, 41);
  InserirAVL(&raiz, 52);
  //InserirAVL(&raiz, 40);
  InserirAVL(&raiz, 89);
  InserirAVL(&raiz, 93);
  InserirAVL(&raiz, 64);

  printf("Pré Ordem:\n");
  preOrdem(&raiz);

  //RemoveAVL(&raiz, 41);
  //RemoveAVL(&raiz, 40);




  return 0;
}
